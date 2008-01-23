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

#include "Exit.h"
#include "Global.h"
#include "db.h"

using mud::Exit;

Exit::Exit(SavableManagerPtr exit) :
m_exit(exit)
{
	Assert(m_exit);
}

Exit::~Exit(void)
{

}

value_type Exit::getRoom() const
{
	return m_exit->getfield(db::ExitsFields::Get()->FKROOMS)->getIntegerValue();
}

const std::string& Exit::getDir() const
{
	return m_exit->getfield(db::ExitsFields::Get()->DIR)->getStringValue();
}

void Exit::setRoom(value_type room)
{
	ValuePtr value(new Value(db::ExitsFields::Get()->FKROOMS, room));
	m_exit->setvalue(value);
}

void Exit::setDir(const std::string& dir)
{
	ValuePtr value(new Value(db::ExitsFields::Get()->DIR, dir));
	m_exit->setvalue(value);
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
	return m_exit->exists();
}

std::vector<std::string> Exit::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Room: '%d'.", getRoom()));
	result.push_back(Global::Get()->sprintf("Dir: '%s'.", getDir().c_str()));
	
	return result;
}

std::string Exit::ShowShort()
{
	return Global::Get()->sprintf("%d: %s\n", 
			getRoom(),
			getDir().c_str());
}

TableImplPtr Exit::getTable() const
{
	return m_exit->getTable();
}
