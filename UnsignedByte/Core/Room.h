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
#pragma once

#include "SavableHeaders.h"

namespace mud
{
	class Character;
	typedef std::vector<Character*> Characters;
	class Room;
	typedef SmartPtr<Room> RoomPtr;
	
	class Room : public Savable
	{
	public:
		value_type getID() const;
		const std::string& getName() const;
		const std::string& getDescription() const;
		value_type getSector() const;
		value_type getArea() const;
		value_type getHeight() const;
		value_type getWidth() const;
		value_type getLength() const;

		void setName(const std::string name);
		void setDescription(const std::string description);
		void setSector(value_type sector);
		void setArea(value_type area);
		void setHeight(value_type height);
		void setWidth(value_type width);
		void setLength(value_type length);

		const Characters& getCharactersInRoom();

		void Send(const std::string& msg);
		void Sendf(const char* format, ...);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TablePtr getTable() const;
		
		/**
		 * \brief Database utilities
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		SavableManagerPtr m_room;
		Characters m_charactersInRoom;

		Room(SavableManagerPtr room);
		Room(const Room& rhs);
		Room operator=(const Room& rhs);
		~Room(void);

		friend class RoomManager; // constructor
		friend SmartPtrDelete(mud::Room);
		// friend class SmartPtr<mud::Room>;
	};
}
