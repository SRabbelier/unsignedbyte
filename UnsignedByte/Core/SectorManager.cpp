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

#include "SectorManager.h"
#include "Sector.h"
#include "Global.h"

#include "Table.h"
#include "Tables.h"

using mud::SectorManager;
using mud::Sector;
using mud::SectorPtr;

std::vector<std::string> SectorManager::List()
{
	return GetTable()->tableList();
}

TablePtr SectorManager::GetTable()
{
	return Tables::Get()->SECTORS;
}

value_type SectorManager::Add()
{	
	db::Sectors d;
	d.save();
	value_type id = d.getsectorid();
	if(id == 0)
		Global::Get()->bug("SectorManager::AddSector(), id = 0");
	
	return id;	
}

mud::SectorPtr SectorManager::GetByKey(value_type id)
{
	SectorPtr p = m_byKey[id];
	if(p)
		return p;
		
	db::Sectors* d = db::Sectors::bykey(id);
	p = cacheSector(d);
	return p;
}

mud::SectorPtr SectorManager::GetByName(cstring value)
{
	SectorPtr p = m_byName[value];
	if(p)
		return p;
		
	db::Sectors* d = db::Sectors::byname(value);
	p = cacheSector(d);
	return p;
} 

value_type SectorManager::lookupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupByName.find(value);
	if(it != m_lookupByName.end())
		return it->second;
	
	value_type id = db::Sectors::lookupname(value);
	m_lookupByName[value] = id;
	return id;
}

void SectorManager::Close(value_type id)
{
	sectors_m::iterator key = m_byKey.find(id);
	sectors_ms::iterator name = m_byName.find(key->second->getName());
	m_byKey.erase(key);
	m_byName.erase(name);	
}

SectorPtr SectorManager::cacheSector(db::Sectors* d)
{
	SectorPtr p(new Sector(d));
	m_byKey[d->getsectorid()] = p;
	m_byName[d->getname()] = p;
	return p;
}
