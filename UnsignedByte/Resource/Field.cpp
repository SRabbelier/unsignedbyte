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

#include "Field.h"

Field::Field(const std::string& name, bool text, const std::string& defaultvalue) :
m_name(name),
m_text(text),
m_defaultvalue(defaultvalue)
{
	
}

Field::~Field()
{
	
}
	
std::string Field::creationString() const
{
	std::string result;
	
	result.append(", ");
	result.append(m_name);
	
	if(m_text)
		result.append(" TEXT");
	else
		result.append(" INTEGER");
	
	if(m_defaultvalue.size() != 0)
	{
		result.append(" RESTRAINT ");
		result.append(m_name);
		result.append(" DEFAULT ");
		
		if(m_text)
			result.append("'");
		result.append(m_defaultvalue);
		if(m_text)
			result.append("'");		
	}
	
	return result;
}
