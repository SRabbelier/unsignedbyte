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

#include "Cache.h"
#include "UBSocket.h"
#include "DatabaseMgr.h"
#include "Global.h"
#include "ub.h"

#include "Account.h"
#include "PCharacter.h"
#include "MCharacter.h"
#include "Race.h"
#include "Area.h"
#include "Room.h"
#include "Sector.h"
#include "Exit.h"
#include "Colour.h"
#include "Command.h"
#include "GrantGroup.h"
#include "Permission.h"

long Cache::AddAccount()
{
	db::Accounts p(DatabaseMgr::Get()->DB());
	long id = p.insert();

	return id;
}

long Cache::AddCharacter()
{
	db::Characters p(DatabaseMgr::Get()->DB());
	long id = p.insert();

	return id;
}

long Cache::AddRace()
{
	db::Races p(DatabaseMgr::Get()->DB());
	long id = p.insert();

	return id;
}

long Cache::AddArea()
{
	db::Areas p(DatabaseMgr::Get()->DB());
	p.height = 1;
	p.width = 1;
	long id = p.insert();
	
	return id;
}

long Cache::AddRoom()
{
	db::Rooms p(DatabaseMgr::Get()->DB());
	long id = p.insert();

	return id;
}

long Cache::AddSector()
{
	db::Sectors p(DatabaseMgr::Get()->DB());
	long id = p.insert();

	return id;
}

/*
long Cache::AddExit()
{
	db::Exits ex(DatabaseMgr::Get()->DB());
	long id = ex.insert();

	return id;
}
*/

long Cache::AddColour()
{
	db::Colours p(DatabaseMgr::Get()->DB());
	long id = p.insert();

	return id;
}

long Cache::AddCommand()
{
	db::Commands p(DatabaseMgr::Get()->DB());
	long id = p.insert();

	return id;
}

long Cache::AddGrantGroup()
{
	db::GrantGroups p(DatabaseMgr::Get()->DB());
	long id = p.insert();
	
	return id;
}

long Cache::AddPermission()
{
	db::Permissions p(DatabaseMgr::Get()->DB());
	long id = p.insert();
	
	return id;
}

bool Cache::IsMobile(long id)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->CHARACTERS, id);
	if(count <= 0)
		return false;

	MCharacter* mobile = GetMCharacter(id);
	return (mobile->getID() == 1);
}

Account* Cache::GetAccount(long id)
{
	Account* p = m_accounts[id];
	if (p)
		return p;

	// Account delete's db::Account on deletion
	db::Accounts* d = new db::Accounts(DatabaseMgr::Get()->DBref(), id);
	p = new Account(d);

	m_accounts[id] = p;
	m_account[d->name] = id;

	if(!p->Exists())
		Global::Get()->bugf("Cache::GetAccount() was asked to get account %d, which does not exist!\n", id);
	
	return p;
}

long Cache::GetAccountID(const std::string& name)
{
	lookup_mi it = m_account.find(name);
	if(it != m_account.end())
	{		
		return it->second;
	}

	long num = DatabaseMgr::Get()->GetSavableID(Tables::Get()->ACCOUNTS, name);

	m_account[name] = num;

	return num;
}

PCharacter* Cache::GetPCharacter(UBSocket* sock, long id)
{
	PCharacter* p = m_players[id];
	if (p)
	{
		p->m_sock = sock;
		return p;
	}

	// Character delete's db::Characters on deletion
	db::Characters* d = new db::Characters(DatabaseMgr::Get()->DBref(), id);
	p = new PCharacter(sock, d);

	m_players[id] = p;
	m_character[d->name] = id;

	if(!p->Exists())
		Global::Get()->bugf("Cache::GetPCharacter() was asked to get character %d, which does not exist!\n", id);

	return p;
}

MCharacter* Cache::GetMCharacter(long id)
{
	MCharacter* p = m_mobiles[id];
	if (p)
		return p;

	// MCharacter delete's db::Characters on deletion
	db::Characters* d = new db::Characters(DatabaseMgr::Get()->DBref(), id);
	p = new MCharacter(d);

	m_mobiles[id] = p;
	m_character[d->name] = id;

	if(!p->Exists())
		Global::Get()->bugf("Cache::GetMCharacter() was asked to get character %d, which does not exist!\n", id);

	return p;
}

Character* Cache::GetCharacter(long id)
{
	Character* p = m_characters[id];
	if (p)
		return p;

	// Character delete's db::Characters on deletion
	db::Characters* d = new db::Characters(DatabaseMgr::Get()->DBref(), id);
	p = new Character(d);

	m_characters[id] = p;
	m_character[d->name] = id;

	if(!p->Exists())
		Global::Get()->bugf("Cache::GetCharacter() was asked to get character %d, which does not exist!\n", id);

	return p;
}

long Cache::GetPCharacterID(const std::string& name)
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

bool Cache::isActive(long id)
{
	players_m::iterator it = m_players.find(id);
	if(it == m_players.end())
		return false;

	return true;
}

bool Cache::isActive(cstring name)
{
	lookup_mi it = m_character.find(name);
	if(it == m_character.end())
		return false;

	return isActive(it->second);
}
	
Race* Cache::GetRace(long id)
{
	Race* p = m_races[id];
	if (p)
		return p;

	// Races delete's db::Races on deletion
	db::Races* d = new db::Races(DatabaseMgr::Get()->DBref(), id);
	p = new Race(d);

	m_races[id] = p;
	m_race[d->name] = id;
	
	if(!p->Exists())
		Global::Get()->bugf("Cache::GetRace() was asked to get race %d, which does not exist!\n", id);
	return p;
}

long Cache::GetRaceID(const std::string& name)
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

Area* Cache::GetArea(long id)
{
	Area* p = m_areas[id];
	if (p)
		return p;

	// Area delete's db::Area on deletion
	p = new Area(new db::Areas(DatabaseMgr::Get()->DBref(), id));
	m_areas[id] = p;

	if(!p->Exists())	
		Global::Get()->bugf("Cache::GetArea() was asked to get area %d, which does not exist!\n", id);

	return p;
}

Room* Cache::GetRoom(long id)
{
	Room* p = m_rooms[id];
	if (p)
		return p;

	// Room delete's db::Room on deletion
	p = new Room(new db::Rooms(DatabaseMgr::Get()->DBref(), id));
	m_rooms[id] = p;

	if(!p->Exists())
		Global::Get()->bugf("Cache::GetRoom() was asked to get room %d, which does not exist!\n", id);

	return p;
}

/*
long Cache::GetRoomID(long area, long x, long y)
{
	Coordinate c(area, xycoord(x,y));
	rlookup_mi it = m_room.find(c);
	if(it != m_room.end())
	{		
		return it->second;
	}

	Query q(DatabaseMgr::Get()->DBref());
	long num = (long)q.get_num(Global::Get()->sprintf(
		"SELECT %s FROM %s WHERE %s=%d AND x=%d AND y=%d;", 
		Tables::Get()->ROOMS->tableID().c_str(),
		Tables::Get()->ROOMS->tableName().c_str(),
		Tables::Get()->AREAS->tableID().c_str(),
		area, x, y));

	//m_room[c] = num;
	// TODO

	return num;
}
*/

Sector* Cache::GetSector(long id)
{
	Sector* p = m_sectors[id];
	if (p)
		return p;

	// Sector delete's db::Sectors on deletion
	db::Sectors* d = new db::Sectors(DatabaseMgr::Get()->DBref(), id);
	p = new Sector(d);
	
	m_sectors[id] = p;
	m_sector[d->name] = id;

	if(!p->Exists())	
		Global::Get()->bugf("Cache::GetSector() was asked to get sector %d, which does not exist!\n", id);
	return p;
}

long Cache::GetSectorID(const std::string& name)
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

Colour* Cache::GetColour(long id)
{
	Colour* p = m_colours[id];
	if (p)
		return p;

	// Colour delete's db::Colours on deletion
	db::Colours* d = new db::Colours(DatabaseMgr::Get()->DBref(), id);
	p = new Colour(d);

	m_colours[id] = p;
	m_colour[d->code] = id;
	
	if(!p->Exists())
		Global::Get()->bugf("Cache::GetColour() was asked to get colour %d, which does not exist!\n", id);
	return p;
}

long Cache::GetColourID(const std::string& code)
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
Exit* Cache::GetExit(long id)
{
	Exit* p = m_exits[id];
	if (p)
		return p;

	// Exit delete's db::Exits on deletion
	db::Exits* d = new db::Exits(DatabaseMgr::Get()->DBref(), id);
	p = new Exit(d);

	m_exits[id] = p;
	
	if(!p->Exists())
		Global::Get()->bugf("Cache::GetExit() was asked to get exit %d, which does not exist!\n", id);
	return p;
}

long Cache::GetExitID(long room, Exit::DIRECTION dir)
{
	roomexit e(room, dir);	
	elookup_mi it = m_exit.find(e);
	if(it != m_exit.end())
	{		
		return it->second;
	}

	Query q(DatabaseMgr::Get()->DBref());
	long id = (long)q.get_num(Global::Get()->sprintf(
		"SELECT %s FROM %s WHERE %s=%d AND dir=%d;", 
		Tables::Get()->EXITS->tableID().c_str(),
		Tables::Get()->EXITS->tableName().c_str(),
		Tables::Get()->ROOMS->tableID().c_str(),
		room, (int)dir));

	m_exit[e] = id;

	return id;
}
*/

Command* Cache::GetCommand(long id)
{
	Command* p = m_commands[id];
	if (p)
		return p;

	// Command delete's db::Commands on deletion
	db::Commands* d = new db::Commands(DatabaseMgr::Get()->DBref(), id);
	p = new Command(d);
	
	m_commands[id] = p;
	m_command[d->name] = id;

	if(!p->Exists())	
		Global::Get()->bugf("Cache::GetCommand() was asked to get command %d, which does not exist!\n", id);
	return p;
}

long Cache::GetCommandID(const std::string& name)
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

GrantGroup* Cache::GetGrantGroup(long id)
{
	GrantGroup* p = m_grantgroups[id];
	if(p)
		return p;
		
	db::GrantGroups* d = new db::GrantGroups(DatabaseMgr::Get()->DBref(), id);
	p = new GrantGroup(d);
	
	m_grantgroups[id] = p;
	m_grantgroup[d->name] = id;
	
	if(!p->Exists())
		Global::Get()->bugf("Cache::GetGrantGroup() was asked to get grant group %d, which does not exist!\n", id);
	
	return p;
}

long Cache::GetGrantGroupID(const std::string& name)
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

Permission* Cache::GetPermission(long id)
{
	Permission* p = m_permissions[id];
	if (p)
		return p;

	// Command delete's db::Commands on deletion
	db::Permissions* d = new db::Permissions(DatabaseMgr::Get()->DBref(), id);
	p = new Permission(d);
	
	m_permissions[id] = p;
	m_permission[permission(d->fkaccount, d->fkgrantgroup)] = id;

	if(!p->Exists())	
		Global::Get()->bugf("Cache::GetPermission() was asked to get permission %d, which does not exist!\n", id);
	return p;
}

long Cache::GetPermissionID(const long account, const long grantgroup)
{
	plookup_mi it = m_permission.find(permission(account, grantgroup));
	if(it != m_permission.end())
	{		
		return it->second;
	}

	Query q(DatabaseMgr::Get()->DBref());
	long id = (long)q.get_num(Global::Get()->sprintf(
		"SELECT %s FROM %s WHERE %s=%d AND %s=%d;", 
		Tables::Get()->PERMISSIONS->tableID().c_str(),
		Tables::Get()->PERMISSIONS->tableName().c_str(),
		Tables::Get()->ACCOUNTS->tableID().c_str(),
		account, 
		Tables::Get()->GRANTGROUPS->tableID().c_str(),
		grantgroup));

	m_permission[permission(account, grantgroup)] = id;

	return id;
}

void Cache::CloseAccount(long accountid)
{
	Account* p = m_accounts[accountid];
	if(p)
		m_account.erase(p->getName());

	m_accounts.erase(accountid);
}

void Cache::CloseCharacter(long characterid)
{
	Character* p = m_characters[characterid];
	if(p)
		m_character.erase(p->getName());
		
	m_characters.erase(characterid);
}

void Cache::ClosePCharacter(long characterid)
{
	PCharacter* p = m_players[characterid];
	if(p)
		m_character.erase(p->getName());

	m_players.erase(characterid);
}

void Cache::CloseMCharacter(long characterid)
{
	MCharacter* p = m_mobiles[characterid];
	if(p)
		m_character.erase(p->getName());
		
	m_mobiles.erase(characterid);
}

void Cache::CloseRace(long raceid)
{
	Race* p = m_races[raceid];
	if(p)
		m_race.erase(p->getName());
	
	m_races.erase(raceid);
}

void Cache::CloseArea(long areaid)
{
	m_areas.erase(areaid);
}

void Cache::CloseRoom(long roomid)
{
	// Room* p = m_rooms[roomid];
	m_rooms.erase(roomid);
}

void Cache::CloseSector(long sectorid)
{
	m_sectors.erase(sectorid);
}

/*
void Cache::CloseExit(long exitid)
{
	Exit* p = m_exits[exitid];
	if(p && p->m_exit)
		m_exit.erase(roomexit(p->m_exit->fkroom, Exit::DIRECTION(p->m_exit->dir)));

	m_exits.erase(exitid);
}
*/

void Cache::CloseColour(long colourcode)
{
	Colour* p = m_colours[colourcode];
	if(p)
		m_colour.erase(p->getCode());

	m_colours.erase(colourcode);
}

void Cache::CloseCommand(long commandid)
{
	Command* p = m_commands[commandid];
	if(p)
		m_command.erase(p->getName());

	m_commands.erase(commandid);
}

void Cache::CloseGrantGroup(long grantgroupid)
{
	GrantGroup* p = m_grantgroups[grantgroupid];
	if(p)
		m_grantgroup.erase(p->getName());

	m_grantgroups.erase(grantgroupid);
}

void Cache::ClosePermission(long permissionid)
{
	Permission* p = m_permissions[permissionid];
	if(p && p->m_permission)
		m_permission.erase(permission(p->m_permission->fkaccount, p->m_permission->fkgrantgroup));
	
	m_permissions.erase(permissionid);	
}
