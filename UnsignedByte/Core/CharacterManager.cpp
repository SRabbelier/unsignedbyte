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

#include "Character.h"
#include "CharacterManager.h"
#include "Global.h"

#include "Table.h"
#include "Tables.h"

using mud::CharacterManager;
using mud::Character;
using mud::CharacterPtr;

std::vector<std::string> CharacterManager::List()
{
	return GetTable()->tableList();
}

void CharacterManager::Close(mud::Character* Ch)
{
	if(Ch == NULL)
	{
		throw std::invalid_argument("CharacterManager::Close(), Ch == NULL");
		return;
	}
	
	Close(Ch->getID());
}

TablePtr CharacterManager::GetTable()
{ 
	return Tables::Get()->CHARACTERS; 
}

bool CharacterManager::IllegalName(const std::string& name)
{
	if(lookupByName(name))
		return true;

	return false;
}

value_type CharacterManager::Add()
{
	db::Characters d;
	d.save();
	value_type id = d.getcharacterid();
	if(id == 0)
		Global::Get()->bug("CharacterManager::AddCharacter(), id = 0");
		
	return id;
}

mud::CharacterPtr CharacterManager::GetByKey(value_type id)
{
	CharacterPtr p(m_byKey[id]);
	if(p)
		return p;

	db::Characters* d = db::Characters::bykey(id);
	p = cacheCharacter(d);
	return p;
}

mud::CharacterPtr CharacterManager::GetByName(cstring value)
{
	CharacterPtr p(m_byName[value]);
	if(p)
		return p;
		
	db::Characters* d = db::Characters::byname(value);
	p = cacheCharacter(d);
	return p;
}

value_type CharacterManager::lookupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupByName.find(value);
	if(it != m_lookupByName.end())
		return it->second;
	
	value_type id = db::Characters::lookupname(value);
	m_lookupByName[value] = id;
	return id;
}

void CharacterManager::Close(value_type id)
{
	characters_m::iterator key = m_byKey.find(id);
	characters_ms::iterator name = m_byName.find(key->second->getName());
	m_byKey.erase(key);
	m_byName.erase(name);
}

CharacterPtr CharacterManager::cacheCharacter(db::Characters *d)
{
	CharacterPtr p(new Character(d));
	m_byKey[d->getcharacterid()] = p;
	m_byName[d->getname()] = p;
	return p;
}
