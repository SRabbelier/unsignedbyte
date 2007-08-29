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

#include "GrantGroup.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "db.h"
#include "Permission.h"

GrantGroup::GrantGroup(db::GrantGroups* area) :
m_grantgroup(area)
{
	if(m_grantgroup == NULL)
		throw std::invalid_argument("GrantGroup::GrantGroup(), m_grantgroup == NULL!");
}

GrantGroup::~GrantGroup(void)
{
	delete m_grantgroup;
	m_grantgroup = NULL;
}

bool GrantGroup::getDefaultGrant()
{
	return Permission::isGrant(m_grantgroup->defaultgrant);
}

bool GrantGroup::getDefaultLog()
{
	return Permission::isLog(m_grantgroup->defaultgrant);
}

/*void GrantGroup::setDefaultGrant(bool defaultgrant)
{
	UBASSERT(m_grantgroup != NULL);
	if(m_grantgroup)
		m_grantgroup->defaultgrant = defaultgrant;
}*/

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
	return m_grantgroup->grantgroupid;
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

std::vector<std::string> GrantGroup::List()
{
	std::vector<std::string> result;
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->GRANTGROUPS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		GrantGroup* grantgroup = Cache::Get()->GetGrantGroup(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(grantgroup->ShowShort());
		result.push_back(line);
	}
	return result;
}

Table* GrantGroup::getTable() const
{
	return Tables::Get()->GRANTGROUPS;
}

