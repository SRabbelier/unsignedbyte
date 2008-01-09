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

#ifdef _WIN32
#pragma warning (disable:4244)
#pragma warning (disable:4267)
#endif

#include "db.h"

#include <Database.h>
#include <Query.h>

#include "TableImpl.h"
#include "Tables.h"
#include "FieldImpl.h"
#include "KeyDef.h"

using namespace db;

TableImpls::TableImpls() :
ACCOUNTS(new TableImpl(Tables::Get()->ACCOUNTS, "Accounts")),
AREAS(new TableImpl(Tables::Get()->AREAS, "Areas")),
BRANCHES(new TableImpl(Tables::Get()->BRANCHES, "Branches")),
CHARACTERACCOUNT(new TableImpl(Tables::Get()->CHARACTERACCOUNT, "CharacterAccount")),
CHARACTERBRANCH(new TableImpl(Tables::Get()->CHARACTERBRANCH, "CharacterBranch")),
CHARACTERCLUSTER(new TableImpl(Tables::Get()->CHARACTERCLUSTER, "CharacterCluster")),
CHARACTERS(new TableImpl(Tables::Get()->CHARACTERS, "Characters")),
CHARACTERSKILL(new TableImpl(Tables::Get()->CHARACTERSKILL, "CharacterSkill")),
CHARACTERSTAT(new TableImpl(Tables::Get()->CHARACTERSTAT, "CharacterStat")),
CHARACTERTREE(new TableImpl(Tables::Get()->CHARACTERTREE, "CharacterTree")),
CLUSTERS(new TableImpl(Tables::Get()->CLUSTERS, "Clusters")),
CHUNKS(new TableImpl(Tables::Get()->CHUNKS, "Chunks")),
COLOURS(new TableImpl(Tables::Get()->COLOURS, "Colours")),
COMMANDS(new TableImpl(Tables::Get()->COMMANDS, "Commands")),
DETAILS(new TableImpl(Tables::Get()->DETAILS, "Details")),
DETAILROOM(new TableImpl(Tables::Get()->DETAILROOM, "DetailRoom")),
DETAILCHUNK(new TableImpl(Tables::Get()->DETAILCHUNK, "DetailChunk")),
DETAILCHARACTER(new TableImpl(Tables::Get()->DETAILCHARACTER, "DetailCharacter")),
DETAILDETAIL(new TableImpl(Tables::Get()->DETAILDETAIL, "DetailDetail")),
EXITS(new TableImpl(Tables::Get()->EXITS, "Exits")),
GRANTGROUPS(new TableImpl(Tables::Get()->GRANTGROUPS, "GrantGroups")),
PERMISSIONS(new TableImpl(Tables::Get()->PERMISSIONS, "Permissions")),
RACES(new TableImpl(Tables::Get()->RACES, "Races")),
ROOMS(new TableImpl(Tables::Get()->ROOMS, "Rooms")),
SECTORS(new TableImpl(Tables::Get()->SECTORS, "Sectors")),
SKILLS(new TableImpl(Tables::Get()->SKILLS, "Skills")),
STATS(new TableImpl(Tables::Get()->STATS, "Stats")),
TREES(new TableImpl(Tables::Get()->TREES, "Trees")),
VERSION(new TableImpl(Tables::Get()->VERSION, "Version"))
{
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
	m_tables.push_back(CHUNKS);
	m_tables.push_back(COLOURS);
	m_tables.push_back(COMMANDS);
	m_tables.push_back(DETAILS);
	m_tables.push_back(DETAILROOM);
	m_tables.push_back(DETAILCHUNK);
	m_tables.push_back(DETAILCHARACTER);
	m_tables.push_back(DETAILDETAIL);
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

AccountsFields::AccountsFields() :
ACCOUNTID(new KeyDef(TableImpls::Get()->ACCOUNTS, "accountid")),
NAME(new FieldImpl(TableImpls::Get()->ACCOUNTS, "name", true)),
PASSWORD(new FieldImpl(TableImpls::Get()->ACCOUNTS, "password", true))
{

}

AreasFields::AreasFields() :
AREAID(new KeyDef(TableImpls::Get()->AREAS, "areaid")),
NAME(new FieldImpl(TableImpls::Get()->AREAS, "name", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->AREAS, "description", true)),
HEIGHT(new FieldImpl(TableImpls::Get()->AREAS, "height")),
WIDTH(new FieldImpl(TableImpls::Get()->AREAS, "width"))
{

}

BranchesFields::BranchesFields() :
BRANCHID(new KeyDef(TableImpls::Get()->BRANCHES, "branchid")),
NAME(new FieldImpl(TableImpls::Get()->BRANCHES, "name", true)),
FKTREES(new FieldImpl(TableImpls::Get()->BRANCHES, "fkTrees")),
FKSTATSPRIMARY(new FieldImpl(TableImpls::Get()->BRANCHES, "fkStatsPrimary")),
FKSTATSSECONDARY(new FieldImpl(TableImpls::Get()->BRANCHES, "fkStatsSecondary"))
{

}

CharacterAccountFields::CharacterAccountFields() :
FKACCOUNTS(new KeyDef(TableImpls::Get()->CHARACTERACCOUNT, "fkAccounts")),
FKCHARACTERS(new KeyDef(TableImpls::Get()->CHARACTERACCOUNT, "fkCharacters"))
{

}

CharacterBranchFields::CharacterBranchFields() :
FKBRANCHES(new KeyDef(TableImpls::Get()->CHARACTERBRANCH, "fkBranches")),
FKCHARACTERS(new KeyDef(TableImpls::Get()->CHARACTERBRANCH, "fkCharacters")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERBRANCH, "xp"))
{

}

CharacterClusterFields::CharacterClusterFields() :
FKCHARACTERS(new KeyDef(TableImpls::Get()->CHARACTERCLUSTER, "fkCharacters")),
FKCLUSTERS(new KeyDef(TableImpls::Get()->CHARACTERCLUSTER, "fkClusters")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERCLUSTER, "xp"))
{

}

CharactersFields::CharactersFields() :
CHARACTERID(new KeyDef(TableImpls::Get()->CHARACTERS, "characterid")),
FKRACES(new FieldImpl(TableImpls::Get()->CHARACTERS, "fkRaces")),
FKROOMS(new FieldImpl(TableImpls::Get()->CHARACTERS, "fkRooms")),
NAME(new FieldImpl(TableImpls::Get()->CHARACTERS, "name", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->CHARACTERS, "description", true))
{

}

CharacterSkillFields::CharacterSkillFields() :
FKBRANCHES(new KeyDef(TableImpls::Get()->CHARACTERSKILL, "fkBranches")),
FKCHARACTERS(new KeyDef(TableImpls::Get()->CHARACTERSKILL, "fkCharacters")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERSKILL, "xp"))
{

}

CharacterStatFields::CharacterStatFields() :
FKCHARACTERS(new KeyDef(TableImpls::Get()->CHARACTERSTAT, "fkCharacters")),
FKSTATS(new KeyDef(TableImpls::Get()->CHARACTERSTAT, "fkStats")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERSTAT, "xp"))
{

}

CharacterTreeFields::CharacterTreeFields() :
FKCHARACTERS(new KeyDef(TableImpls::Get()->CHARACTERTREE, "fkCharacters")),
FKTREES(new KeyDef(TableImpls::Get()->CHARACTERTREE, "fkTrees")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERTREE, "xp"))
{

}

ClustersFields::ClustersFields() :
CLUSTERID(new KeyDef(TableImpls::Get()->CLUSTERS, "clusterid")),
NAME(new FieldImpl(TableImpls::Get()->CLUSTERS, "name", true))
{

}

ChunksFields::ChunksFields() :
CHUNKID(new KeyDef(TableImpls::Get()->CHUNKS, "chunkid")),
FKROOMS(new FieldImpl(TableImpls::Get()->CHUNKS, "fkRooms")),
NAME(new FieldImpl(TableImpls::Get()->CHUNKS, "name", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->CHUNKS, "description", true)),
TAGS(new FieldImpl(TableImpls::Get()->CHUNKS, "tags", true))
{

}

ColoursFields::ColoursFields() :
COLOURID(new KeyDef(TableImpls::Get()->COLOURS, "colourid")),
NAME(new FieldImpl(TableImpls::Get()->COLOURS, "name", true)),
CODE(new FieldImpl(TableImpls::Get()->COLOURS, "code", true)),
COLOURSTRING(new FieldImpl(TableImpls::Get()->COLOURS, "colourstring", true)),
ANSI(new FieldImpl(TableImpls::Get()->COLOURS, "ansi"))
{

}

CommandsFields::CommandsFields() :
COMMANDID(new KeyDef(TableImpls::Get()->COMMANDS, "commandid")),
NAME(new FieldImpl(TableImpls::Get()->COMMANDS, "name", true)),
GRANTGROUP(new FieldImpl(TableImpls::Get()->COMMANDS, "grantgroup")),
HIGHFORCE(new FieldImpl(TableImpls::Get()->COMMANDS, "highforce")),
FORCE(new FieldImpl(TableImpls::Get()->COMMANDS, "force")),
LOWFORCE(new FieldImpl(TableImpls::Get()->COMMANDS, "lowforce"))
{

}

DetailsFields::DetailsFields() :
DETAILID(new KeyDef(TableImpls::Get()->DETAILS, "detailid")),
KEY(new FieldImpl(TableImpls::Get()->DETAILS, "key", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->DETAILS, "description", true))
{

}

DetailRoomFields::DetailRoomFields() :
FKDETAILS(new KeyDef(TableImpls::Get()->DETAILROOM, "fkDetails")),
FKROOMS(new KeyDef(TableImpls::Get()->DETAILROOM, "fkRooms"))
{

}

DetailChunkFields::DetailChunkFields() :
FKCHUNKS(new KeyDef(TableImpls::Get()->DETAILCHUNK, "fkChunks")),
FKDETAILS(new KeyDef(TableImpls::Get()->DETAILCHUNK, "fkDetails"))
{

}

DetailCharacterFields::DetailCharacterFields() :
FKCHARACTERS(new KeyDef(TableImpls::Get()->DETAILCHARACTER, "fkCharacters")),
FKDETAILS(new KeyDef(TableImpls::Get()->DETAILCHARACTER, "fkDetails"))
{

}

DetailDetailFields::DetailDetailFields() :
FKDETAILSPRIMARY(new KeyDef(TableImpls::Get()->DETAILDETAIL, "fkDetailsPrimary")),
FKDETAILSSECONDARY(new KeyDef(TableImpls::Get()->DETAILDETAIL, "fkDetailsSecondary"))
{

}

ExitsFields::ExitsFields() :
EXITID(new KeyDef(TableImpls::Get()->EXITS, "exitid")),
DIR(new FieldImpl(TableImpls::Get()->EXITS, "dir"))
{

}

GrantGroupsFields::GrantGroupsFields() :
GRANTGROUPID(new KeyDef(TableImpls::Get()->GRANTGROUPS, "grantgroupid")),
NAME(new FieldImpl(TableImpls::Get()->GRANTGROUPS, "name", true)),
DEFAULTGRANT(new FieldImpl(TableImpls::Get()->GRANTGROUPS, "defaultgrant")),
IMPLIES(new FieldImpl(TableImpls::Get()->GRANTGROUPS, "implies"))
{

}

PermissionsFields::PermissionsFields() :
FKACCOUNTS(new KeyDef(TableImpls::Get()->PERMISSIONS, "fkAccounts")),
FKGRANTGROUPS(new KeyDef(TableImpls::Get()->PERMISSIONS, "fkGrantGroups")),
GRANT(new FieldImpl(TableImpls::Get()->PERMISSIONS, "grant"))
{

}

RacesFields::RacesFields() :
RACEID(new KeyDef(TableImpls::Get()->RACES, "raceid")),
NAME(new FieldImpl(TableImpls::Get()->RACES, "name", true))
{

}

RoomsFields::RoomsFields() :
ROOMID(new KeyDef(TableImpls::Get()->ROOMS, "roomid")),
NAME(new FieldImpl(TableImpls::Get()->ROOMS, "name", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->ROOMS, "description", true)),
FKAREAS(new FieldImpl(TableImpls::Get()->ROOMS, "fkAreas")),
FKSECTORS(new FieldImpl(TableImpls::Get()->ROOMS, "fkSectors")),
WIDTH(new FieldImpl(TableImpls::Get()->ROOMS, "width")),
LENGTH(new FieldImpl(TableImpls::Get()->ROOMS, "length")),
HEIGHT(new FieldImpl(TableImpls::Get()->ROOMS, "height"))
{

}

SectorsFields::SectorsFields() :
SECTORID(new KeyDef(TableImpls::Get()->SECTORS, "sectorid")),
NAME(new FieldImpl(TableImpls::Get()->SECTORS, "name", true)),
SYMBOL(new FieldImpl(TableImpls::Get()->SECTORS, "symbol", true)),
MOVECOST(new FieldImpl(TableImpls::Get()->SECTORS, "movecost")),
WATER(new FieldImpl(TableImpls::Get()->SECTORS, "water"))
{

}

SkillsFields::SkillsFields() :
SKILLID(new KeyDef(TableImpls::Get()->SKILLS, "skillid")),
NAME(new FieldImpl(TableImpls::Get()->SKILLS, "name", true)),
FKBRANCHES(new FieldImpl(TableImpls::Get()->SKILLS, "fkBranches"))
{

}

StatsFields::StatsFields() :
STATID(new KeyDef(TableImpls::Get()->STATS, "statid")),
NAME(new FieldImpl(TableImpls::Get()->STATS, "name", true)),
SHORTNAME(new FieldImpl(TableImpls::Get()->STATS, "shortname", true))
{

}

TreesFields::TreesFields() :
TREEID(new KeyDef(TableImpls::Get()->TREES, "treeid")),
NAME(new FieldImpl(TableImpls::Get()->TREES, "name", true)),
FKCLUSTERS(new FieldImpl(TableImpls::Get()->TREES, "fkClusters")),
FKSTATSPRIMARY(new FieldImpl(TableImpls::Get()->TREES, "fkStatsPrimary")),
FKSTATSSECONDARY(new FieldImpl(TableImpls::Get()->TREES, "fkStatsSecondary"))
{

}

VersionFields::VersionFields() :
VERSIONID(new KeyDef(TableImpls::Get()->VERSION, "versionid")),
VERSIONTEXT(new FieldImpl(TableImpls::Get()->VERSION, "versiontext", true)),
MAJOR(new FieldImpl(TableImpls::Get()->VERSION, "major")),
MINOR(new FieldImpl(TableImpls::Get()->VERSION, "minor")),
MICRO(new FieldImpl(TableImpls::Get()->VERSION, "micro"))
{

}

