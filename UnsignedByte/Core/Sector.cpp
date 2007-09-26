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

#include "Sector.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "db.h"

using mud::Sector;

Sector::Sector(db::Sectors* Sector) :
m_sector(Sector)
{
	if(m_sector == NULL)
		throw std::invalid_argument("Sector::Sector(), m_sector == NULL!");
}

Sector::~Sector(void)
{
	delete m_sector;
	m_sector = NULL;
}

void Sector::Delete()
{
	m_sector->erase();
}

void Sector::Save()
{
	m_sector->save();
}

bool Sector::Exists()
{
	return m_sector->getsectorid();
}

std::vector<std::string> Sector::Show()
{
	std::vector<std::string> result;
	
	return result;
}

std::string Sector::ShowShort()
{
	std::string result;
	
	return result;
}

std::vector<std::string> Sector::List()
{
	return GetTable()->tableList();
}

TablePtr Sector::GetTable()
{
	return Tables::Get()->SECTORS;
}

