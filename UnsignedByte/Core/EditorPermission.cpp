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

#include "EditorPermission.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "TableImpls.h"
#include "Exceptions.h"

#include "Account.h"
#include "AccountManager.h"
#include "Permission.h"
#include "PermissionManager.h"
#include "GrantGroup.h"
#include "GrantGroupManager.h"

using mud::Permission;
		
EditorPermission::PermissionCommand EditorPermission::m_editAccount("Account", &EditorPermission::editAccount);
EditorPermission::PermissionCommand EditorPermission::m_editGrantGroup("GrantGroup", &EditorPermission::editGrantGroup);
EditorPermission::PermissionCommand EditorPermission::m_editGrant("Grant", &EditorPermission::editGrant);
EditorPermission::PermissionCommand EditorPermission::m_editLogging("Logging", &EditorPermission::editLogging);
EditorPermission::PermissionCommand EditorPermission::m_showPermission("Show", &EditorPermission::showPermission);
EditorPermission::PermissionCommand EditorPermission::m_savePermission("Save", &EditorPermission::savePermission);

EditorPermission::EditorPermission(UBSocket* sock) :
OLCEditor(sock),
m_permission()
{
	listCommands(Global::Get()->EmptyString);
}

EditorPermission::~EditorPermission(void)
{

}

std::string EditorPermission::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	PermissionCommand* act = PermissionInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorPermission::dispatch(const std::string& action, const std::string& argument)
{
	PermissionCommand* act = PermissionInterpreter::Get()->translate(action);
	
	if(act && !m_permission)
	{
		m_sock->Send("You need to be editing a permission first.\n");
		m_sock->Send("(Use the 'edit' command.)\n");
		return;
	}
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorPermission::getEditing()
{
	return m_permission;
}

TableImplPtr EditorPermission::getTable()
{
	return db::TableImpls::Get()->PERMISSIONS;
}

KeysPtr EditorPermission::addNew()
{
	throw std::runtime_error("EditorPermission::addNew(), Not yet implemented.");
}

std::vector<std::string> EditorPermission::getList()
{
	return mud::PermissionManager::Get()->List();
}

void EditorPermission::setEditing(KeysPtr keys)
{
	if(!keys->size())
	{
		m_permission.reset();
		return;
	}
	
	mud::PermissionPtr permission = mud::PermissionManager::Get()->GetByKeys(keys);
	m_permission = permission;
	return;
}

std::vector<std::string> EditorPermission::getCommands()
{
	return PermissionInterpreter::Get()->getWords();
}

EditorPermission::PermissionInterpreter::PermissionInterpreter(void)
{
	addWord("account", &m_editAccount);
	addWord("grantgroup", &m_editGrantGroup);
	addWord("grant", &m_editGrant);
	addWord("logging", &m_editLogging);
	addWord("show", &m_showPermission);
	addWord("save", &m_savePermission);
}

EditorPermission::PermissionInterpreter::~PermissionInterpreter(void)
{
	
}

void EditorPermission::editAccount(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Please specify an account!\n");
		return;
	}

	try
	{
		long id = mud::AccountManager::Get()->lookupByName(argument);
		m_sock->Sendf("Preparing to edit permission with account '%d'.\n", id);
		m_account = id;
	}
	catch(RowNotFoundException& e)
	{
		m_sock->Sendf("'%s' is not a valid account!\n", argument.c_str());
		m_sock->Send(String::Get()->box(mud::AccountManager::Get()->List(), "Accounts"));
	}
}

void EditorPermission::editGrantGroup(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Please specify a grantgroup!\n");
		return;
	}

	try
	{
		long id = mud::GrantGroupManager::Get()->lookupByName(argument);
		m_sock->Sendf("Preparing to edit permission with grangroup '%d'.\n", id);
		m_grantgroup = id;
	}
	catch(RowNotFoundException& e)
	{
		m_sock->Sendf("'%s' is not a valid grantgroup!\n", argument.c_str());
		m_sock->Send(String::Get()->box(mud::GrantGroupManager::Get()->List(), "GrantGroups"));
	}
}

void EditorPermission::editGrant(const std::string& argument)
{
	if(!argument.compare("Enable"))
	{
		m_permission->setGrant(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		m_permission->setGrant(false);
		return;
	}

	m_sock->Send("Please specify a grant level!\n");
	m_sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorPermission::editLogging(const std::string& argument)
{
	if(!argument.compare("Enable"))
	{
		m_permission->setLog(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		m_permission->setLog(false);
		return;
	}
	
	m_sock->Send("Please specify a log level!\n");
	m_sock->Send("Choose bewteen 'Enable' and 'Disable'.\n");
	return;
}

void EditorPermission::savePermission(const std::string& argument)
{
	m_sock->Send("Saving...\n");
	m_permission->Save();
	m_sock->Send("Saved.\n");
	return;
}

void EditorPermission::showPermission(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_permission->Show(), "Permission"));
}
