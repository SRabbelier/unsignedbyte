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

#include "Tables.h"
#include "TableDef.h"

Tables::Tables() :
	ACCOUNTS( new TableDef("Accounts") ),
	AREAS( new TableDef("Areas") ),
	BRANCHES( new TableDef("Branches") ),
	CHANNELS( new TableDef("Channels") ),
	CHARACTERACCOUNT( new TableDef("CharacterAccount") ),
	CHARACTERBRANCH( new TableDef("CharacterBranch") ),
	CHARACTERCLUSTER( new TableDef("CharacterCluster") ),
	CHARACTERSKILL( new TableDef("CharacterSkill") ),
	CHARACTERSTAT( new TableDef("CharacterStat") ),
	CHARACTERTREE( new TableDef("CharacterTree") ),
	CHUNKS( new TableDef("Chunks") ),
	CLUSTERS( new TableDef("Clusters") ),
	COLOURS( new TableDef("Colours") ),
	COMMANDS( new TableDef("Commands") ),
	DETAILS( new TableDef("Details") ),
	DETAILROOM( new TableDef("DetailRoom") ),
	DETAILCHUNK( new TableDef("DetailChunk") ),
	DETAILCHARACTER( new TableDef("DetailCharacter") ),
	DETAILDETAIL( new TableDef("DetailDetail") ),
	ECHOS( new TableDef("Echos") ),
	ENTITIES( new TableDef("Entities") ),
	EXITROOM( new TableDef("ExitRoom") ),
	EXITS( new TableDef("Exits") ),
	GRANTGROUPS( new TableDef("GrantGroups") ),
	PERMISSIONS( new TableDef("Permissions") ),
	RACES( new TableDef("Races") ),
	ROOMS( new TableDef("Rooms") ),
	SECTORS( new TableDef("Sectors") ),
	SKILLS( new TableDef("Skills") ),
	STATS( new TableDef("Stats") ),
	TRACES( new TableDef("Traces") ),
	TRACECHUNK( new TableDef("TraceChunk") ),
	TRACEDETAIL( new TableDef("TraceDetail") ),
	TRACEENTITY( new TableDef("TraceEntity") ),
	TRACEROOM( new TableDef("TraceRoom") ),
	TREES( new TableDef("Trees") ),
	VERSION( new TableDef("Version") )
{	
	ACCOUNTS->addPK("accountid");
	ACCOUNTS->addLookupTextField("name");
	ACCOUNTS->addTextField("password");
	
	AREAS->addPK("areaid");
	AREAS->addLookupTextField("name");
	AREAS->addTextField("description");
	AREAS->addValue("height");
	AREAS->addValue("width");
	
	BRANCHES->addPK("branchid");
	BRANCHES->addLookupTextField("name");
	BRANCHES->addFK(TREES);
	BRANCHES->addFK(STATS, "Primary");
	BRANCHES->addFK(STATS, "Secondary");
	
	CHANNELS->addPK("channelid");
	CHANNELS->addLookupTextField("name");
	CHANNELS->addTextField("description");
	CHANNELS->addValue("needLogin", 1);
	
	CHARACTERACCOUNT->addFPK(ENTITIES);
	CHARACTERACCOUNT->addFPK(ACCOUNTS);
	
	CHARACTERBRANCH->addFPK(ENTITIES);
	CHARACTERBRANCH->addFPK(BRANCHES);
	CHARACTERBRANCH->addValue("xp");
	
	CHARACTERCLUSTER->addFPK(ENTITIES);
	CHARACTERCLUSTER->addFPK(CLUSTERS);
	CHARACTERCLUSTER->addValue("xp");
	
	CHARACTERSKILL->addFPK(ENTITIES);
	CHARACTERSKILL->addFPK(BRANCHES);
	CHARACTERSKILL->addValue("xp");
	
	CHARACTERSTAT->addFPK(ENTITIES);
	CHARACTERSTAT->addFPK(STATS);
	CHARACTERSTAT->addValue("xp");
	
	CHARACTERTREE->addFPK(ENTITIES);
	CHARACTERTREE->addFPK(TREES);
	CHARACTERTREE->addValue("xp");
	
	CHUNKS->addPK("chunkid");
	CHUNKS->addFK(ROOMS);
	CHUNKS->addTextField("name");
	CHUNKS->addTextField("description");
	CHUNKS->addTextField("tags");
	
	CLUSTERS->addPK("clusterid");
	CLUSTERS->addLookupTextField("name");
		
	COLOURS->addPK("colourid");
	COLOURS->addLookupTextField("name");
	COLOURS->addLookupTextField("code");
	COLOURS->addTextField("colourstring");
	COLOURS->addValue("ansi");
	
	COMMANDS->addPK("commandid");
	COMMANDS->addLookupTextField("name");
	COMMANDS->addValue("grantgroup", 1);
	COMMANDS->addValue("highforce", 1);
	COMMANDS->addValue("force", 1);
	COMMANDS->addValue("lowforce", 0);
	
	DETAILS->addPK("detailid");
	DETAILS->addLookupTextField("key");
	DETAILS->addTextField("description");
	
	DETAILROOM->addFPK(DETAILS);
	DETAILROOM->addFPK(ROOMS);
	
	DETAILCHUNK->addFPK(DETAILS);
	DETAILCHUNK->addFPK(CHUNKS);
	
	DETAILCHARACTER->addFPK(DETAILS);
	DETAILCHARACTER->addFPK(ENTITIES);
	
	DETAILDETAIL->addFPK(DETAILS, "Primary");
	DETAILDETAIL->addFPK(DETAILS, "Secondary");
	
	ECHOS->addPK("echoid");
	ECHOS->addTextField("message");
	ECHOS->addValue("visibility");
	ECHOS->addValue("audibility");
	
	ENTITIES->addPK("entityid");
	ENTITIES->addFK(RACES);
	ENTITIES->addFK(ROOMS);
	ENTITIES->addLookupTextField("name");
	ENTITIES->addTextField("description");
	
	EXITROOM->addFPK(EXITS);
	EXITROOM->addFPK(ROOMS);
	
	EXITS->addPK("exitid");
	EXITS->addFK(ROOMS);
	EXITS->addValue("dir");
		
	GRANTGROUPS->addPK("grantgroupid");
	GRANTGROUPS->addLookupTextField("name");
	GRANTGROUPS->addValue("defaultgrant");
	GRANTGROUPS->addValue("defaultlog");
	GRANTGROUPS->addValue("implies");
	
	PERMISSIONS->addFPK(ACCOUNTS);
	PERMISSIONS->addFPK(GRANTGROUPS);
	PERMISSIONS->addValue("grant");
	PERMISSIONS->addValue("log");
	
	RACES->addPK("raceid");
	RACES->addLookupTextField("name");
	
	ROOMS->addPK("roomid");
	ROOMS->addTextField("name");
	ROOMS->addTextField("description");
	ROOMS->addFK(AREAS);
	ROOMS->addFK(SECTORS);
	ROOMS->addValue("width");
	ROOMS->addValue("length");
	ROOMS->addValue("height");
	
	SECTORS->addPK("sectorid");
	SECTORS->addLookupTextField("name");
	SECTORS->addTextField("symbol");
	SECTORS->addValue("movecost");
	SECTORS->addValue("water");
	
	SKILLS->addPK("skillid");
	SKILLS->addLookupTextField("name");
	SKILLS->addFK(BRANCHES);
	
	STATS->addPK("statid");
	STATS->addLookupTextField("name");
	STATS->addLookupTextField("shortname");
	
	TRACES->addPK("traceid");
	TRACES->addFK(ACCOUNTS);
	TRACES->addValue("time");
	TRACES->addTextField("description");
	TRACES->addTextField("diff");
	
	TRACECHUNK->addFPK(TRACES);
	TRACECHUNK->addFPK(CHUNKS);
	
	TRACEDETAIL->addFPK(TRACES);
	TRACEDETAIL->addFPK(DETAILS);
	
	TRACEENTITY->addFPK(TRACES);
	TRACEENTITY->addFPK(ENTITIES);
	
	TRACEROOM->addFPK(TRACES);
	TRACEROOM->addFPK(ROOMS);
	
	TREES->addPK("treeid");
	TREES->addLookupTextField("name");
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
	m_tables.push_back(CHANNELS);
	m_tables.push_back(CHARACTERACCOUNT);
	m_tables.push_back(CHARACTERBRANCH);
	m_tables.push_back(CHARACTERCLUSTER);
	m_tables.push_back(CHARACTERSKILL);
	m_tables.push_back(CHARACTERSTAT);
	m_tables.push_back(CHARACTERTREE);
	m_tables.push_back(CLUSTERS);
	m_tables.push_back(CHUNKS);
	m_tables.push_back(COLOURS);
	m_tables.push_back(COMMANDS);
	m_tables.push_back(DETAILS);
	m_tables.push_back(DETAILROOM);
	m_tables.push_back(DETAILCHUNK);
	m_tables.push_back(DETAILCHARACTER);
	m_tables.push_back(DETAILDETAIL);
	m_tables.push_back(ECHOS);
	m_tables.push_back(ENTITIES);
	m_tables.push_back(EXITROOM);
	m_tables.push_back(EXITS);
	m_tables.push_back(GRANTGROUPS);
	m_tables.push_back(PERMISSIONS);
	m_tables.push_back(RACES);
	m_tables.push_back(ROOMS);
	m_tables.push_back(SECTORS);
	m_tables.push_back(SKILLS);
	m_tables.push_back(STATS);
	m_tables.push_back(TRACES);
	m_tables.push_back(TRACECHUNK);
	m_tables.push_back(TRACEDETAIL);
	m_tables.push_back(TRACEENTITY);
	m_tables.push_back(TRACEROOM);
	m_tables.push_back(TREES);
	m_tables.push_back(VERSION);
}

Tables::~Tables()
{

}
