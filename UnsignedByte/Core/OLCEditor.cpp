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

#include "OLCEditor.h"
#include "DatabaseMgr.h"
#include "UBSocket.h"
#include "StringUtilities.h"
#include "Savable.h"

#include "EditorOLC.h"
#include "Command.h"
#include "Permission.h"
#include "Parse.h"
#include "Cache.h"
#include "Account.h" // needed because we include UBSocket.h

#include "Table.h"
#include "Tables.h"

OLCEditor::SavableCommand OLCEditor::m_listCommands("Commands", &OLCEditor::listCommands);
OLCEditor::SavableCommand OLCEditor::m_newSavable("New", &OLCEditor::newSavable);
OLCEditor::SavableCommand OLCEditor::m_deleteSavable("Delete", &OLCEditor::deleteSavable);
OLCEditor::SavableCommand OLCEditor::m_editSavable("Edit", &OLCEditor::editSavable);
OLCEditor::SavableCommand OLCEditor::m_quitEditor("Quit", &OLCEditor::quitEditor);
OLCEditor::SavableCommand OLCEditor::m_doneEditing("Done", &OLCEditor::doneEditing);
OLCEditor::SavableCommand OLCEditor::m_listSavable("List", &OLCEditor::listSavable);

OLCEditor::GeneralInterpreter::GeneralInterpreter(void)
{
	addWord("new", &m_newSavable);
	addWord("edit", &m_editSavable);
	addWord("list", &m_listSavable);
	addWord("commands", &m_listCommands);
	addWord("quit", &m_quitEditor);
	addWord("done", &m_doneEditing);
}

OLCEditor::GeneralInterpreter::~GeneralInterpreter(void)
{

}

std::string OLCEditor::lookup(const std::string& action)
{
	SavableCommand* act = GeneralInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void OLCEditor::dispatch(const std::string& action, const std::string& argument)
{
	SavableCommand* act = GeneralInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		Global::Get()->bugf("OLCEditor::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}

void OLCEditor::newSavable(const std::string& argument)
{
	KeysPtr keys = addNew();
	if(!keys->size())
	{
		Sendf("Could not create a new %s!\n", name().c_str());
		return;
	}

	Sendf("%s created!\n", name().c_str());
	setEditing(keys);
	return;
}

void OLCEditor::editSavable(const std::string& argument)
{
	TableImplPtr table = getTable();
	
	if(argument.size() == 0)
	{
		Send("Please specify an id to edit.\n");
		Send("Type 'list' to see a list of available id's.\n");
		Sendf("Type 'new' to create a new %s!\n", name().c_str());
		return;
	}
	
	KeysPtr keys;
	
	try
	{
		keys = new Keys(table, argument);
	}
	catch(std::invalid_argument& e)
	{
		Send("Please specify an id to edit.\n");
		Sendf("'%s' is not a valid id.\n", argument.c_str());
		return;
	}
	
	int count = DatabaseMgr::Get()->CountSavable(table, keys);

	if(!count)
	{
		Send("Please specify an id to edit.\n");
		Sendf("'%s' is not a valid id!\n", argument.c_str());
		return;
	}

	if(count >= 2)
	{
		Global::Get()->bugf("OLCEditor::editSavable(), count for id '%s' is '%d'!\n", argument.c_str(), count);
		Sendf("For some reason there are more than two copy's of id %s known!\n", argument.c_str());
		Send("Disconnecting you now.\n");
		Disconnect();
		return;
	}

	setEditing(keys);
	m_sock->Sendf("You are now editing id %s> ", argument.c_str());
	m_sock->Send(getEditing()->ShowShort());
	m_sock->Send("\n");
	return;
}

void OLCEditor::deleteSavable(const std::string& argument)
{
	if(argument.size() == 0)
	{
		Send("Please specify an id to delete.\n");
		Send("Type 'list' to see a list of available id's.\n");
		return;
	}

	KeysPtr keys;

	try
	{
		keys = new Keys(getTable(), argument);
	}
	catch(std::invalid_argument& e)
	{
		Send("Please specify an id to edit.\n");
		Sendf("'%s' is not a valid id.\n", argument.c_str());
	}


	int count = DatabaseMgr::Get()->CountSavable(getTable(), keys);

	if(!count)
	{
		Send("Please specify an id to delete.\n");
		Sendf("'%s' (%d) is not a valid id!\n", argument.c_str(), keys->toString().c_str());
		return;
	}

	if(count >= 2)
	{
		Global::Get()->bugf("OLCEditor::deleteSavable(), count for id '%s' is '%d'!\n", keys->toString().c_str(), count);
		Sendf("For some reason there are more than two copy's of id %s known!\n", keys->toString().c_str());
		Send("Disconnecting you now.\n");
		Disconnect();
		return;
	}

	SavableManagerPtr manager = SavableManager::bykeys(getTable(), keys);
	manager->erase();

	m_sock->Sendf("Deleted id %s.\n", keys->toString().c_str());
	m_sock->Send("\n");
	return;
}

void OLCEditor::listSavable(const std::string& argument)
{
	std::string name = this->name();
	name.append("s");
	Strings list = getList();
	if(list.size())
		m_sock->Send(String::Get()->box(list,name));
	else
		m_sock->Sendf("No %ss.\n", this->name().c_str());
	return;
}

void OLCEditor::listCommands(const std::string& argument)
{
	m_sock->Send(String::Get()->box(GeneralInterpreter::Get()->getWords(), name()));
	std::string name = this->name();
	name.append("Editing");
	m_sock->Send(String::Get()->box(getCommands(), name));
	m_sock->Send("\n");
	return;
}

void OLCEditor::quitEditor(const std::string& argument)
{
	m_sock->Send("Ok.\n");
	m_sock->PopEditor();
	return;
}

void OLCEditor::doneEditing(const std::string& argument)
{
	m_sock->Send("Ok.\n");
	
	SavablePtr editing = getEditing();
	if(editing)
		editing->Save();

	setEditing(0);
	return;
}
