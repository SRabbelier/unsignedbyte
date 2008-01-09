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

#include "TableDef.h"
#include "FieldDef.h"
#include "Global.h"

TableDef::TableDef(std::string name) :
Table(name)
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

TableDef::~TableDef()
{
	
}

void TableDef::addPK(const std::string& name)
{
	m_primarykeys[name].reset(); // TODO - maybe this needs fixing?
	
	if(m_primarykeys.size() == 1)
		m_spkey = true;
	else
		m_spkey = false;
}

void TableDef::addFPK(TableDefPtr table)
{
	std::string name;
	name.append(table->tableForeignName());
	
	m_primarykeys[name] = table;
	
	if(m_primarykeys.size() == 1)
		m_spkey = true;
	else
		m_spkey = false;
}

void TableDef::addFPK(TableDefPtr table, const std::string& suffix)
{
	std::string name;
	name.append(table->tableForeignName());
	name.append(suffix);
	
	m_primarykeys[name] = table;
	
	if(m_primarykeys.size() == 1)
		m_spkey = true;
	else
		m_spkey = false;
}

void TableDef::addValue(const std::string& name)
{
	addField(name, false, Global::Get()->EmptyString, false);
}

void TableDef::addValue(const std::string& name, value_type defaultvalue)
{
	std::ostringstream str;
	str << defaultvalue;
	addField(name, false, str.str(), false);
}

void TableDef::addTextField(const std::string& name)
{
	addField(name, true, Global::Get()->EmptyString, false);
}

void TableDef::addLookupTextField(const std::string& name)
{
	addField(name, true, Global::Get()->EmptyString, true);
}

void TableDef::addTextField(const std::string& name, const std::string& defaulttext)
{
	addField(name, true, defaulttext, false);
}

void TableDef::addField(const std::string& name, bool text, const std::string& defaulttext, bool providelookup)
{
	FieldDefPtr field(new FieldDef(name, text, defaulttext));
	m_fields.push_back(field);
	m_deffields.push_back(field);
	
	if(providelookup)
		m_lookupfields.push_back(field);
}

void TableDef::addFK(TableDefPtr table)
{
	addFK(table, Global::Get()->EmptyString);
}

void TableDef::addFK(TableDefPtr table, const std::string& suffix)
{	
	std::string name;
	name.append(table->tableForeignName());
	name.append(suffix);

	addValue(name);
	// TODO, add SQLite triggers
}

const std::string& TableDef::tableForeignName() const
{	
	return m_foreignname;
}

bool TableDef::hasfield(FieldPtr field) const
{
	for(FieldVector::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		if((*it) == field)
			return true;
	}
	
	return false;
}
