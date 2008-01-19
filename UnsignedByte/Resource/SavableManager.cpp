/***************************************************************************
 *   Copyright (C) 2007 by Sverre Rabbelier                                *
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
#include "SqliteError.h"

ByKeyCache SavableManager::ms_byKeyCache;
ByValueCache SavableManager::ms_byValueCache;

SavableManager::SavableManager(TableImplPtr table) :
m_table(table),
m_keys(new Keys(table)),
m_newentry(true),
m_dirty(false)
{
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
	SavableManagerPtr result(new SavableManager(table));
	return result;
}

SavableManagerPtr SavableManager::bykeys(KeyPtr key)
{
	KeysPtr keys(new Keys(keys->getTable()));
	keys->addKey(key);
	return bykeys(keys);
}

SavableManagerPtr SavableManager::bykeys(KeysPtr keys)
{
	if(ms_byKeyCache.find(keys.get()) == ms_byKeyCache.end())
	{		
		SavableManagerPtr result = getnew(keys->first()->getKeyDef()->getTable());
		result->setkeys(keys);
		SqliteMgr::Get()->doSelect(result);
		ms_byKeyCache[keys.get()] = result;
	}
	
	return ms_byKeyCache[keys.get()];
}

SavableManagerPtr SavableManager::byvalue(ValuePtr value)
{	
	if(ms_byValueCache.find(value.get()) == ms_byValueCache.end())
	{
		SavableManagerPtr result = getnew(value->getField()->getTable());
		result->m_lookupvalue = value;
		SqliteMgr::Get()->doLookup(result, value->getField());
		ms_byValueCache[value.get()] = result;
	}
	
	return ms_byValueCache[value.get()];
}

KeysPtr SavableManager::lookupvalue(ValuePtr value)
{
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
		m_dirty = false;
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
	bindFields(db, stmt);
	bindKeys(db, stmt, m_fields.size() + 1);
}

void SavableManager::bindLookup(sqlite3* db, sqlite3_stmt* stmt) const
{
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
	// assert(m_keys.size() == 0);
	value_type value = sqlite3_last_insert_rowid(db);
	KeyPtr key(new Key(m_table->firstImplKey(), value));
	m_keys->addKey(key);
}

void SavableManager::parseSelect(sqlite3_stmt* stmt)
{
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
	// assert(m_keys.size() == 0);
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
	KeyMap::const_iterator it = m_keys->find(keydef.get());
	if(it != m_keys->end())
		return it->second;
	else
		throw std::invalid_argument("SavableManager::getkey(), key not in m_keys.");
}

ValuePtr SavableManager::getfield(FieldImplPtr field) const
{
	Fields::const_iterator it = m_fields.find(field.get());
	if(it != m_fields.end())
		return it->second;
	else
		throw std::invalid_argument("SavableManager::getfield(), field not in m_fields.");
}

void SavableManager::setkeys(KeysPtr keys)
{
	if(keys->size() != m_table->keysize())
		throw std::invalid_argument("SavableManager::setkeys(), key sizes don't match.");
		
	for(KeyMap::const_iterator it = keys->begin(); it != keys->end(); it++)
	{
		if(it->first->getTable() != m_table)
			throw std::invalid_argument("SavableManager::setkeys(), key type is not m_table.");
	}
		
	m_keys = keys;
	m_dirty = true;
}

void SavableManager::setvalue(ValuePtr value)
{
	if(!m_table->hasfield(value->getField()))
		throw std::invalid_argument("SavableManager::setfield(), field not in m_table.");
	
	if(m_fields.find(value->getField().get()) == m_fields.end())
		throw std::invalid_argument("SavableManager::setfield(), field not in m_fields.");
	
	m_fields[value->getField().get()] = value;
	m_dirty = true;
}
