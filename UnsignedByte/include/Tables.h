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
#include "Table.h"

typedef std::vector<TablePtr> TableVector;

class Tables : public Singleton<Tables>
{
public:
	TablePtr ACCOUNTS;
	TablePtr AREAS;
	TablePtr BRANCHES;
	TablePtr CHARACTERACCOUNT;
	TablePtr CHARACTERBRANCH;
	TablePtr CHARACTERCLUSTER;
	TablePtr CHARACTERS;
	TablePtr CHARACTERSKILL;
	TablePtr CHARACTERSTAT;
	TablePtr CHARACTERTREE;
	TablePtr CLUSTERS;
	TablePtr COLOURS;
	TablePtr COMMANDS;
	TablePtr EXITS;
	TablePtr GRANTGROUPS;
	TablePtr PERMISSIONS;
	TablePtr RACES;
	TablePtr ROOMS;
	TablePtr SECTORS;
	TablePtr SKILLS;
	TablePtr STATS;
	TablePtr TREES;
	TablePtr VERSION;
	
	TableVector::const_iterator begin() const { return m_tables.begin(); };
	TableVector::const_iterator end() const { return m_tables.end(); };
	
private:
	friend class Singleton<Tables>;
	Tables();
	~Tables();
	
	TableVector m_tables;
};
