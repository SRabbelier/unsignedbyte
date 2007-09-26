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

#include "EditorMobile.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Action.h"

#include "Account.h"
#include "MCharacter.h"

EditorMobile::EditorMobile(UBSocket* sock) :
OLCEditor(sock),
m_mobile(NULL)
{
	GeneralAction* act = Commands::Get();
	act->Run(this, Global::Get()->EmptyString);
	OnLine(Global::Get()->EmptyString);
}

EditorMobile::~EditorMobile(void)
{

}

std::string EditorMobile::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	MobileAction* act = MobileInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorMobile::dispatch(const std::string& action, const std::string& argument)
{
	MobileAction* act = MobileInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_mobile);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorMobile::getEditing()
{
	return m_mobile;
}

TablePtr EditorMobile::getTable()
{
	return Tables::Get()->CHARACTERS;
}

long EditorMobile::addNew()
{
	return mud::Cache::Get()->AddCharacter();
}

std::vector<std::string> EditorMobile::getList()
{
	return mud::MCharacter::List();
}

void EditorMobile::setEditing(long id)
{
	if(id == 0)
	{
		m_mobile = NULL;
		return;
	}
	
	m_mobile = mud::Cache::Get()->GetMCharacterByKey(id);
	return;
}

std::vector<std::string> EditorMobile::getCommands()
{
	return MobileInterpreter::Get()->getWords();
}

EditorMobile::MobileInterpreter::MobileInterpreter(void)
{
	addWord("name", Name::Get());
	addWord("description", Description::Get());
	addWord("show", Show::Get());
	addWord("save", Save::Get());
}

EditorMobile::MobileInterpreter::~MobileInterpreter(void)
{
	Name::Free();
	Description::Free();
	Show::Free();
	Save::Free();
}

void EditorMobile::Name::Run(UBSocket* sock, const std::string& argument, mud::MCharacter* mobile)
{
	if(argument.size() == 0)
	{
		sock->Send("Mobile name can't be zero length!\n");
		return;
	}

	sock->Sendf("Mobile name changed from '%s' to '%s'.\n", mobile->getName().c_str(), argument.c_str());
	mobile->setName(argument);
	return;
}

void EditorMobile::Description::Run(UBSocket* sock, const std::string& argument, mud::MCharacter* mobile)
{
	if(!mobile->Exists())
	{
		sock->Send("For some reason the mobile you are editing does not exist.\n");
		return;
	}

	if(argument.size() == 0)
	{
		sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	sock->Sendf("Mobile description changed from '%s' to '%s'.\n", mobile->getDescription().c_str(), argument.c_str());
	mobile->setDescription(argument);
	return;
}

void EditorMobile::Show::Run(UBSocket* sock, const std::string& argument, mud::MCharacter* mobile)
{
	sock->Send(String::Get()->box(mobile->Show(), "Mobile"));
	return;
}

void EditorMobile::Save::Run(UBSocket* sock, const std::string& argument, mud::MCharacter* mobile)
{
	sock->Sendf("Saving mobile '%s'.\n", mobile->getName().c_str());
	mobile->Save();
	sock->Send("Saved.\n");
	return;
}
