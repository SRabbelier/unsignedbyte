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

#include <stdarg.h>

#include "Character.h"

#include "Global.h"
#include "StringUtilities.h"

#include "UBSocket.h"
#include "UBHandler.h"

#include "Race.h"
#include "RaceManager.h"
#include "Area.h"
#include "Room.h"
#include "RoomManager.h"
#include "Account.h" // needed because UBSocket.h is included
#include "AreaManager.h"

using mud::Character;

Character::Character(SavableManagerPtr character) :
m_character(character)
{
	if(!m_character)
		throw std::invalid_argument("Character::Character(), m_character == NULL");
}

Character::~Character(void)
{

}

value_type Character::getID() const
{
	return m_character->getkey(db::CharactersFields::Get()->CHARACTERID)->getValue();
}

const std::string& Character::getName() const
{
	return m_character->getfield(db::CharactersFields::Get()->NAME)->getStringValue();
}

const std::string& Character::getDescription() const
{
	return m_character->getfield(db::CharactersFields::Get()->DESCRIPTION)->getStringValue();
}

value_type Character::getRace() const
{
	return m_character->getfield(db::CharactersFields::Get()->FKRACES)->getIntegerValue();
}

value_type Character::getRoom() const
{
	return m_character->getfield(db::CharactersFields::Get()->FKROOMS)->getIntegerValue();
}


/**
 * \brief Setters
 */ 
void Character::setName(const std::string& name)
{
	ValuePtr value(new Value(db::CharactersFields::Get()->NAME, name));
	m_character->setvalue(value);	
}

void Character::setDescription(const std::string& description)
{
	ValuePtr value(new Value(db::CharactersFields::Get()->DESCRIPTION, description));
	m_character->setvalue(value);
}

void Character::setRace(value_type race)
{
	ValuePtr value(new Value(db::CharactersFields::Get()->FKRACES, race));
	m_character->setvalue(value);
}

void Character::setRoom(value_type room)
{
	ValuePtr value(new Value(db::CharactersFields::Get()->FKROOMS, room));
	m_character->setvalue(value);
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
	OnSend(String::Get()->box(mud::AreaManager::Get()->List(), "Areas"));
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
		RoomPtr room = mud::RoomManager::Get()->GetByKey(id);

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
	catch (RowNotFoundException& e) 
	{
		Global::Get()->bug(e.what());
		return;
	}
}

void Character::OnRaceList(const std::string& msg)
{
	OnSend(String::Get()->box(mud::RaceManager::Get()->List(), "Races"));
	return;
}

void Character::OnRoomList(const std::string& msg)
{
	OnSend(String::Get()->box(mud::RoomManager::Get()->List(), "Rooms"));
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
		RoomPtr room = mud::RoomManager::Get()->GetByKey(id);

		room->Sendf("%s says '%s`^'\n", getName().c_str(), msg.c_str());
		return;
	}
	catch (RowNotFoundException& e)
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
}

bool Character::Exists() 
{ 
	return m_character->exists(); 
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

TablePtr Character::getTable() const
{ 
	return Tables::Get()->CHARACTERS; 
}
