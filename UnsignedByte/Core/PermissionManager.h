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

#include <string>
#include <vector>

#include "singleton.h"
#include "db.h"

namespace mud 
{ 
	class Permission; 
	typedef SmartPtr<mud::Permission> PermissionPtr;
}

typedef const std::string& cstring;
typedef std::pair<value_type, value_type> twoValueKey;
typedef std::map<twoValueKey,mud::Permission*> permissions_m; // account, grantgroup

namespace mud
{
	class PermissionManager : public Singleton<mud::PermissionManager>
	{
	public:
		bool defaultGrant;
		bool defaultLog;
	
		TableImplPtr GetTable();
		std::vector<std::string> List();
		
		mud::PermissionPtr GetByKeys(KeysPtr keys);
		mud::PermissionPtr GetByKeys(value_type grantgroup, value_type account);
		
		value_type lookupByName(cstring value);

	private:
		PermissionManager(void);
		PermissionManager(const PermissionManager& rhs);
		PermissionManager operator=(const PermissionManager& rhs);
		~PermissionManager(void) {};
		
		friend class Singleton<mud::PermissionManager>;
	};
}
