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

#include <string>
#include <stdexcept>

#include "UBSocket.h"
#include "Command.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "ub.h"
#include "GrantGroup.h"
#include "Account.h"

bool Command::defaultHighForce = true;
bool Command::defaultForce = true;
bool Command::defaultLowForce = false;

Command::Command(db::Commands* Command) :
m_command(Command)
{
	if(m_command == NULL)
		throw std::invalid_argument("Command::Command(), m_command == NULL!");
}

Command::~Command(void)
{
	delete m_command;
	m_command = NULL;
}

bool Command::getGrant(UBSocket* sock)
{
	try
	{
		long gid = getGrantGroup();
		long aid = sock->GetAccount()->getID();
		
		long pid = Cache::Get()->GetPermissionID(aid, gid);
		Permission* prm = Cache::Get()->GetPermission(pid);
		return prm->hasGrant();
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		return getDefaultGrant();
	}
}

bool Command::getDefaultGrant()
{
	try
	{
		long id = getGrantGroup();
		GrantGroup* grp = Cache::Get()->GetGrantGroup(id);
		return grp->getDefaultGrant();
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		return Permission::defaultGrant;
	}
}

bool Command::getLog(UBSocket* sock)
{
	try
	{
		long gid = getGrantGroup();
		long aid = sock->GetAccount()->getID();
		
		long pid = Cache::Get()->GetPermissionID(aid, gid);
		Permission* prm = Cache::Get()->GetPermission(pid);
		return prm->hasLog();
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		return getDefaultLog();
	}
}

bool Command::getDefaultLog()
{
	try
	{
		long id = getGrantGroup();
		GrantGroup* grp = Cache::Get()->GetGrantGroup(id);
		return grp->getDefaultLog();
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		return Permission::defaultLog;
	}
}

void Command::Delete()
{
	m_command->erase();
}

void Command::Save()
{
	m_command->save();
}

bool Command::Exists()
{
	return m_command->commandid;
}

std::vector<std::string> Command::Show()
{
	std::vector<std::string> result;
	result.push_back(Global::Get()->sprintf("Name: '%s'.\n", getName().c_str()));
	result.push_back(Global::Get()->sprintf("GrantGroup: '%d'.\n", getGrantGroup()));
	result.push_back(Global::Get()->sprintf("HighForce: %s.\n", canHighForce() ? "ON" : "OFF"));
	result.push_back(Global::Get()->sprintf("Force: %s.\n", canForce() ? "ON" : "OFF"));
	result.push_back(Global::Get()->sprintf("LowForce: %s.\n", canLowForce() ? "ON" : "OFF")); 
	return result;
}
	
std::string Command::ShowShort()
{
	std::string forcelevel;
	if(canLowForce())
		forcelevel = "LOW";
	else if(canForce())
		forcelevel = "NORMAL";
	else if(canHighForce())
		forcelevel = "HIGH";
	else
		forcelevel = "NONE";
		
		
	return Global::Get()->sprintf("%s: %d (Force: %s)\n", 
			getName().c_str(),
			getGrantGroup(),
			forcelevel.c_str());
}

std::vector<std::string> Command::List()
{
	std::vector<std::string> result;
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->COMMANDS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		Command* command = Cache::Get()->GetCommand(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(command->ShowShort());
		result.push_back(line);
	}
	return result;
}

Table* Command::getTable() const
{
	return Tables::Get()->COMMANDS;
}
