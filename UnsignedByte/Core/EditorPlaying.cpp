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

#include "EditorAccount.h"
#include "EditorPlaying.h"
#include "UBSocket.h"

#include "StringUtilities.h"
#include "Exceptions.h"

#include "Account.h"
#include "Character.h"
#include "PCharacter.h"
#include "PCharacterManager.h"
#include "Room.h"
#include "RoomManager.h"

using mud::PCharacter;

EditorPlaying::PlayingCommand EditorPlaying::m_listAreas("Areas", &EditorPlaying::listAreas);
EditorPlaying::PlayingCommand EditorPlaying::m_listColours("Colours", &EditorPlaying::listColours);
EditorPlaying::PlayingCommand EditorPlaying::m_listCommands("Commands", &EditorPlaying::listCommands);
EditorPlaying::PlayingCommand EditorPlaying::m_listRaces("Races", &EditorPlaying::listRaces);
EditorPlaying::PlayingCommand EditorPlaying::m_listRooms("Rooms", &EditorPlaying::listRooms);
EditorPlaying::PlayingCommand EditorPlaying::m_showScore("Score", &EditorPlaying::showScore);
EditorPlaying::PlayingCommand EditorPlaying::m_look("Look", &EditorPlaying::look);
EditorPlaying::PlayingCommand EditorPlaying::m_say("Say", &EditorPlaying::say);
EditorPlaying::PlayingCommand EditorPlaying::m_deleteCharacter("Delete", &EditorPlaying::deleteCharacter);
EditorPlaying::PlayingCommand EditorPlaying::m_quitEditor("Quit", &EditorPlaying::quitEditor);

EditorPlaying::EditorPlaying(UBSocket* sock, mud::PCharacterPtr character) :
Editor(sock),
m_char(character)
{
	try
	{
		long id = m_char->getRoom();
		mud::RoomPtr inroom = mud::RoomManager::Get()->GetByKey(id);
		inroom->addCharacter(m_char->getID());
	
		inroom->Sendf("%s enters the realm.\n", m_char->getName().c_str());
	}
	catch(RowNotFoundException& e)
	{
		Global::Get()->bug(e.what());
	}
	m_char->OnSend(String::Get()->box(PlayingInterpreter::Get()->getWords(), "Playing"));
}

EditorPlaying::~EditorPlaying(void)
{
	m_char->Save();
	mud::PCharacterManager::Get()->UnloadByKey(m_char->getID());
}

std::string EditorPlaying::lookup(const std::string& action)
{
	PlayingCommand* act = PlayingInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorPlaying::dispatch(const std::string& action, const std::string& argument)
{
	PlayingCommand* act = PlayingInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		Global::Get()->bugf("EditorPlaying::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}

EditorPlaying::PlayingInterpreter::PlayingInterpreter(void)
{
	addWord("areas", &m_listAreas);
	addWord("colours", &m_listColours);
	addWord("commands", &m_listCommands);
	addWord("look", &m_look);
	addWord("races", &m_listRaces);
	addWord("rooms", &m_listRooms);
	addWord("score", &m_showScore);
	addWord("say", &m_say);
	addWord("delete", &m_deleteCharacter);
	addWord("quit", &m_quitEditor);
}

EditorPlaying::PlayingInterpreter::~PlayingInterpreter(void)
{

}

void EditorPlaying::listAreas(const std::string& argument)
{
	m_char->OnAreaList(argument);
	return;
}

void EditorPlaying::listColours(const std::string& argument)
{
	m_char->OnColourList(argument);
}

void EditorPlaying::listCommands(const std::string& argument)
{
	m_char->OnSend(String::Get()->box(PlayingInterpreter::Get()->getWords(), "Playing"));
	return;
}

void EditorPlaying::deleteCharacter(const std::string& argument)
{
	if(argument.compare("confirm"))
	{
		m_char->OnSend("If you really want to delete, please type 'delete confirm'.\n");
		return;
	}

	printf("Deleting PCharacter %s.\n", m_char->getName().c_str());

	m_char->OnSend("Goodbye.\n");
	m_sock->SetEditor(new EditorAccount(m_sock));
	m_char->Delete();
	return;
}

void EditorPlaying::look(const std::string& argument)
{
	m_char->OnLook(argument);
}

void EditorPlaying::quitEditor(const std::string& argument)
{
	m_char->OnSend("Thank you for visiting.\n");
	
	try
	{
		value_type id = m_char->getRoom();
		mud::RoomPtr room = mud::RoomManager::Get()->GetByKey(id);
		
		room->Sendf("%s fades from the realm.\n", m_char->getName().c_str());	
	}
	catch(RowNotFoundException& e)
	{
		Global::Get()->bug(e.what());
		// don't return
	}
	
	try
	{
		m_sock->PopEditor();
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		return;
	}
}

void EditorPlaying::listRaces(const std::string& argument)
{
	m_char->OnRaceList(argument);
	return;
}

void EditorPlaying::listRooms(const std::string& argument)
{
	m_char->OnRoomList(argument);
	return;
}

void EditorPlaying::showScore(const std::string& argument)
{
	m_char->OnScore(argument);
}

void EditorPlaying::say(const std::string& argument)
{
	m_char->OnSay(argument);
}
