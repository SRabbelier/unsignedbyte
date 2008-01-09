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

#include "GrantGroupManager.h"
#include "GrantGroup.h"
#include "Global.h"
#include "GrantGroup.h"

#include "Table.h"
#include "Tables.h"

using mud::GrantGroupManager;
using mud::GrantGroup;
using mud::GrantGroupPtr;

std::vector<std::string> GrantGroupManager::List()
{
	return GetTable()->tableList();
}

TablePtr GrantGroupManager::GetTable()
{
	return Tables::Get()->GRANTGROUPS;
}

value_type GrantGroupManager::Add()
{
	db::GrantGroups d;
	d.save();
	value_type id = d.getgrantgroupid();
	if(id == 0)
		Global::Get()->bug("GrantGroupManager::AddGrantGroup(), id = 0");
	
	return id;
}

mud::GrantGroupPtr GrantGroupManager::GetByKey(value_type id)
{
	GrantGroupPtr p = m_byKey[id];
	if(p)
		return p;
		
	db::GrantGroups* d = db::GrantGroups::bykey(id);
	p = cacheGrantGroup(d);
	return p;
}

mud::GrantGroupPtr GrantGroupManager::GetByName(cstring value)
{
	GrantGroupPtr p = m_byName[value];
	if(p)
		return p;
		
	db::GrantGroups* d = db::GrantGroups::byname(value);
	p = cacheGrantGroup(d);
	return p;
}

value_type GrantGroupManager::lookupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupByName.find(value);
	if(it != m_lookupByName.end())
		return it->second;
	
	value_type id = db::GrantGroups::lookupname(value);
	m_lookupByName[value] = id;
	return id;
}

void GrantGroupManager::Close(value_type id)
{
	grantgroups_m::iterator key = m_byKey.find(id);
	grantgroups_ms::iterator name = m_byName.find(key->second->getName());
	m_byKey.erase(key);
	m_byName.erase(name);
}

GrantGroupPtr GrantGroupManager::cacheGrantGroup(db::GrantGroups* d)
{
	GrantGroupPtr p(new GrantGroup(d));
	m_byKey[d->getgrantgroupid()] = p;
	m_byName[d->getname()] = p;
	return p;
}
