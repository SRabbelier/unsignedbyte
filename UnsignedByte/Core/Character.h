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

#include "SavableHeaders.h"

namespace mud
{
	class CharacterManager;
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
		virtual void OnLook(const std::string& msg);
		virtual void OnRaceList(const std::string& msg);
		virtual void OnRoomList(const std::string& msg);
		virtual void OnScore(const std::string& msg);
		virtual void OnSay(const std::string& msg);
		/**
		 * End of commands
		 */ 
	 
		/**
		 * \brief Getters
		 */ 
		value_type getID() const;
		const std::string& getName() const;
		const std::string& getDescription() const;
		value_type getRace() const;
		value_type getRoom() const;

		/**
		 * \brief Setters
		 */ 
		void setName(const std::string& name);
		void setDescription(const std::string& description);
		void setRace(value_type race);
		void setRoom(value_type room);
		
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
		TablePtr getTable() const;

	protected:
		SavableManagerPtr m_character;

		Character(SavableManagerPtr character);
		virtual ~Character(void);
		
		friend class mud::CharacterManager; // for constructor
		friend SmartPtrDelete(mud::Character);
		
	private:
		Character(const Character& rhs);
		Character operator=(const Character& rhs);
	};
}
