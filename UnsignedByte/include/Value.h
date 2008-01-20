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
#pragma once

#include "Types.h"

class Value
{
public:
	Value(FieldImplPtr field) : m_field(field), m_textvalue(""), m_integervalue(0) {}
	Value(FieldImplPtr field, cstring value) : m_field(field), m_textvalue(value), m_integervalue(0) {}
	Value(FieldImplPtr field, value_type value) : m_field(field), m_textvalue(""), m_integervalue(value) {}
	~Value() {}
	
	FieldImplPtr getField() const { return m_field; }

	const std::string& getStringValue() const { return m_textvalue; }
	value_type getIntegerValue() const { return m_integervalue; }
	bool getBoolValue() const { return m_integervalue == 1 ? true : false; }
	
	void setTextValue(const std::string& value) { m_textvalue = value; }
	void setIntegerValue(value_type value) { m_integervalue = value; }
	void setBoolValue(bool value) { m_integervalue = (value ? 1 : 0); }
	
private:
	FieldImplPtr m_field;
	std::string m_textvalue;
	value_type m_integervalue;
};
