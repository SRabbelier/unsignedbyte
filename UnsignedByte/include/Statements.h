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

#include "Types.h"

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
	sqlite3_stmt* getSelect() const {return m_select;}
	sqlite3_stmt* getLookup(FieldPtr field) {return m_lookup[field.get()];}
	sqlite3_stmt* getList() const {return m_list;}
	sqlite3_stmt* getForEach() const {return m_foreach;}
	
	// Setters
	void setErase(sqlite3_stmt* erase) { m_erase = erase; }
	void setInsert(sqlite3_stmt* insert) { m_insert = insert; }
	void setUpdate(sqlite3_stmt* update) { m_update = update; }
	void setSelect(sqlite3_stmt* select) { m_select = select; }
	void setLookup(FieldPtr field, sqlite3_stmt* lookup) { m_lookup[field.get()] = lookup; }
	void setList(sqlite3_stmt* list) { m_list = list; }
	void setForEach(sqlite3_stmt* forEach) { m_foreach = forEach; }
	
	void commit();
	
private:
	typedef std::map<Field*, sqlite3_stmt*> fieldmap;
	
	sqlite3_stmt* m_insert;
	sqlite3_stmt* m_erase;
	sqlite3_stmt* m_update;
	sqlite3_stmt* m_select;
	fieldmap m_lookup;
	sqlite3_stmt* m_list;
	sqlite3_stmt* m_foreach;
};

typedef SmartPtr<Statements> StatementsPtr;
