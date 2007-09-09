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

#include "Area.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"

using mud::Area;

Area::Area(db::Areas* area) :
m_area(area)
{
	if(m_area == NULL)
		throw new std::invalid_argument("Area::Area(), m_area == NULL!");
}

Area::~Area(void)
{
	delete m_area;
	m_area = NULL;
}

void Area::Delete()
{
	m_area->erase();
}

void Area::Save()
{
	m_area->save();
}

bool Area::Exists()
{
	return m_area->exists();
}

std::vector<std::string> Area::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Name: '%s'.\n", getName().c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.\n", getDescription().c_str()));
	result.push_back(Global::Get()->sprintf("Height: %d.\n", getHeight()));
	result.push_back(Global::Get()->sprintf("Width: %d.\n", getWidth()));
	
	return result;
}

std::string Area::ShowShort()
{
	return Global::Get()->sprintf("%s (%d*%d): %s\n", 
			getName().c_str(),
			getHeight(),
			getWidth(),
			getDescription().c_str());
}

std::vector<std::string> Area::List()
{
	std::vector<std::string> result;
	/*Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->AREAS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		Area* area = Cache::Get()->GetArea(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(area->ShowShort());
		result.push_back(line);
	}*/
	return result;
}

Table* Area::getTable() const
{
	return Tables::Get()->AREAS;
}
