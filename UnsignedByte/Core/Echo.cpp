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

#include "Echo.h"
#include "Global.h"
#include "db.h"

using mud::Echo;
using namespace mud;

Echo::Echo(SavableManagerPtr echo) :
m_echo(echo)
{
	Assert(echo);
}

Echo::~Echo(void)
{

}

const std::string& Echo::getMessage() const
{
	return m_echo->getfield(db::EchosFields::Get()->MESSAGE)->getStringValue();
}

value_type Echo::getAudibility() const
{
	return m_echo->getfield(db::EchosFields::Get()->AUDIBILITY)->getIntegerValue();
}

value_type Echo::getVisibility() const
{
	return m_echo->getfield(db::EchosFields::Get()->VISIBILITY)->getIntegerValue();
}

void Echo::setMessage(const std::string& message)
{
	ValuePtr value(new Value(db::EchosFields::Get()->MESSAGE, message));
	m_echo->setvalue(value);
}

void Echo::setAudibility(value_type audibility)
{
	ValuePtr value(new Value(db::EchosFields::Get()->AUDIBILITY, audibility));
	m_echo->setvalue(value);
}

void Echo::setVisibility(value_type visibility)
{
	ValuePtr value(new Value(db::EchosFields::Get()->VISIBILITY, visibility));
	m_echo->setvalue(value);
}

void Echo::Delete()
{
	m_echo->erase();
}

void Echo::Save()
{
	m_echo->save();
}

bool Echo::Exists()
{
	return m_echo->exists();
}

std::vector<std::string> Echo::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Audibility: '%d'.", getAudibility()));
	result.push_back(Global::Get()->sprintf("Visibility: %d.", getVisibility()));
	result.push_back(Global::Get()->sprintf("Message: '%s'.", getMessage().c_str()));
	
	return result;
}

std::string Echo::ShowShort()
{
	return Global::Get()->sprintf("(%d,%d): %s\n", 
			getAudibility(),
			getVisibility(),
			getMessage().c_str());
}

TableImplPtr Echo::getTable() const
{
	return m_echo->getTable();
}
