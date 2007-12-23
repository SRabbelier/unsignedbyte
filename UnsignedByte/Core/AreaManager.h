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
#include <vector>

#include "singleton.h"
#include "db.h"

namespace mud 
{ 
	class Area; 
	typedef SmartPtr<Area> AreaPtr;
}

typedef const std::string& cstring;
typedef std::map<value_type,mud::AreaPtr> areas_m;
typedef std::map<std::string,mud::AreaPtr> areas_ms;
typedef std::map<std::string, value_type> reverseStringKey;

namespace mud
{
	class AreaManager : public Singleton<mud::AreaManager>
	{
	public:
		TablePtr GetTable();
		std::vector<std::string> List();
		void Close(AreaPtr area);
		
		value_type Add();
		mud::AreaPtr GetByKey(value_type id);
		mud::AreaPtr GetByName(cstring name);
		
		value_type lookupByName(cstring value);
		
		void Close(value_type Areaid);
		
	private:
		AreaPtr cacheArea(db::Areas* d);
		
		areas_m m_byKey;
		areas_ms m_byName;
		reverseStringKey m_lookupByName;

	private:
		AreaManager(void) {};
		AreaManager(const AreaManager& rhs);
		AreaManager operator=(const AreaManager& rhs);
		~AreaManager(void) {};
		
		friend class Singleton<mud::AreaManager>;
	};
}
