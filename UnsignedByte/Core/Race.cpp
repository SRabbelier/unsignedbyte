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

#include "Race.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "db.h"

#include "Table.h"
#include "Tables.h"

using mud::Race;

Race::Race(db::Races* race) :
m_race(race)
{
	if(m_race == NULL)
		throw std::invalid_argument("Race::Race(), m_race == NULL!");
}

Race::~Race(void)
{
	delete m_race;
	m_race = NULL;
}

void Race::Delete()
{
	m_race->erase();
}

void Race::Save()
{
	m_race->save();
}

bool Race::Exists()
{
	return m_race->getraceid();
}

std::vector<std::string> Race::Show()
{
	std::vector<std::string> result;
	
	return result;
}

std::string Race::ShowShort()
{
	std::string result;
	
	return result;
}

TablePtr Race::getTable() const
{
	return Tables::Get()->RACES;
}
