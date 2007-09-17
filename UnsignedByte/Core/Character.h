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
#pragma once

#include <string>
#include <map>
#include <vector>
#include "Savable.h"
#include "db.h"

namespace mud
{
	class Character : public Savable
	{
	public:
		virtual void OnSend(const std::string& msg);
		virtual void OnSendf(const char* format, ...);
		
		/**
		 * Start of Commands
		 */ 	
		virtual void OnAreaList(const std::string& msg);
		virtual void OnColourList(const std::string& msg);
		virtual void OnLaston(const std::string& msg);
		virtual void OnLook(const std::string& msg);
		virtual void OnRaceList(const std::string& msg);
		virtual void OnRoomList(const std::string& msg);
		virtual void OnScore(const std::string& msg);
		virtual void OnSay(const std::string& msg);
		virtual void OnWho(const std::string& msg);
		/**
		 * End of commands
		 */ 
	 
		/**
		 * \brief Getters
		 */ 
		long getID() { return m_character->getcharacterid(); }
		const std::string& getName() { return m_character->getname(); }
		const std::string& getDescription() { return m_character->getdescription(); }
		long getRace() { return m_character->getfkRaces(); }
		long getRoom() { return m_character->getfkRooms(); }

		/**
		 * \brief Setters
		 */ 
		void setName(const std::string& name) { m_character->setname(name); }
		void setDescription(const std::string& description) { m_character->setdescription(description); }
		void setRace(long race) { m_character->setfkRaces(race); }
		void setRoom(long room) { m_character->setfkRooms(room); }
		
		/**
		 * \brief Database operations
		 */
		void Delete();
		void Save();
		bool Exists();	
		
		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		Table* getTable() const { return GetTable(); }
		
		/**
		 * \brief Static utilities
		 */
		static Table* GetTable();
		static std::vector<std::string> List();
		static void Close(Character* Ch);
		static bool IllegalName(const std::string& name);

	protected:
		db::Characters* m_character;

		Character(db::Characters* character);
		virtual ~Character(void);
		
		friend class Cache; // for constructor
		
	private:
		Character(const Character& rhs) { };
		Character operator=(const Character& rhs) { return *this; };
	};
}
