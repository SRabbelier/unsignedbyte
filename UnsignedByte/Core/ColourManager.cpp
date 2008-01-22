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

#include "ColourManager.h"
#include "Colour.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

using mud::ColourManager;
using mud::Colour;
using mud::ColourPtr;

std::vector<std::string> ColourManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr ColourManager::GetTable()
{
	return db::TableImpls::Get()->COLOURS;
}


KeysPtr ColourManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->COLOURS);
	manager->save();
	return manager->getkeys();
}

mud::ColourPtr ColourManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->COLOURS));
	KeyPtr key(new Key(db::ColoursFields::Get()->COLOURID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	ColourPtr p(new Colour(manager));
	return p;
}

mud::ColourPtr ColourManager::GetByName(cstring value)
{
	ValuePtr val(new Value(db::ColoursFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	ColourPtr p(new Colour(manager));
	return p;
}

mud::ColourPtr ColourManager::GetByCode(cstring value)
{
	ValuePtr val(new Value(db::ColoursFields::Get()->CODE, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	ColourPtr p(new Colour(manager));
	return p;
}

value_type ColourManager::lookupByCode(cstring value)
{
	ValuePtr val(new Value(db::ColoursFields::Get()->CODE, value));
	KeysPtr keys = SavableManager::lookupvalue(val);
	value_type id = keys->getKey(db::ColoursFields::Get()->COLOURID)->getValue();
	return id;
}

value_type ColourManager::lookupByName(cstring value)
{
	ValuePtr val(new Value(db::ColoursFields::Get()->NAME, value));
	KeysPtr keys = SavableManager::lookupvalue(val);
	value_type id = keys->getKey(db::ColoursFields::Get()->COLOURID)->getValue();
	return id;
}
