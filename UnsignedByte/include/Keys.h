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

class Keys
{
public:
	Keys(TableImplPtr table) : m_table(table) { }
	Keys(TableImplPtr table, cstring initstring);
	~Keys() { }
	
	TableImplPtr getTable() const { return m_table; }
	void addKey(KeyPtr key);
	
	std::string toString() const;
	
	size_t size() const { return m_keys.size(); }
	KeyPtr first() const { return m_keys.begin()->second; }
	KeyMap::const_iterator begin() const { return m_keys.begin(); }
	KeyMap::const_iterator end() const { return m_keys.end(); }
	KeyMap::const_iterator find(KeyDefPtr key) const { return m_keys.find(key.get()); }
	KeyPtr getKey(KeyDefPtr key) const;

private:
	TableImplPtr m_table;
	KeyMap m_keys;
};
