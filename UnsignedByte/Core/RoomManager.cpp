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

#include "RoomManager.h"
#include "Room.h"
#include "Global.h"

#include "Table.h"
#include "Tables.h"

using mud::RoomManager;
using mud::Room;
using mud::RoomPtr;

std::vector<std::string> RoomManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr RoomManager::GetTable()
{
	return db::TableImpls::Get()->ROOMS;
}

value_type RoomManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->ROOMS);
	manager->save();
	value_type id = manager->getkey(db::RoomsFields::Get()->ROOMID);
	if(id == 0)
		Global::Get()->bug("RoomManager::Add(), id = 0");
	
	return id;	
}

mud::RoomPtr RoomManager::GetByKey(value_type id)
{
	KeyPtr key(new Key(db::RoomsFields::Get()->ROOMID, id));
	Keys keys;
	keys[db::RoomsFields::Get()->ROOMID.get()] = key;
	SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->ROOMS, keys);
	RoomPtr p(new Room(manager));
	return p;
}
