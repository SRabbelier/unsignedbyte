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

#include "ColourManager.h"
#include "Colour.h"
#include "Global.h"

#include "Table.h"
#include "Tables.h"

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


value_type ColourManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->COLOURS);
	manager->save();
	value_type id = manager->getkey(db::ColoursFields::Get()->COLOURID);
	if(id == 0)
		Global::Get()->bug("ColourManager::Add(), id = 0");
	
	return id;
}

mud::ColourPtr ColourManager::GetByKey(value_type id)
{
	KeyPtr key(new Key(db::ColoursFields::Get()->COLOURID, id));
	Keys keys;
	keys[db::ColoursFields::Get()->COLOURID.get()] = key;
	SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->COLOURS, keys);
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
	Keys keys = SavableManager::lookupvalue(val);
	value_type id = keys[db::ColoursFields::Get()->COLOURID.get()];
	return id;
}

value_type ColourManager::lookupByName(cstring value)
{
	ValuePtr val(new Value(db::ColoursFields::Get()->NAME, value));
	Keys keys = SavableManager::lookupvalue(val);
	value_type id = keys[db::ColoursFields::Get()->COLOURID.get()];
	return id;
}
