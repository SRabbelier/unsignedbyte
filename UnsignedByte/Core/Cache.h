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

typedef std::map<oneValueKey,mud::Sector*> sectors_m;

typedef std::map<oneStringKey,mud::Sector*> sectors_ms;

typedef std::map<twoValueKey,db::CharacterAccount*> characteraccount_m; // character, account

typedef const std::string& cstring;

namespace mud
{
	class Cache : public Singleton<Cache>
	{
	public:
		value_type AddSector();
		
		mud::Sector* GetSectorByKey(value_type id);
		mud::Sector* GetSectorByName(cstring name);
		
		value_type lookupSectorByName(cstring value);

		void CloseSector(value_type sectorid);
		
		bool existsCharacterWithAccount(value_type characterid, value_type accountid);

	private:
		Sector* cacheSector(db::Sectors* d);
		
		characteraccount_m m_characteraccountByKey;
		
		sectors_m m_sectorByKey;
		sectors_ms m_sectorByName;
		
		reverseStringKey m_lookupSectorByName;

	private:
		Cache(void) {};
		Cache(const Cache& rhs);
		Cache operator=(const Cache& rhs);
		~Cache(void) {};
		
		friend class Singleton<Cache>;
	};
}
