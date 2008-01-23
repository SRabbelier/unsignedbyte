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

#include "SPKCriteria.h"
#include "Table.h"

bool SPKCriteria::evaluate(sqlite3_stmt* statement)
{
	Assert(statement);
	
	value_type key = sqlite3_column_int64(statement, 0);
	if(key == m_key)
		return true;
		
	return false;
}

bool SPKCriteria::evaluate(sqlite3_stmt* statement, const TablePtr table)
{
	Assert(statement);
	Assert(table);
	Assert(table->hasSingularPrimaryKey());
		
	return evaluate(statement);
}
