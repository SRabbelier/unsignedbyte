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

#include "Permission.h"
#include "PermissionManager.h"

using mud::Permission;

Permission::Permission(SavableManagerPtr area) :
m_permission(area)
{
	if(!m_permission)
		throw std::invalid_argument("Permission::Permission(), m_permission == NULL!");
}

Permission::~Permission(void)
{

}

bool Permission::hasGrant() const
{
	return m_permission->getfield(db::PermissionsFields::Get()->GRANT)->getBoolValue();
}

bool Permission::hasLog() const
{
	return m_permission->getfield(db::PermissionsFields::Get()->LOG)->getBoolValue();
}

void Permission::setGrant(bool grant)
{
	ValuePtr value(new Value(db::PermissionsFields::Get()->GRANT, grant ? 1 : 0));
	m_permission->setvalue(value);
}

void Permission::setLog(bool log)
{
	ValuePtr value(new Value(db::PermissionsFields::Get()->LOG, log ? 1 : 0));
	m_permission->setvalue(value);
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

TableImplPtr Permission::getTable() const
{
	return m_permission->getTable();
}
