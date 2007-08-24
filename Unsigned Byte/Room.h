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
#include <vector>
#include "Savable.h"
#include "ub.h"

class Area;
class Character;
class Cache;

typedef std::vector<Character*> Characters;

class Room : public Savable
{
public:
	const std::string& getName() const { return m_room->name; };
	const std::string& getDescription() const { return m_room->description; };
	long getSector() const { return m_room->fksector; }
	long getArea() const { return m_room->fkarea; };
	long getHeight() const { return m_room->height; };
	long getWidth() const { return m_room->width; };
	long getLength() const { return m_room->length; };

	void setName(const std::string name) { m_room->name = name; };
	void setDescription(const std::string description) { m_room->description = description; };
	void setSector(long sector) { m_room->fksector = sector; };
	void setArea(long area) { m_room->fkarea = area; };
	void setHeight(long height) { m_room->height = height; };
	void setWidth(long width) { m_room->width = width; };
	void setLength(long length) { m_room->length = length; };

	Characters getCharacters();

	void Send(const std::string& msg);
	void Sendf(char* format, ...);

	/**
	 * \brief Utilities
	 */
	std::vector<std::string> Show();
	std::string ShowShort();
	Table* getTable() const;
	
	/**
	 * \brief static utilities
	 */
	static std::vector<std::string> List();
	static std::string CreateMap(long id, long origx, long origy);
	static void Close(Room* room);
	
	/**
	 * \brief Database utilities
	 */
	void Delete();
	void Save();
	bool Exists();

private:
	db::Rooms* m_room;

	Room(db::Rooms* room);
	Room(const Room& rhs) {};
	Room operator=(const Room& rhs) { return *this; };
	~Room(void);

	friend class Cache; // constructor
};
