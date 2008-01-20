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
#include "Sector.h"
#include "db.h"

using mud::Sector;

Sector::Sector(SavableManagerPtr Sector) :
m_sector(Sector)
{
	Assert(Sector);
}

Sector::~Sector(void)
{

}

const std::string& Sector::getName() const
{
	return m_sector->getfield(db::SectorsFields::Get()->NAME)->getStringValue();
}

const std::string& Sector::getSymbol() const
{
	return m_sector->getfield(db::SectorsFields::Get()->SYMBOL)->getStringValue();
}

long Sector::getMoveCost() const
{
	return m_sector->getfield(db::SectorsFields::Get()->MOVECOST)->getIntegerValue();
}

bool Sector::isWater() const
{
	return m_sector->getfield(db::SectorsFields::Get()->WATER)->getBoolValue();
}


void Sector::setName(const std::string& name)
{
	ValuePtr value(new Value(db::SectorsFields::Get()->NAME, name));
	m_sector->setvalue(value);
}

void Sector::setSymbol(const std::string& symbol)
{
	ValuePtr value(new Value(db::SectorsFields::Get()->SYMBOL, symbol));
	m_sector->setvalue(value);
}

void Sector::setMoveCost(long movecost)
{
	ValuePtr value(new Value(db::SectorsFields::Get()->MOVECOST, movecost));
	m_sector->setvalue(value);	
}

void Sector::setWater(bool water)
{
	ValuePtr value(new Value(db::SectorsFields::Get()->WATER, water ? 0 : 1));
	m_sector->setvalue(value);	
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
	return m_sector->exists();
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

TablePtr Sector::getTable() const
{
	return Tables::Get()->SECTORS;
}
