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

#include "EditorGrantGroup.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Action.h"

#include "Account.h"
#include "GrantGroup.h"

using mud::GrantGroup;

EditorGrantGroup::GrantGroupCommand EditorGrantGroup::m_editName("Name", &EditorGrantGroup::editName);
EditorGrantGroup::GrantGroupCommand EditorGrantGroup::m_editImplication("Description", &EditorGrantGroup::editImplication);
EditorGrantGroup::GrantGroupCommand EditorGrantGroup::m_showGrantGroup("Show", &EditorGrantGroup::showGrantGroup);
EditorGrantGroup::GrantGroupCommand EditorGrantGroup::m_saveGrantGroup("Save", &EditorGrantGroup::saveGrantGroup);

EditorGrantGroup::EditorGrantGroup(UBSocket* sock) :
OLCEditor(sock),
m_grantgroup(NULL)
{
	listCommands(Global::Get()->EmptyString);
}

EditorGrantGroup::~EditorGrantGroup(void)
{

}

std::string EditorGrantGroup::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	GrantGroupCommand* act = GrantGroupInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorGrantGroup::dispatch(const std::string& action, const std::string& argument)
{
	GrantGroupCommand* act = GrantGroupInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorGrantGroup::getEditing()
{
	return m_grantgroup;
}

TablePtr EditorGrantGroup::getTable()
{
	return Tables::Get()->GRANTGROUPS;
}

long EditorGrantGroup::addNew()
{
	return mud::Cache::Get()->AddGrantGroup();
}

std::vector<std::string> EditorGrantGroup::getList()
{
	return GrantGroup::List();
}

void EditorGrantGroup::setEditing(long id)
{
	if(id == 0)
	{
		m_grantgroup = NULL;
		return;
	}
	
	m_grantgroup = mud::Cache::Get()->GetGrantGroupByKey(id);
	return;
}

std::vector<std::string> EditorGrantGroup::getCommands()
{
	return GrantGroupInterpreter::Get()->getWords();
}

EditorGrantGroup::GrantGroupInterpreter::GrantGroupInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("implication", &m_editImplication);
	addWord("show", &m_showGrantGroup);
	addWord("save", &m_saveGrantGroup);
}

EditorGrantGroup::GrantGroupInterpreter::~GrantGroupInterpreter(void)
{

}

void EditorGrantGroup::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("GrantGroup name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("GrantGroup name changed from '%s' to '%s'.\n", m_grantgroup->getName().c_str(), argument.c_str());
	m_grantgroup->setName(argument);
	return;
}

void EditorGrantGroup::editImplication(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Please specify the implicated grantgroup!\n");
		return;
	}

	int implication = atoi(argument.c_str());
	if(implication <= 0)
	{
		m_sock->Sendf("Please specify an implication > 0!\n");
		return;
	}

	m_sock->Sendf("GrantGroup implication changed from '%d' to '%d'.\n", m_grantgroup->getImplication(), implication);
	m_grantgroup->setImplication(implication);
}

void EditorGrantGroup::showGrantGroup(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_grantgroup->Show(),"GrantGroup"));
	return;
}

void EditorGrantGroup::saveGrantGroup(const std::string& argument)
{
	m_sock->Sendf("Saving grantgroup '%s'.\n", m_grantgroup->getName().c_str());
	m_grantgroup->Save();
	m_sock->Send("Saved.\n");
	return;
}
