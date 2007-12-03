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

#include "EditorCommand.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Action.h"

#include "Account.h"
#include "Command.h"
#include "GrantGroup.h"

using mud::Command;

EditorCommand::CommandCommand EditorCommand::m_editName("Name", &EditorCommand::editName);
EditorCommand::CommandCommand EditorCommand::m_editGrantGroups("GrantGroup", &EditorCommand::editGrantGroups);
EditorCommand::CommandCommand EditorCommand::m_editHighForce("HighForce", &EditorCommand::editHighForce);
EditorCommand::CommandCommand EditorCommand::m_editForce("Force", &EditorCommand::editForce);
EditorCommand::CommandCommand EditorCommand::m_editLowForce("LowForce", &EditorCommand::editLowForce);
EditorCommand::CommandCommand EditorCommand::m_showCommand("Show", &EditorCommand::showCommand);
EditorCommand::CommandCommand EditorCommand::m_saveCommand("Save", &EditorCommand::saveCommand);

EditorCommand::EditorCommand(UBSocket* sock) :
OLCEditor(sock),
m_command(NULL)
{
	SavableCommand* act = &OLCEditor::m_listCommands;
	act->Run(this, Global::Get()->EmptyString);
}

EditorCommand::~EditorCommand(void)
{

}

std::string EditorCommand::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	CommandCommand* act = CommandInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorCommand::dispatch(const std::string& action, const std::string& argument)
{
	CommandCommand* act = CommandInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorCommand::getEditing()
{
	return m_command;
}

TablePtr EditorCommand::getTable()
{
	return Tables::Get()->COMMANDS;
}

long EditorCommand::addNew()
{
	return mud::Cache::Get()->AddCommand();
}

std::vector<std::string> EditorCommand::getList()
{
	return Command::List();
}

void EditorCommand::setEditing(long id)
{
	if(id == 0)
	{
		m_command = NULL;
		return;
	}
	
	m_command = mud::Cache::Get()->GetCommandByKey(id);
	return;
}

std::vector<std::string> EditorCommand::getCommands()
{
	return CommandInterpreter::Get()->getWords();
}

EditorCommand::CommandInterpreter::CommandInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("grantgroup", &m_editGrantGroups);
	addWord("highforce", &m_editHighForce);
	addWord("force", &m_editForce);
	addWord("lowforce", &m_editLowForce);
	addWord("show", &m_showCommand);
	addWord("save", &m_saveCommand);
}

EditorCommand::CommandInterpreter::~CommandInterpreter(void)
{

}

void EditorCommand::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Command name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Command name changed from '%s' to '%s'.\n", m_command->getName().c_str(), argument.c_str());
	m_command->setName(argument);
	return;
}

void EditorCommand::editGrantGroups(const std::string& argument)
{
	if(!m_command->Exists())
	{
		m_sock->Send("For some reason the command you are editing does not exist.\n");
		return;
	}

	long id = db::GrantGroups::lookupname(argument);
	if(!id)
	{
		m_sock->Sendf("'%s' is not a valid grantgroup!\n", argument.c_str());
		m_sock->Send(String::Get()->box(mud::GrantGroup::List(), "GrantGroups"));
		return;
	}

	m_sock->Sendf("Grantgroup changed from '%d' to '%d'.\n", m_command->getGrantGroup(), id);
	m_command->setGrantGroup(id);
	return;
}

void EditorCommand::editHighForce(const std::string& argument)
{
	if(!argument.compare("Enable"))
	{
		m_command->setHighForce(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		m_command->setHighForce(false);
		return;
	}

	m_sock->Send("Please specify a force level!\n");
	m_sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorCommand::editForce(const std::string& argument)
{
	if(!argument.compare("Enable"))
	{
		m_command->setForce(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		m_command->setForce(false);
		return;
	}

	m_sock->Send("Please specify a force level!\n");
	m_sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorCommand::editLowForce(const std::string& argument)
{
	if(!argument.compare("Enable"))
	{
		m_command->setLowForce(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		m_command->setLowForce(false);
		return;
	}

	m_sock->Send("Please specify a force level!\n");
	m_sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorCommand::showCommand(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_command->Show(),"Command"));
	return;
}

void EditorCommand::saveCommand(const std::string& argument)
{
	m_sock->Sendf("Saving command '%s'.\n", m_command->getName().c_str());
	m_command->Save();
	m_sock->Send("Saved.\n");
	return;
}

