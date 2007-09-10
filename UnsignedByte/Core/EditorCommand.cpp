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

EditorCommand::EditorCommand(UBSocket* sock) :
OLCEditor(sock),
m_command(NULL)
{
	GeneralAction* act = Commands::Get();
	act->Run(this, Global::Get()->EmptyString);
	OnLine(Global::Get()->EmptyString);
}

EditorCommand::~EditorCommand(void)
{

}

std::string EditorCommand::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	CommandAction* act = CommandInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorCommand::dispatch(const std::string& action, const std::string& argument)
{
	CommandAction* act = CommandInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_command);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

Savable* EditorCommand::getEditing()
{
	return m_command;
}

Table* EditorCommand::getTable()
{
	return Tables::Get()->COMMANDS;
}

long EditorCommand::addNew()
{
	// return mud::Cache::Get()->AddCommand();
	// TODO - addNew()
	return 0;
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
	addWord("name", Name::Get());
	addWord("grantgroup", GrantGroups::Get());
	addWord("highforce", HighForce::Get());
	addWord("force", Force::Get());
	addWord("lowforce", LowForce::Get());
	addWord("show", Show::Get());
	addWord("save", Save::Get());
}

EditorCommand::CommandInterpreter::~CommandInterpreter(void)
{
	Name::Free();
	GrantGroups::Free();
	HighForce::Get();
	Force::Get();
	LowForce::Get();
	Show::Free();
	Save::Free();
}

void EditorCommand::Name::Run(UBSocket* sock, const std::string& argument, Command* command)
{
	if(argument.size() == 0)
	{
		sock->Send("Command name can't be zero length!\n");
		return;
	}

	sock->Sendf("Command name changed from '%s' to '%s'.\n", command->getName().c_str(), argument.c_str());
	command->setName(argument);
	return;
}

void EditorCommand::GrantGroups::Run(UBSocket* sock, const std::string& argument, Command* command)
{
	if(!command->Exists())
	{
		sock->Send("For some reason the command you are editing does not exist.\n");
		return;
	}

	long id = db::GrantGroups::lookupname(argument);
	if(!id)
	{
		sock->Sendf("'%s' is not a valid grantgroup!\n", argument.c_str());
		sock->Send(String::Get()->box(mud::GrantGroup::List(), "GrantGroups"));
		return;
	}

	sock->Sendf("Grantgroup changed from '%d' to '%d'.\n", command->getGrantGroup(), id);
	command->setGrantGroup(id);
	return;
}

void EditorCommand::HighForce::Run(UBSocket* sock, const std::string& argument, Command* command)
{
	if(!argument.compare("Enable"))
	{
		command->setHighForce(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		command->setHighForce(false);
		return;
	}

	sock->Send("Please specify a force level!\n");
	sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorCommand::Force::Run(UBSocket* sock, const std::string& argument, Command* command)
{
	if(!argument.compare("Enable"))
	{
		command->setForce(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		command->setForce(false);
		return;
	}

	sock->Send("Please specify a force level!\n");
	sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorCommand::LowForce::Run(UBSocket* sock, const std::string& argument, Command* command)
{
	if(!argument.compare("Enable"))
	{
		command->setLowForce(true);
		return;
	}
	
	if(!argument.compare("Disable"))
	{
		command->setLowForce(false);
		return;
	}

	sock->Send("Please specify a force level!\n");
	sock->Send("Choose between 'Enable' and 'Disable'.\n");
	return;
}

void EditorCommand::Show::Run(UBSocket* sock, const std::string& argument, Command* command)
{
	sock->Send(String::Get()->box(command->Show(),"Command"));
	return;
}

void EditorCommand::Save::Run(UBSocket* sock, const std::string& argument, Command* command)
{
	sock->Sendf("Saving command '%s'.\n", command->getName().c_str());
	command->Save();
	sock->Send("Saved.\n");
	return;
}

