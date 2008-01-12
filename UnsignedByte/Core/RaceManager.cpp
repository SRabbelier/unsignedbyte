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

TableImplPtr RaceManager::GetTable()
{
	return db::TableImpls::Get()->RACES;
}

KeysPtr RaceManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->RACES);
	manager->save();
	return manager->getkeys();
}

mud::RacePtr RaceManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->RACES));
	KeyPtr key(new Key(db::RacesFields::Get()->RACEID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->RACES, keys);
	RacePtr p(new Race(manager));
	return p;
}

mud::RacePtr RaceManager::GetByName(cstring value)
{
	ValuePtr val(new Value(db::RacesFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	RacePtr p(new Race(manager));
	return p;
}

value_type RaceManager::lookupByName(cstring value)
{
	ValuePtr val(new Value(db::RacesFields::Get()->NAME, value));
	KeysPtr keys = SavableManager::lookupvalue(val);
	value_type id = keys->getKey(db::RacesFields::Get()->RACEID);
	return id;
}
