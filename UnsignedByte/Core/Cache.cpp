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

bool Cache::isActive(value_type id)
{
	return m_pcharactersByKey.find(id) != m_pcharactersByKey.end();
}

bool Cache::isActive(cstring value)
{
	return m_pcharactersByName.find(value) != m_pcharactersByName.end();
}

/**
 *
 *	 Adding
 *	 New
 *	 Rows
 *	 Functionality
 * 
 */ 

value_type Cache::AddAccount()
{
	printf("Creating new local instance...\n");
	db::Accounts d;
	printf("Saving it now...\n");
	d.save();
	printf("Requesting account id...\n");
	value_type id = d.getaccountid();
	if(id == 0)
		Global::Get()->bug("Cache::AddAcount(), id = 0");
		
	return id;
}

value_type Cache::AddArea()
{
	db::Areas d;
	d.save();
	value_type id = d.getareaid();
	if(id == 0)
		Global::Get()->bug("Cache::AddArea(), id = 0");
		
	return id;
}

value_type Cache::AddCharacter()
{
	db::Characters d;
	d.save();
	value_type id = d.getcharacterid();
	if(id == 0)
		Global::Get()->bug("Cache::AddCharacter(), id = 0");
		
	return id;
}

value_type Cache::AddColour()
{
	db::Colours d;
	d.save();
	value_type id = d.getcolourid();
	if(id == 0)
		Global::Get()->bug("Cache::AddColour(), id = 0");
	
	return id;
}

value_type Cache::AddCommand()
{
	db::Commands d;
	d.save();
	value_type id = d.getcommandid();
	if(id == 0)
		Global::Get()->bug("Cache::AddCommand(), id = 0");
	
	return id;
}

value_type Cache::AddGrantGroup()
{
	db::GrantGroups d;
	d.save();
	value_type id = d.getgrantgroupid();
	if(id == 0)
		Global::Get()->bug("Cache::AddGrantGroup(), id = 0");
	
	return id;
}

value_type Cache::AddRace()
{
	db::Races d;
	d.save();
	value_type id = d.getraceid();
	if(id == 0)
		Global::Get()->bug("Cache::AddRace(), id = 0");
	
	return id;
}

value_type Cache::AddRoom()
{
	db::Rooms d;
	d.save();
	value_type id = d.getroomid();
	if(id == 0)
		Global::Get()->bug("Cache::AddRoom(), id = 0");
	
	return id;
}

value_type Cache::AddSector()
{	
	db::Sectors d;
	d.save();
	value_type id = d.getsectorid();
	if(id == 0)
		Global::Get()->bug("Cache::AddSector(), id = 0");
	
	return id;	
}

/**
 *
 *   Wrapped
 *   Database
 *   Object
 *	 Retreival 
 * 
 */

Account* Cache::GetAccountByKey(value_type id)
{
	Account* p = m_accountByKey[id];
	if (p)
		return p;

	db::Accounts* d = db::Accounts::bykey(id);
	p = cacheAccount(d);
	return p;
}

Account* Cache::GetAccountByName(cstring value)
{
	Account* p = m_accountByName[value];
	if(p)
		return p;

	db::Accounts* d = db::Accounts::byname(value);
	p = cacheAccount(d);
	
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

mud::Character* Cache::GetCharacterByKey(value_type id)
{
	Character* p = m_characterByKey[id];
	if(p)
		return p;

	db::Characters* d = db::Characters::bykey(id);
	p = cacheCharacter(d);
	return p;
}

mud::Character* Cache::GetCharacterByName(cstring value)
{
	Character* p = m_characterByName[value];
	if(p)
		return p;
		
	db::Characters* d = db::Characters::byname(value);
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

mud::Colour* Cache::GetColourByName(cstring value)
{
	Colour* p = m_colourByName[value];
	if(p)
		return p;

	db::Colours* d = db::Colours::byname(value);
	p = cacheColour(d);
	return p;
}

mud::Colour* Cache::GetColourByCode(cstring value)
{
	Colour* p = m_colourByCode[value];
	if(p)
		return p;

	db::Colours* d = db::Colours::bycode(value);
	p = cacheColour(d);
	return p;
}

mud::Command* Cache::GetCommandByKey(value_type id)
{
	Command* p = m_commandByKey[id];
	if(p)
		return p;
		
	db::Commands* d = db::Commands::bykey(id);
	p = cacheCommand(d);
	return p;
}

mud::Command* Cache::GetCommandByName(cstring value)
{
	Command* p = m_commandByName[value];
	if(p)
		return p;
		
	db::Commands* d = db::Commands::byname(value);
	p = cacheCommand(d);
	return p;
}

mud::GrantGroup* Cache::GetGrantGroupByKey(value_type id)
{
	GrantGroup* p = m_grantgroupByKey[id];
	if(p)
		return p;
		
	db::GrantGroups* d = db::GrantGroups::bykey(id);
	p = cacheGrantGroup(d);
	return p;
}

mud::GrantGroup* Cache::GetGrantGroupByName(cstring value)
{
	GrantGroup* p = m_grantgroupByName[value];
	if(p)
		return p;
		
	db::GrantGroups* d = db::GrantGroups::byname(value);
	p = cacheGrantGroup(d);
	return p;
}

mud::MCharacter* Cache::GetMCharacterByKey(value_type id)
{
	MCharacter* p = m_mobileByKey[id];
	if(p)
		return p;
		
	db::Characters* d = db::Characters::bykey(id);
	p = cacheMCharacter(d);
	return p;
}

mud::MCharacter* Cache::GetMCharacterByName(cstring value)
{
	MCharacter* p = m_mobileByName[value];
	if(p)
		return p;
		
	db::Characters* d = db::Characters::byname(value);
	p = cacheMCharacter(d);
	return p;
}

mud::PCharacter* Cache::GetPCharacterByKey(value_type id)
{
	PCharacter* p = m_playerByKey[id];
	if(p)
		return p;
		
	std::ostringstream err;
	err << "Cache::GetPCharacterByKey(), The id '" << id << "' has not been loaded yet.";
	throw std::invalid_argument(err.str());
}

mud::PCharacter* Cache::GetPCharacterByName(cstring value)
{
	PCharacter* p = m_playerByName[value];
	if(p)
		return p;
		
	std::ostringstream err;
	err << "Cache::GetPCharacterByKey(), No character with name '" << value << "' has not been loaded yet.";
	throw std::invalid_argument(err.str());	
}

mud::PCharacter* Cache::LoadPCharacterByKey(UBSocket* sock, value_type id)
{
	PCharacter* p = m_playerByKey[id];
	if(p)
	{
		std::ostringstream err;
		err << "Cache::LoadPCharacterByKey(), id '" << id << "' has already been loaded.";
		throw std::invalid_argument(err.str());
	}
	
	db::Characters* d = db::Characters::bykey(id);
	p = cachePCharacter(sock, d);
	return p;
}

mud::PCharacter* Cache::LoadPCharacterByName(UBSocket* sock, cstring value)
{
	PCharacter* p = m_playerByName[value];
	if(p)
	{
		std::ostringstream err;
		err << "Cache::LoadPCharacterByKey(), A character with name '" << value << "' has already been loaded.";
		throw std::invalid_argument(err.str());
	}	
	
	db::Characters* d = db::Characters::byname(value);
	p = cachePCharacter(sock, d);
	return p;
}

mud::Permission* Cache::GetPermissionByKeys(value_type account, value_type grantgroup)
{
	twoValueKey key(account, grantgroup);
	Permission* p = m_permissionByKeys[key];
	if(p)
		return p;
		
	db::Permissions* d = db::Permissions::bykey(account, grantgroup);
	p = new Permission(d);
	m_permissionByKeys[key] = p;
	return p;	
}
		
mud::Race* Cache::GetRaceByKey(value_type id)
{
	Race* p = m_raceByKey[id];
	if(p)
		return p;
		
	db::Races* d = db::Races::bykey(id);
	p = cacheRace(d);
	return p;
}

mud::Race* Cache::GetRaceByName(cstring value)
{
	Race* p = m_raceByName[value];
	if(p)
		return p;
		
	db::Races* d = db::Races::byname(value);
	p = cacheRace(d);
	return p;
}

mud::Room* Cache::GetRoomByKey(value_type id)
{
	Room* p = m_roomByKey[id];
	if(p)
		return p;
		
	db::Rooms* d = db::Rooms::bykey(id);
	p = cacheRoom(d);
	return p;
}

mud::Sector* Cache::GetSectorByKey(value_type id)
{
	Sector* p = m_sectorByKey[id];
	if(p)
		return p;
		
	db::Sectors* d = db::Sectors::bykey(id);
	p = cacheSector(d);
	return p;
}

mud::Sector* Cache::GetSectorByName(cstring value)
{
	Sector* p = m_sectorByName[value];
	if(p)
		return p;
		
	db::Sectors* d = db::Sectors::byname(value);
	p = cacheSector(d);
	return p;
}

/**
 *
 * Database
 * Relation
 * Checking 
 *
 */ 

bool Cache::existsCharacterWithAccount(value_type characterid, value_type accountid)
{
	twoValueKey key(accountid, characterid);
	db::CharacterAccount* d = m_characteraccountByKey[key];
	if(d)
		return d->exists();
	
	d = db::CharacterAccount::bykey(accountid, characterid);
	m_characteraccountByKey[key] = d;
	return d->exists();
}


/**
 *
 * Lookup
 * By Field
 * Functionality 
 *
 */ 

value_type Cache::lookupAccountByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupAccountByName.find(value);
	if(it != m_lookupAccountByName.end())
		return it->second;
	
	value_type id = db::Accounts::lookupname(value);
	m_lookupAccountByName[value] = id;
	return id;
}

value_type Cache::lookupCharacterByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupCharacterByName.find(value);
	if(it != m_lookupCharacterByName.end())
		return it->second;
	
	value_type id = db::Characters::lookupname(value);
	m_lookupCharacterByName[value] = id;
	return id;
}

value_type Cache::lookupColourByCode(cstring value)
{
	reverseStringKey::iterator it = m_lookupColourByCode.find(value);
	if(it != m_lookupColourByCode.end())
		return it->second;
	
	value_type id = db::Colours::lookupcode(value);
	m_lookupColourByCode[value] = id;
	return id;
}

value_type Cache::lookupColourByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupColourByName.find(value);
	if(it != m_lookupColourByName.end())
		return it->second;
	
	value_type id = db::Colours::lookupname(value);
	m_lookupColourByName[value] = id;
	return id;
}

value_type Cache::lookupCommandByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupCommandByName.find(value);
	if(it != m_lookupCommandByName.end())
		return it->second;
	
	value_type id = db::Commands::lookupname(value);
	m_lookupCommandByName[value] = id;
	return id;
}

value_type Cache::lookupGrantGroupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupGrantGroupByName.find(value);
	if(it != m_lookupGrantGroupByName.end())
		return it->second;
	
	value_type id = db::GrantGroups::lookupname(value);
	m_lookupGrantGroupByName[value] = id;
	return id;
}

value_type Cache::lookupRaceByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupRaceByName.find(value);
	if(it != m_lookupRaceByName.end())
		return it->second;
	
	value_type id = db::Races::lookupname(value);
	m_lookupRaceByName[value] = id;
	return id;
}

value_type Cache::lookupSectorByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupSectorByName.find(value);
	if(it != m_lookupSectorByName.end())
		return it->second;
	
	value_type id = db::Sectors::lookupname(value);
	m_lookupSectorByName[value] = id;
	return id;
}

/**
 *
 * Close
 * Entity
 * Functionality 
 *
 */ 

void Cache::CloseAccount(value_type id)
{
	accounts_m::iterator key = m_accountByKey.find(id);
	accounts_ms::iterator name = m_accountByName.find(key->second->getName());
	m_accountByKey.erase(key);
	m_accountByName.erase(name);
}

void Cache::CloseArea(value_type id)
{
	areas_m::iterator key = m_areaByKey.find(id);
	m_areaByKey.erase(key);
}

void Cache::CloseCharacter(value_type id)
{
	characters_m::iterator key = m_characterByKey.find(id);
	characters_ms::iterator name = m_characterByName.find(key->second->getName());
	m_characterByKey.erase(key);
	m_characterByName.erase(name);
}

void Cache::CloseColour(value_type id)
{
	colours_m::iterator key = m_colourByKey.find(id);
	colours_ms::iterator name = m_colourByName.find(key->second->getName());
	colours_ms::iterator code = m_colourByCode.find(key->second->getCode());
	m_colourByKey.erase(key);
	m_colourByName.erase(name);
	m_colourByCode.erase(code);
}

void Cache::CloseCommand(value_type id)
{
	commands_m::iterator key = m_commandByKey.find(id);
	commands_ms::iterator name = m_commandByName.find(key->second->getName());
	m_commandByKey.erase(key);
	m_commandByName.erase(name);
}

void Cache::CloseGrantGroup(value_type id)
{
	grantgroups_m::iterator key = m_grantgroupByKey.find(id);
	grantgroups_ms::iterator name = m_grantgroupByName.find(key->second->getName());
	m_grantgroupByKey.erase(key);
	m_grantgroupByName.erase(name);
}

void Cache::CloseMCharacter(value_type id)
{
	mobiles_m::iterator key = m_mobileByKey.find(id);
	mobiles_ms::iterator name = m_mobileByName.find(key->second->getName());
	m_mobileByKey.erase(key);
	m_mobileByName.erase(name);
}

void Cache::ClosePCharacter(value_type id)
{
	players_m::iterator key = m_playerByKey.find(id);
	players_ms::iterator name = m_playerByName.find(key->second->getName());
	m_playerByKey.erase(key);
	m_playerByName.erase(name);
}

void Cache::ClosePermission(value_type account, value_type permission)
{
	permissions_m::iterator key = m_permissionByKeys.find(twoValueKey(account, permission));
	m_permissionByKeys.erase(key);
}

void Cache::CloseRace(value_type id)
{
	races_m::iterator key = m_raceByKey.find(id);
	races_ms::iterator name = m_raceByName.find(key->second->getName());
	m_raceByKey.erase(key);
	m_raceByName.erase(name);	
}

void Cache::CloseRoom(value_type id)
{
	rooms_m::iterator key = m_roomByKey.find(id);
	m_roomByKey.erase(key);
}

void Cache::CloseSector(value_type id)
{
	sectors_m::iterator key = m_sectorByKey.find(id);
	sectors_ms::iterator name = m_sectorByName.find(key->second->getName());
	m_sectorByKey.erase(key);
	m_sectorByName.erase(name);	
}

Account* Cache::cacheAccount(db::Accounts* d)
{
	Account* p = new Account(d);
	m_accountByKey[d->getaccountid()] = p;
	m_accountByName[d->getname()] = p;
	return p;
}

Area* Cache::cacheArea(db::Areas* d)
{
	Area* p = new Area(d);
	m_areaByKey[d->getareaid()] = p;
	return p;
}

Character* Cache::cacheCharacter(db::Characters *d)
{
	Character* p = new Character(d);
	m_characterByKey[d->getcharacterid()] = p;
	m_characterByName[d->getname()] = p;
	return p;
}

Colour* Cache::cacheColour(db::Colours* d)
{
	Colour* p = new Colour(d);
	m_colourByKey[d->getcolourid()] = p;
	m_colourByName[d->getname()] = p;
	m_colourByCode[d->getcode()] = p;
	return p;
}

Command* Cache::cacheCommand(db::Commands* d)
{
	Command* p = new Command(d);
	m_commandByKey[d->getcommandid()] = p;
	m_commandByName[d->getname()] = p;
	return p;
}

GrantGroup* Cache::cacheGrantGroup(db::GrantGroups* d)
{
	GrantGroup* p = new GrantGroup(d);
	m_grantgroupByKey[d->getgrantgroupid()] = p;
	m_grantgroupByName[d->getname()] = p;
	return p;
}

MCharacter* Cache::cacheMCharacter(db::Characters* d)
{
	MCharacter* p = new MCharacter(d);
	m_mobileByKey[d->getcharacterid()] = p;
	m_mobileByName[d->getname()] = p;
	return p;
}

PCharacter* Cache::cachePCharacter(UBSocket* sock, db::Characters* d)
{
	PCharacter* p = new PCharacter(sock, d);
	m_playerByKey[d->getcharacterid()] = p;
	m_pcharactersByKey.insert(d->getcharacterid());
	m_playerByName[d->getname()] = p;
	m_pcharactersByName.insert(d->getname());
	return p;
}

Race* Cache::cacheRace(db::Races* d)
{
	Race* p = new Race(d);
	m_raceByKey[d->getraceid()] = p;
	m_raceByName[d->getname()] = p;
	return p;
}

Room* Cache::cacheRoom(db::Rooms* d)
{
	Room* p = new Room(d);
	m_roomByKey[d->getroomid()] = p;
	return p;
}

Sector* Cache::cacheSector(db::Sectors* d)
{
	Sector* p = new Sector(d);
	m_sectorByKey[d->getsectorid()] = p;
	m_sectorByName[d->getname()] = p;
	return p;
}
