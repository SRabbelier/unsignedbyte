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

#include <string>
#include <stdexcept>

#include "PermissionManager.h"
#include "Permission.h"
#include "Global.h"

using mud::PermissionManager;
using mud::Permission;
using mud::PermissionPtr;

PermissionManager::PermissionManager(void) :
defaultGrant(true),
defaultLog(false)
{
	
}

std::vector<std::string> PermissionManager::List()
{
	return GetTable()->tableList();
}

TablePtr PermissionManager::GetTable()
{
	return Tables::Get()->PERMISSIONS;
}

bool PermissionManager::isGrant(long grant)
{
	switch(grant)
	{
		default:
			return defaultGrant;
			
		case Permission::GRANT_ENABLE:
		case Permission::GRANT_ENABLEANDLOG:
			return true;
			
		case Permission::GRANT_DISABLE:
		case Permission::GRANT_DISABLEANDLOG:
			return false;
	}
}

bool PermissionManager::isLog(long grant)
{
	switch(grant)
	{
		default:
			return defaultLog;
			
		case Permission::GRANT_ENABLEANDLOG:
		case Permission::GRANT_DISABLEANDLOG:
			return true;
			
		case Permission::GRANT_ENABLE:
		case Permission::GRANT_DISABLE:
			return false;
	}
}

mud::PermissionPtr PermissionManager::GetByKeys(value_type account, value_type grantgroup)
{
	twoValueKey key(account, grantgroup);
	PermissionPtr p(m_byKeys[key]);
	if(p)
		return p;
		
	db::Permissions* d = db::Permissions::bykey(account, grantgroup);
	p = PermissionPtr(new Permission(d));
	m_byKeys[key] = p.get();
	return p;	
}

void PermissionManager::Close(value_type account, value_type permission)
{
	permissions_m::iterator key = m_byKeys.find(twoValueKey(account, permission));
	m_byKeys.erase(key);
}
