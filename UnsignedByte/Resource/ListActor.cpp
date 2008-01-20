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

#include "ListActor.h"
#include "Table.h"

void ListActor::parseRow(sqlite3_stmt* statement, Table* table)
{
	std::string result;

	int columns = sqlite3_column_count(statement);
	for(int i = 0; i < columns; i++)
	{
		int type = sqlite3_column_type(statement, i);
		std::ostringstream str;
		
		if(i != 0)
			str << ", ";

		switch(type)
		{
		case SQLITE_TEXT:			
			str << sqlite3_column_text(statement, i);
			break;

		case SQLITE_INTEGER:
			str << sqlite3_column_int64(statement, i);
			break;
			
		case SQLITE_NULL:
			str << "empty";
			break;
			
		default:
			std::ostringstream err;
			err << "Unknown data type '" << type << "'.";
			throw std::runtime_error(err.str());
		}

		result.append(str.str());
	}

	m_list.push_back(result);
}

const Strings& ListActor::getList() const
{
	return m_list;
}

