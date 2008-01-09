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
#include <map>
#include <smart_ptr.h>

typedef const std::string& cstring;

class StatementStrings
{
public:
	// Constructors
	StatementStrings() { }
	~StatementStrings() { }
	
	// Getters
	cstring getErase() const {return m_erase;}
	cstring getInsert() const {return m_insert;}
	cstring getUpdate() const {return m_update;}
	cstring getSelect() const {return m_select;}
	cstring getLookup(FieldPtr field) {return m_lookup[field];}
	cstring getList() const {return m_list;}
	cstring getForEach() const {return m_foreach;}
	
	// Setters
	void setErase(cstring erase) { m_erase = erase; }
	void setInsert(cstring insert) { m_insert = insert; }
	void setUpdate(cstring update) { m_update = update; }
	void setSelect(cstring select) { m_select = select; }
	void setLookup(FieldPtr field, cstring lookup) { m_lookup[field] = lookup; }
	void setList(cstring list) { m_list = list; }
	void setForEach(cstring forEach) { m_foreach = forEach; }
	
private:
	typedef std::map<FieldPtr, std::string> fieldmap;
	
	std::string m_insert;
	std::string m_erase;
	std::string m_update;
	std::string m_select;
	fieldmap m_lookup;
	std::string m_list;
	std::string m_foreach;
};

typedef SmartPtr<StatementStrings> StatementStringsPtr;
