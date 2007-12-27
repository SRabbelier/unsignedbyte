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
	class Sector; 
	typedef SmartPtr<Sector> SectorPtr;
}

typedef const std::string& cstring;
typedef std::map<value_type,mud::SectorPtr> sectors_m;
typedef std::map<std::string,mud::SectorPtr> sectors_ms;
typedef std::map<std::string, value_type> reverseStringKey;

namespace mud
{
	class SectorManager : public Singleton<mud::SectorManager>
	{
	public:
		TablePtr GetTable();
		std::vector<std::string> List();
		void Close(SectorPtr sector);
		
		value_type Add();
		mud::SectorPtr GetByKey(value_type id);
		mud::SectorPtr GetByName(cstring name);
		
		value_type lookupByName(cstring value);
		
		void Close(value_type Sectorid);
		
	private:
		SectorPtr cacheSector(db::Sectors* d);
		
		sectors_m m_byKey;
		sectors_ms m_byName;
		reverseStringKey m_lookupByName;

	private:
		SectorManager(void) {};
		SectorManager(const SectorManager& rhs);
		SectorManager operator=(const SectorManager& rhs);
		~SectorManager(void) {};
		
		friend class Singleton<mud::SectorManager>;
	};
}
