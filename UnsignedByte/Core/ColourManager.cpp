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

#include "ColourManager.h"
#include "Colour.h"
#include "Global.h"

using mud::ColourManager;
using mud::Colour;
using mud::ColourPtr;

std::vector<std::string> ColourManager::List()
{
	return GetTable()->tableList();
}

TablePtr ColourManager::GetTable()
{
	return Tables::Get()->COLOURS;
}


value_type ColourManager::Add()
{
	db::Colours d;
	d.save();
	value_type id = d.getcolourid();
	if(id == 0)
		Global::Get()->bug("ColourManager::AddColour(), id = 0");
	
	return id;
}

mud::ColourPtr ColourManager::GetByKey(value_type id)
{
	ColourPtr p = m_byKey[id];
	if(p)
		return p;

	db::Colours* d = db::Colours::bykey(id);
	p = cacheColour(d);
	return p;
}

mud::ColourPtr ColourManager::GetByName(cstring value)
{
	ColourPtr p = m_byName[value];
	if(p)
		return p;

	db::Colours* d = db::Colours::byname(value);
	p = cacheColour(d);
	return p;
}

mud::ColourPtr ColourManager::GetByCode(cstring value)
{
	ColourPtr p = m_byCode[value];
	if(p)
		return p;

	db::Colours* d = db::Colours::bycode(value);
	p = cacheColour(d);
	return p;
}

value_type ColourManager::lookupByCode(cstring value)
{
	reverseStringKey::iterator it = m_lookupByCode.find(value);
	if(it != m_lookupByCode.end())
		return it->second;
	
	value_type id = db::Colours::lookupcode(value);
	m_lookupByCode[value] = id;
	return id;
}

value_type ColourManager::lookupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupByName.find(value);
	if(it != m_lookupByName.end())
		return it->second;
	
	value_type id = db::Colours::lookupname(value);
	m_lookupByName[value] = id;
	return id;
}

void ColourManager::Close(value_type id)
{
	colours_m::iterator key = m_byKey.find(id);
	colours_ms::iterator name = m_byName.find(key->second->getName());
	colours_ms::iterator code = m_byCode.find(key->second->getCode());
	m_byKey.erase(key);
	m_byName.erase(name);
	m_byCode.erase(code);
}

ColourPtr ColourManager::cacheColour(db::Colours* d)
{
	ColourPtr p(new Colour(d));
	m_byKey[d->getcolourid()] = p;
	m_byName[d->getname()] = p;
	m_byCode[d->getcode()] = p;
	return p;
}
