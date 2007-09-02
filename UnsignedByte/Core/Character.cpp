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

#ifdef _WIN32
#include <winsock2.h>
#endif

#include <string>
#include <map>
#include <stdarg.h>
#include <stdexcept>

#include "Character.h"
#include "DatabaseMgr.h"
#include "db.h"
#include "Global.h"
#include "Cache.h"

#include "Global.h"
#include "StringUtilities.h"

#include "UBSocket.h"
#include "UBHandler.h"

#include "Race.h"
#include "Area.h"
#include "Room.h"

using mud::Character;

Character::Character(db::Characters* character) :
m_character(character)
{
	if(m_character == NULL)
		throw std::invalid_argument("Character::Character(), m_character == NULL");
}

Character::~Character(void)
{
	delete m_character;
	m_character = NULL;
}

/**
 * Start of Output
 */ 
void Character::OnSend(const std::string& msg)
{
	// discard msg
	return;
}

void Character::OnSendf(char* format, ...)
{
	va_list args;
	va_start(args, format);
	OnSend(Global::Get()->sprint(args, format));
	va_end(args);
	return;
}
/**
 * End of Output
 */ 


/**
 * Start of Commands
 */ 	
void Character::OnAreaList(const std::string& msg)
{
	OnSend("Listing known areas:\n");
	OnSend(String::Get()->unlines(DatabaseMgr::Get()->GetSavable(Tables::Get()->AREAS), "\t", 3));
	OnSend("\n");
	OnSend("End of area list\n");
	return;
}

void Character::OnColourList(const std::string& msg)
{
	OnSend("Listing available colours:\n");
	OnSend("End of colour list.\n");
	return;
}

void Character::OnLaston(const std::string& msg)
{
	OnSend("Listing known characters:\n");

	Strings list = DatabaseMgr::Get()->GetSavable(Tables::Get()->CHARACTERS);
	for(Strings::iterator it = list.begin(); it != list.end(); it++)
	{
		OnSend(*it);
		OnSend("\n");
	}

	OnSend("End of character list\n");
	return;	
}

void Character::OnLook(const std::string& msg)
{
	try 
	{
		long id = this->getRoom();
		Room* room = Cache::Get()->GetRoom(id);
		
		OnSendf("Room (%d|<%dx%dx%d): %s\n", room->getArea(), room->getHeight(), room->getLength(), room->getWidth(), room->getName().c_str());
		OnSendf("%s\n", room->getDescription().c_str());

		/*
		Characters chars = room->getCharacters();
		for(Characters::iterator it = chars.begin(); it != chars.end(); it++)
		{
			OnSendf("(%s) %s.\n", (*it)->getName().c_str(), (*it)->getDescription().c_str());
		}
		*/
		
		return;
	}
	catch (std::exception& e) 
	{
		Global::Get()->bug(e.what());
		return;
	}
}

void Character::OnRaceList(const std::string& msg)
{
	OnSend("Listing known races:\n");
	OnSend(String::Get()->unlines(DatabaseMgr::Get()->GetSavable(Tables::Get()->RACES), "\t", 3));
	OnSend("\n");
	OnSend("End of races list\n");
	return;
}

void Character::OnRoomList(const std::string& msg)
{
	OnSend("Listing known rooms:\n");
	OnSend(String::Get()->unlines(DatabaseMgr::Get()->GetSavable(Tables::Get()->ROOMS), "\t", 3));
	OnSend("\n");
	OnSend("End of room list\n");
	return;
}

void Character::OnScore(const std::string& msg)
{
	OnSend(String::Get()->box(Show(), "Character"));
	return;
}

void Character::OnSay(const std::string& msg)
{
	if(msg.size() == 0)
	{
		OnSend("Say what?\n");
		return;
	}

	try
	{
		long id = getRoom();
		Room* room = Cache::Get()->GetRoom(id);

		room->Sendf("%s says '%s`^'\n", getName().c_str(), msg.c_str());
		return;
	}
	catch (std::exception& e)
	{
		Global::Get()->bug(e.what());
		return;
	}
}

void Character::OnWho(const std::string& msg)
{
	std::map<SOCKET,Socket *> ref = UBHandler::Get()->Sockets();
	for (std::map<SOCKET,Socket *>::iterator it = ref.begin(); it != ref.end(); it++)
	{
		UBSocket* sock = UBSocket::Cast(it->second, false);
		Character* PCh = NULL;
		if (sock)
		{
			// PCh = sock->GetCharacter();
		}

		if(PCh)
		{
			OnSendf("Player: %s\n", PCh->getName().c_str());
		}
	}
	return;
}
	
/**
 * End of commands
 */ 

void Character::Delete() 
{ 
	m_character->erase(); 
}

void Character::Save() 
{
	m_character->save(); 
};

bool Character::Exists() 
{ 
	return m_character->exists(); 
};

bool Character::IllegalName(const std::string& name)
{
	if(DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, name) > 0)
		return true;

	return false;
}

std::vector<std::string> Character::Show()
{
	std::vector<std::string> result;
	// TODO - Character::Show()
	return result;
}

std::string Character::ShowShort()
{
	std::string result;
	// TODO - Character::ShowShort()
	return result;
}

std::vector<std::string> Character::List()
{
	std::vector<std::string> result;
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->CHARACTERS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		Character* character= Cache::Get()->GetCharacter(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(character->ShowShort());
		result.push_back(line);
	}
	return result;
}

void Character::Close(mud::Character* Ch)
{
	if(Ch == NULL)
	{
		throw std::invalid_argument("Character::Close(), Ch == NULL");
		return;
	}
	
	Cache::Get()->CloseCharacter(Ch->getID());
	delete Ch;
}

Table* Character::getTable() const
{ 
	return Tables::Get()->CHARACTERS; 
};
