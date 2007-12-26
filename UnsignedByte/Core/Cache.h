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
#include <set>

#include "singleton.h"
#include "db.h"
#include "smart_ptr.h"

namespace mud
{
	class Account;
	class Area;
	class Character;
	class Command;
	class Colour;
	class GrantGroup;
	class MCharacter;
	class Race;
	class Room;
	class Sector;
	class PCharacter;
	class Permission; 
}

class UBSocket;

typedef unsigned long value_type;

typedef value_type oneValueKey;
typedef std::string oneStringKey;

typedef std::pair<value_type, value_type> twoValueKey;

typedef std::map<std::string, value_type> reverseStringKey;

typedef std::map<oneValueKey,mud::Race*> races_m;
typedef std::map<oneValueKey,mud::Room*> rooms_m;
typedef std::map<oneValueKey,mud::Sector*> sectors_m;

typedef std::map<oneStringKey,mud::Race*> races_ms;
typedef std::map<oneStringKey,mud::Room*> rooms_ms;
typedef std::map<oneStringKey,mud::Sector*> sectors_ms;

typedef std::map<twoValueKey,db::CharacterAccount*> characteraccount_m; // character, account

typedef const std::string& cstring;

namespace mud
{
	class Cache : public Singleton<Cache>
	{
	public:
		value_type AddRace();
		value_type AddRoom();
		value_type AddSector();
		
		mud::Race* GetRaceByKey(value_type id);
		mud::Race* GetRaceByName(cstring name);

		mud::Room* GetRoomByKey(value_type id);
		
		mud::Sector* GetSectorByKey(value_type id);
		mud::Sector* GetSectorByName(cstring name);
		
		value_type lookupRaceByName(cstring value);
		value_type lookupSectorByName(cstring value);

		void CloseRace(value_type raceid);
		void CloseRoom(value_type roomid);
		void CloseSector(value_type sectorid);
		
		bool existsCharacterWithAccount(value_type characterid, value_type accountid);

	private:
		Race* cacheRace(db::Races* d);
		Room* cacheRoom(db::Rooms* d);
		Sector* cacheSector(db::Sectors* d);
		
		characteraccount_m m_characteraccountByKey;
		
		races_m m_raceByKey;
		races_ms m_raceByName;
		
		rooms_m m_roomByKey;
		
		sectors_m m_sectorByKey;
		sectors_ms m_sectorByName;
		
		reverseStringKey m_lookupRaceByName;
		reverseStringKey m_lookupSectorByName;

	private:
		Cache(void) {};
		Cache(const Cache& rhs);
		Cache operator=(const Cache& rhs);
		~Cache(void) {};
		
		friend class Singleton<Cache>;
	};
}
