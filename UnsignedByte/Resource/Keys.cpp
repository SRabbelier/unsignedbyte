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

#include "Keys.h"
#include "SavableHeaders.h"
#include "Parse.h"

Keys::Keys(TableImplPtr table, cstring initstring) :
m_table(table)
{
	Parse p(initstring);
		
	try
	{
		for(KeyDefs::const_iterator it = m_table->keyimplbegin(); it != m_table->keyimplend(); it++)
		{
			std::string keystring = p.getword();
			int value = atoi(keystring.c_str());
			KeyPtr key(new Key(*it, value));
			addKey(key);
		}
	}
	catch(std::exception& e) 
	{
		throw std::invalid_argument("Keys::Keys(), could not parse initstring.");
	}
}

KeyPtr Keys::getKey(KeyDefPtr key) const
{
	KeyMap::const_iterator it = m_keys.find(key.get());
	if(it == m_keys.end())
		throw std::invalid_argument("Keys::getKey(), key not in m_keys.");
		
	return it->second;
}

void Keys::addKey(KeyPtr key)
{
	if(key->getKeyDef()->getTable() != m_table)
		throw std::invalid_argument("Keys::addKey(), key->getTable() != m_table");
		
	m_keys[key->getKeyDef().get()] = key;
}
	
std::string Keys::toString() const
{
	std::string result;
	
	return result;
}
