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

using mud::SectorManager;
using mud::Sector;
using mud::SectorPtr;

std::vector<std::string> SectorManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr SectorManager::GetTable()
{
	return db::TableImpls::Get()->SECTORS;
}

value_type SectorManager::Add()
{	
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->SECTORS);
	manager->save();
	value_type id = manager->getkey(db::SectorsFields::Get()->SECTORID);
	if(id == 0)
		Global::Get()->bug("SectorManager::Add(), id = 0");
	
	return id;	
}

mud::SectorPtr SectorManager::GetByKey(value_type id)
{		
	KeyPtr key(new Key(db::SectorsFields::Get()->SECTORID, id));
	Keys keys;
	keys[db::SectorsFields::Get()->SECTORID.get()] = key;
	SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->SECTORS, keys);
	SectorPtr p(new Sector(manager));
	return p;
}

mud::SectorPtr SectorManager::GetByName(cstring value)
{		
	ValuePtr val(new Value(db::SectorsFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	SectorPtr p(new Sector(manager));
	return p;
} 

value_type SectorManager::lookupByName(cstring value)
{	
	ValuePtr val(new Value(db::SectorsFields::Get()->NAME, value));
	Keys keys = SavableManager::lookupvalue(val);
	value_type id = keys[db::SectorsFields::Get()->SECTORID.get()];
	return id;
}
