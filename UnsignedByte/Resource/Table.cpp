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

#include <stdexcept>

#include "Global.h"
#include "Table.h"
#include "Tables.h"
#include "Field.h"

Table::Table(std::string name, std::string id) :
m_name(name),
m_id(id),
m_lookuptable(false)
{
	
}

Table::Table(std::string name) :
m_name(name),
m_lookuptable(true)
{
	
}

Table::~Table()
{
	for(Fields::iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		delete (*it);
	}
}

void Table::addField(const std::string& name, bool text)
{
	addField(name, text, Global::Get()->EmptyString);
}

void Table::addField(const std::string& name, bool text, const std::string& defaulttext)
{
	if(m_lookuptable)
	{
		std::string errormsg;
		errormsg.append("Table::tableID() in a lookup table: '");
		errormsg.append(m_name);
		errormsg.append("'.");
		throw std::logic_error(errormsg);
	}
		
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
	
	m_fields.push_back(new Field(name, false, Global::Get()->EmptyString));
	// TODO, add SQLite triggers
}

const std::string& Table::tableName() const
{
	return m_name;
}

std::string Table::tableID() const
{
	if(m_lookuptable)
	{
		std::string errormsg;
		errormsg.append("Table::tableID() in a lookup table: '");
		errormsg.append(m_name);
		errormsg.append("'.");
		throw std::logic_error(errormsg);
	}
		
	std::string name;
	name.append(m_id);
	name.append("id");
	
	return name;
}

std::string Table::tableQuery() const
{
	std::string result;
	result.append("SELECT type FROM sqlite_master WHERE tbl_name='");
	result.append(m_name);
	result.append("' and sql='");
	
	result.append("CREATE TABLE ");
	result.append(m_name);
	result.append("(");
	
	if(!m_lookuptable)
	{
		result.append(tableID());
		result.append(" INTEGER PRIMARY KEY AUTOINCREMENT");
	}
	
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
		result.append((*it)->creationString());

	result.append(")';");
	
	return result;
}

/*
	"CREATE TABLE IF NOT EXISTS %s("
	"%s INTEGER PRIMARY KEY AUTOINCREMENT"
	",versiontext TEXT"
	",grantgroup INTEGER RESTRAINT grantgroup DEFAULT 1"
	");",
*/
std::string Table::creationQuery() const
{
	std::string result;
	
	result.append("CREATE TABLE IF NOT EXISTS ");
	result.append(m_name);
	result.append("(");
	
	if(!m_lookuptable)
	{
		result.append(tableID());
		result.append(" INTEGER PRIMARY KEY AUTOINCREMENT");
	}
	
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
		result.append((*it)->creationString());
	
	result.append(");");
	
	return result;
}

bool Table::isLookupTable() const
{
	return m_lookuptable;
}
