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

#include "Area.h"
#include "Global.h"
#include "db.h"

using mud::Area;

Area::Area(SavableManagerPtr area) :
m_area(area)
{
	Assert(area);
}

Area::~Area(void)
{

}

const std::string& Area::getName() const
{
	return m_area->getfield(db::AreasFields::Get()->NAME)->getStringValue();
}

const std::string& Area::getDescription() const
{
	return m_area->getfield(db::AreasFields::Get()->DESCRIPTION)->getStringValue();
}

value_type Area::getHeight() const
{
	return m_area->getfield(db::AreasFields::Get()->HEIGHT)->getIntegerValue();
}

value_type Area::getWidth() const
{
	return m_area->getfield(db::AreasFields::Get()->WIDTH)->getIntegerValue();
}

void Area::setName(const std::string& name)
{
	ValuePtr value(new Value(db::AreasFields::Get()->NAME, name));
	m_area->setvalue(value);
}

void Area::setDescription(const std::string& description)
{
	ValuePtr value(new Value(db::AreasFields::Get()->DESCRIPTION, description));
	m_area->setvalue(value);
}

void Area::setHeight(value_type height)
{
	ValuePtr value(new Value(db::AreasFields::Get()->HEIGHT, height));
	m_area->setvalue(value);
}

void Area::setWidth(value_type width)
{
	ValuePtr value(new Value(db::AreasFields::Get()->WIDTH, width));
	m_area->setvalue(value);
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
	
	result.push_back(Global::Get()->sprintf("Name: '%s'.", getName().c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.", getDescription().c_str()));
	result.push_back(Global::Get()->sprintf("Height: %d.", getHeight()));
	result.push_back(Global::Get()->sprintf("Width: %d.", getWidth()));
	
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

TableImplPtr Area::getTable() const
{
	return m_area->getTable();
}
