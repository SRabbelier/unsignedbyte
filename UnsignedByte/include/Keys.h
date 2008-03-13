/***************************************************************************
 *   Copyright (C) 2008 by Sverre Rabbelier                                *
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
	Keys(TableImplPtr table);
	Keys(TableImplPtr table, cstring initstring);
	~Keys();
	
	TableImplPtr getTable() const;
	void addKey(KeyPtr key);
	
	std::string toString() const;
	Strings getDiff(KeysPtr orig) const;
	
	size_t size() const;
	KeyPtr first() const;
	KeyMap::const_iterator begin() const;
	KeyMap::const_iterator end() const;
	KeyMap::const_iterator find(KeyDefPtr key) const;
	KeyPtr getKey(KeyDefPtr key) const;
	
	void setDirty(KeysPtr oldKeys);

private:
	TableImplPtr m_table;
	KeyMap m_keys;
};
