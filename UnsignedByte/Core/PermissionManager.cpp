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

TableImplPtr PermissionManager::GetTable()
{
	return db::TableImpls::Get()->PERMISSIONS;
}

mud::PermissionPtr PermissionManager::GetByKeys(KeysPtr keys)
{
	SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->PERMISSIONS, keys);
	PermissionPtr p(new Permission(manager));
	return p;
}

mud::PermissionPtr PermissionManager::GetByKeys(value_type grantgroup, value_type account)
{	
	KeysPtr keys(new Keys(db::TableImpls::Get()->PERMISSIONS));
	KeyPtr key;
	key = new Key(db::PermissionsFields::Get()->FKGRANTGROUPS, grantgroup);
	keys->addKey(key);
	key = new Key(db::PermissionsFields::Get()->FKACCOUNTS, account);
	keys->addKey(key);
	
	return GetByKeys(keys);
}
