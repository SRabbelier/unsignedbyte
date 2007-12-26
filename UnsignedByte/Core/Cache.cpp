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

#include "Cache.h"
#include "UBSocket.h"
#include "DatabaseMgr.h"
#include "Global.h"
#include "db.h"

#include "Account.h"
#include "PCharacter.h"
#include "MCharacter.h"
#include "Race.h"
#include "Room.h"
#include "Sector.h"
#include "Colour.h"
#include "Command.h"
#include "GrantGroup.h"
#include "Permission.h"

using namespace mud;

/**
 *
 *	 Adding
 *	 New
 *	 Rows
 *	 Functionality
 * 
 */

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
 * Lookup
 * By Field
 * Functionality 
 *
 */ 

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

/**
 * Entity
 * Caching
 * Functions 
 */ 

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

/**
 * Belongs to CharacterAccount
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
