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
#include "TableDef.h"

class TableImpl : public Table
{
public:
	TableImpl(TableDefPtr table);
	~TableImpl() { }
	
	void modify();
	const Strings& tableList();
	
	void addKey(KeyDefPtr key) { m_keys.push_back(key); }
	void addField(FieldImplPtr field) { m_implfields.push_back(field); }
	
	// Lookup fields
	FieldDefVector::const_iterator lookupbegin() const { return m_table->lookupbegin(); }
	FieldDefVector::const_iterator lookupend() const { return m_table->lookupend(); }
	size_t lookupsize() const { return m_table->lookupsize(); }
	
	FieldDefVector::const_iterator defbegin() const { return m_table->defbegin(); }
	FieldDefVector::const_iterator defend() const { return m_table->defend(); }
	size_t defsize() const { return m_table->defsize(); }
	
	FieldImplVector::const_iterator implbegin() const { return m_implfields.begin(); }
	FieldImplVector::const_iterator implend() const { return m_implfields.end(); }
	size_t implsize() const { return m_implfields.size(); }
	bool hasfield(FieldImplPtr field) const;
	
	KeyDefPtr firstImplKey() const { return *(m_keys.begin()); }
	KeyDefs::const_iterator keyimplbegin() const { return m_keys.begin(); }
	KeyDefs::const_iterator keyimplend() const { return m_keys.end(); }
	size_t keyimplsize() const { return m_keys.size(); }
	
	std::string firstKey() const { return m_table->firstKey(); }
	TableMap::const_iterator keybegin() const { return m_table->keybegin(); }
	TableMap::const_iterator keyend() const { return m_table->keyend(); }
	size_t keysize() const { return m_table->keysize(); }
	
	bool hasSingularPrimaryKey() const { return m_table->hasSingularPrimaryKey(); }
	
private:
	TableDefPtr m_table;
	FieldImplVector m_implfields;
	KeyDefs m_keys;
	
	time_t m_lastchange;	
	std::vector<std::string> m_list; // a list representation of all elements in the table
	time_t m_listcache; // the moment the list was cached
};
