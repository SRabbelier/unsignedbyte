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

#include "Character.h"
#include "CharacterManager.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

using mud::CharacterManager;
using mud::Character;
using mud::CharacterPtr;

std::vector<std::string> CharacterManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr CharacterManager::GetTable()
{ 
	return db::TableImpls::Get()->ENTITIES; 
}

bool CharacterManager::IllegalName(const std::string& name)
{
	try
	{
		lookupByName(name);
		return true;
	}
	catch(RowNotFoundException& e) { }

	return false;
}

KeysPtr CharacterManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->ENTITIES);
	manager->save();
	return manager->getkeys();
}

mud::CharacterPtr CharacterManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->ENTITIES));
	KeyPtr key(new Key(db::EntitiesFields::Get()->ENTITYID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	CharacterPtr p(new Character(manager));
	return p;
}

mud::CharacterPtr CharacterManager::GetByName(cstring value)
{
	ValuePtr val(new Value(db::EntitiesFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	CharacterPtr p(new Character(manager));
	return p;
}

value_type CharacterManager::lookupByName(cstring value)
{
	ValuePtr val(new Value(db::EntitiesFields::Get()->NAME, value));
	KeysPtr keys = SavableManager::lookupvalue(val);
	value_type id = keys->getKey(db::EntitiesFields::Get()->ENTITYID)->getValue();
	return id;
}
