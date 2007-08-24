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
#include "Savable.h"

namespace db { class Exits; };
class Cache;

class Exit : public Savable
{
public:
	enum DIRECTION
	{
		NONE,
		SOUTHWEST,
		SOUTH,
		SOUTHEAST,
		WEST,
		UP,
		EAST,
		NORTHWEST,
		NORTH,
		NORTHEAST,
		DOWN
	};

	static const int MAXDIR = 11;
	static std::string getName(const DIRECTION& dir);
	static DIRECTION getDirection(const std::string& name);

	bool isClosed();
	void setClosed(bool closed);

	/**
	 * \brief Utilities
	 */
	std::vector<std::string> Show();
	std::string ShowShort();
	Table* getTable() const;
	
	/**
	 * \brief Static utilities
	 */
	static std::vector<std::string> List();
	static void Close(Exit* exit);
	
	/**
	 * \brief Database utilities
	 */
	void Delete();
	void Save();
	bool Exists();

private:
	db::Exits* m_exit;

	Exit(db::Exits* exit);
	Exit(const Exit& rhs) {};
	Exit operator=(const Exit& rhs) {return *this; };
	~Exit(void);
	
	friend class Cache; // constructor
};
