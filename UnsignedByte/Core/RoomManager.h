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
#include <vector>

#include "singleton.h"
#include "db.h"

namespace mud 
{ 
	class Room; 
	typedef SmartPtr<Room> RoomPtr;
}

typedef const std::string& cstring;
typedef std::map<value_type,mud::RoomPtr> rooms_m;
typedef std::map<std::string,mud::RoomPtr> rooms_ms;
typedef std::map<std::string, value_type> reverseStringKey;

namespace mud
{
	class RoomManager : public Singleton<mud::RoomManager>
	{
	public:
		TablePtr GetTable();
		std::vector<std::string> List();
		void Close(RoomPtr room);
		
		value_type Add();
		mud::RoomPtr GetByKey(value_type id);
		mud::RoomPtr GetByName(cstring name);
		
		value_type lookupByName(cstring value);
		
		void Close(value_type Roomid);
		
	private:
		RoomPtr cacheRoom(db::Rooms* d);
		
		rooms_m m_byKey;
		rooms_ms m_byName;
		reverseStringKey m_lookupByName;

	private:
		RoomManager(void) {};
		RoomManager(const RoomManager& rhs);
		RoomManager operator=(const RoomManager& rhs);
		~RoomManager(void) {};
		
		friend class Singleton<mud::RoomManager>;
	};
}
