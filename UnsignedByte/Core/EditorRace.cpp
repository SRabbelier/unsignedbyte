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

#include "EditorRace.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "TableImpls.h"

#include "Account.h"
#include "Race.h"
#include "RaceManager.h"

EditorRace::RaceCommand EditorRace::m_editName("Name", &EditorRace::editName);
EditorRace::RaceCommand EditorRace::m_showRace("Show", &EditorRace::showRace);
EditorRace::RaceCommand EditorRace::m_saveRace("Save", &EditorRace::saveRace);

EditorRace::EditorRace(UBSocket* sock) :
OLCEditor(sock),
m_race()
{
	listCommands(Global::Get()->EmptyString);
}

EditorRace::~EditorRace(void)
{

}

std::string EditorRace::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	RaceCommand* act = RaceInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorRace::dispatch(const std::string& action, const std::string& argument)
{
	RaceCommand* act = RaceInterpreter::Get()->translate(action);
	
	if(act && !m_race)
	{
		m_sock->Send("You need to be editing an race first.\n");
		m_sock->Send("(Use the 'edit' command.)\n");
		return;
	}
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorRace::getEditing()
{
	return m_race;
}

TableImplPtr EditorRace::getTable()
{
	return db::TableImpls::Get()->RACES;
}

KeysPtr EditorRace::addNew()
{
	return mud::RaceManager::Get()->Add();
}

std::vector<std::string> EditorRace::getList()
{
	return mud::RaceManager::Get()->List();
}

void EditorRace::setEditing(KeysPtr keys)
{
	if(!keys->size())
	{
		m_race.reset();
		return;
	}
	
	m_race = mud::RaceManager::Get()->GetByKey(keys->first()->getValue());
	return;
}

std::vector<std::string> EditorRace::getCommands()
{
	return RaceInterpreter::Get()->getWords();
}

EditorRace::RaceInterpreter::RaceInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("show", &m_showRace);
	addWord("save", &m_saveRace);
}

EditorRace::RaceInterpreter::~RaceInterpreter(void)
{

}

void EditorRace::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Race name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Race name changed from '%s' to '%s'.\n", m_race->getName().c_str(), argument.c_str());
	m_race->setName(argument);
	return;
}

void EditorRace::showRace(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_race->Show(), "Race"));
}

void EditorRace::saveRace(const std::string& argument)
{
	m_sock->Sendf("Saving race '%s'.\n", m_race->getName().c_str());
	m_race->Save();
	m_sock->Send("Saved.\n");
	return;
}
