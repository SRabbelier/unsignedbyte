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

#include "AreaManager.h"
#include "Area.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

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

KeysPtr AreaManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->AREAS);
	manager->save();
	return manager->getkeys();
}

mud::AreaPtr AreaManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->AREAS));
	KeyPtr key(new Key(db::AreasFields::Get()->AREAID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	AreaPtr p(new Area(manager));
	return p;
}
