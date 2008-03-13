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

/* NOTE: This file was generated automatically. Do not edit. */

#ifdef _WIN32
#pragma warning (disable:4244)
#pragma warning (disable:4267)
#endif

#include "db.h"

#include <Database.h>
#include <Query.h>

#include "TableImpl.h"
#include "TableImpls.h"
#include "Tables.h"
#include "FieldImpl.h"
#include "KeyDef.h"

using namespace db;

AccountsFields::AccountsFields() :
ACCOUNTID(new KeyDef(TableImpls::Get()->ACCOUNTS, "accountid")),
NAME(new FieldImpl(TableImpls::Get()->ACCOUNTS, "name", true)),
PASSWORD(new FieldImpl(TableImpls::Get()->ACCOUNTS, "password", true))
{
	TableImpls::Get()->ACCOUNTS->addKey(ACCOUNTID);
	TableImpls::Get()->ACCOUNTS->addField(NAME);
	TableImpls::Get()->ACCOUNTS->addField(PASSWORD);
}

AreasFields::AreasFields() :
AREAID(new KeyDef(TableImpls::Get()->AREAS, "areaid")),
NAME(new FieldImpl(TableImpls::Get()->AREAS, "name", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->AREAS, "description", true)),
HEIGHT(new FieldImpl(TableImpls::Get()->AREAS, "height")),
WIDTH(new FieldImpl(TableImpls::Get()->AREAS, "width"))
{
	TableImpls::Get()->AREAS->addKey(AREAID);
	TableImpls::Get()->AREAS->addField(NAME);
	TableImpls::Get()->AREAS->addField(DESCRIPTION);
	TableImpls::Get()->AREAS->addField(HEIGHT);
	TableImpls::Get()->AREAS->addField(WIDTH);
}

BranchesFields::BranchesFields() :
BRANCHID(new KeyDef(TableImpls::Get()->BRANCHES, "branchid")),
NAME(new FieldImpl(TableImpls::Get()->BRANCHES, "name", true)),
FKTREES(new FieldImpl(TableImpls::Get()->BRANCHES, "fkTrees")),
FKSTATSPRIMARY(new FieldImpl(TableImpls::Get()->BRANCHES, "fkStatsPrimary")),
FKSTATSSECONDARY(new FieldImpl(TableImpls::Get()->BRANCHES, "fkStatsSecondary"))
{
	TableImpls::Get()->BRANCHES->addKey(BRANCHID);
	TableImpls::Get()->BRANCHES->addField(NAME);
	TableImpls::Get()->BRANCHES->addField(FKTREES);
	TableImpls::Get()->BRANCHES->addField(FKSTATSPRIMARY);
	TableImpls::Get()->BRANCHES->addField(FKSTATSSECONDARY);
}

CharacterAccountFields::CharacterAccountFields() :
FKACCOUNTS(new KeyDef(TableImpls::Get()->CHARACTERACCOUNT, "fkAccounts")),
FKENTITIES(new KeyDef(TableImpls::Get()->CHARACTERACCOUNT, "fkEntities"))
{
	TableImpls::Get()->CHARACTERACCOUNT->addKey(FKACCOUNTS);
	TableImpls::Get()->CHARACTERACCOUNT->addKey(FKENTITIES);
}

CharacterBranchFields::CharacterBranchFields() :
FKBRANCHES(new KeyDef(TableImpls::Get()->CHARACTERBRANCH, "fkBranches")),
FKENTITIES(new KeyDef(TableImpls::Get()->CHARACTERBRANCH, "fkEntities")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERBRANCH, "xp"))
{
	TableImpls::Get()->CHARACTERBRANCH->addKey(FKBRANCHES);
	TableImpls::Get()->CHARACTERBRANCH->addKey(FKENTITIES);
	TableImpls::Get()->CHARACTERBRANCH->addField(XP);
}

CharacterClusterFields::CharacterClusterFields() :
FKCLUSTERS(new KeyDef(TableImpls::Get()->CHARACTERCLUSTER, "fkClusters")),
FKENTITIES(new KeyDef(TableImpls::Get()->CHARACTERCLUSTER, "fkEntities")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERCLUSTER, "xp"))
{
	TableImpls::Get()->CHARACTERCLUSTER->addKey(FKCLUSTERS);
	TableImpls::Get()->CHARACTERCLUSTER->addKey(FKENTITIES);
	TableImpls::Get()->CHARACTERCLUSTER->addField(XP);
}

CharacterSkillFields::CharacterSkillFields() :
FKBRANCHES(new KeyDef(TableImpls::Get()->CHARACTERSKILL, "fkBranches")),
FKENTITIES(new KeyDef(TableImpls::Get()->CHARACTERSKILL, "fkEntities")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERSKILL, "xp"))
{
	TableImpls::Get()->CHARACTERSKILL->addKey(FKBRANCHES);
	TableImpls::Get()->CHARACTERSKILL->addKey(FKENTITIES);
	TableImpls::Get()->CHARACTERSKILL->addField(XP);
}

CharacterStatFields::CharacterStatFields() :
FKENTITIES(new KeyDef(TableImpls::Get()->CHARACTERSTAT, "fkEntities")),
FKSTATS(new KeyDef(TableImpls::Get()->CHARACTERSTAT, "fkStats")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERSTAT, "xp"))
{
	TableImpls::Get()->CHARACTERSTAT->addKey(FKENTITIES);
	TableImpls::Get()->CHARACTERSTAT->addKey(FKSTATS);
	TableImpls::Get()->CHARACTERSTAT->addField(XP);
}

CharacterTreeFields::CharacterTreeFields() :
FKENTITIES(new KeyDef(TableImpls::Get()->CHARACTERTREE, "fkEntities")),
FKTREES(new KeyDef(TableImpls::Get()->CHARACTERTREE, "fkTrees")),
XP(new FieldImpl(TableImpls::Get()->CHARACTERTREE, "xp"))
{
	TableImpls::Get()->CHARACTERTREE->addKey(FKENTITIES);
	TableImpls::Get()->CHARACTERTREE->addKey(FKTREES);
	TableImpls::Get()->CHARACTERTREE->addField(XP);
}

ClustersFields::ClustersFields() :
CLUSTERID(new KeyDef(TableImpls::Get()->CLUSTERS, "clusterid")),
NAME(new FieldImpl(TableImpls::Get()->CLUSTERS, "name", true))
{
	TableImpls::Get()->CLUSTERS->addKey(CLUSTERID);
	TableImpls::Get()->CLUSTERS->addField(NAME);
}

ChunksFields::ChunksFields() :
CHUNKID(new KeyDef(TableImpls::Get()->CHUNKS, "chunkid")),
FKROOMS(new FieldImpl(TableImpls::Get()->CHUNKS, "fkRooms")),
NAME(new FieldImpl(TableImpls::Get()->CHUNKS, "name", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->CHUNKS, "description", true)),
TAGS(new FieldImpl(TableImpls::Get()->CHUNKS, "tags", true))
{
	TableImpls::Get()->CHUNKS->addKey(CHUNKID);
	TableImpls::Get()->CHUNKS->addField(FKROOMS);
	TableImpls::Get()->CHUNKS->addField(NAME);
	TableImpls::Get()->CHUNKS->addField(DESCRIPTION);
	TableImpls::Get()->CHUNKS->addField(TAGS);
}

ColoursFields::ColoursFields() :
COLOURID(new KeyDef(TableImpls::Get()->COLOURS, "colourid")),
NAME(new FieldImpl(TableImpls::Get()->COLOURS, "name", true)),
CODE(new FieldImpl(TableImpls::Get()->COLOURS, "code", true)),
COLOURSTRING(new FieldImpl(TableImpls::Get()->COLOURS, "colourstring", true)),
ANSI(new FieldImpl(TableImpls::Get()->COLOURS, "ansi"))
{
	TableImpls::Get()->COLOURS->addKey(COLOURID);
	TableImpls::Get()->COLOURS->addField(NAME);
	TableImpls::Get()->COLOURS->addField(CODE);
	TableImpls::Get()->COLOURS->addField(COLOURSTRING);
	TableImpls::Get()->COLOURS->addField(ANSI);
}

CommandsFields::CommandsFields() :
COMMANDID(new KeyDef(TableImpls::Get()->COMMANDS, "commandid")),
NAME(new FieldImpl(TableImpls::Get()->COMMANDS, "name", true)),
GRANTGROUP(new FieldImpl(TableImpls::Get()->COMMANDS, "grantgroup")),
HIGHFORCE(new FieldImpl(TableImpls::Get()->COMMANDS, "highforce")),
FORCE(new FieldImpl(TableImpls::Get()->COMMANDS, "force")),
LOWFORCE(new FieldImpl(TableImpls::Get()->COMMANDS, "lowforce"))
{
	TableImpls::Get()->COMMANDS->addKey(COMMANDID);
	TableImpls::Get()->COMMANDS->addField(NAME);
	TableImpls::Get()->COMMANDS->addField(GRANTGROUP);
	TableImpls::Get()->COMMANDS->addField(HIGHFORCE);
	TableImpls::Get()->COMMANDS->addField(FORCE);
	TableImpls::Get()->COMMANDS->addField(LOWFORCE);
}

DetailsFields::DetailsFields() :
DETAILID(new KeyDef(TableImpls::Get()->DETAILS, "detailid")),
KEY(new FieldImpl(TableImpls::Get()->DETAILS, "key", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->DETAILS, "description", true))
{
	TableImpls::Get()->DETAILS->addKey(DETAILID);
	TableImpls::Get()->DETAILS->addField(KEY);
	TableImpls::Get()->DETAILS->addField(DESCRIPTION);
}

DetailRoomFields::DetailRoomFields() :
FKDETAILS(new KeyDef(TableImpls::Get()->DETAILROOM, "fkDetails")),
FKROOMS(new KeyDef(TableImpls::Get()->DETAILROOM, "fkRooms"))
{
	TableImpls::Get()->DETAILROOM->addKey(FKDETAILS);
	TableImpls::Get()->DETAILROOM->addKey(FKROOMS);
}

DetailChunkFields::DetailChunkFields() :
FKCHUNKS(new KeyDef(TableImpls::Get()->DETAILCHUNK, "fkChunks")),
FKDETAILS(new KeyDef(TableImpls::Get()->DETAILCHUNK, "fkDetails"))
{
	TableImpls::Get()->DETAILCHUNK->addKey(FKCHUNKS);
	TableImpls::Get()->DETAILCHUNK->addKey(FKDETAILS);
}

DetailCharacterFields::DetailCharacterFields() :
FKDETAILS(new KeyDef(TableImpls::Get()->DETAILCHARACTER, "fkDetails")),
FKENTITIES(new KeyDef(TableImpls::Get()->DETAILCHARACTER, "fkEntities"))
{
	TableImpls::Get()->DETAILCHARACTER->addKey(FKDETAILS);
	TableImpls::Get()->DETAILCHARACTER->addKey(FKENTITIES);
}

DetailDetailFields::DetailDetailFields() :
FKDETAILSPRIMARY(new KeyDef(TableImpls::Get()->DETAILDETAIL, "fkDetailsPrimary")),
FKDETAILSSECONDARY(new KeyDef(TableImpls::Get()->DETAILDETAIL, "fkDetailsSecondary"))
{
	TableImpls::Get()->DETAILDETAIL->addKey(FKDETAILSPRIMARY);
	TableImpls::Get()->DETAILDETAIL->addKey(FKDETAILSSECONDARY);
}

EchosFields::EchosFields() :
ECHOID(new KeyDef(TableImpls::Get()->ECHOS, "echoid")),
MESSAGE(new FieldImpl(TableImpls::Get()->ECHOS, "message", true)),
VISIBILITY(new FieldImpl(TableImpls::Get()->ECHOS, "visibility")),
AUDIBILITY(new FieldImpl(TableImpls::Get()->ECHOS, "audibility"))
{
	TableImpls::Get()->ECHOS->addKey(ECHOID);
	TableImpls::Get()->ECHOS->addField(MESSAGE);
	TableImpls::Get()->ECHOS->addField(VISIBILITY);
	TableImpls::Get()->ECHOS->addField(AUDIBILITY);
}

EntitiesFields::EntitiesFields() :
ENTITYID(new KeyDef(TableImpls::Get()->ENTITIES, "entityid")),
FKRACES(new FieldImpl(TableImpls::Get()->ENTITIES, "fkRaces")),
FKROOMS(new FieldImpl(TableImpls::Get()->ENTITIES, "fkRooms")),
NAME(new FieldImpl(TableImpls::Get()->ENTITIES, "name", true)),
DESCRIPTION(new FieldImpl(TableImpls::Get()->ENTITIES, "description", true))
{
	TableImpls::Get()->ENTITIES->addKey(ENTITYID);
	TableImpls::Get()->ENTITIES->addField(FKRACES);
	TableImpls::Get()->ENTITIES->addField(FKROOMS);
	TableImpls::Get()->ENTITIES->addField(NAME);
	TableImpls::Get()->ENTITIES->addField(DESCRIPTION);
}

ExitRoomFields::ExitRoomFields() :
FKEXITS(new KeyDef(TableImpls::Get()->EXITROOM, "fkExits")),
FKROOMS(new KeyDef(TableImpls::Get()->EXITROOM, "fkRooms"))
{
	TableImpls::Get()->EXITROOM->addKey(FKEXITS);
	TableImpls::Get()->EXITROOM->addKey(FKROOMS);
}

ExitsFields::ExitsFields() :
EXITID(new KeyDef(TableImpls::Get()->EXITS, "exitid")),
FKROOMS(new FieldImpl(TableImpls::Get()->EXITS, "fkRooms")),
DIR(new FieldImpl(TableImpls::Get()->EXITS, "dir"))
{
	TableImpls::Get()->EXITS->addKey(EXITID);
	TableImpls::Get()->EXITS->addField(FKROOMS);
	TableImpls::Get()->EXITS->addField(DIR);
}

GrantGroupsFields::GrantGroupsFields() :
GRANTGROUPID(new KeyDef(TableImpls::Get()->GRANTGROUPS, "grantgroupid")),
NAME(new FieldImpl(TableImpls::Get()->GRANTGROUPS, "name", true)),
DEFAULTGRANT(new FieldImpl(TableImpls::Get()->GRANTGROUPS, "defaultgrant")),
DEFAULTLOG(new FieldImpl(TableImpls::Get()->GRANTGROUPS, "defaultlog")),
IMPLIES(new FieldImpl(TableImpls::Get()->GRANTGROUPS, "implies"))
{
	TableImpls::Get()->GRANTGROUPS->addKey(GRANTGROUPID);
	TableImpls::Get()->GRANTGROUPS->addField(NAME);
	TableImpls::Get()->GRANTGROUPS->addField(DEFAULTGRANT);
	TableImpls::Get()->GRANTGROUPS->addField(DEFAULTLOG);
	TableImpls::Get()->GRANTGROUPS->addField(IMPLIES);
}

PermissionsFields::PermissionsFields() :
FKACCOUNTS(new KeyDef(TableImpls::Get()->PERMISSIONS, "fkAccounts")),
FKGRANTGROUPS(new KeyDef(TableImpls::Get()->PERMISSIONS, "fkGrantGroups")),
GRANT(new FieldImpl(TableImpls::Get()->PERMISSIONS, "grant")),
LOG(new FieldImpl(TableImpls::Get()->PERMISSIONS, "log"))
{
	TableImpls::Get()->PERMISSIONS->addKey(FKACCOUNTS);
	TableImpls::Get()->PERMISSIONS->addKey(FKGRANTGROUPS);
	TableImpls::Get()->PERMISSIONS->addField(GRANT);
	TableImpls::Get()->PERMISSIONS->addField(LOG);
}

RacesFields::RacesFields() :
RACEID(new KeyDef(TableImpls::Get()->RACES, "raceid")),
NAME(new FieldImpl(TableImpls::Get()->RACES, "name", true))
{
	TableImpls::Get()->RACES->addKey(RACEID);
	TableImpls::Get()->RACES->addField(NAME);
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
	TableImpls::Get()->ROOMS->addKey(ROOMID);
	TableImpls::Get()->ROOMS->addField(NAME);
	TableImpls::Get()->ROOMS->addField(DESCRIPTION);
	TableImpls::Get()->ROOMS->addField(FKAREAS);
	TableImpls::Get()->ROOMS->addField(FKSECTORS);
	TableImpls::Get()->ROOMS->addField(WIDTH);
	TableImpls::Get()->ROOMS->addField(LENGTH);
	TableImpls::Get()->ROOMS->addField(HEIGHT);
}

SectorsFields::SectorsFields() :
SECTORID(new KeyDef(TableImpls::Get()->SECTORS, "sectorid")),
NAME(new FieldImpl(TableImpls::Get()->SECTORS, "name", true)),
SYMBOL(new FieldImpl(TableImpls::Get()->SECTORS, "symbol", true)),
MOVECOST(new FieldImpl(TableImpls::Get()->SECTORS, "movecost")),
WATER(new FieldImpl(TableImpls::Get()->SECTORS, "water"))
{
	TableImpls::Get()->SECTORS->addKey(SECTORID);
	TableImpls::Get()->SECTORS->addField(NAME);
	TableImpls::Get()->SECTORS->addField(SYMBOL);
	TableImpls::Get()->SECTORS->addField(MOVECOST);
	TableImpls::Get()->SECTORS->addField(WATER);
}

SkillsFields::SkillsFields() :
SKILLID(new KeyDef(TableImpls::Get()->SKILLS, "skillid")),
NAME(new FieldImpl(TableImpls::Get()->SKILLS, "name", true)),
FKBRANCHES(new FieldImpl(TableImpls::Get()->SKILLS, "fkBranches"))
{
	TableImpls::Get()->SKILLS->addKey(SKILLID);
	TableImpls::Get()->SKILLS->addField(NAME);
	TableImpls::Get()->SKILLS->addField(FKBRANCHES);
}

StatsFields::StatsFields() :
STATID(new KeyDef(TableImpls::Get()->STATS, "statid")),
NAME(new FieldImpl(TableImpls::Get()->STATS, "name", true)),
SHORTNAME(new FieldImpl(TableImpls::Get()->STATS, "shortname", true))
{
	TableImpls::Get()->STATS->addKey(STATID);
	TableImpls::Get()->STATS->addField(NAME);
	TableImpls::Get()->STATS->addField(SHORTNAME);
}

TracesFields::TracesFields() :
TRACEID(new KeyDef(TableImpls::Get()->TRACES, "traceid")),
FKACCOUNTS(new FieldImpl(TableImpls::Get()->TRACES, "fkAccounts")),
TIME(new FieldImpl(TableImpls::Get()->TRACES, "time")),
DESCRIPTION(new FieldImpl(TableImpls::Get()->TRACES, "description", true)),
DIFF(new FieldImpl(TableImpls::Get()->TRACES, "diff", true))
{
	TableImpls::Get()->TRACES->addKey(TRACEID);
	TableImpls::Get()->TRACES->addField(FKACCOUNTS);
	TableImpls::Get()->TRACES->addField(TIME);
	TableImpls::Get()->TRACES->addField(DESCRIPTION);
	TableImpls::Get()->TRACES->addField(DIFF);
}

TraceChunkFields::TraceChunkFields() :
FKCHUNKS(new KeyDef(TableImpls::Get()->TRACECHUNK, "fkChunks")),
FKTRACES(new KeyDef(TableImpls::Get()->TRACECHUNK, "fkTraces"))
{
	TableImpls::Get()->TRACECHUNK->addKey(FKCHUNKS);
	TableImpls::Get()->TRACECHUNK->addKey(FKTRACES);
}

TraceDetailFields::TraceDetailFields() :
FKDETAILS(new KeyDef(TableImpls::Get()->TRACEDETAIL, "fkDetails")),
FKTRACES(new KeyDef(TableImpls::Get()->TRACEDETAIL, "fkTraces"))
{
	TableImpls::Get()->TRACEDETAIL->addKey(FKDETAILS);
	TableImpls::Get()->TRACEDETAIL->addKey(FKTRACES);
}

TraceEntityFields::TraceEntityFields() :
FKENTITIES(new KeyDef(TableImpls::Get()->TRACEENTITY, "fkEntities")),
FKTRACES(new KeyDef(TableImpls::Get()->TRACEENTITY, "fkTraces"))
{
	TableImpls::Get()->TRACEENTITY->addKey(FKENTITIES);
	TableImpls::Get()->TRACEENTITY->addKey(FKTRACES);
}

TraceRoomFields::TraceRoomFields() :
FKROOMS(new KeyDef(TableImpls::Get()->TRACEROOM, "fkRooms")),
FKTRACES(new KeyDef(TableImpls::Get()->TRACEROOM, "fkTraces"))
{
	TableImpls::Get()->TRACEROOM->addKey(FKROOMS);
	TableImpls::Get()->TRACEROOM->addKey(FKTRACES);
}

TreesFields::TreesFields() :
TREEID(new KeyDef(TableImpls::Get()->TREES, "treeid")),
NAME(new FieldImpl(TableImpls::Get()->TREES, "name", true)),
FKCLUSTERS(new FieldImpl(TableImpls::Get()->TREES, "fkClusters")),
FKSTATSPRIMARY(new FieldImpl(TableImpls::Get()->TREES, "fkStatsPrimary")),
FKSTATSSECONDARY(new FieldImpl(TableImpls::Get()->TREES, "fkStatsSecondary"))
{
	TableImpls::Get()->TREES->addKey(TREEID);
	TableImpls::Get()->TREES->addField(NAME);
	TableImpls::Get()->TREES->addField(FKCLUSTERS);
	TableImpls::Get()->TREES->addField(FKSTATSPRIMARY);
	TableImpls::Get()->TREES->addField(FKSTATSSECONDARY);
}

VersionFields::VersionFields() :
VERSIONID(new KeyDef(TableImpls::Get()->VERSION, "versionid")),
VERSIONTEXT(new FieldImpl(TableImpls::Get()->VERSION, "versiontext", true)),
MAJOR(new FieldImpl(TableImpls::Get()->VERSION, "major")),
MINOR(new FieldImpl(TableImpls::Get()->VERSION, "minor")),
MICRO(new FieldImpl(TableImpls::Get()->VERSION, "micro"))
{
	TableImpls::Get()->VERSION->addKey(VERSIONID);
	TableImpls::Get()->VERSION->addField(VERSIONTEXT);
	TableImpls::Get()->VERSION->addField(MAJOR);
	TableImpls::Get()->VERSION->addField(MINOR);
	TableImpls::Get()->VERSION->addField(MICRO);
}

