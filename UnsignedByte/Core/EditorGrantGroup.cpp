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

EditorGrantGroup::EditorGrantGroup(UBSocket* sock) :
OLCEditor(sock),
m_grantgroup(NULL)
{
	GeneralAction* act = Commands::Get();
	act->Run(this, Global::Get()->EmptyString);
	OnLine(Global::Get()->EmptyString);
}

EditorGrantGroup::~EditorGrantGroup(void)
{

}

std::string EditorGrantGroup::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	GrantGroupAction* act = GrantGroupInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorGrantGroup::dispatch(const std::string& action, const std::string& argument)
{
	GrantGroupAction* act = GrantGroupInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_grantgroup);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

Savable* EditorGrantGroup::getEditing()
{
	return m_grantgroup;
}

Table* EditorGrantGroup::getTable()
{
	return Tables::Get()->GRANTGROUPS;
}

long EditorGrantGroup::addNew()
{
	// return mud::Cache::Get()->AddGrantGroup();
	// TODO - addNew()
	return 0;
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
	addWord("name", Name::Get());
	addWord("show", Show::Get());
	addWord("save", Save::Get());
}

EditorGrantGroup::GrantGroupInterpreter::~GrantGroupInterpreter(void)
{
	Name::Free();
	Show::Free();
	Save::Free();
}

void EditorGrantGroup::Name::Run(UBSocket* sock, const std::string& argument, GrantGroup* grantgroup)
{
	if(argument.size() == 0)
	{
		sock->Send("GrantGroup name can't be zero length!\n");
		return;
	}

	sock->Sendf("GrantGroup name changed from '%s' to '%s'.\n", grantgroup->getName().c_str(), argument.c_str());
	grantgroup->setName(argument);
	return;
}

void EditorGrantGroup::Show::Run(UBSocket* sock, const std::string& argument, GrantGroup* grantgroup)
{
	sock->Send(String::Get()->box(grantgroup->Show(),"GrantGroup"));
	return;
}

void EditorGrantGroup::Save::Run(UBSocket* sock, const std::string& argument, GrantGroup* grantgroup)
{
	sock->Sendf("Saving grantgroup '%s'.\n", grantgroup->getName().c_str());
	grantgroup->Save();
	sock->Send("Saved.\n");
	return;
}
