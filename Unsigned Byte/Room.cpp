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
#include <winsock2.h>
#endif

#include <string>
#include <stdarg.h>
#include <stdexcept>

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "ub.h"

#include "Room.h"
#include "Area.h"
#include "Exit.h"
#include "Sector.h"
#include "Character.h"

Room::Room(db::Rooms* room) :
m_room(room)
{
	if(m_room == NULL)
		throw std::invalid_argument("Room::Room(), m_room == NULL!");
}

Room::~Room(void)
{	
	delete m_room;
	m_room = NULL;
}

Characters Room::getCharacters()
{
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(
		Tables::Get()->CHARACTERS, 
		m_room->roomid, 
		Tables::Get()->ROOMS->tableID());

	Characters result;
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = *it;
		if(!Cache::Get()->isActive(id))
			continue;

		try
		{
			Character* Ch = Cache::Get()->GetCharacter(id);
			result.push_back(Ch);
		}
		catch(std::exception& e)
		{
			Global::Get()->bug(e.what());
		}
	}

	return result;
}

void Room::Send(const std::string& msg)
{
	Characters inroom = getCharacters();

	for(Characters::iterator it = inroom.begin(); it != inroom.end(); it++)
	{
		(*it)->OnSend(msg);
	}
}

void Room::Sendf(char* format, ...)
{
	va_list args;
	va_start(args, format);
	Send(Global::Get()->sprint(args, format));
	va_end(args);
}

void Room::Delete()
{
	m_room->erase();
}

void Room::Save()
{
	m_room->save();
}

bool Room::Exists()
{
	return m_room->roomid;
}

std::string Room::CreateMap(long id, long origx, long origy)
{
	std::string result;
	/*
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, id);

	if(count <= 0)
	{
		Global::Get()->bug("EditorMap::Map::Run() with areacount <= 0!\n");
		return std::string("For some reason the area the room you are in does not belong to an area?!\n");
	}

	if(count >= 2)
	{
		Global::Get()->bugf("EditorMap::Map::Run() with areacount '%d'!\n", count);
		return std::string(Global::Get()->sprintf("For some reason the area the room you are in exists multiple times in the database?!n"));
	}

	Area* p = Cache::Get()->GetArea(id);

	for(long y = 1; y <= p->getHeight(); y++)
	{
		std::string toprow;
		std::string thisrow;
		std::string bottomrow;

		for(long x = 1; x <= p->getWidth(); x++)
		{
			long rid = Cache::Get()->GetRoomID(id, x, y);
			long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->ROOMS, rid);
			if(!count)
			{
				if(x == origx && y == origy)
				{
					toprow.append   ("   ");
					thisrow.append  (" o "); // Empty, current
					bottomrow.append("   ");
				}
				else
				{
					toprow.append   ("   ");
					thisrow.append  (" . "); // Empty, not current
					bottomrow.append("   ");
				}

			}
			else 
			{
				Room* room = Cache::Get()->GetRoom(rid);

				if(!room->isClosed(Exit::NORTHWEST))
					toprow.append("\\");
				else
					toprow.append(" ");

				if(!room->isClosed(Exit::NORTH))
					toprow.append("|");
				else
					toprow.append(" ");

				if(!room->isClosed(Exit::NORTHEAST))
					toprow.append("/");
				else
					toprow.append(" ");

				if(!room->isClosed(Exit::WEST))
					thisrow.append("-");
				else
					thisrow.append(" ");

				if(x == origx && y == origy)
				{
					thisrow.append("*");
				}
				else
				{
					try
					{
						Sector* sector = Cache::Get()->GetSector(room->getSector());
						thisrow.append(sector->getSymbol());
					}
					catch(std::exception& e)
					{
						Global::Get()->log(e.what());
						thisrow.append("?");
					}					
				}

				if(!room->isClosed(Exit::EAST))
					thisrow.append("-");
				else
					thisrow.append(" ");

				if(!room->isClosed(Exit::SOUTHWEST))
					bottomrow.append("/");
				else
					bottomrow.append(" ");

				if(!room->isClosed(Exit::SOUTH))
					bottomrow.append("|");
				else
					bottomrow.append(" ");

				if(!room->isClosed(Exit::SOUTHEAST))
					bottomrow.append("\\");
				else
					bottomrow.append(" ");
			}
		}

		result.append(toprow);
		result.append("\n");
		result.append(thisrow);
		result.append("\n");
		result.append(bottomrow);
		result.append("\n");
	}

	*/
	return result;
}

std::vector<std::string> Room::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Name: '%s'.\n", getName().c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.\n", getDescription().c_str()));
	try
	{
		Sector* sector = Cache::Get()->GetSector(getSector());
		result.push_back(Global::Get()->sprintf("Sector: '%s' (%s).\n", sector->getName().c_str(), sector->getSymbol().c_str()));
	}
	catch(std::exception& e)
	{
		Global::Get()->bug(e.what());
	}
	
	return result;
}

std::string Room::ShowShort()
{
	std::string result;
	
	return result;
}

std::vector<std::string> Room::List()
{
	std::vector<std::string> result;
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->ROOMS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		Room* room = Cache::Get()->GetRoom(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(room->ShowShort());
		result.push_back(line);
	}
	return result;
}

void Room::Close(Room* room)
{
	if(room == NULL)
		throw std::invalid_argument("Room::Close(), room == NULL!");
	
	Cache::Get()->CloseRoom(room->m_room->roomid);
	delete room;
}

Table* Room::getTable() const
{
	return Tables::Get()->ROOMS;
}

