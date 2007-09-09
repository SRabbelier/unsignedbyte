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

class Table;

class Bindable
{
public:
	Bindable(void) { }
	virtual ~Bindable(void) { }
	
	virtual void bindKeys(sqlite3_stmt* stmt) const = 0;
	virtual void bindUpdate(sqlite3_stmt* stmt) const = 0;
	virtual void bindLookup(sqlite3_stmt* stmt) const = 0;
	
	virtual void parseInsert(sqlite3* db) = 0;
	virtual void parseSelect(sqlite3_stmt* stmt) = 0;
	
	virtual Table* getTable() const = 0;
	
private:
	Bindable(const Bindable& rhs) {};
};
