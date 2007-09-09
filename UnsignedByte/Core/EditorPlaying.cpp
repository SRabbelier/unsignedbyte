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

#include <string>

#include "EditorAccount.h"
#include "EditorPlaying.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Account.h"
#include "Character.h"
#include "PCharacter.h"
#include "Room.h"

using mud::PCharacter;

EditorPlaying::EditorPlaying(UBSocket* sock, PCharacter* character) :
Editor(sock),
m_char(character)
{
	try
	{
		long id = m_char->getRoom();
		mud::Room* inroom = mud::Cache::Get()->GetRoom(id);
	
		inroom->Sendf("%s enters the realm.\n", m_char->getName().c_str());
	}
	/*
	catch(unfoundroom)
	{
		// continue execution, don't return
	}
	*/
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		return;
	}
	m_char->OnSend(String::Get()->box(PlayingInterpreter::Get()->getWords(), "Playing"));
}

EditorPlaying::~EditorPlaying(void)
{
	m_char->Save();
	PCharacter::Close(m_char);
	m_char = NULL;
}

std::string EditorPlaying::lookup(const std::string& action)
{
	PlayingAction* act = PlayingInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorPlaying::dispatch(const std::string& action, const std::string& argument)
{
	PlayingAction* act = PlayingInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_char);
	else
		Global::Get()->bugf("EditorPlaying::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}

EditorPlaying::PlayingInterpreter::PlayingInterpreter(void)
{
	addWord("areas", Areas::Get());
	addWord("colours", Colours::Get());
	addWord("commands", Commands::Get());
	addWord("laston", Laston::Get());
	addWord("look", Look::Get());
	addWord("races", Races::Get());
	addWord("rooms", Rooms::Get());
	addWord("score", Score::Get());
	addWord("say", Say::Get());
	addWord("delete", Delete::Get());
	addWord("quit", Quit::Get());
	addWord("who", Who::Get());
}

EditorPlaying::PlayingInterpreter::~PlayingInterpreter(void)
{
	Areas::Free();
	Colours::Free();
	Commands::Free();
	Laston::Free();
	Look::Free();
	Races::Free();
	Rooms::Free();
	Score::Free();
	Say::Free();
	Delete::Free();
	Quit::Free();
	Who::Free();
}

void EditorPlaying::Areas::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnAreaList(argument);
	return;
}

void EditorPlaying::Colours::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnColourList(argument);
}

void EditorPlaying::Commands::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnSend(String::Get()->box(PlayingInterpreter::Get()->getWords(), "Playing"));
	return;
}

void EditorPlaying::Delete::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	if(argument.compare("confirm"))
	{
		Ch->OnSend("If you really want to delete, please type 'delete confirm'.\n");
		return;
	}

	printf("Deleting PCharacter %s.\n", Ch->getName().c_str());

	Ch->OnSend("Goodbye.\n");
	sock->SetEditor(new EditorAccount(sock));
	Ch->Delete();
	return;
}

void EditorPlaying::Laston::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnLaston(argument);
}

void EditorPlaying::Look::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnLook(argument);
}

void EditorPlaying::Quit::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	try
	{
		Ch->OnSend("Thank you for visiting.\n");
		long id =Ch->getRoom();
		mud::Room* room = mud::Cache::Get()->GetRoom(id);
		
		room->Sendf("%s fades from the realm.\n", Ch->getName().c_str());	
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		// don't return
	}
	
	try
	{
		sock->SetEditor(new EditorAccount(sock));
		mud::PCharacter::Close(Ch);
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
		return;
	}
}

void EditorPlaying::Races::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnRaceList(argument);
	return;
}


void EditorPlaying::Rooms::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnRoomList(argument);
	return;
}

void EditorPlaying::Score::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnScore(argument);
}

void EditorPlaying::Say::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnSay(argument);
}

void EditorPlaying::Who::Run(UBSocket* sock, const std::string &argument, PCharacter* Ch)
{
	Ch->OnWho(argument);
}
