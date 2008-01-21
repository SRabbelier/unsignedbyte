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

#include "Statements.h"
#include "sqlite3.h"
#include "Field.h"
#include "Table.h"
#include "Assert.h"

Statements::Statements() :
m_insert(NULL),
m_erase(NULL),
m_update(NULL),
m_select(NULL),
m_list(NULL),
m_foreach(NULL)
{
	
}

Statements::~Statements() 
{ 
	sqlite3_finalize(m_insert);
	sqlite3_finalize(m_erase);
	sqlite3_finalize(m_update);
	sqlite3_finalize(m_select);
	sqlite3_finalize(m_list);
	sqlite3_finalize(m_foreach);
	for(fieldmap::iterator it = m_lookup.begin(); it != m_lookup.end(); it++)
		sqlite3_finalize(it->second);
}

// Getters
sqlite3_stmt* Statements::getErase() const 
{
	return m_erase;
}

sqlite3_stmt* Statements::getInsert() const 
{
	return m_insert;
}

sqlite3_stmt* Statements::getUpdate() const 
{
	return m_update;
}

sqlite3_stmt* Statements::getSelect() const 
{
	return m_select;
}

sqlite3_stmt* Statements::getLookup(FieldPtr field)
{
	Assert(field);
	
	return m_lookup[field.get()];
}

sqlite3_stmt* Statements::getList() const 
{
	return m_list;
}

sqlite3_stmt* Statements::getForEach() const 
{
	return m_foreach;
}

// Setters
void Statements::setErase(sqlite3_stmt* erase) 
{
	Assert(erase);
	
	m_erase = erase; 
}

void Statements::setInsert(sqlite3_stmt* insert) 
{ 
	Assert(insert);
	
	m_insert = insert; 
}

void Statements::setUpdate(sqlite3_stmt* update) 
{ 
	Assert(update);
	
	m_update = update; 
}

void Statements::setSelect(sqlite3_stmt* select) 
{ 
	Assert(select);
	
	m_select = select; 
}

void Statements::setLookup(FieldPtr field, sqlite3_stmt* lookup) 
{ 
	Assert(field);
	Assert(lookup);
	
	m_lookup[field.get()] = lookup; 
}

void Statements::setList(sqlite3_stmt* list) 
{ 
	Assert(list);
	
	m_list = list; 
}

void Statements::setForEach(sqlite3_stmt* forEach) 
{ 
	Assert(forEach);
	
	m_foreach = forEach; 
}

void Statements::commit()
{
	sqlite3_finalize(m_insert);
	sqlite3_finalize(m_erase);
	sqlite3_finalize(m_update);
	
	m_insert = NULL;
	m_erase = NULL;
	m_update = NULL;
}
