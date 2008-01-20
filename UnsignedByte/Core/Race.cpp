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

#include "Assert.h"
#include "Race.h"

using mud::Race;

Race::Race(SavableManagerPtr race) :
m_race(race)
{
	Assert(race);
}

Race::~Race(void)
{
	
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
	return m_race->exists();
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
