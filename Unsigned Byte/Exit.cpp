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

#include "Exit.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "ub.h"

Exit::Exit(db::Exits* exit) :
m_exit(exit)
{
	if(m_exit == NULL)
		throw std::invalid_argument("Exit::Exit(), m_exit == NULL!");
}

Exit::~Exit(void)
{
	delete m_exit;
	m_exit = NULL;
}

std::string Exit::getName(const DIRECTION& dir)
{
	switch(dir)
	{
	case NONE:
		return "None";
	case SOUTHWEST:
		return "Southwest";
	case SOUTH:
		return "South";
	case SOUTHEAST:
		return "Southeast";
	case WEST:
		return "West";
	case UP:
		return "Up";
	case EAST:
		return "East";
	case NORTHWEST:
		return "Northwest";
	case NORTH:
		return "North";
	case NORTHEAST:
		return "Northeast";
	case DOWN:
		return "Down";

	default:
		return "Unknown";
	}
}

Exit::DIRECTION Exit::getDirection(const std::string& name)
{
	if(!name.compare("none"))
		return NONE;

	if(!name.compare("southwest"))
		return SOUTHWEST;

	if(!name.compare("south"))
		return SOUTH;

	if(!name.compare("southeast"))
		return SOUTHEAST;

	if(!name.compare("west"))
		return WEST;

	if(!name.compare("up"))
		return UP;

	if(!name.compare("east"))
		return EAST;

	if(!name.compare("northwest"))
		return NORTHWEST;

	if(!name.compare("north"))
		return NORTH;

	if(!name.compare("northeast"))
		return NORTHEAST;

	if(!name.compare("down"))
		return DOWN;

	return NONE;

}

bool Exit::isClosed()
{
	return m_exit->closed;
}

void Exit::setClosed(bool closed)
{
	m_exit->closed = closed;
}

void Exit::Delete()
{
	m_exit->erase();
}

void Exit::Save()
{
	m_exit->save();
}

bool Exit::Exists()
{
	return m_exit->exitid;
}

std::vector<std::string> Exit::Show()
{
	std::vector<std::string> result;
	
	return result;
}

std::string Exit::ShowShort()
{
	std::string result;
	
	return result;
}

std::vector<std::string> Exit::List()
{
	std::vector<std::string> result;
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->EXITS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		Exit* exit = Cache::Get()->GetExit(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(exit->ShowShort());
		result.push_back(line);
	}
	return result;
}

void Exit::Close(Exit* exit)
{
	if(exit == NULL)
		throw std::invalid_argument("Exit::Close(), exit == NULL!");
	
	Cache::Get()->CloseExit(exit->m_exit->exitid);
	delete exit;
}

Table* Exit::getTable() const
{
	return Tables::Get()->EXITS;
}
