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

#include "Colour.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "db.h"
#include <sqlite3.h>

Colour::Colour(db::Colours* object) :
m_colour(object)
{
	if(m_colour == NULL)
		throw std::invalid_argument("Colour::Colour(), m_colour == NULL");
}

Colour::~Colour(void)
{
	delete m_colour;
	m_colour = 0;
}

std::string Colour::getColourString()
{
	std::string restore = "\x1B[0;0m";
	std::string prefix = "\x1B[";
	std::string str = m_colour->colourstring;
	
	std::string result = restore;
	result.append(prefix);
	result.append(str);

	return result;
}

void Colour::Delete()
{
	m_colour->erase();
}

void Colour::Save()
{
	m_colour->save();
}

bool Colour::Exists()
{
	return m_colour->colourid;
}

std::vector<std::string> Colour::Show()
{
	std::vector<std::string> result;
	result.push_back(Global::Get()->sprintf("Name: '%s'.\n", getName().c_str()));
	result.push_back(Global::Get()->sprintf("ColourString: '%s'.\n", getColourString().c_str()));
	return result;
}

std::string Colour::ShowShort()
{
	return Global::Get()->sprintf("%s: %s\n", 
			getName().c_str(),
			getColourString().c_str());
}

std::vector<std::string> Colour::List()
{
	std::vector<std::string> result;
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->COLOURS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		Colour* colour = Cache::Get()->GetColour(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(colour->ShowShort());
		result.push_back(line);
	}
	return result;
}

Table* Colour::getTable() const
{
	return Tables::Get()->COLOURS;
}