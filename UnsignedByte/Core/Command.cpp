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

#include "UBSocket.h"
#include "Command.h"
#include "Global.h"
#include "GrantGroup.h"
#include "GrantGroupManager.h"
#include "PermissionManager.h"
#include "Account.h"
#include "Exceptions.h"
#include "Permission.h"

using mud::Command;

Command::Command(SavableManagerPtr Command) :
m_command(Command)
{
	Assert(Command);
}

Command::~Command(void)
{

}

const std::string& Command::getName() const
{
	return m_command->getfield(db::CommandsFields::Get()->NAME)->getStringValue();
}

long Command::getGrantGroup() const
{
	return m_command->getfield(db::CommandsFields::Get()->GRANTGROUP)->getIntegerValue();
}

bool Command::canHighForce() const
{
	return m_command->getfield(db::CommandsFields::Get()->HIGHFORCE)->getBoolValue();
}

bool Command::canForce() const
{
	return m_command->getfield(db::CommandsFields::Get()->FORCE)->getBoolValue();
}

bool Command::canLowForce() const
{
	return m_command->getfield(db::CommandsFields::Get()->LOWFORCE)->getBoolValue();
}


void Command::setName(const std::string& name)
{
	ValuePtr value(new Value(db::CommandsFields::Get()->NAME, name));
	m_command->setvalue(value);
}

void Command::setGrantGroup(long grantgroup)
{
	ValuePtr value(new Value(db::CommandsFields::Get()->GRANTGROUP, grantgroup));
	m_command->setvalue(value);
}

void Command::setHighForce(bool highforce)
{
	ValuePtr value(new Value(db::CommandsFields::Get()->HIGHFORCE, highforce ? 0 : 1));
	m_command->setvalue(value);
}

void Command::setForce(bool force)
{
	ValuePtr value(new Value(db::CommandsFields::Get()->FORCE, force ? 0 : 1));
	m_command->setvalue(value);
}

void Command::setLowForce(bool lowforce)
{
	ValuePtr value(new Value(db::CommandsFields::Get()->LOWFORCE, lowforce ? 0 : 1));
	m_command->setvalue(value);
}


bool Command::getGrant(UBSocket* sock)
{
	try
	{
		long gid = getGrantGroup();
		long aid = sock->GetAccount()->getID();
		
		PermissionPtr prm = mud::PermissionManager::Get()->GetByKeys(aid, gid);
		return prm->hasGrant();
	}
	catch(RowNotFoundException& e)
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
		GrantGroupPtr grp = mud::GrantGroupManager::Get()->GetByKey(id);
		return grp->getDefaultGrant();
	}
	catch(RowNotFoundException& e)
	{
		Global::Get()->bug(e.what());
		return mud::PermissionManager::Get()->defaultGrant;
	}
}

bool Command::getLog(UBSocket* sock)
{
	try
	{
		long gid = getGrantGroup();
		long aid = sock->GetAccount()->getID();
		
		PermissionPtr prm = mud::PermissionManager::Get()->GetByKeys(aid, gid);
		return prm->hasLog();
	}
	catch(RowNotFoundException& e)
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
		GrantGroupPtr grp = mud::GrantGroupManager::Get()->GetByKey(id);
		return grp->getDefaultLog();
	}
	catch(RowNotFoundException& e)
	{
		Global::Get()->bug(e.what());
		return mud::PermissionManager::Get()->defaultLog;
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
	return m_command->exists();
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

TableImplPtr Command::getTable() const
{
	return m_command->getTable();
}
