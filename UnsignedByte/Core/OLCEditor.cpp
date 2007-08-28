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

OLCEditor::GeneralInterpreter::GeneralInterpreter(void)
{
	addWord("new", New::Get());
	addWord("edit", Edit::Get());
	addWord("list", List::Get());
	addWord("commands", Commands::Get());
	addWord("quit", Quit::Get());
	addWord("done", Done::Get());
}

OLCEditor::GeneralInterpreter::~GeneralInterpreter(void)
{
	New::Free();
	Edit::Free();
	List::Free();
	Commands::Free();
	Quit::Free();
	Done::Get();
}

std::string OLCEditor::lookup(const std::string& action)
{
	GeneralAction* act = GeneralInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void OLCEditor::dispatch(const std::string& action, const std::string& argument)
{
	GeneralAction* act = GeneralInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		Global::Get()->bugf("OLCEditor::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}

void OLCEditor::New::Run(OLCEditor* editor, const std::string& argument)
{
	long id = editor->addNew();
	if(!id)
	{
		editor->Sendf("Could not create a new %s!\n", editor->name().c_str());
		return;
	}

	editor->Sendf("%s created! Please give it at least a name!\n", editor->name().c_str());
	editor->setEditing(id);
	return;
}

void OLCEditor::Edit::Run(OLCEditor* editor, const std::string& argument)
{
	if(argument.size() == 0)
	{
		editor->Send("Please specify an id to edit.\n");
		editor->Send("Type 'list' to see a list of available id's.\n");
		editor->Sendf("Type 'new' to create a new %s!\n", editor->name().c_str());
		return;
	}

	int id = atoi(argument.c_str());
	int count = DatabaseMgr::Get()->CountSavable(editor->getTable(), id);

	if(!count)
	{
		editor->Send("Please specify an id to edit.\n");
		editor->Sendf("'%s' is not a valid id!\n", argument.c_str());
		return;
	}

	if(count >= 2)
	{
		Global::Get()->bugf("OLCEditor::Edit::Run(), count for id '%d' is '%d'!\n", id, count);
		editor->Sendf("For some reason there are more than two copy's of id %d known!\n", id);
		editor->Send("Disconnecting you now.\n");
		editor->Disconnect();
		return;
	}

	editor->setEditing(id);
	editor->m_sock->Sendf("You are now editing id %d> ", id);
	editor->m_sock->Send(editor->getEditing()->ShowShort());
	return;
}

void OLCEditor::List::Run(OLCEditor* editor, const std::string& argument)
{
	std::string name = editor->name();
	name.append("s");
	editor->m_sock->Send(String::Get()->box(editor->getList(),name));
	return;
}

void OLCEditor::Commands::Run(OLCEditor* editor, const std::string& argument)
{
	editor->m_sock->Send(String::Get()->box(GeneralInterpreter::Get()->getWords(), editor->name()));
	std::string name = editor->name();
	name.append("Editing");
	editor->m_sock->Send(String::Get()->box(editor->getCommands(), name));
	editor->m_sock->Send("\n");
	return;
}

void OLCEditor::Quit::Run(OLCEditor* editor, const std::string& argument)
{
	editor->m_sock->Send("Ok.\n");
	editor->m_sock->SetEditor(new EditorOLC(editor->m_sock));
	return;
}

void OLCEditor::Done::Run(OLCEditor* editor, const std::string& argument)
{
	editor->m_sock->Send("Ok.\n");
	
	Savable* editing = editor->getEditing();
	if(editing)
		editing->Save();

	editor->setEditing(0);
	return;
}
