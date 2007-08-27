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

class sqlite3_stmt;

class Statements
{
public:
	// Constructors
	Statements();	
	~Statements();
	
	// Getters
	sqlite3_stmt* getErase() const {return m_erase;}
	sqlite3_stmt* getInsert() const {return m_insert;}
	sqlite3_stmt* getUpdate() const {return m_update;}
	
	// Setters
	void setErase(sqlite3_stmt* erase) { m_erase = erase; }
	void setInsert(sqlite3_stmt* insert) { m_insert = insert; }
	void setUpdate(sqlite3_stmt* update) { m_update = update; }
	
private:
	sqlite3_stmt* m_insert;
	sqlite3_stmt* m_erase;
	sqlite3_stmt* m_update;
};
