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

#ifdef _WIN32
	#include "winsock2.h"
#endif

#include <stdexcept>
#include <sstream>

#include "Cache.h"
#include "UBSocket.h"
#include "DatabaseMgr.h"
#include "Global.h"
#include "db.h"

#include "Account.h"
#include "PCharacter.h"
#include "MCharacter.h"
#include "Race.h"
#include "Area.h"
#include "Room.h"
#include "Sector.h"
#include "Colour.h"
#include "Command.h"
#include "GrantGroup.h"
#include "Permission.h"

using namespace mud;

/**
 *   Wrapped
 *   Database
 *   Object
 *	 Retreival 
 */

Account* Cache::cacheAccount(db::Accounts* d)
{
	Account* p = new Account(d);
	m_accountByName[d->getname()] = p;
	m_accountByKey[d->getaccountid()] = p;
	return p;
}

Account* Cache::GetAccountByKey(value_type id)
{
	Account* p = m_accountByKey[id];
	if (p)
		return p;

	db::Accounts* d = db::Accounts::bykey(id);
	p = cacheAccount(d);
	return p;
}

Account* Cache::GetAccountByName(const std::string& value)
{
	Account* p = m_accountByName[value];
	if(p)
		return p;

	db::Accounts* d = db::Accounts::byname(value);
	p = cacheAccount(d);
	
	return p;
}

Area* Cache::cacheArea(db::Areas* d)
{
	Area* p = new Area(d);
	m_areaByKey[d->getareaid()] = p;
	return p;
}

mud::Area* Cache::GetAreaByKey(value_type id)
{
	Area* p = m_areaByKey[id];
	if(p)
		return p;

	db::Areas* d = db::Areas::bykey(id);
	p = cacheArea(d);
	return p;
}

Character* Cache::cacheCharacter(db::Characters *d)
{
	Character* p = new Character(d);
	m_characterByKey[d->getcharacterid()] = p;
	m_characterByName[d->getname()] = p;
	return p;
}

mud::Character* Cache::GetCharacterByKey(value_type id)
{
	Character* p = m_characterByKey[id];
	if(p)
		return p;

	db::Characters* d = db::Characters::bykey(id);
	p = cacheCharacter(d);
	return p;
}

mud::Colour* Cache::GetColourByKey(value_type id)
{
	Colour* p = m_colourByKey[id];
	if(p)
		return p;

	db::Colours* d = db::Colours::bykey(id);
	p = cacheColour(d);
	return p;
}

#if 0

PCharacter* Cache::GetPCharacter(value_type id)
{
	PCharacter* p = m_players[id];
	if (p)
		return p;
	
	std::ostringstream err;
	err << "No such PCharacter '" << id << "' logged in.";
	throw std::invalid_argument(err.str());
}

PCharacter* Cache::LoadPCharacter(UBSocket* sock, value_type id)
{
	// Character delete's db::Characters on deletion
	db::Characters* d = new db::Characters(id);
	PCharacter* p = new PCharacter(sock, d);

	m_players[id] = p;
	m_character[d->getname()] = id;
	
	m_pcharacters.insert(id);

	return p;
}

MCharacter* Cache::GetMCharacter(value_type id)
{
	MCharacter* p = m_mobiles[id];
	if (p)
		return p;

	// MCharacter delete's db::Characters on deletion
	db::Characters* d = new db::Characters(id);
	p = new MCharacter(d);

	m_mobiles[id] = p;
	m_character[d->getname()] = id;

	return p;
}

Character* Cache::GetCharacter(value_type id)
{
	Character* p = m_characters[id];
	if (p)
		return p;

	// Character delete's db::Characters on deletion
	db::Characters* d = new db::Characters(id);
	p = new Character(d);

	m_characters[id] = p;
	m_character[d->getname()] = id;

	return p;
}

value_type Cache::GetCharacterID(const std::string& name)
{
	lookup_mi it = m_character.find(name);
	if(it != m_character.end())
	{		
		return it->second;
	}

	long id = DatabaseMgr::Get()->GetSavableID(Tables::Get()->CHARACTERS, name);

	m_character[name] = id;

	return id;
}

bool Cache::isActive(value_type id)
{
	valueset::iterator it = m_pcharacters.find(id);
	if(it == m_pcharacters.end())
		return false;
	
	return true;
}

bool Cache::isActive(cstring name)
{
	value_type id = GetCharacterID(name);
	return isActive(id);
}
	
Race* Cache::GetRace(value_type id)
{
	Race* p = m_races[id];
	if (p)
		return p;

	// Races delete's db::Races on deletion
	db::Races* d = new db::Races(id);
	p = new Race(d);

	m_races[id] = p;
	m_race[d->getname()] = id;
	
	return p;
}

value_type Cache::GetRaceID(const std::string& name)
{
	lookup_mi it = m_race.find(name);
	if(it != m_race.end())
	{		
		return it->second;
	}

	long id = DatabaseMgr::Get()->GetSavableID(Tables::Get()->RACES, name);
	m_race[name] = id;

	return id;
}

Area* Cache::GetArea(value_type id)
{
	Area* p = m_areas[id];
	if (p)
		return p;

	// Area delete's db::Area on deletion
	db::Areas* d = new db::Areas(id);
	p = new Area(d);
	m_areas[id] = p;

	return p;
}

Room* Cache::GetRoom(value_type id)
{
	Room* p = m_rooms[id];
	if (p)
		return p;

	// Room delete's db::Room on deletion
	db::Rooms* d = new db::Rooms(id);
	p = new Room(d);
	m_rooms[id] = p;

	return p;
}

/*
value_type Cache::GetRoomID(value_type area, value_type x, value_type y)
{
	Coordinate c(area, xycoord(x,y));
	rlookup_mi it = m_room.find(c);
	if(it != m_room.end())
	{		
		return it->second;
	}

	Query q(DatabaseMgr::Get()->DBref());
	value_type num = (value_type)q.get_num(Global::Get()->sprintf(
		"SELECT %s FROM %s WHERE %s=%d AND x=%d AND y=%d;", 
		Tables::Get()->ROOMS->tableID().c_str(),
		Tables::Get()->ROOMS->tableName().c_str(),
		Tables::Get()->AREAS->tableID().c_str(),
		area, x, y));

	//m_room[c] = num;
	// TODO - Cache Room

	return num;
}
*/
// TODO - getroom()

Sector* Cache::GetSector(value_type id)
{
	Sector* p = m_sectors[id];
	if (p)
		return p;

	// Sector delete's db::Sectors on deletion
	db::Sectors* d = new db::Sectors(id);
	p = new Sector(d);
	
	m_sectors[id] = p;
	m_sector[d->getname()] = id;

	return p;
}

value_type Cache::GetSectorID(const std::string& name)
{
	lookup_mi it = m_sector.find(name);
	if(it != m_sector.end())
	{		
		return it->second;
	}

	long id = DatabaseMgr::Get()->GetSavableID(Tables::Get()->SECTORS, name);
	m_sector[name] = id;

	return id;
}

Colour* Cache::GetColour(value_type id)
{
	Colour* p = m_colours[id];
	if (p)
		return p;

	// Colour delete's db::Colours on deletion
	db::Colours* d = new db::Colours(id);
	p = new Colour(d);

	m_colours[id] = p;
	m_colour[d->getcode()] = id;
	
	return p;
}

value_type Cache::GetColourID(const std::string& code)
{
	lookup_mi it = m_colour.find(code);
	if(it != m_colour.end())
	{		
		return it->second;
	}

	long id = DatabaseMgr::Get()->GetSavableID(Tables::Get()->COLOURS, code, "code");
	m_colour[code] = id;

	return id;
}

/*
Exit* Cache::GetExit(value_type id)
{
	Exit* p = m_exits[id];
	if (p)
		return p;

	// Exit delete's db::Exits on deletion
	db::Exits* d = new db::Exits(id);
	p = new Exit(d);

	m_exits[id] = p;
	
	if(!p->Exists())
		Global::Get()->bugf("Cache::GetExit() was asked to get exit %d, which does not exist!\n", id);
	return p;
}

value_type Cache::GetExitID(value_type room, Exit::DIRECTION dir)
{
	roomexit e(room, dir);	
	elookup_mi it = m_exit.find(e);
	if(it != m_exit.end())
	{		
		return it->second;
	}

	Query q(DatabaseMgr::Get()->DBref());
	(value_type)q.get_num(Global::Get()->sprintf(
		"SELECT %s FROM %s WHERE %s=%d AND dir=%d;", 
		Tables::Get()->EXITS->tableID().c_str(),
		Tables::Get()->EXITS->tableName().c_str(),
		Tables::Get()->ROOMS->tableID().c_str(),
		room, (int)dir));

	m_exit[e] = id;

	return id;
}
*/

Command* Cache::GetCommand(value_type id)
{
	Command* p = m_commands[id];
	if (p)
		return p;

	// Command delete's db::Commands on deletion
	db::Commands* d = new db::Commands(id);
	p = new Command(d);
	
	m_commands[id] = p;
	m_command[d->getname()] = id;

	return p;
}

value_type Cache::GetCommandID(const std::string& name)
{
	lookup_mi it = m_command.find(name);
	if(it != m_command.end())
	{		
		return it->second;
	}

	long id = DatabaseMgr::Get()->GetSavableID(Tables::Get()->COMMANDS, name);
	m_command[name] = id;

	return id;
}

GrantGroup* Cache::GetGrantGroup(value_type id)
{
	GrantGroup* p = m_grantgroups[id];
	if(p)
		return p;
		
	db::GrantGroups* d = new db::GrantGroups(id);
	p = new GrantGroup(d);
	
	m_grantgroups[id] = p;
	m_grantgroup[d->getname()] = id;
	
	return p;
}

value_type Cache::GetGrantGroupID(const std::string& name)
{
	lookup_mi it = m_grantgroup.find(name);
	if(it != m_grantgroup.end())
	{		
		return it->second;
	}

	long id = DatabaseMgr::Get()->GetSavableID(Tables::Get()->GRANTGROUPS, name);
	m_grantgroup[name] = id;

	return id;
}

Permission* Cache::GetPermission(value_type account, value_type grantgroup)
{
	twokey key(account, grantgroup);
	Permission* p = m_permissions[key];
	if (p)
		return p;

	// Permission delete's db::Permissions on deletion
	db::Permissions* d = new db::Permissions(account, grantgroup);
	p = new Permission(d);
	
	m_permissions[key] = p;

	return p;
}

void Cache::CloseAccount(value_type accountid)
{
	Account* p = m_accounts[accountid];
	if(p)
		m_account.erase(p->getName());

	m_accounts.erase(accountid);
}

void Cache::CloseCharacter(value_type characterid)
{
	Character* p = m_characters[characterid];
	if(p)
		m_character.erase(p->getName());
		
	m_characters.erase(characterid);
}

void Cache::ClosePCharacter(value_type characterid)
{
	PCharacter* p = m_players[characterid];
	if(p)
		m_character.erase(p->getName());

	m_players.erase(characterid);
}

void Cache::CloseMCharacter(value_type characterid)
{
	MCharacter* p = m_mobiles[characterid];
	if(p)
		m_character.erase(p->getName());
		
	m_mobiles.erase(characterid);
}

void Cache::CloseRace(value_type raceid)
{
	Race* p = m_races[raceid];
	if(p)
		m_race.erase(p->getName());
	
	m_races.erase(raceid);
}

void Cache::CloseArea(value_type areaid)
{
	m_areas.erase(areaid);
}

void Cache::CloseRoom(value_type roomid)
{
	// Room* p = m_rooms[roomid];
	m_rooms.erase(roomid);
}

void Cache::CloseSector(value_type sectorid)
{
	m_sectors.erase(sectorid);
}

/*
void Cache::CloseExit(value_type exitid)
{
	Exit* p = m_exits[exitid];
	if(p && p->m_exit)
		m_exit.erase(roomexit(p->m_exit->fkroom, Exit::DIRECTION(p->m_exit->dir)));

	m_exits.erase(exitid);
}
*/

void Cache::CloseColour(value_type colourcode)
{
	Colour* p = m_colours[colourcode];
	if(p)
		m_colour.erase(p->getCode());

	m_colours.erase(colourcode);
}

void Cache::CloseCommand(value_type commandid)
{
	Command* p = m_commands[commandid];
	if(p)
		m_command.erase(p->getName());

	m_commands.erase(commandid);
}

void Cache::CloseGrantGroup(value_type grantgroupid)
{
	GrantGroup* p = m_grantgroups[grantgroupid];
	if(p)
		m_grantgroup.erase(p->getName());

	m_grantgroups.erase(grantgroupid);
}

void Cache::ClosePermission(value_type account, value_type permission)
{
	m_permissions.erase(twokey(account, permission));	
}
#endif
