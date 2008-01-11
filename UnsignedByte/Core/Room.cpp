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

#include <stdarg.h>

#include "Room.h"
#include "Area.h"
#include "Sector.h"
#include "SectorManager.h"
#include "Character.h"
#include "Global.h"

using mud::Room;

Room::Room(SavableManagerPtr room) :
m_room(room)
{
	if(m_room)
		throw std::invalid_argument("Room::Room(), m_room == NULL!");
}

Room::~Room(void)
{	
	
}

value_type Room::getID() const
{
	return m_room->getkey(db::RoomsFields::Get()->ROOMID)->getValue();
}

const std::string& Room::getName() const
{
	return m_room->getfield(db::RoomsFields::Get()->NAME)->getStringValue();
}

const std::string& Room::getDescription() const
{
	return m_room->getfield(db::RoomsFields::Get()->DESCRIPTION)->getStringValue();
}

value_type Room::getSector() const
{
	return m_room->getfield(db::RoomsFields::Get()->FKSECTORS)->getIntegerValue();
}

value_type Room::getArea() const
{
	return m_room->getfield(db::RoomsFields::Get()->FKAREAS)->getIntegerValue();
}

value_type Room::getHeight() const
{
	return m_room->getfield(db::RoomsFields::Get()->HEIGHT)->getIntegerValue();
}

value_type Room::getWidth() const
{
	return m_room->getfield(db::RoomsFields::Get()->WIDTH)->getIntegerValue();
}

value_type Room::getLength() const
{
	return m_room->getfield(db::RoomsFields::Get()->NAME)->getIntegerValue();
}


void Room::setName(const std::string name)
{
	ValuePtr value(new Value(db::RoomsFields::Get()->NAME, name));
	m_room->setvalue(value);
}

void Room::setDescription(const std::string description)
{
	ValuePtr value(new Value(db::RoomsFields::Get()->DESCRIPTION, description));
	m_room->setvalue(value);
}

void Room::setSector(value_type sector)
{
	ValuePtr value(new Value(db::RoomsFields::Get()->FKSECTORS, sector));
	m_room->setvalue(value);	
}

void Room::setArea(value_type area)
{
	ValuePtr value(new Value(db::RoomsFields::Get()->FKAREAS, area));
	m_room->setvalue(value);	
}

void Room::setHeight(value_type height)
{
	ValuePtr value(new Value(db::RoomsFields::Get()->HEIGHT, height));
	m_room->setvalue(value);
}

void Room::setWidth(value_type width)
{
	ValuePtr value(new Value(db::RoomsFields::Get()->WIDTH, width));
	m_room->setvalue(value);	
}

void Room::setLength(value_type length)
{
	ValuePtr value(new Value(db::RoomsFields::Get()->LENGTH, length));
	m_room->setvalue(value);	
}


const mud::Characters& mud::Room::getCharactersInRoom()
{
	return m_charactersInRoom;
}

void Room::Send(const std::string& msg)
{
	Characters inroom = getCharactersInRoom();
	
	for(Characters::iterator it = inroom.begin(); it != inroom.end(); it++)
		(*it)->OnSend(msg);
}

void Room::Sendf(const char* format, ...)
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
	return m_room->exists();
}
/*
std::string Room::CreateMap(value_type id, long origx, long origy)
{
	std::string result;

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

	for(value_type y = 1; y <= p->getHeight(); y++)
	{
		std::string toprow;
		std::string thisrow;
		std::string bottomrow;

		for(value_type x = 1; x <= p->getWidth(); x++)
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
					catch(RowNotFoundException& e)
					{
						Global::Get()->bug(e.what());
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

	return result;
}
*/

std::vector<std::string> Room::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Name: '%s'.", getName().c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.", getDescription().c_str()));
	try
	{
		SectorPtr sector = mud::SectorManager::Get()->GetByKey(getSector());
		result.push_back(Global::Get()->sprintf("Sector: '%s' (%s).", sector->getName().c_str(), sector->getSymbol().c_str()));
	}
	catch(RowNotFoundException& e)
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

TablePtr Room::getTable() const
{
	return Tables::Get()->ROOMS;
}
