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

#include "Tables.h"
#include "Table.h"

Tables::Tables() :
	ACCOUNTS( new Table("Accounts") ),
	AREAS( new Table("Areas") ),
	BRANCHES( new Table("Branches") ),
	CHARACTERACCOUNT( new Table("CharacterAccount") ),
	CHARACTERBRANCH( new Table("CharacterBranch") ),
	CHARACTERCLUSTER( new Table("CharacterCluster") ),
	CHARACTERS( new Table("Characters") ),
	CHARACTERSKILL( new Table("CharacterSkill") ),
	CHARACTERSTAT( new Table("CharacterStat") ),
	CHARACTERTREE( new Table("CharacterTree") ),
	CLUSTERS( new Table("Clusters") ),
	COLOURS( new Table("Colours") ),
	COMMANDS( new Table("Commands") ),
	EXITS( new Table("Exits") ),
	GRANTGROUPS( new Table("GrantGroups") ),
	PERMISSIONS( new Table("Permissions") ),
	RACES( new Table("Races") ),
	ROOMS( new Table("Rooms") ),
	SECTORS( new Table("Sectors") ),
	SKILLS( new Table("Skills") ),
	STATS( new Table("Stats") ),
	TREES( new Table("Trees") ),
	VERSION( new Table("Version") )
{	
	ACCOUNTS->addPK("accountid");
	ACCOUNTS->addTextField("name");
	ACCOUNTS->addTextField("password");
	
	AREAS->addPK("areaid");
	AREAS->addTextField("name");
	AREAS->addTextField("description");
	AREAS->addValue("height");
	AREAS->addValue("width");
	
	BRANCHES->addPK("branchid");
	BRANCHES->addTextField("name");
	BRANCHES->addFK(TREES);
	BRANCHES->addFK(STATS, "Primary");
	BRANCHES->addFK(STATS, "Secondary");
	
	CHARACTERACCOUNT->addFPK(CHARACTERS);
	CHARACTERACCOUNT->addFPK(ACCOUNTS);
	
	CHARACTERBRANCH->addFPK(CHARACTERS);
	CHARACTERBRANCH->addFPK(BRANCHES);
	CHARACTERBRANCH->addValue("xp");
	
	CHARACTERCLUSTER->addFPK(CHARACTERS);
	CHARACTERCLUSTER->addFPK(CLUSTERS);
	CHARACTERCLUSTER->addValue("xp");
	
	CHARACTERS->addPK("characterid");
	CHARACTERS->addFK(RACES);
	CHARACTERS->addFK(ROOMS);
	CHARACTERS->addTextField("name");
	CHARACTERS->addTextField("description");
	
	CHARACTERSKILL->addFPK(CHARACTERS);
	CHARACTERSKILL->addFPK(BRANCHES);
	CHARACTERSKILL->addValue("xp");
	
	CHARACTERSTAT->addFPK(CHARACTERS);
	CHARACTERSTAT->addFPK(STATS);
	CHARACTERSTAT->addValue("xp");
	
	CHARACTERTREE->addFPK(CHARACTERS);
	CHARACTERTREE->addFPK(TREES);
	CHARACTERTREE->addValue("xp");
	
	CLUSTERS->addPK("clusterid");
	CLUSTERS->addTextField("name");
		
	COLOURS->addPK("colourid");
	COLOURS->addTextField("name");
	COLOURS->addTextField("code");
	COLOURS->addTextField("colourstring");
	COLOURS->addValue("ansi");
	
	COMMANDS->addPK("commandid");
	COMMANDS->addTextField("name");
	COMMANDS->addValue("grantgroup", 1);
	COMMANDS->addValue("highforce", 1);
	COMMANDS->addValue("force", 1);
	COMMANDS->addValue("lowforce", 0);
	
	EXITS->addPK("exitid");
	EXITS->addValue("dir");
		
	GRANTGROUPS->addPK("grantgroupid");
	GRANTGROUPS->addTextField("name");
	GRANTGROUPS->addValue("defaultgrant");
	GRANTGROUPS->addValue("implies");
	
	PERMISSIONS->addFPK(ACCOUNTS);
	PERMISSIONS->addFPK(GRANTGROUPS);
	PERMISSIONS->addValue("grant");
	
	RACES->addPK("areaid");
	RACES->addTextField("name");
	
	ROOMS->addPK("roomid");
	ROOMS->addTextField("name");
	ROOMS->addTextField("description");
	ROOMS->addFK(AREAS);
	ROOMS->addFK(SECTORS);
	ROOMS->addValue("width");
	ROOMS->addValue("length");
	ROOMS->addValue("height");
	
	SECTORS->addPK("sectorid");
	SECTORS->addTextField("name");
	SECTORS->addTextField("symbol");
	SECTORS->addValue("movecost");
	SECTORS->addValue("water");
	
	SKILLS->addPK("skillid");
	SKILLS->addTextField("name");
	SKILLS->addFK(BRANCHES);
	
	STATS->addPK("statid");
	STATS->addTextField("name");
	STATS->addTextField("shortname");
	
	TREES->addPK("treeid");
	TREES->addTextField("name");
	TREES->addFK(CLUSTERS);
	TREES->addFK(STATS, "Primary");
	TREES->addFK(STATS, "Secondary");
	
	VERSION->addPK("versionid");
	VERSION->addTextField("versiontext");
	VERSION->addValue("major");
	VERSION->addValue("minor");
	VERSION->addValue("micro");
	
	m_tables.push_back(ACCOUNTS);
	m_tables.push_back(AREAS);
	m_tables.push_back(BRANCHES);
	m_tables.push_back(CHARACTERACCOUNT);
	m_tables.push_back(CHARACTERBRANCH);
	m_tables.push_back(CHARACTERCLUSTER);
	m_tables.push_back(CHARACTERS);
	m_tables.push_back(CHARACTERSKILL);
	m_tables.push_back(CHARACTERSTAT);
	m_tables.push_back(CHARACTERTREE);
	m_tables.push_back(CLUSTERS);
	m_tables.push_back(COLOURS);
	m_tables.push_back(COMMANDS);
	m_tables.push_back(EXITS);
	m_tables.push_back(GRANTGROUPS);
	m_tables.push_back(PERMISSIONS);
	m_tables.push_back(RACES);
	m_tables.push_back(ROOMS);
	m_tables.push_back(SECTORS);
	m_tables.push_back(SKILLS);
	m_tables.push_back(STATS);
	m_tables.push_back(TREES);
	m_tables.push_back(VERSION);
}

Tables::~Tables()
{
	for(TableVector::iterator it = m_tables.begin(); it != m_tables.end(); it++)
	{
		delete (*it);
	}
}
