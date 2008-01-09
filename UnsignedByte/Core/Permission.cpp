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

#include "Permission.h"
#include "PermissionManager.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "db.h"

#include "Table.h"
#include "Tables.h"

using mud::Permission;

Permission::Permission(db::Permissions* area) :
m_permission(area)
{
	if(m_permission == NULL)
		throw std::invalid_argument("Permission::Permission(), m_permission == NULL!");
}

Permission::~Permission(void)
{
	delete m_permission;
	m_permission = NULL;
}

bool Permission::hasGrant() const
{
	return mud::PermissionManager::Get()->isGrant(m_permission->getgrant());
}

bool Permission::hasLog() const
{
	return mud::PermissionManager::Get()->isLog(m_permission->getgrant());
}

void Permission::setGrant(bool grant)
{
	if(grant)
	{
		if(hasLog())
			m_permission->setgrant(GRANT_ENABLEANDLOG);
		else
			m_permission->setgrant(GRANT_ENABLE);
	}
	else
	{
		if(hasLog())
			m_permission->setgrant(GRANT_DISABLEANDLOG);
		else
			m_permission->setgrant(GRANT_DISABLE);
	}
}

void Permission::setLog(bool log)
{
	if(log)
	{
		if(hasGrant())
			m_permission->setgrant(GRANT_ENABLEANDLOG);
		else
			m_permission->setgrant(GRANT_DISABLEANDLOG);
	}
	else
	{
		if(hasGrant())
			m_permission->setgrant(GRANT_ENABLE);
		else
			m_permission->setgrant(GRANT_DISABLE);
	}
}

void Permission::Delete()
{
	m_permission->erase();
}

void Permission::Save()
{
	m_permission->save();
}

bool Permission::Exists()
{
	return m_permission->exists();
}

std::vector<std::string> Permission::Show()
{
	std::vector<std::string> result;
	
	return result;
}

std::string Permission::ShowShort()
{
	std::string result;
	
	return result;
}

TablePtr Permission::getTable() const
{
	return Tables::Get()->PERMISSIONS;
}
