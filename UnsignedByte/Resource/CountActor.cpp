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

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "CountActor.h"
#include "Table.h"

CountActor::CountActor(CriteriaPtr crit) : 
m_count(0), 
m_criteria(crit) 
{
	Assert(crit);
}

CountActor::~CountActor() 
{
	
}

void CountActor::parseRow(sqlite3_stmt* statement, Table* table)
{ 
	Assert(statement);
	Assert(table);
	
	if(m_criteria->evaluate(statement, table))
		m_count++;
}

const value_type CountActor::getCount() const
{
	return m_count;
}

