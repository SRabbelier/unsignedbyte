/***************************************************************************
 *   Copyright (C) 2008 by Sverre Rabbelier                                *
 *   sverre@rabbelier.nl                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "SavableManager.h"
#include "Key.h"
#include "KeyDef.h"
#include "Keys.h"
#include "Value.h"
#include "FieldImpl.h"
#include "TableImpl.h"
#include "SqliteMgr.h"
#include "Exceptions.h"
#include "StringUtilities.h"

ByKeyCache SavableManager::ms_byKeyCache;
ByValueCache SavableManager::ms_byValueCache;

SavableManager::SavableManager(TableImplPtr table) :
m_table(table),
m_keys(new Keys(table)),
m_newentry(true),
m_dirty(false)
{
	Assert(table);
	
	for(FieldImplVector::const_iterator it = table->implbegin(); it != table->implend(); it++)
	{
		ValuePtr value(new Value(*it));
		m_fields[it->get()] = value;
	}
	
	for(KeyDefs::const_iterator it = table->keyimplbegin(); it != table->keyimplend(); it++)
	{
		KeyPtr key(new Key(*it, 0));
		m_keys->addKey(key);
	}
}

SavableManager::~SavableManager()
{

}

SavableManagerPtr SavableManager::getnew(TableImplPtr table)
{
	Assert(table);
	
	SavableManagerPtr result(new SavableManager(table));
	return result;
}

SavableManagerPtr SavableManager::bykeys(KeyPtr key)
{
	Assert(key);
	
	TableImplPtr table = key->getTable();
	KeysPtr keys(new Keys(table));
	keys->addKey(key);
	return bykeys(keys);
}

SavableManagerPtr SavableManager::bykeys(KeysPtr keys)
{
	Assert(keys);
	
	if(ms_byKeyCache.find(keys.get()) == ms_byKeyCache.end())
	{		
		SavableManagerPtr result = getnew(keys->getTable());
		result->setkeys(keys);
		SqliteMgr::Get()->doSelect(result);
		ms_byKeyCache[keys.get()] = result;
		result->cleanup();
	}
	
	return ms_byKeyCache[keys.get()];
}

SavableManagerPtr SavableManager::byvalue(ValuePtr value)
{	
	Assert(value);
	
	if(ms_byValueCache.find(value.get()) == ms_byValueCache.end())
	{
		SavableManagerPtr result = getnew(value->getTable());
		result->m_lookupvalue = value;
		SqliteMgr::Get()->doLookup(result, value->getField());
		ms_byValueCache[value.get()] = result;
		result->cleanup();
	}
	
	return ms_byValueCache[value.get()];
}

KeysPtr SavableManager::lookupvalue(ValuePtr value)
{
	Assert(value);
	
	SavableManagerPtr result = byvalue(value);
	KeysPtr keys = result->getkeys();
	return keys;
}

void SavableManager::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void SavableManager::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		if(m_fields.size())
			SqliteMgr::Get()->doUpdate(this);
		
		cleanup();
	}
}

bool SavableManager::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void SavableManager::bindKeys(sqlite3* db, sqlite3_stmt* stmt, int startpos) const
{
	Assert(db);
	Assert(stmt);
	
	int pos = startpos;
	int rc = 0;
	for(KeyMap::const_iterator it = m_keys->begin(); it != m_keys->end(); it++)
	{
		rc = sqlite3_bind_int64(stmt, pos, it->second->getValue());
		
		if(rc != SQLITE_OK)
			throw SqliteError(db);
		pos++;
	}
}

void SavableManager::bindFields(sqlite3* db, sqlite3_stmt* stmt, int startpos) const
{
	Assert(db);
	Assert(stmt);
	
	int pos = startpos;
	int rc = 0;
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		if(!it->second)
		{
			printf("Empty field '%s'\n", it->first->getName().c_str());
			continue;
		}
		
		if(it->first->isText())
			rc = sqlite3_bind_text(stmt, pos, it->second->getStringValue().c_str(), it->second->getStringValue().size(), SQLITE_TRANSIENT);
		else
			rc = sqlite3_bind_int64(stmt, pos, it->second->getIntegerValue());
			
		if(rc != SQLITE_OK)
			throw SqliteError(db);
		pos++;
	}
}

void SavableManager::bindUpdate(sqlite3* db, sqlite3_stmt* stmt) const
{
	Assert(db);
	Assert(stmt);
	
	bindFields(db, stmt);
	bindKeys(db, stmt, m_fields.size() + 1);
}

void SavableManager::bindLookup(sqlite3* db, sqlite3_stmt* stmt) const
{
	Assert(db);
	Assert(stmt);
	
	int rc = 0;
	if(m_lookupvalue->getField()->isText())
		rc = sqlite3_bind_text(stmt, 1, m_lookupvalue->getStringValue().c_str(), m_lookupvalue->getStringValue().size(), SQLITE_TRANSIENT);
	else
		rc = sqlite3_bind_int64(stmt, 1, m_lookupvalue->getIntegerValue());
		
	if(rc != SQLITE_OK)
		throw SqliteError(db);
}

void SavableManager::parseInsert(sqlite3* db)
{	
	Assert(db);
	
	value_type value = sqlite3_last_insert_rowid(db);
	KeyPtr key(new Key(m_table->firstImplKey(), value));
	m_keys->addKey(key);
}

void SavableManager::parseSelect(sqlite3_stmt* stmt)
{
	Assert(stmt);
	
	int pos = 0;
	const unsigned char * text;
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		if(it->first->isText())
		{
			text = sqlite3_column_text(stmt, pos);
			if(text != 0)
			{
				std::string value = std::string((const char *)text);
				it->second->setTextValue(value);
			}
		}
		else
		{
			value_type value =  sqlite3_column_int64(stmt, pos);
			it->second->setIntegerValue(value);
		}
		
		pos++;
	}
	
	m_newentry = false;
}

void SavableManager::parseLookup(sqlite3_stmt* stmt)
{
	Assert(stmt);
	
	KeyPtr key(new Key(m_table->firstImplKey(), sqlite3_column_int64(stmt, 0)));
	m_keys->addKey(key);
}

TableImplPtr SavableManager::getTable() const
{
	return m_table;
}

KeysPtr SavableManager::getkeys() const
{
	return m_keys;
}

KeyPtr SavableManager::getkey(KeyDefPtr keydef) const
{
	Assert(keydef);
	
	KeyMap::const_iterator it = m_keys->find(keydef);
	Assert(it != m_keys->end());
	
	return it->second;
}

ValuePtr SavableManager::getfield(FieldImplPtr field) const
{
	Assert(field);
	
	Fields::const_iterator it = m_fields.find(field.get());
	Assert(it != m_fields.end());
	
	return it->second;
}

std::string SavableManager::getDiff() const
{
	std::vector<std::string> result;
	
	for(KeyMap::const_iterator it = m_keys->begin(); it != m_keys->end(); it++)
	{
		KeyPtr key = it->second;
		if(!key->isDirty())
			continue;
			
		std::string line = "Changed key '";
		line.append(key->getKeyDef()->getName());
		line.append("' to '");
		line.append(String::Get()->fromInt(key->getValue()));
		line.append("'.");
			
		result.push_back(line);
	}
	
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		ValuePtr value = it->second;
		if(!value->isDirty())
			continue;
			
		std::string line = "Changed field '";
		line.append(value->getField()->getName());
		line.append("' to '");
		if(value->getField()->isText())
			line.append(value->getStringValue());
		else
			line.append(String::Get()->fromInt(value->getIntegerValue()));
		line.append("'.");
			
		result.push_back(line);
	}
	
	return String::Get()->unlines(result, "\n", 0);
}

bool SavableManager::isDirty() const
{
	return m_dirty;
}

void SavableManager::setkeys(KeysPtr keys)
{
	Assert(keys);
	Assert(keys->size() == m_table->keysize());
		
	for(KeyMap::const_iterator it = keys->begin(); it != keys->end(); it++) {
		Assert(it->first->getTable() == m_table);
	}
		
	keys->setDirty(m_keys);
	m_keys = keys;
	m_dirty = true;
}

void SavableManager::setvalue(ValuePtr value)
{
	Assert(value);
	Assert(m_table->hasfield(value->getField()));	
	Assert(m_fields.find(value->getField().get()) != m_fields.end());
	value->setDirty(true);
	
	m_fields[value->getField().get()] = value;
	m_dirty = true;
}

void SavableManager::cleanup()
{
	for(KeyMap::const_iterator it = m_keys->begin(); it != m_keys->end(); it++)
	{
		KeyPtr key = it->second;
		key->setDirty(false);
	}
	
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		ValuePtr value = it->second;
		value->setDirty(false);
	}
	
	m_dirty = false;
}
