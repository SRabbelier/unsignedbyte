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

#include "Permission.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "db.h"

using mud::Permission;

bool Permission::defaultGrant = true;
bool Permission::defaultLog = false;

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
	return isGrant(m_permission->getgrant());
}

bool Permission::hasLog() const
{
	return isLog(m_permission->getgrant());
}

bool Permission::isGrant(long grant)
{
	switch(grant)
	{
		default:
			return defaultGrant;
			
		case GRANT_ENABLE:
		case GRANT_ENABLEANDLOG:
			return true;
			
		case GRANT_DISABLE:
		case GRANT_DISABLEANDLOG:
			return false;
	}
}

bool Permission::isLog(long grant)
{
	switch(grant)
	{
		default:
			return defaultLog;
			
		case GRANT_ENABLEANDLOG:
		case GRANT_DISABLEANDLOG:
			return true;
			
		case GRANT_ENABLE:
		case GRANT_DISABLE:
			return false;
	}
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

std::vector<std::string> Permission::List()
{
	return GetTable()->tableList();
}

TablePtr Permission::GetTable()
{
	return Tables::Get()->PERMISSIONS;
}
