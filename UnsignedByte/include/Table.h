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
#pragma once

#include <string>
#include <vector>
#include <map>

class Field;
class Table;

typedef std::vector<Field*> Fields;
typedef std::map<std::string, Table*> TableMap;
typedef unsigned long value_type;

class Table
{
public:
	Table(std::string name);
	~Table();
	
	// Add Primary Key
	void addPK(const std::string& name);

	// Add Field
	void addValue(const std::string& name);
	void addValue(const std::string& name, value_type defaultvalue);
	void addTextField(const std::string& name);
	void addTextField(const std::string& name, const std::string& defaulttext);
	
	// Add Foreign Key
	void addFK(Table* table);
	void addFK(Table* table, const std::string& suffix);

	const std::string& tableName() const;
	
	std::string tableQuery() const;
	std::string creationQuery(bool verify = false) const;
	
	Fields::const_iterator begin() { return m_fields.begin(); }
	Fields::const_iterator end() { return m_fields.end(); }
	size_t size() { return m_fields.size(); }
	
	std::string firstKey() const { return m_keys.begin()->first; }
	TableMap::const_iterator keybegin() { return m_keys.begin(); }
	TableMap::const_iterator keyend() { return m_keys.end(); }
	size_t keysize() { return m_keys.size(); }
	
	bool hasSinglularPrimaryKey() { return m_spkey; }
	
private:
	void addField(const std::string& name, bool text, const std::string& defaulttext);

	std::string m_name;
	bool m_spkey; // singular primary key

	Fields m_fields;
	TableMap m_keys;
};
