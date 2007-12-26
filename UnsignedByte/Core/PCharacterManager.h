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
#include <set>

#include "singleton.h"
#include "db.h"

namespace mud 
{ 
	class PCharacter; 
	typedef SmartPtr<PCharacter> PCharacterPtr;
}

class UBSocket;

typedef const std::string& cstring;
typedef std::map<value_type,mud::PCharacterPtr> players_m;
typedef std::map<std::string,mud::PCharacterPtr> players_ms;
typedef std::map<std::string, value_type> reverseStringKey;
typedef std::set<value_type> valueset;
typedef std::set<std::string> stringset;

namespace mud
{
	class PCharacterManager : public Singleton<mud::PCharacterManager>
	{
	public:	
		bool isActive(value_type id);
		bool isActive(cstring name);
	
		value_type Add();
		
		mud::PCharacterPtr GetByKey(value_type id);
		mud::PCharacterPtr GetByName(cstring name);
		
		mud::PCharacterPtr LoadByKey(UBSocket* sock, value_type id);
		mud::PCharacterPtr LoadByName(UBSocket* sock, cstring name);

		void Close(value_type id);
		void Close(PCharacterPtr Ch);
		
	private:
		PCharacterPtr cachePCharacter(UBSocket* sock, db::Characters* d);
		
		players_m m_byKey;
		players_ms m_byName;
		
		valueset m_pcharactersByKey;
		stringset m_pcharactersByName;
		
		reverseStringKey m_lookupByName;

	private:
		PCharacterManager(void) {};
		PCharacterManager(const PCharacterManager& rhs);
		PCharacterManager operator=(const PCharacterManager& rhs);
		~PCharacterManager(void) {};
		
		friend class Singleton<mud::PCharacterManager>;
	};
}
