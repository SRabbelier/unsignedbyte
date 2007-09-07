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
 *   avalue_type with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#pragma once

#include <string>
#include <map>
#include <set>

#include "singleton.h"
#include "Exit.h"
#include "Coordinate.h"

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
typedef std::set<value_type> valueset;

typedef value_type oneValueKey;
typedef std::string oneStringKey;

typedef std::pair<value_type, value_type> twoValueKey;

typedef std::map<oneValueKey,mud::Account*> accounts_m;
typedef std::map<oneValueKey,mud::Area*> areas_m;
typedef std::map<oneValueKey,mud::MCharacter*> mobiles_m;
typedef std::map<oneValueKey,mud::Character*> characters_m;
typedef std::map<oneValueKey,mud::Colour*> colours_m;
typedef std::map<oneValueKey,mud::Command*> command_m;
typedef std::map<oneValueKey,mud::GrantGroup*> grantgroup_m;
typedef std::map<oneValueKey,mud::Race*> races_m;
typedef std::map<oneValueKey,mud::Room*> rooms_m;
typedef std::map<oneValueKey,mud::Sector*> sectors_m;
typedef std::map<oneValueKey,mud::PCharacter*> players_m;
typedef std::map<twoValueKey,mud::Permission*> permission_m;

typedef const std::string& cstring;

namespace mud
{
	class Cache : public Singleton<Cache>
	{
	public:
		bool IsMobile(value_type id);
		bool isActive(value_type id);
		bool isActive(cstring name);

		mud::Account* GetAccountByKey(value_type id);
		mud::Area* GetAreaByKey(value_type id);
		mud::Character* GetCharacterByKey(value_type id);
		mud::Colour* GetColourByKey(value_type id);
		mud::Command* GetCommandByKey(value_type id);
		mud::GrantGroup* GetGrantGroupByKey(value_type id);
		mud::MCharacter* GetMCharacterByKey(value_type id);
		mud::PCharacter* GetPCharacterByKey(value_type id);
		mud::PCharacter* LoadPCharacter(UBSocket* sock, value_type id);
		mud::Permission* GetPermissionByKeys(value_type account, value_type grantgroup);
		mud::Race* GetRaceByKey(value_type id);
		mud::Room* GetRoomByKey(value_type id);
		mud::Sector* GetSectorByKey(value_type id);

		void CloseAccount(value_type accountid);
		void CloseArea(value_type areaid);
		void CloseColour(value_type colourid);
		void CloseCommand(value_type commandid);
		void CloseGrantGroup(value_type grantgroupid);
		void CloseMCharacter(value_type characterid);
		void ClosePCharacter(value_type characterid);
		void ClosePermission(value_type account, value_type permission);
		void CloseRace(value_type raceid);
		void CloseRoom(value_type roomid);
		void CloseSector(value_type sectorid);

	private:
		Account* cacheAccount(db::Accounts* d);
		Area* cacheArea(db::Areas* d);
		Colour* cacheColour(db::Colours* d);
		Command* cacheCommand(db::Commands* d);
		GrantGroup* cacheGrantGroup(db::GrantGroups* d);
		MCharacter* cacheMCharacter(db::Characters* d);
		PCharacter* cachePCharacter(UBSocket* sock, db::Characters* d);
		Permission* cachePermission(db::Permissions* d);
		Race* cacheRace(db::Race* d);
		Room* cacheRoom(db::Room* d);
		Sector* cacheSector(db::Sector* d);
		
		accounts_m m_accountByKey;
		areas_m m_areaByKey;
		mobiles_m m_mobileByKey;
		characters_m m_characterByKey;
		colours_m m_colourByKey;
		command_m m_commandByKey;
		grantgroup_m m_grantgroupByKey;
		races_m m_raceByKey;
		rooms_m m_roomByKey;
		sectors_m m_sectorByKey;
		players_m m_playerByKey;
		permission_m m_permissionByKeys;

		valueset m_pcharacters;

	private:
		Cache(void) {};
		Cache(const Cache& rhs) {};
		Cache operator=(const Cache& rhs) {return *this; };
		~Cache(void) {};
		
		friend class Singleton<Cache>;
	};
}
