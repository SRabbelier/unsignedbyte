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

#include "Global.h"
#include "Table.h"
#include "Tables.h"
#include "Field.h"

Table::Table(std::string name) :
m_name(name),
m_spkey(true)
{
	
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
	if(m_spkey && m_keys.size() > 1)
		m_spkey = false;
		
	m_keys[name] = this;
}

void Table::addValue(const std::string& name)
{
	addField(name, false, Global::Get()->EmptyString);
}

void Table::addValue(const std::string& name, value_type defaultvalue)
{
	std::ostringstream str;
	str << defaultvalue;
	addField(name, false, str.str());
}

void Table::addTextField(const std::string& name)
{
	addField(name, true, Global::Get()->EmptyString);
}

void Table::addTextField(const std::string& name, const std::string& defaulttext)
{
	addField(name, true, defaulttext);
}

void Table::addField(const std::string& name, bool text, const std::string& defaulttext)
{
	m_fields.push_back(new Field(name, text, defaulttext));
}

void Table::addFK(Table* table)
{
	addFK(table, Global::Get()->EmptyString);
}

void Table::addFK(Table* table, const std::string& suffix)
{
	std::string name;
	name.append("fk");
	
	std::string tablename = table->tableName();
	char first = tablename[0];
	first = toupper(first);
	
	tablename[0] = first;
	name.append(tablename);
	
	name.append(suffix);
	
	m_keys[name] = table;
	// TODO, add SQLite triggers
}

const std::string& Table::tableName() const
{
	return m_name;
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
	
	if(m_spkey)
	{
		result.append(firstKey());
		result.append(" INTEGER PRIMARY KEY AUTOINCREMENT, ");
	}
	
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		if(it != m_fields.begin())
			result.append(", ");
			
		result.append((*it)->creationString());
	}
	
	if(verify)
		result.append(")");
	else
		result.append(");");
	
	return result;
}

