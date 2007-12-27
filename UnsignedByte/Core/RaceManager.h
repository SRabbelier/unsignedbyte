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
	class Race; 
	typedef SmartPtr<Race> RacePtr;
}

typedef const std::string& cstring;
typedef std::map<value_type,mud::RacePtr> races_m;
typedef std::map<std::string,mud::RacePtr> races_ms;
typedef std::map<std::string, value_type> reverseStringKey;

namespace mud
{
	class RaceManager : public Singleton<mud::RaceManager>
	{
	public:
		TablePtr GetTable();
		std::vector<std::string> List();
		void Close(RacePtr race);
		
		value_type Add();
		mud::RacePtr GetByKey(value_type id);
		mud::RacePtr GetByName(cstring name);
		
		value_type lookupByName(cstring value);
		
		void Close(value_type Raceid);
		
	private:
		RacePtr cacheRace(db::Races* d);
		
		races_m m_byKey;
		races_ms m_byName;
		reverseStringKey m_lookupByName;

	private:
		RaceManager(void) {};
		RaceManager(const RaceManager& rhs);
		RaceManager operator=(const RaceManager& rhs);
		~RaceManager(void) {};
		
		friend class Singleton<mud::RaceManager>;
	};
}
