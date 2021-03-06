/***************************************************************************
 *   Copyright (C) 2008 by Sverre Rabbelier                                *
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
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

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

KeysPtr RoomManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->ROOMS);
	manager->save();
	return manager->getkeys();
}

mud::RoomPtr RoomManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->ROOMS));
	KeyPtr key(new Key(db::RoomsFields::Get()->ROOMID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	RoomPtr p(new Room(manager));
	return p;
}
