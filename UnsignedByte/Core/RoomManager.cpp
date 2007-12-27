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

#include <string>
#include <stdexcept>

#include "RoomManager.h"
#include "Room.h"
#include "Global.h"

using mud::RoomManager;
using mud::Room;
using mud::RoomPtr;

std::vector<std::string> RoomManager::List()
{
	return GetTable()->tableList();
}

void RoomManager::Close(RoomPtr room)
{
	if(room == NULL)
		throw std::invalid_argument("Room::Close(), room == NULL!");
	
	Close(room->getID());
}

TablePtr RoomManager::GetTable()
{
	return Tables::Get()->ROOMS;
}

value_type RoomManager::Add()
{
	db::Rooms d;
	d.save();
	value_type id = d.getroomid();
	if(id == 0)
		Global::Get()->bug("RoomManager::AddRoom(), id = 0");
	
	return id;
}

mud::RoomPtr RoomManager::GetByKey(value_type id)
{
	RoomPtr p = m_byKey[id];
	if(p)
		return p;
		
	db::Rooms* d = db::Rooms::bykey(id);
	p = cacheRoom(d);
	return p;
}

void RoomManager::Close(value_type id)
{
	rooms_m::iterator key = m_byKey.find(id);
	m_byKey.erase(key);
}

RoomPtr RoomManager::cacheRoom(db::Rooms* d)
{
	RoomPtr p(new Room(d));
	m_byKey[d->getroomid()] = p;
	return p;
}
