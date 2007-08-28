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

#include "singleton.h"
#include "Exit.h"
#include "Coordinate.h"

class UBSocket;
class Account;
class Character;
class PCharacter;
class MCharacter;
class Race;
class Area;
class Room;
class Sector;
class Object;
class Colour;
class Command;
class GrantGroup;
class Permission;

typedef std::pair<long, Exit::DIRECTION> roomexit; // roomid, direction
typedef std::pair<long, long> permission; // account, grantgroup
typedef std::map<Coordinate, long> rlookup_m; // room lookup
// typedef std::map<roomexit, long> elookup_m; // exit lookup
typedef std::map<permission, long> plookup_m; // grants lookup
typedef std::map<std::string, long> lookup_m; // string lookup

typedef rlookup_m::iterator rlookup_mi;
// typedef elookup_m::iterator elookup_mi;
typedef plookup_m::iterator plookup_mi;
typedef lookup_m::iterator lookup_mi;

typedef std::map<long,Account*> accounts_m;
typedef std::map<long,PCharacter*> players_m;
typedef std::map<long,MCharacter*> mobiles_m;
typedef std::map<long,Character*> characters_m;
typedef std::map<long,Race*> races_m;
typedef std::map<long,Area*> areas_m;
typedef std::map<long,Room*> rooms_m;
// typedef std::map<long,Exit*> exits_m;
typedef std::map<long,Sector*> sectors_m;
typedef std::map<long,Colour*> colours_m;
typedef std::map<long,Command*> command_m;
typedef std::map<long,GrantGroup*> grantgroup_m;
typedef std::map<long,Permission*> permission_m;

typedef const std::string& cstring;

class Cache : public Singleton<Cache>
{
public:
	long AddAccount();
	long AddCharacter();
	long AddRace();
	long AddArea();
	long AddRoom();
	// long AddExit();
	long AddSector();
	long AddColour();
	long AddCommand();
	long AddGrantGroup();
	long AddPermission();

	bool IsMobile(long id);
	bool isActive(long id);
	bool isActive(cstring name);

	Account* GetAccount(long id);
	long GetAccountID(cstring name);

	PCharacter* GetPCharacter(UBSocket* sock, long id);
	long GetPCharacterID(cstring name);

	MCharacter* GetMCharacter(long id);
	//long GetMCharacterID(cstring name);

	Character* GetCharacter(long id);
	//long GetCharacterID(cstring name);

	Race* GetRace(long id);
	long GetRaceID(cstring name);

	Sector* GetSector(long id);
	long GetSectorID(cstring name);

	Area* GetArea(long id);

	Room* GetRoom(long id);
	// long GetRoomID(long area, long x, long y);

	// Exit* GetExit(long id);
	// long GetExitID(long roomid, Exit::DIRECTION dir);

	Object* GetObj(long id);

	Colour* GetColour(long id);
	long GetColourID(cstring code);
	
	Command* GetCommand(long id);
	long GetCommandID(cstring name);
	
	GrantGroup* GetGrantGroup(long id);
	long GetGrantGroupID(cstring name);
	
	Permission* GetPermission(long id);
	long GetPermissionID(long account, long grantgroup);

	void CloseAccount(long accountid);
	void CloseCharacter(long characterid);
	void ClosePCharacter(long characterid);
	void CloseMCharacter(long characterid);
	void CloseRace(long raceid);
	void CloseArea(long areaid);
	void CloseRoom(long roomid);
	void CloseSector(long sectorid);
	// void CloseExit(long exitid);
	void CloseColour(long colourid);
	void CloseCommand(long commandid);
	void CloseGrantGroup(long grantgroupid);
	void ClosePermission(long permissionid);

private:
	accounts_m m_accounts;
	players_m m_players;
	mobiles_m m_mobiles;
	characters_m m_characters;
	races_m m_races;
	areas_m m_areas;
	rooms_m m_rooms;
	// exits_m m_exits;
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
	// elookup_m m_exit;
	plookup_m m_permission;

private:
	Cache(void) {};
	Cache(const Cache& rhs) {};
	Cache operator=(const Cache& rhs) {return *this; };
	~Cache(void) {};
	
	friend class Singleton<Cache>;
};
