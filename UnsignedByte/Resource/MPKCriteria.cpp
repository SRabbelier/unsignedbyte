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

#include "Keys.h"
#include "Key.h"
#include "KeyDef.h"
#include "TableImpl.h"
#include "FieldImpl.h"
#include "MPKCriteria.h"

bool MPKCriteria::evaluate(sqlite3_stmt* statement)
{
	int pos = 0;
	for(KeyMap::const_iterator it = m_keys->begin(); it != m_keys->end(); it++)
	{
		const char* text = sqlite3_column_name(statement, pos);
		if(text == 0)
			return false;
			
		std::string keyname(text);
		value_type value = sqlite3_column_int64(statement, pos);
		
		// TODO - fix? currently positional....
		if(it->first->getName().compare(keyname))
			return false;
		
		if(it->second->getValue() != value)
			return false;
			
		pos++;
	}
	
	return true;
}

bool MPKCriteria::evaluate(sqlite3_stmt* statement, const TablePtr table)
{
	if(table->hasSingularPrimaryKey())
		throw std::logic_error("MPKCriteria::evaluate(), table has a singular primary key.");
		
	return evaluate(statement);
}
