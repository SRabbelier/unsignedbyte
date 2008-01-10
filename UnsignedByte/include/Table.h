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

typedef std::vector<FieldPtr> FieldVector;
typedef std::map<std::string, TablePtr> TableMap;

class Table
{
public:
	const std::string& tableName() const;
	
	virtual FieldDefVector::const_iterator lookupbegin() const = 0;
	virtual FieldDefVector::const_iterator lookupend() const = 0;
	virtual size_t lookupsize() const = 0;
	
	virtual FieldDefVector::const_iterator defbegin() const = 0;
	virtual FieldDefVector::const_iterator defend() const = 0;
	virtual size_t defsize() const = 0;
	
	virtual std::string firstKey() const = 0;
	virtual TableMap::const_iterator keybegin() const = 0;
	virtual TableMap::const_iterator keyend() const = 0;
	virtual size_t keysize() const = 0;
	
	virtual bool hasSingularPrimaryKey() const = 0;
	
protected:
	Table(std::string name);
	~Table();
	friend SmartPtrDelete(Table);

	std::string m_name;
};
