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

typedef std::pair<value_type, Exit::DIRECTION> roomexit; // roomid, direction
typedef std::pair<value_type, value_type> twokey; // account, grantgroup
typedef std::map<Coordinate, value_type> rlookup_m; // room lookup
typedef std::map<twokey, value_type> plookup_m; // grants lookup
typedef std::map<std::string, value_type> lookup_m; // string lookup

typedef rlookup_m::iterator rlookup_mi;
typedef plookup_m::iterator plookup_mi;
typedef lookup_m::iterator lookup_mi;

typedef std::map<value_type,mud::Account*> accounts_m;
typedef std::map<value_type,mud::Area*> areas_m;
typedef std::map<value_type,mud::MCharacter*> mobiles_m;
typedef std::map<value_type,mud::Character*> characters_m;
typedef std::map<value_type,mud::Colour*> colours_m;
typedef std::map<value_type,mud::Command*> command_m;
typedef std::map<value_type,mud::GrantGroup*> grantgroup_m;
typedef std::map<value_type,mud::Race*> races_m;
typedef std::map<value_type,mud::Room*> rooms_m;
typedef std::map<value_type,mud::Sector*> sectors_m;
typedef std::map<value_type,mud::PCharacter*> players_m;
typedef std::map<twokey,mud::Permission*> permission_m;

typedef const std::string& cstring;

namespace mud
{
	class Cache : public Singleton<Cache>
	{
	public:
		value_type AddAccount();
		value_type AddCharacter();
		value_type AddRace();
		value_type AddArea();
		value_type AddRoom();
		value_type AddSector();
		value_type AddColour();
		value_type AddCommand();
		value_type AddGrantGroup();
		void AddPermission(value_type account, value_type grantgroup);

		bool IsMobile(value_type id);
		bool isActive(value_type id);
		bool isActive(cstring name);

		mud::Account* GetAccount(value_type id);
		value_type GetAccountID(cstring name);
		
		mud::Area* GetArea(value_type id);

		mud::PCharacter* LoadPCharacter(UBSocket* sock, value_type id);
		mud::PCharacter* GetPCharacter(value_type id);
		mud::MCharacter* GetMCharacter(value_type id);
		mud::Character* GetCharacter(value_type id);
		value_type GetCharacterID(const std::string& name);

		mud::Race* GetRace(value_type id);
		value_type GetRaceID(cstring name);

		mud::Sector* GetSector(value_type id);
		value_type GetSectorID(cstring name);

		mud::Room* GetRoom(value_type id);
		// value_type GetRoomID(value_type area, value_type x, value_type y);

		mud::Colour* GetColour(value_type id);
		value_type GetColourID(cstring code);
		
		mud::Command* GetCommand(value_type id);
		value_type GetCommandID(cstring name);
		
		mud::GrantGroup* GetGrantGroup(value_type id);
		value_type GetGrantGroupID(cstring name);
		
		mud::Permission* GetPermission(value_type account, value_type grantgroup);

		void CloseAccount(value_type accountid);
		void CloseCharacter(value_type characterid);
		void ClosePCharacter(value_type characterid);
		void CloseMCharacter(value_type characterid);
		void CloseRace(value_type raceid);
		void CloseArea(value_type areaid);
		void CloseRoom(value_type roomid);
		void CloseSector(value_type sectorid);
		// void CloseExit(value_type exitid);
		void CloseColour(value_type colourid);
		void CloseCommand(value_type commandid);
		void CloseGrantGroup(value_type grantgroupid);
		void ClosePermission(value_type account, value_type permission);

	private:
		accounts_m m_accounts;
		players_m m_players;
		mobiles_m m_mobiles;
		characters_m m_characters;
		races_m m_races;
		areas_m m_areas;
		rooms_m m_rooms;
		sectors_m m_sectors;
		colours_m m_colours;
		command_m m_commands;
		grantgroup_m m_grantgroups;
		permission_m m_permissions;

		lookup_m m_account;
		lookup_m m_character;
		lookup_m m_race;
		lookup_m m_sector;
		lookup_m m_command;
		lookup_m m_grantgroup;
		lookup_m m_colour;
		
		rlookup_m m_room;
		plookup_m m_permission;
		
		valueset m_pcharacters;

	private:
		Cache(void) {};
		Cache(const Cache& rhs) {};
		Cache operator=(const Cache& rhs) {return *this; };
		~Cache(void) {};
		
		friend class Singleton<Cache>;
	};
}
