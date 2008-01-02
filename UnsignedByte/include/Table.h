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
#include <smart_ptr.h>
#include "sqlite3.h"

class Field;
class Table;

typedef SmartPtr<Field> FieldPtr;
typedef SmartPtr<Table> TablePtr;

typedef std::vector<FieldPtr> Fields;
typedef std::map<std::string, TablePtr> TableMap;
typedef unsigned long value_type;

class Table
{
public:
	Table(std::string name);
	~Table();
	
	// Add Primary Key
	void addPK(const std::string& name);
	void addFPK(TablePtr table);
	void addFPK(TablePtr table, const std::string& suffix);

	// Add Field
	void addValue(const std::string& name);
	void addValue(const std::string& name, value_type defaultvalue);
	void addTextField(const std::string& name);
	void addLookupTextField(const std::string& name);
	void addTextField(const std::string& name, const std::string& defaulttext);
	
	// Add Foreign Key
	void addFK(TablePtr table);
	void addFK(TablePtr table, const std::string& suffix);
	
	// Provide lookup functionality for the last 'count' entries
	// void provideLookup(unsigned int count);

	const std::string& tableName() const;
	const std::string& tableForeignName() const;
	const std::vector<std::string>& tableList();
	
	std::string tableQuery() const;
	std::string creationQuery(bool verify = false) const;

	void parseRow(sqlite3_stmt* statement);

	void modify();
	
	Fields::const_iterator begin() const { return m_fields.begin(); }
	Fields::const_iterator end() const { return m_fields.end(); }
	size_t size() const { return m_fields.size(); }
	
	std::string firstKey() const { return m_primarykeys.begin()->first; }
	TableMap::const_iterator keybegin() const { return m_primarykeys.begin(); }
	TableMap::const_iterator keyend() const { return m_primarykeys.end(); }
	size_t keysize() const { return m_primarykeys.size(); }
	
	Fields::const_iterator lookupbegin() const { return m_lookupfields.begin(); }
	Fields::const_iterator lookupend() const { return m_lookupfields.end(); }
	size_t lookupsize() const { return m_lookupfields.size(); }
	
	bool hasSingularPrimaryKey() const { return m_spkey; }
	
private:
	void addField(const std::string& name, bool text, const std::string& defaulttext, bool providelookup);

	std::string m_name;
	std::string m_foreignname;
	
	bool m_spkey; // singular primary key

	Fields m_fields;
	Fields m_lookupfields;
	TableMap m_primarykeys; // All keys added with addFPK()

	time_t m_lastchange;
	
	std::vector<std::string> m_list; // a list representation of all elements in the table
	time_t m_listcache; // the moment the list was cached
};
