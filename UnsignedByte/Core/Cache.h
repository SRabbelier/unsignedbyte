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
#include "db.h"

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

typedef std::map<oneStringKey,mud::Account*> accounts_ms;
typedef std::map<oneStringKey,mud::Area*> areas_ms;
typedef std::map<oneStringKey,mud::MCharacter*> mobiles_ms;
typedef std::map<oneStringKey,mud::Character*> characters_ms;
typedef std::map<oneStringKey,mud::Colour*> colours_ms;
typedef std::map<oneStringKey,mud::Command*> command_ms;
typedef std::map<oneStringKey,mud::GrantGroup*> grantgroup_ms;
typedef std::map<oneStringKey,mud::Race*> races_ms;
typedef std::map<oneStringKey,mud::Room*> rooms_ms;
typedef std::map<oneStringKey,mud::Sector*> sectors_ms;
typedef std::map<oneStringKey,mud::PCharacter*> players_ms;

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
		mud::Account* GetAccountByName(cstring name);
		
		mud::Area* GetAreaByKey(value_type id);
		
		mud::Character* GetCharacterByKey(value_type id);
		mud::Character* GetCharacterByName(cstring name);
		
		mud::Colour* GetColourByKey(value_type id);
		mud::Colour* GetColourByCode(cstring code);
		mud::Colour* GetColourByName(cstring name);
		
		mud::Command* GetCommandByKey(value_type id);
		mud::Command* GetCommandByName(cstring name);
		
		mud::GrantGroup* GetGrantGroupByKey(value_type id);
		mud::GrantGroup* GetGrantGroupByName(cstring name);

		mud::MCharacter* GetMCharacterByKey(value_type id);
		mud::MCharacter* GetMCharacterByName(cstring name);
		
		mud::PCharacter* GetPCharacterByKey(value_type id);
		mud::PCharacter* GetPCharacterByName(cstring name);
		
		mud::PCharacter* LoadPCharacterByKey(UBSocket* sock, value_type id);
		mud::PCharacter* LoadPCharacterByName(UBSocket* sock, cstring name);
		
		mud::Permission* GetPermissionByKeys(value_type account, value_type grantgroup);
		
		mud::Race* GetRaceByKey(value_type id);
		mud::Race* GetRaceByName(cstring name);

		mud::Room* GetRoomByKey(value_type id);
		
		mud::Sector* GetSectorByKey(value_type id);
		mud::Sector* GetSectorByName(cstring name);

		void CloseAccount(value_type accountid);
		void CloseArea(value_type areaid);
		void CloseCharacter(value_type characterid);
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
		Character* cacheCharacter(db::Characters* d);
		Colour* cacheColour(db::Colours* d);
		Command* cacheCommand(db::Commands* d);
		GrantGroup* cacheGrantGroup(db::GrantGroups* d);
		MCharacter* cacheMCharacter(db::Characters* d);
		PCharacter* cachePCharacter(UBSocket* sock, db::Characters* d);
		Permission* cachePermission(db::Permissions* d);
		Race* cacheRace(db::Races* d);
		Room* cacheRoom(db::Rooms* d);
		Sector* cacheSector(db::Sectors* d);
		
		accounts_m m_accountByKey;
		accounts_ms m_accountByName;
		
		areas_m m_areaByKey;
		
		characters_m m_characterByKey;
		characters_ms m_characterByName;
		
		colours_m m_colourByKey;
		colours_ms m_colourByCode;
		colours_ms m_colourByName;
		
		command_m m_commandByKey;
		command_ms m_commandByName;
		
		grantgroup_m m_grantgroupByKey;
		grantgroup_ms m_grantgroupByName;
		
		mobiles_m m_mobileByKey;
		mobiles_ms m_mobileByName;
		
		permission_m m_permissionByKeys;
		
		players_m m_playerByKey;
		players_ms m_playerByName;
		
		races_m m_raceByKey;
		races_ms m_raceByName;
		
		rooms_m m_roomByKey;
		
		sectors_m m_sectorByKey;
		sectors_ms m_sectorByName;

		valueset m_pcharacters;

	private:
		Cache(void) {};
		Cache(const Cache& rhs);
		Cache operator=(const Cache& rhs);
		~Cache(void) {};
		
		friend class Singleton<Cache>;
	};
}
