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

#include "AreaManager.h"
#include "Area.h"
#include "Global.h"

using mud::AreaManager;
using mud::Area;
using mud::AreaPtr;

std::vector<std::string> AreaManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr AreaManager::GetTable()
{
	return db::TableImpls::Get()->AREAS;
}

value_type AreaManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->AREAS);
	manager->save();
	value_type id = manager->getkey(db::AreasFields::Get()->AREAID)->getValue();
	if(id == 0)
		Global::Get()->bug("AreaManager::Add(), id = 0");
	
	return id;	
}

mud::AreaPtr AreaManager::GetByKey(value_type id)
{
	KeyPtr key(new Key(db::AreasFields::Get()->AREAID, id));
	Keys keys;
	keys[db::AreasFields::Get()->AREAID.get()] = key;
	SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->AREAS, keys);
	AreaPtr p(new Area(manager));
	return p;
}
