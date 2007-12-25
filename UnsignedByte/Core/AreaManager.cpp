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

#include "AreaManager.h"
#include "Area.h"
#include "Global.h"
#include "Area.h"

using mud::AreaManager;
using mud::Area;
using mud::AreaPtr;

std::vector<std::string> AreaManager::List()
{
	return GetTable()->tableList();
}

TablePtr AreaManager::GetTable()
{
	return Tables::Get()->AREAS;
}

value_type AreaManager::Add()
{
	db::Areas d;
	d.save();
	value_type id = d.getareaid();
	if(id == 0)
		Global::Get()->bug("Cache::AddArea(), id = 0");
		
	return id;
}

mud::AreaPtr AreaManager::GetByKey(value_type id)
{
	AreaPtr p = m_byKey[id];
	if(p)
		return p;

	db::Areas* d = db::Areas::bykey(id);
	p = cacheArea(d);
	return p;
}

void AreaManager::Close(value_type id)
{
	areas_m::iterator key = m_byKey.find(id);
	m_byKey.erase(key);
}

AreaPtr AreaManager::cacheArea(db::Areas* d)
{
	AreaPtr p(new Area(d));
	m_byKey[d->getareaid()] = p;
	return p;
}
