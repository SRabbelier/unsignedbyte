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

#include "EditorMobile.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "TableImpls.h"

#include "Account.h"
#include "MCharacter.h"
#include "MCharacterManager.h"
#include "CharacterManager.h"

EditorMobile::MobileCommand EditorMobile::m_editName("Name", &EditorMobile::editName);
EditorMobile::MobileCommand EditorMobile::m_editDescription("Description", &EditorMobile::editDescription);
EditorMobile::MobileCommand EditorMobile::m_showMobile("Show", &EditorMobile::showMobile);
EditorMobile::MobileCommand EditorMobile::m_saveMobile("Save", &EditorMobile::saveMobile);

EditorMobile::EditorMobile(UBSocket* sock) :
OLCEditor(sock),
m_mobile()
{
	listCommands(Global::Get()->EmptyString);
}

EditorMobile::~EditorMobile(void)
{

}

std::string EditorMobile::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	MobileCommand* act = MobileInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorMobile::dispatch(const std::string& action, const std::string& argument)
{
	MobileCommand* act = MobileInterpreter::Get()->translate(action);
	
	if(act && !m_mobile)
	{
		m_sock->Send("You need to be editing a mobile first.\n");
		m_sock->Send("(Use the 'edit' command.)\n");
		return;
	}
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorMobile::getEditing()
{
	return m_mobile;
}

TableImplPtr EditorMobile::getTable()
{
	return db::TableImpls::Get()->ENTITIES;
}

KeysPtr EditorMobile::addNew()
{
	return mud::CharacterManager::Get()->Add();
}

std::vector<std::string> EditorMobile::getList()
{
	return mud::CharacterManager::Get()->List();
}

void EditorMobile::setEditing(KeysPtr keys)
{
	if(!keys->size())
	{
		m_mobile.reset();
		return;
	}
	
	m_mobile = mud::MCharacterManager::Get()->GetByKey(keys->first()->getValue());
	return;
}

std::vector<std::string> EditorMobile::getCommands()
{
	return MobileInterpreter::Get()->getWords();
}

EditorMobile::MobileInterpreter::MobileInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("description", &m_editDescription);
	addWord("show", &m_showMobile);
	addWord("save", &m_saveMobile);
}

EditorMobile::MobileInterpreter::~MobileInterpreter(void)
{

}

void EditorMobile::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Mobile name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Mobile name changed from '%s' to '%s'.\n", m_mobile->getName().c_str(), argument.c_str());
	m_mobile->setName(argument);
	return;
}

void EditorMobile::editDescription(const std::string& argument)
{
	if(!m_mobile->Exists())
	{
		m_sock->Send("For some reason the mobile you are editing does not exist.\n");
		return;
	}

	if(argument.size() == 0)
	{
		m_sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	m_sock->Sendf("Mobile description changed from '%s' to '%s'.\n", m_mobile->getDescription().c_str(), argument.c_str());
	m_mobile->setDescription(argument);
	return;
}

void EditorMobile::showMobile(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_mobile->Show(), "Mobile"));
	return;
}

void EditorMobile::saveMobile(const std::string& argument)
{
	m_sock->Sendf("Saving mobile '%s'.\n", m_mobile->getName().c_str());
	m_mobile->Save();
	m_sock->Send("Saved.\n");
	return;
}
