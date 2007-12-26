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
	class Colour; 
	typedef SmartPtr<Colour> ColourPtr;
}

typedef const std::string& cstring;
typedef std::map<value_type,mud::ColourPtr> colours_m;
typedef std::map<std::string,mud::ColourPtr> colours_ms;
typedef std::map<std::string, value_type> reverseStringKey;

namespace mud
{
	class ColourManager : public Singleton<mud::ColourManager>
	{
	public:
		TablePtr GetTable();
		std::vector<std::string> List();
		void Close(ColourPtr area);
		
		value_type Add();
		mud::ColourPtr GetByKey(value_type id);
		mud::ColourPtr GetByName(cstring name);
		mud::ColourPtr GetByCode(cstring code);
		
		value_type lookupByName(cstring value);
		value_type lookupByCode(cstring value);
		
		void Close(value_type colourid);
		
	private:
		ColourPtr cacheColour(db::Colours* d);
		
		colours_m m_byKey;
		colours_ms m_byName;
		colours_ms m_byCode;
		reverseStringKey m_lookupByName;
		reverseStringKey m_lookupByCode;

	private:
		ColourManager(void) {};
		ColourManager(const ColourManager& rhs);
		ColourManager operator=(const ColourManager& rhs);
		~ColourManager(void) {};
		
		friend class Singleton<mud::ColourManager>;
	};
}
