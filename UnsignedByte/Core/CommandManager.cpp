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

#include "Table.h"
#include "Tables.h"

using mud::CommandManager;
using mud::Command;
using mud::CommandPtr;

std::vector<std::string> CommandManager::List()
{
	return GetTable()->tableList();
}

TablePtr CommandManager::GetTable()
{
	return Tables::Get()->COMMANDS;
}

value_type CommandManager::Add()
{
	db::Commands d;
	d.save();
	value_type id = d.getcommandid();
	if(id == 0)
		Global::Get()->bug("CommandManager::AddCommand(), id = 0");
	
	return id;
}

mud::CommandPtr CommandManager::GetByKey(value_type id)
{
	CommandPtr p = m_byKey[id];
	if(p)
		return p;
		
	db::Commands* d = db::Commands::bykey(id);
	p = cacheCommand(d);
	return p;
}

mud::CommandPtr CommandManager::GetByName(cstring value)
{
	CommandPtr p = m_byName[value];
	if(p)
		return p;
		
	db::Commands* d = db::Commands::byname(value);
	p = cacheCommand(d);
	return p;
}

value_type CommandManager::lookupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupByName.find(value);
	if(it != m_lookupByName.end())
		return it->second;
	
	value_type id = db::Commands::lookupname(value);
	m_lookupByName[value] = id;
	return id;
}

void CommandManager::Close(value_type id)
{
	commands_m::iterator key = m_byKey.find(id);
	commands_ms::iterator name = m_byName.find(key->second->getName());
	m_byKey.erase(key);
	m_byName.erase(name);
}

CommandPtr CommandManager::cacheCommand(db::Commands* d)
{
	CommandPtr p(new Command(d));
	m_byKey[d->getcommandid()] = p;
	m_byName[d->getname()] = p;
	return p;
}
