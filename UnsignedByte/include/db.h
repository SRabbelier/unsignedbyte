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

#pragma once
#ifdef _WIN32
	#pragma warning (disable:4800)
#endif

#include "Types.h"

#include <Database.h>
#include <SqliteMgr.h>

namespace db
{
	class AccountsFields : public Singleton<AccountsFields>
	{
	public:
		KeyDefPtr ACCOUNTID;
		FieldImplPtr NAME;
		FieldImplPtr PASSWORD;

	private:
		// Hide constructor and assignment operator
		AccountsFields();
		~AccountsFields() { }
		AccountsFields(const AccountsFields& rhs);
		AccountsFields operator=(const AccountsFields& rhs);
		friend class Singleton<AccountsFields>;
	};

	class AreasFields : public Singleton<AreasFields>
	{
	public:
		KeyDefPtr AREAID;
		FieldImplPtr NAME;
		FieldImplPtr DESCRIPTION;
		FieldImplPtr HEIGHT;
		FieldImplPtr WIDTH;

	private:
		// Hide constructor and assignment operator
		AreasFields();
		~AreasFields() { }
		AreasFields(const AreasFields& rhs);
		AreasFields operator=(const AreasFields& rhs);
		friend class Singleton<AreasFields>;
	};

	class BranchesFields : public Singleton<BranchesFields>
	{
	public:
		KeyDefPtr BRANCHID;
		FieldImplPtr NAME;
		FieldImplPtr FKTREES;
		FieldImplPtr FKSTATSPRIMARY;
		FieldImplPtr FKSTATSSECONDARY;

	private:
		// Hide constructor and assignment operator
		BranchesFields();
		~BranchesFields() { }
		BranchesFields(const BranchesFields& rhs);
		BranchesFields operator=(const BranchesFields& rhs);
		friend class Singleton<BranchesFields>;
	};

	class ChannelsFields : public Singleton<ChannelsFields>
	{
	public:
		KeyDefPtr CHANNELID;
		FieldImplPtr NAME;
		FieldImplPtr DESCRIPTION;

	private:
		// Hide constructor and assignment operator
		ChannelsFields();
		~ChannelsFields() { }
		ChannelsFields(const ChannelsFields& rhs);
		ChannelsFields operator=(const ChannelsFields& rhs);
		friend class Singleton<ChannelsFields>;
	};

	class CharacterAccountFields : public Singleton<CharacterAccountFields>
	{
	public:
		KeyDefPtr FKACCOUNTS;
		KeyDefPtr FKENTITIES;

	private:
		// Hide constructor and assignment operator
		CharacterAccountFields();
		~CharacterAccountFields() { }
		CharacterAccountFields(const CharacterAccountFields& rhs);
		CharacterAccountFields operator=(const CharacterAccountFields& rhs);
		friend class Singleton<CharacterAccountFields>;
	};

	class CharacterBranchFields : public Singleton<CharacterBranchFields>
	{
	public:
		KeyDefPtr FKBRANCHES;
		KeyDefPtr FKENTITIES;
		FieldImplPtr XP;

	private:
		// Hide constructor and assignment operator
		CharacterBranchFields();
		~CharacterBranchFields() { }
		CharacterBranchFields(const CharacterBranchFields& rhs);
		CharacterBranchFields operator=(const CharacterBranchFields& rhs);
		friend class Singleton<CharacterBranchFields>;
	};

	class CharacterClusterFields : public Singleton<CharacterClusterFields>
	{
	public:
		KeyDefPtr FKCLUSTERS;
		KeyDefPtr FKENTITIES;
		FieldImplPtr XP;

	private:
		// Hide constructor and assignment operator
		CharacterClusterFields();
		~CharacterClusterFields() { }
		CharacterClusterFields(const CharacterClusterFields& rhs);
		CharacterClusterFields operator=(const CharacterClusterFields& rhs);
		friend class Singleton<CharacterClusterFields>;
	};

	class CharacterSkillFields : public Singleton<CharacterSkillFields>
	{
	public:
		KeyDefPtr FKBRANCHES;
		KeyDefPtr FKENTITIES;
		FieldImplPtr XP;

	private:
		// Hide constructor and assignment operator
		CharacterSkillFields();
		~CharacterSkillFields() { }
		CharacterSkillFields(const CharacterSkillFields& rhs);
		CharacterSkillFields operator=(const CharacterSkillFields& rhs);
		friend class Singleton<CharacterSkillFields>;
	};

	class CharacterStatFields : public Singleton<CharacterStatFields>
	{
	public:
		KeyDefPtr FKENTITIES;
		KeyDefPtr FKSTATS;
		FieldImplPtr XP;

	private:
		// Hide constructor and assignment operator
		CharacterStatFields();
		~CharacterStatFields() { }
		CharacterStatFields(const CharacterStatFields& rhs);
		CharacterStatFields operator=(const CharacterStatFields& rhs);
		friend class Singleton<CharacterStatFields>;
	};

	class CharacterTreeFields : public Singleton<CharacterTreeFields>
	{
	public:
		KeyDefPtr FKENTITIES;
		KeyDefPtr FKTREES;
		FieldImplPtr XP;

	private:
		// Hide constructor and assignment operator
		CharacterTreeFields();
		~CharacterTreeFields() { }
		CharacterTreeFields(const CharacterTreeFields& rhs);
		CharacterTreeFields operator=(const CharacterTreeFields& rhs);
		friend class Singleton<CharacterTreeFields>;
	};

	class ClustersFields : public Singleton<ClustersFields>
	{
	public:
		KeyDefPtr CLUSTERID;
		FieldImplPtr NAME;

	private:
		// Hide constructor and assignment operator
		ClustersFields();
		~ClustersFields() { }
		ClustersFields(const ClustersFields& rhs);
		ClustersFields operator=(const ClustersFields& rhs);
		friend class Singleton<ClustersFields>;
	};

	class ChunksFields : public Singleton<ChunksFields>
	{
	public:
		KeyDefPtr CHUNKID;
		FieldImplPtr FKROOMS;
		FieldImplPtr NAME;
		FieldImplPtr DESCRIPTION;
		FieldImplPtr TAGS;

	private:
		// Hide constructor and assignment operator
		ChunksFields();
		~ChunksFields() { }
		ChunksFields(const ChunksFields& rhs);
		ChunksFields operator=(const ChunksFields& rhs);
		friend class Singleton<ChunksFields>;
	};

	class ColoursFields : public Singleton<ColoursFields>
	{
	public:
		KeyDefPtr COLOURID;
		FieldImplPtr NAME;
		FieldImplPtr CODE;
		FieldImplPtr COLOURSTRING;
		FieldImplPtr ANSI;

	private:
		// Hide constructor and assignment operator
		ColoursFields();
		~ColoursFields() { }
		ColoursFields(const ColoursFields& rhs);
		ColoursFields operator=(const ColoursFields& rhs);
		friend class Singleton<ColoursFields>;
	};

	class CommandsFields : public Singleton<CommandsFields>
	{
	public:
		KeyDefPtr COMMANDID;
		FieldImplPtr NAME;
		FieldImplPtr GRANTGROUP;
		FieldImplPtr HIGHFORCE;
		FieldImplPtr FORCE;
		FieldImplPtr LOWFORCE;

	private:
		// Hide constructor and assignment operator
		CommandsFields();
		~CommandsFields() { }
		CommandsFields(const CommandsFields& rhs);
		CommandsFields operator=(const CommandsFields& rhs);
		friend class Singleton<CommandsFields>;
	};

	class DetailsFields : public Singleton<DetailsFields>
	{
	public:
		KeyDefPtr DETAILID;
		FieldImplPtr KEY;
		FieldImplPtr DESCRIPTION;

	private:
		// Hide constructor and assignment operator
		DetailsFields();
		~DetailsFields() { }
		DetailsFields(const DetailsFields& rhs);
		DetailsFields operator=(const DetailsFields& rhs);
		friend class Singleton<DetailsFields>;
	};

	class DetailRoomFields : public Singleton<DetailRoomFields>
	{
	public:
		KeyDefPtr FKDETAILS;
		KeyDefPtr FKROOMS;

	private:
		// Hide constructor and assignment operator
		DetailRoomFields();
		~DetailRoomFields() { }
		DetailRoomFields(const DetailRoomFields& rhs);
		DetailRoomFields operator=(const DetailRoomFields& rhs);
		friend class Singleton<DetailRoomFields>;
	};

	class DetailChunkFields : public Singleton<DetailChunkFields>
	{
	public:
		KeyDefPtr FKCHUNKS;
		KeyDefPtr FKDETAILS;

	private:
		// Hide constructor and assignment operator
		DetailChunkFields();
		~DetailChunkFields() { }
		DetailChunkFields(const DetailChunkFields& rhs);
		DetailChunkFields operator=(const DetailChunkFields& rhs);
		friend class Singleton<DetailChunkFields>;
	};

	class DetailCharacterFields : public Singleton<DetailCharacterFields>
	{
	public:
		KeyDefPtr FKDETAILS;
		KeyDefPtr FKENTITIES;

	private:
		// Hide constructor and assignment operator
		DetailCharacterFields();
		~DetailCharacterFields() { }
		DetailCharacterFields(const DetailCharacterFields& rhs);
		DetailCharacterFields operator=(const DetailCharacterFields& rhs);
		friend class Singleton<DetailCharacterFields>;
	};

	class DetailDetailFields : public Singleton<DetailDetailFields>
	{
	public:
		KeyDefPtr FKDETAILSPRIMARY;
		KeyDefPtr FKDETAILSSECONDARY;

	private:
		// Hide constructor and assignment operator
		DetailDetailFields();
		~DetailDetailFields() { }
		DetailDetailFields(const DetailDetailFields& rhs);
		DetailDetailFields operator=(const DetailDetailFields& rhs);
		friend class Singleton<DetailDetailFields>;
	};

	class EchosFields : public Singleton<EchosFields>
	{
	public:
		KeyDefPtr ECHOID;
		FieldImplPtr MESSAGE;
		FieldImplPtr VISIBILITY;
		FieldImplPtr AUDIBILITY;

	private:
		// Hide constructor and assignment operator
		EchosFields();
		~EchosFields() { }
		EchosFields(const EchosFields& rhs);
		EchosFields operator=(const EchosFields& rhs);
		friend class Singleton<EchosFields>;
	};

	class EntitiesFields : public Singleton<EntitiesFields>
	{
	public:
		KeyDefPtr ENTITYID;
		FieldImplPtr FKRACES;
		FieldImplPtr FKROOMS;
		FieldImplPtr NAME;
		FieldImplPtr DESCRIPTION;

	private:
		// Hide constructor and assignment operator
		EntitiesFields();
		~EntitiesFields() { }
		EntitiesFields(const EntitiesFields& rhs);
		EntitiesFields operator=(const EntitiesFields& rhs);
		friend class Singleton<EntitiesFields>;
	};

	class ExitRoomFields : public Singleton<ExitRoomFields>
	{
	public:
		KeyDefPtr FKEXITS;
		KeyDefPtr FKROOMS;

	private:
		// Hide constructor and assignment operator
		ExitRoomFields();
		~ExitRoomFields() { }
		ExitRoomFields(const ExitRoomFields& rhs);
		ExitRoomFields operator=(const ExitRoomFields& rhs);
		friend class Singleton<ExitRoomFields>;
	};

	class ExitsFields : public Singleton<ExitsFields>
	{
	public:
		KeyDefPtr EXITID;
		FieldImplPtr FKROOMS;
		FieldImplPtr DIR;

	private:
		// Hide constructor and assignment operator
		ExitsFields();
		~ExitsFields() { }
		ExitsFields(const ExitsFields& rhs);
		ExitsFields operator=(const ExitsFields& rhs);
		friend class Singleton<ExitsFields>;
	};

	class GrantGroupsFields : public Singleton<GrantGroupsFields>
	{
	public:
		KeyDefPtr GRANTGROUPID;
		FieldImplPtr NAME;
		FieldImplPtr DEFAULTGRANT;
		FieldImplPtr DEFAULTLOG;
		FieldImplPtr IMPLIES;

	private:
		// Hide constructor and assignment operator
		GrantGroupsFields();
		~GrantGroupsFields() { }
		GrantGroupsFields(const GrantGroupsFields& rhs);
		GrantGroupsFields operator=(const GrantGroupsFields& rhs);
		friend class Singleton<GrantGroupsFields>;
	};

	class PermissionsFields : public Singleton<PermissionsFields>
	{
	public:
		KeyDefPtr FKACCOUNTS;
		KeyDefPtr FKGRANTGROUPS;
		FieldImplPtr GRANT;
		FieldImplPtr LOG;

	private:
		// Hide constructor and assignment operator
		PermissionsFields();
		~PermissionsFields() { }
		PermissionsFields(const PermissionsFields& rhs);
		PermissionsFields operator=(const PermissionsFields& rhs);
		friend class Singleton<PermissionsFields>;
	};

	class RacesFields : public Singleton<RacesFields>
	{
	public:
		KeyDefPtr RACEID;
		FieldImplPtr NAME;

	private:
		// Hide constructor and assignment operator
		RacesFields();
		~RacesFields() { }
		RacesFields(const RacesFields& rhs);
		RacesFields operator=(const RacesFields& rhs);
		friend class Singleton<RacesFields>;
	};

	class RoomsFields : public Singleton<RoomsFields>
	{
	public:
		KeyDefPtr ROOMID;
		FieldImplPtr NAME;
		FieldImplPtr DESCRIPTION;
		FieldImplPtr FKAREAS;
		FieldImplPtr FKSECTORS;
		FieldImplPtr WIDTH;
		FieldImplPtr LENGTH;
		FieldImplPtr HEIGHT;

	private:
		// Hide constructor and assignment operator
		RoomsFields();
		~RoomsFields() { }
		RoomsFields(const RoomsFields& rhs);
		RoomsFields operator=(const RoomsFields& rhs);
		friend class Singleton<RoomsFields>;
	};

	class SectorsFields : public Singleton<SectorsFields>
	{
	public:
		KeyDefPtr SECTORID;
		FieldImplPtr NAME;
		FieldImplPtr SYMBOL;
		FieldImplPtr MOVECOST;
		FieldImplPtr WATER;

	private:
		// Hide constructor and assignment operator
		SectorsFields();
		~SectorsFields() { }
		SectorsFields(const SectorsFields& rhs);
		SectorsFields operator=(const SectorsFields& rhs);
		friend class Singleton<SectorsFields>;
	};

	class SkillsFields : public Singleton<SkillsFields>
	{
	public:
		KeyDefPtr SKILLID;
		FieldImplPtr NAME;
		FieldImplPtr FKBRANCHES;

	private:
		// Hide constructor and assignment operator
		SkillsFields();
		~SkillsFields() { }
		SkillsFields(const SkillsFields& rhs);
		SkillsFields operator=(const SkillsFields& rhs);
		friend class Singleton<SkillsFields>;
	};

	class StatsFields : public Singleton<StatsFields>
	{
	public:
		KeyDefPtr STATID;
		FieldImplPtr NAME;
		FieldImplPtr SHORTNAME;

	private:
		// Hide constructor and assignment operator
		StatsFields();
		~StatsFields() { }
		StatsFields(const StatsFields& rhs);
		StatsFields operator=(const StatsFields& rhs);
		friend class Singleton<StatsFields>;
	};

	class TracesFields : public Singleton<TracesFields>
	{
	public:
		KeyDefPtr TRACEID;
		FieldImplPtr FKACCOUNTS;
		FieldImplPtr TIME;
		FieldImplPtr DESCRIPTION;
		FieldImplPtr DIFF;

	private:
		// Hide constructor and assignment operator
		TracesFields();
		~TracesFields() { }
		TracesFields(const TracesFields& rhs);
		TracesFields operator=(const TracesFields& rhs);
		friend class Singleton<TracesFields>;
	};

	class TraceChunkFields : public Singleton<TraceChunkFields>
	{
	public:
		KeyDefPtr FKCHUNKS;
		KeyDefPtr FKTRACES;

	private:
		// Hide constructor and assignment operator
		TraceChunkFields();
		~TraceChunkFields() { }
		TraceChunkFields(const TraceChunkFields& rhs);
		TraceChunkFields operator=(const TraceChunkFields& rhs);
		friend class Singleton<TraceChunkFields>;
	};

	class TraceDetailFields : public Singleton<TraceDetailFields>
	{
	public:
		KeyDefPtr FKDETAILS;
		KeyDefPtr FKTRACES;

	private:
		// Hide constructor and assignment operator
		TraceDetailFields();
		~TraceDetailFields() { }
		TraceDetailFields(const TraceDetailFields& rhs);
		TraceDetailFields operator=(const TraceDetailFields& rhs);
		friend class Singleton<TraceDetailFields>;
	};

	class TraceEntityFields : public Singleton<TraceEntityFields>
	{
	public:
		KeyDefPtr FKENTITIES;
		KeyDefPtr FKTRACES;

	private:
		// Hide constructor and assignment operator
		TraceEntityFields();
		~TraceEntityFields() { }
		TraceEntityFields(const TraceEntityFields& rhs);
		TraceEntityFields operator=(const TraceEntityFields& rhs);
		friend class Singleton<TraceEntityFields>;
	};

	class TraceRoomFields : public Singleton<TraceRoomFields>
	{
	public:
		KeyDefPtr FKROOMS;
		KeyDefPtr FKTRACES;

	private:
		// Hide constructor and assignment operator
		TraceRoomFields();
		~TraceRoomFields() { }
		TraceRoomFields(const TraceRoomFields& rhs);
		TraceRoomFields operator=(const TraceRoomFields& rhs);
		friend class Singleton<TraceRoomFields>;
	};

	class TreesFields : public Singleton<TreesFields>
	{
	public:
		KeyDefPtr TREEID;
		FieldImplPtr NAME;
		FieldImplPtr FKCLUSTERS;
		FieldImplPtr FKSTATSPRIMARY;
		FieldImplPtr FKSTATSSECONDARY;

	private:
		// Hide constructor and assignment operator
		TreesFields();
		~TreesFields() { }
		TreesFields(const TreesFields& rhs);
		TreesFields operator=(const TreesFields& rhs);
		friend class Singleton<TreesFields>;
	};

	class VersionFields : public Singleton<VersionFields>
	{
	public:
		KeyDefPtr VERSIONID;
		FieldImplPtr VERSIONTEXT;
		FieldImplPtr MAJOR;
		FieldImplPtr MINOR;
		FieldImplPtr MICRO;

	private:
		// Hide constructor and assignment operator
		VersionFields();
		~VersionFields() { }
		VersionFields(const VersionFields& rhs);
		VersionFields operator=(const VersionFields& rhs);
		friend class Singleton<VersionFields>;
	};

} // end of namespace


