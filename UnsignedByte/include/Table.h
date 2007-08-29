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

class Table
{
public:
	Table(std::string name, std::string id);
	Table(std::string name);
	~Table();

	void addField(const std::string& name, bool text = false);
	void addField(const std::string& name, bool text, const std::string& defaulttext);
	
	void addFK(Table* table);
	void addFK(Table* table, const std::string& suffix);

	const std::string& tableName() const;
	std::string tableID() const;
	std::string tableQuery() const;
	std::string creationQuery(bool verify = false) const;
	
	bool isLookupTable() const;
	
	Fields::const_iterator begin() { return m_fields.begin(); }
	Fields::const_iterator end() { return m_fields.end(); }
	size_t size() { return m_fields.size(); }
	
	TableMap::const_iterator fkbegin() { return m_fks.begin(); }
	TableMap::const_iterator fkend() { return m_fks.end(); }
	size_t fksize() { return m_fks.size(); }
	
private:
	std::string m_name;
	std::string m_id;
	
	const bool m_lookuptable;

	Fields m_fields;
	TableMap m_fks;
};
