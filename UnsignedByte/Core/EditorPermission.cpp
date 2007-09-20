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

#include <vector>
#include <string>

#include "EditorPermission.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Action.h"

#include "Account.h"
#include "Permission.h"
#include "GrantGroup.h"

using mud::Permission;

EditorPermission::EditorPermission(UBSocket* sock) :
OLCEditor(sock),
m_permission(NULL)
{
	GeneralAction* act = Commands::Get();
	act->Run(this, Global::Get()->EmptyString);
	OnLine(Global::Get()->EmptyString);
}

EditorPermission::~EditorPermission(void)
{

}

std::string EditorPermission::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	PermissionAction* act = PermissionInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorPermission::dispatch(const std::string& action, const std::string& argument)
{
	PermissionAction* act = PermissionInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_permission);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

Savable* EditorPermission::getEditing()
{
	return m_permission;
}

Table* EditorPermission::getTable()
{
	return Tables::Get()->PERMISSIONS;
}

long EditorPermission::addNew()
{
	// TODO - TwoKey addNew()
	return 0;
}

std::vector<std::string> EditorPermission::getList()
{
	return Permission::List();
}

void EditorPermission::setEditing(long id)
{
	if(id == 0)
	{
		m_permission = NULL;
		return;
	}
	
	// TODO - TwoKey setEditing()
	return;
}

std::vector<std::string> EditorPermission::getCommands()
{
	return PermissionInterpreter::Get()->getWords();
}

EditorPermission::PermissionInterpreter::PermissionInterpreter(void)
{
	addWord("account", Accounts::Get());
	addWord("grantgroup", GrantGroups::Get());
	addWord("grant", Grants::Get());
	addWord("show", Show::Get());
	addWord("save", Save::Get());
}

EditorPermission::PermissionInterpreter::~PermissionInterpreter(void)
{
	Accounts::Free();
	GrantGroups::Free();
	Grants::Free();
	Show::Free();
	Save::Free();
}

void EditorPermission::Accounts::Run(UBSocket* sock, const std::string& argument, Permission* permission)
{
	if(argument.size() == 0)
	{
		sock->Send("Please specify an account!\n");
		return;
	}

	long id = db::Accounts::lookupname(argument);
	if(!id)
	{
		sock->Sendf("'%s' is not a valid account!\n", argument.c_str());
		sock->Send(String::Get()->box(mud::Account::List(), "Accounts"));
		return;
	}

	sock->Sendf("Preparing to edit permission with account '%d'.\n", id);
	m_account = id;
	return;
}

void EditorPermission::GrantGroups::Run(UBSocket* sock, const std::string& argument, Permission* permission)
{
	if(argument.size() == 0)
	{
		sock->Send("Please specify a grantgroup!\n");
		return;
	}

	long id = db::GrantGroups::lookupname(argument);
	if(!id)
	{
		sock->Sendf("'%s' is not a valid grantgroup!\n", argument.c_str());
		sock->Send(String::Get()->box(mud::GrantGroup::List(), "GrantGroups"));
		return;
	}

	sock->Sendf("Preparing to edit permission with grangroup '%d'.\n", id);
	m_grantgroup = id
	return;
}

void EditorPermission::Grants::Run(UBSocket* sock, const std::string& argument, Permission* permission)
{
	if(!argument.compare("Enable"))
	{
		permission->setGrant(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		permission->setGrant(false);
		return;
	}

	sock->Send("Please specify a grant level!\n");
	sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorPermission::Logging::Run(UBSocket* sock, const std::string& argument, Permission* permission)
{
	if(!argument.compare("Enable"))
	{
		permission->setLog(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		permission->setLog(false);
		return;
	}
	
	sock->Send("Please specify a log level!\n");
	sock->Send("Choose bewteen 'Enable' and 'Disable'.\n");
	return;
}

void EditorPermission::Save::Run(UBSocket* sock, const std::string& argument, Permission* permission)
{
	sock->Send("Saving...\n");
	permission->Save();
	sock->Send("Saved.\n");
	return;
}

void EditorPermission::Show::Run(UBSocket* sock, const std::string& argument, Permission* permission)
{
	sock->Send(String::Get()->box(permission->Show(), "Permission"));
}
