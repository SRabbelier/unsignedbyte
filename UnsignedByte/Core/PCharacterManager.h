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

#include "SavableHeaders.h"

namespace mud 
{ 
	class PCharacter; 
	typedef SmartPtr<mud::PCharacter> PCharacterPtr;
}

typedef std::map<value_type, mud::PCharacterPtr> charactersByKey;
typedef std::map<std::string, mud::PCharacterPtr> charactersByName;

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

	private:
		PCharacterManager(void) {};
		PCharacterManager(const PCharacterManager& rhs);
		PCharacterManager operator=(const PCharacterManager& rhs);
		~PCharacterManager(void) {};
		
		charactersByKey m_activeCharactersByKey;
		charactersByName m_activeCharactersByName;
		
		friend class Singleton<mud::PCharacterManager>;
	};
}
