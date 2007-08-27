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
	ACCOUNTS( new Table("Accounts","account" )),
	AREAS( new Table("Areas","area" )),
	BRANCHES( new Table("Branches", "branch" )),
	CHARACTERACCOUNT( new Table("CharacterAccount" )),
	CHARACTERBRANCH( new Table("CharacterBranch" )),
	CHARACTERCLUSTER( new Table("CharacterCluster" )),
	CHARACTERS( new Table("Characters","character" )),
	CHARACTERSKILL( new Table("CharacterSkill" )),
	CHARACTERSTAT( new Table("CharacterStat" )),
	CHARACTERTREE( new Table("CharacterTree" )),
	CLUSTERS( new Table("Clusters", "cluster" )),
	COLOURS( new Table("Colours","colour" )),
	COMMANDS( new Table("Commands","command" )),
	EXITS( new Table("Exits","exit" )),
	GRANTGROUPS( new Table("GrantGroups","grantgroup" )),
	PERMISSIONS( new Table("Permissions","permission" )),
	RACES( new Table("Races","race" )),
	ROOMS( new Table("Rooms","room" )),
	SECTORS( new Table("Sectors","sector" )),
	SKILLS( new Table("Skills", "skill" )),
	STATS( new Table("Stats", "stat" )),
	TREES( new Table("Trees", "tree" )),
	VERSION( new Table("Version", "version" ))
{	
	ACCOUNTS->addField("name", true);
	ACCOUNTS->addField("password", true);
	
	AREAS->addField("name", true);
	AREAS->addField("description", true);
	AREAS->addField("height");
	AREAS->addField("width");
	
	BRANCHES->addField("name", true);
	BRANCHES->addFK(TREES);
	BRANCHES->addFK(STATS, "Primary");
	BRANCHES->addFK(STATS, "Secondary");
	
	CHARACTERACCOUNT->addFK(CHARACTERS);
	CHARACTERACCOUNT->addFK(ACCOUNTS);
	
	CHARACTERBRANCH->addFK(CHARACTERS);
	CHARACTERBRANCH->addFK(BRANCHES);
	
	CHARACTERCLUSTER->addFK(CHARACTERS);
	CHARACTERCLUSTER->addFK(CLUSTERS);
	
	CHARACTERS->addFK(RACES);
	CHARACTERS->addFK(ROOMS);
	CHARACTERS->addField("name", true);
	CHARACTERS->addField("description", true);
	
	CHARACTERSKILL->addFK(CHARACTERS);
	CHARACTERSKILL->addFK(BRANCHES);
	
	CHARACTERSTAT->addFK(CHARACTERS);
	CHARACTERSTAT->addFK(STATS);
	
	CHARACTERTREE->addFK(CHARACTERS);
	CHARACTERTREE->addFK(TREES);
	
	CLUSTERS->addField("name", true);
		
	COLOURS->addField("name", true);
	COLOURS->addField("code", true);
	COLOURS->addField("colourstring", true);
	COLOURS->addField("ansi");
	
	COMMANDS->addField("name", true);
	COMMANDS->addField("grantgroup", 1);
	COMMANDS->addField("highforce", 1);
	COMMANDS->addField("force", 1);
	COMMANDS->addField("lowforce", 0);
	
	EXITS->addField("dir");
		
	GRANTGROUPS->addField("name", true);
	GRANTGROUPS->addField("defaultgrant");
	GRANTGROUPS->addField("implies");
	
	PERMISSIONS->addFK(ACCOUNTS);
	PERMISSIONS->addFK(COMMANDS);
	PERMISSIONS->addFK(GRANTGROUPS);
	PERMISSIONS->addField("grant");
	
	RACES->addField("name", true);
	
	ROOMS->addField("name", true);
	ROOMS->addField("description", true);
	ROOMS->addFK(AREAS);
	ROOMS->addFK(SECTORS);
	ROOMS->addField("width");
	ROOMS->addField("length");
	ROOMS->addField("height");
	
	SECTORS->addField("name", true);
	SECTORS->addField("symbol", true);
	SECTORS->addField("movecost");
	SECTORS->addField("water");
	
	SKILLS->addField("name", true);
	SKILLS->addFK(BRANCHES);
	
	STATS->addField("name", true);
	STATS->addField("shortname", true);
	
	TREES->addField("name", true);
	TREES->addFK(CLUSTERS);
	TREES->addFK(STATS, "Primary");
	TREES->addFK(STATS, "Secondary");
	
	VERSION->addField("versiontext", true);
	VERSION->addField("major");
	VERSION->addField("minor");
	VERSION->addField("micro");
	
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
