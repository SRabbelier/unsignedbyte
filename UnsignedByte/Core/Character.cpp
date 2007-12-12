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

void Character::OnSendf(const char* format, ...)
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
	OnSend(String::Get()->box(mud::Area::List(), "Areas"));
	return;
}

void Character::OnColourList(const std::string& msg)
{
	OnSend("Listing available colours:\n");
	OnSend("End of colour list.\n");
	return;
}

void Character::OnLook(const std::string& msg)
{
	try 
	{
		long id = this->getRoom();
		Room* room = Cache::Get()->GetRoomByKey(id);

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
	OnSend(String::Get()->box(mud::Race::List(), "Races"));
	return;
}

void Character::OnRoomList(const std::string& msg)
{
	OnSend(String::Get()->box(mud::Room::List(), "Rooms"));
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
		Room* room = Cache::Get()->GetRoomByKey(id);

		room->Sendf("%s says '%s`^'\n", getName().c_str(), msg.c_str());
		return;
	}
	catch (std::exception& e)
	{
		Global::Get()->bug(e.what());
		return;
	}
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
	if(mud::Cache::Get()->lookupCharacterByName(name))
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
	return GetTable()->tableList();
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

TablePtr Character::GetTable()
{ 
	return Tables::Get()->CHARACTERS; 
};
