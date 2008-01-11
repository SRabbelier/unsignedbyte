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

#include "CommandManager.h"
#include "Command.h"
#include "Global.h"
#include "Command.h"

using mud::CommandManager;
using mud::Command;
using mud::CommandPtr;

std::vector<std::string> CommandManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr CommandManager::GetTable()
{
	return db::TableImpls::Get()->COMMANDS;
}

value_type CommandManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->COMMANDS);
	manager->save();
	value_type id = manager->getkey(db::CommandsFields::Get()->COMMANDID)->getValue();
	if(id == 0)
		Global::Get()->bug("CommandManager::Add(), id = 0");
	
	return id;	
}

mud::CommandPtr CommandManager::GetByKey(value_type id)
{
	KeyPtr key(new Key(db::CommandsFields::Get()->COMMANDID, id));
	Keys keys;
	keys[db::CommandsFields::Get()->COMMANDID.get()] = key;
	SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->COMMANDS, keys);
	CommandPtr p(new Command(manager));
	return p;
}

mud::CommandPtr CommandManager::GetByName(cstring value)
{
	ValuePtr val(new Value(db::CommandsFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	CommandPtr p(new Command(manager));
	return p;
}

value_type CommandManager::lookupByName(cstring value)
{
	ValuePtr val(new Value(db::CommandsFields::Get()->NAME, value));
	Keys keys = SavableManager::lookupvalue(val);
	value_type id = keys[db::CommandsFields::Get()->COMMANDID.get()];
	return id;
}
