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

#include "singleton.h"
#include "SavableHeaders.h"

namespace mud 
{ 
	class Sector; 
	typedef SmartPtr<Sector> SectorPtr;
}

namespace mud
{
	class SectorManager : public Singleton<mud::SectorManager>
	{
	public:
		TableImplPtr GetTable();
		std::vector<std::string> List();
		
		KeysPtr Add();
		mud::SectorPtr GetByKey(value_type id);
		mud::SectorPtr GetByName(cstring name);
		
		value_type lookupByName(cstring value);

	private:
		SectorManager(void) {};
		SectorManager(const SectorManager& rhs);
		SectorManager operator=(const SectorManager& rhs);
		~SectorManager(void) {};
		
		friend class Singleton<mud::SectorManager>;
	};
}
