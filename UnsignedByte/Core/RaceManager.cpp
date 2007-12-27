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

#include <string>
#include <stdexcept>

#include "RaceManager.h"
#include "Race.h"
#include "Global.h"

using mud::RaceManager;
using mud::Race;
using mud::RacePtr;

std::vector<std::string> RaceManager::List()
{
	return GetTable()->tableList();
}

TablePtr RaceManager::GetTable()
{
	return Tables::Get()->RACES;
}

value_type RaceManager::Add()
{
	db::Races d;
	d.save();
	value_type id = d.getraceid();
	if(id == 0)
		Global::Get()->bug("Cache::AddRace(), id = 0");
	
	return id;
}

mud::RacePtr RaceManager::GetByKey(value_type id)
{
	RacePtr p = m_byKey[id];
	if(p)
		return p;
		
	db::Races* d = db::Races::bykey(id);
	p = cacheRace(d);
	return p;
}

mud::RacePtr RaceManager::GetByName(cstring value)
{
	RacePtr p = m_byName[value];
	if(p)
		return p;
		
	db::Races* d = db::Races::byname(value);
	p = cacheRace(d);
	return p;
}

value_type RaceManager::lookupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupByName.find(value);
	if(it != m_lookupByName.end())
		return it->second;
	
	value_type id = db::Races::lookupname(value);
	m_lookupByName[value] = id;
	return id;
}

void RaceManager::Close(value_type id)
{
	races_m::iterator key = m_byKey.find(id);
	races_ms::iterator name = m_byName.find(key->second->getName());
	m_byKey.erase(key);
	m_byName.erase(name);	
}

RacePtr RaceManager::cacheRace(db::Races* d)
{
	RacePtr p(new Race(d));
	m_byKey[d->getraceid()] = p;
	m_byName[d->getname()] = p;
	return p;
}
