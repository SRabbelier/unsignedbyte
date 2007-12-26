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
	class MCharacter; 
	typedef SmartPtr<MCharacter> MCharacterPtr;
}

typedef const std::string& cstring;
typedef std::map<value_type,mud::MCharacterPtr> mobiles_m;
typedef std::map<std::string,mud::MCharacterPtr> mobiles_ms;
typedef std::map<std::string, value_type> reverseStringKey;

namespace mud
{
	class MCharacterManager : public Singleton<mud::MCharacterManager>
	{
	public:	
		value_type Add();
		mud::MCharacterPtr GetByKey(value_type id);
		mud::MCharacterPtr GetByName(cstring name);
		void Close(value_type id);
		
	private:
		MCharacterPtr cacheMCharacter(db::Characters* d);
		
		mobiles_m m_byKey;
		mobiles_ms m_byName;
		reverseStringKey m_lookupByName;

	private:
		MCharacterManager(void) {};
		MCharacterManager(const MCharacterManager& rhs);
		MCharacterManager operator=(const MCharacterManager& rhs);
		~MCharacterManager(void) {};
		
		friend class Singleton<mud::MCharacterManager>;
	};
}
