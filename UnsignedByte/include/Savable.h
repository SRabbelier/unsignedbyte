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
#pragma once

#include <string>
#include <vector>
#include <smart_ptr.h>

class Table;
typedef SmartPtr<Table> TablePtr;

class Savable
{
public:
	Savable(void) { };
	virtual ~Savable(void) { };

	virtual void Delete() = 0;
	virtual void Save() = 0;
	virtual bool Exists() = 0;
	
	virtual std::vector<std::string> Show() = 0;
	virtual std::string ShowShort() = 0;
	
	virtual TablePtr getTable() const = 0;
private:
	Savable(const Savable& rhs) {};
};

typedef SmartPtr<Savable> SavablePtr;
