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

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <time.h>

#include "Global.h"
#include "Table.h"
#include "Tables.h"
#include "Field.h"
#include "SqliteMgr.h"

Table::Table(std::string name) :
m_name(name),
m_spkey(false)
{
	std::string foreignname;
	foreignname.append("fk");
	
	std::string tablename = name;
	char first = tablename[0];
	first = toupper(first);
	
	tablename[0] = first;
	foreignname.append(tablename);
	
	m_foreignname = foreignname;
}

Table::~Table()
{
	for(Fields::iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		delete (*it);
	}
}

void Table::addPK(const std::string& name)
{
	m_primarykeys[name] = this;
	
	if(m_primarykeys.size() == 1)
		m_spkey = true;
	else
		m_spkey = false;
}

void Table::addFPK(Table* table)
{
	std::string name;
	name.append(table->tableForeignName());
	
	m_primarykeys[name] = table;
	
	if(m_primarykeys.size() == 1)
		m_spkey = true;
	else
		m_spkey = false;
}

void Table::addValue(const std::string& name)
{
	addField(name, false, Global::Get()->EmptyString, false);
}

void Table::addValue(const std::string& name, value_type defaultvalue)
{
	std::ostringstream str;
	str << defaultvalue;
	addField(name, false, str.str(), false);
}

void Table::addTextField(const std::string& name)
{
	addField(name, true, Global::Get()->EmptyString, false);
}

void Table::addLookupTextField(const std::string& name)
{
	addField(name, true, Global::Get()->EmptyString, true);
}

void Table::addTextField(const std::string& name, const std::string& defaulttext)
{
	addField(name, true, defaulttext, false);
}

void Table::addField(const std::string& name, bool text, const std::string& defaulttext, bool providelookup)
{
	Field* field = new Field(name, text, defaulttext);
	m_fields.push_back(field);
	
	if(providelookup)
		m_lookupfields.push_back(field);
}

void Table::addFK(Table* table)
{
	addFK(table, Global::Get()->EmptyString);
}

void Table::addFK(Table* table, const std::string& suffix)
{	
	std::string name;
	name.append(table->tableForeignName());
	name.append(suffix);

	addValue(name);
	// TODO, add SQLite triggers
}

const std::string& Table::tableName() const
{
	return m_name;
}

const std::string& Table::tableForeignName() const
{	
	return m_foreignname;
}

const std::vector<std::string>& Table::tableList()
{
	if(m_listcache > m_lastchange)
		SqliteMgr::Get()->doList(this);

	return m_list;
}

std::string Table::tableQuery() const
{
	std::string result;
	result.append("SELECT type FROM sqlite_master WHERE tbl_name='");
	result.append(m_name);
	result.append("' and sql='");
	
	result.append(creationQuery(true));
	
	result.append("';");
	
	return result;
}

/*
	"CREATE TABLE IF NOT EXISTS %s("
	"%s INTEGER PRIMARY KEY AUTOINCREMENT"
	",versiontext TEXT"
	",grantgroup INTEGER RESTRAINT grantgroup DEFAULT 1"
	");",
*/
std::string Table::creationQuery(bool verify) const
{
	std::string result;
	
	if(verify)
		result.append("CREATE TABLE ");
	else
		result.append("CREATE TABLE IF NOT EXISTS ");
		
	result.append(m_name);
	result.append("(");
	
	bool comma = false;
	
	for(TableMap::const_iterator it = keybegin(); it != keyend(); it++)
	{
		if(m_spkey && it == keybegin())
		{
			result.append(it->first);
			result.append(" INTEGER PRIMARY KEY AUTOINCREMENT, ");
			continue;
		}
		
		if(comma)
			result.append(", ");
			
		result.append(it->first);
		result.append(" INTEGER");
		comma = true;
	}
	
	for(Fields::const_iterator it = begin(); it != end(); it++)
	{
		if(comma)
			result.append(", ");
			
		result.append((*it)->creationString());
		comma = true;
	}
	
	if(!m_spkey)
	{
		result.append(", PRIMARY KEY(");
		for(TableMap::const_iterator it = keybegin(); it != keyend(); it++)
		{
			if(it != keybegin())
				result.append(", ");
				
			result.append(it->first);
		}
		result.append(")");
	}
	
	if(verify)
		result.append(")");
	else
		result.append(");");
	
	return result;
}

void Table::parseList(sqlite3_stmt* statement)
{
	std::string result;

	int columns = sqlite3_column_count(statement);
	for(int i = 0; i < columns; i++)
	{
		int type = sqlite3_column_type(statement, i);
		std::ostringstream str;
		switch(type)
		{
		case SQLITE_TEXT:			
			str << ", " << sqlite3_column_text(statement, i);
			break;

		case SQLITE_INTEGER:
			str << ", " << sqlite3_column_int64(statement, i);
			break;

		default:
			std::ostringstream err;
			err << "Unknown data type '" << type << "'.";
			throw new std::runtime_error(err.str());
		}

		result.append(str.str());
	}

	m_list.push_back(result);
	m_listcache = time(NULL);
}


void Table::modify()
{
	m_lastchange = time(NULL);
}