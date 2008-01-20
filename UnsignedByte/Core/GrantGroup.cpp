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

#include "GrantGroup.h"
#include "Global.h"
#include "Permission.h"
#include "PermissionManager.h"

using mud::GrantGroup;

GrantGroup::GrantGroup(SavableManagerPtr area) :
m_grantgroup(area)
{
	if(!m_grantgroup)
		throw std::invalid_argument("GrantGroup::GrantGroup(), m_grantgroup == NULL!");
}

GrantGroup::~GrantGroup(void)
{

}

const std::string& GrantGroup::getName() const
{
	return m_grantgroup->getfield(db::GrantGroupsFields::Get()->NAME)->getStringValue();
}

long GrantGroup::getImplication() const
{
	return m_grantgroup->getfield(db::GrantGroupsFields::Get()->IMPLIES)->getIntegerValue();
}

bool GrantGroup::getDefaultGrant() const
{
	return m_grantgroup->getfield(db::GrantGroupsFields::Get()->DEFAULTGRANT)->getBoolValue();
}

bool GrantGroup::getDefaultLog() const
{
	return m_grantgroup->getfield(db::GrantGroupsFields::Get()->DEFAULTLOG)->getBoolValue();
}

void GrantGroup::setName(const std::string& name)
{
	ValuePtr value(new Value(db::GrantGroupsFields::Get()->NAME, name));
	m_grantgroup->setvalue(value);
}

void GrantGroup::setImplication(long implication)
{
	ValuePtr value(new Value(db::GrantGroupsFields::Get()->IMPLIES, implication));
	m_grantgroup->setvalue(value);
}

void GrantGroup::setDefaultGrant(bool defaultgrant)
{
	ValuePtr value(new Value(db::GrantGroupsFields::Get()->DEFAULTGRANT, defaultgrant));
	m_grantgroup->setvalue(value);
}

void GrantGroup::setDefaultLog(bool defaultlog)
{
	ValuePtr value(new Value(db::GrantGroupsFields::Get()->DEFAULTLOG, defaultlog));
	m_grantgroup->setvalue(value);
}

void GrantGroup::Delete()
{
	m_grantgroup->erase();
}

void GrantGroup::Save()
{
	m_grantgroup->save();
}

bool GrantGroup::Exists()
{
	return m_grantgroup->exists();
}

std::vector<std::string> GrantGroup::Show()
{
	std::vector<std::string> result;
	result.push_back(Global::Get()->sprintf("Name: '%s'.\n", getName().c_str()));
	return result;
}

std::string GrantGroup::ShowShort()
{
	return Global::Get()->sprintf("%s\n", 
			getName().c_str());
}

TablePtr GrantGroup::getTable() const
{
	return Tables::Get()->GRANTGROUPS;
}
