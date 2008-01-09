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

#include "Types.h"
#include "Table.h"

typedef std::map<std::string, TablePtr> TableMap;

class TableDef : public Table
{
public:
	TableDef(std::string name);
	~TableDef();
	
	// Add Primary Key
	void addPK(const std::string& name);
	void addFPK(TableDefPtr table);
	void addFPK(TableDefPtr table, const std::string& suffix);

	// Add Field
	void addValue(const std::string& name);
	void addValue(const std::string& name, value_type defaultvalue);
	void addTextField(const std::string& name);
	void addLookupTextField(const std::string& name);
	void addTextField(const std::string& name, const std::string& defaulttext);
	
	// Add Foreign Key
	void addFK(TableDefPtr table);
	void addFK(TableDefPtr table, const std::string& suffix);

	const std::string& tableForeignName() const;
	
	// Lookup fields
	FieldVector::const_iterator lookupbegin() const { return m_lookupfields.begin(); }
	FieldVector::const_iterator lookupend() const { return m_lookupfields.end(); }
	size_t lookupsize() const { return m_lookupfields.size(); }
	
	FieldDefVector::const_iterator defbegin() const { return m_deffields.begin(); }
	FieldDefVector::const_iterator defend() const { return m_deffields.end(); }
	size_t defsize() const { return m_deffields.size(); }
	
	FieldVector::const_iterator begin() const { return m_fields.begin(); }
	FieldVector::const_iterator end() const { return m_fields.end(); }
	size_t size() const { return m_fields.size(); }
	bool hasfield(FieldPtr field) const;
	
	std::string firstKey() const { return m_primarykeys.begin()->first; }
	TableMap::const_iterator keybegin() const { return m_primarykeys.begin(); }
	TableMap::const_iterator keyend() const { return m_primarykeys.end(); }
	size_t keysize() const { return m_primarykeys.size(); }
	
	bool hasSingularPrimaryKey() const { return m_spkey; }
	
private:
	void addField(const std::string& name, bool text, const std::string& defaulttext, bool providelookup);
	
	std::string m_foreignname;
	FieldVector m_lookupfields;
	FieldDefVector m_deffields;
};
