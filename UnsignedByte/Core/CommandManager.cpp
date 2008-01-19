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
#include "Command.h"
#include "db.h"
#include "TableImpls.h"

using mud::CommandManager;
using mud::Command;
using mud::CommandPtr;

CommandManager::CommandManager() :
defaultHighForce(true),
defaultForce(true),
defaultLowForce(true)
{
	
}

CommandManager::~CommandManager()
{
	
}

std::vector<std::string> CommandManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr CommandManager::GetTable()
{
	return db::TableImpls::Get()->COMMANDS;
}

KeysPtr CommandManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->COMMANDS);
	manager->save();
	return manager->getkeys();
}

mud::CommandPtr CommandManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->COMMANDS));
	KeyPtr key(new Key(db::CommandsFields::Get()->COMMANDID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
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
	KeysPtr keys = SavableManager::lookupvalue(val);
	value_type id = keys->getKey(db::CommandsFields::Get()->COMMANDID);
	return id;
}
