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
#include <sqlite3.h>
#include <Database.h>
#include <Tables.h>
#include <SqliteMgr.h>
#include <Bindable.h>

namespace hp
{
	class Accounts : public Bindable
	{
	public:
		// Ctors
		Accounts(Database* db);
		Accounts(Database* db, value_type accountid);
		~Accounts();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		const std::string& getpassword() const;

		// Setters
		void setname(const std::string& value);
		void setpassword(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_accountid;
		std::string m_name;
		std::string m_password;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Accounts(const Accounts& rhs);
		Accounts operator=(const Accounts& rhs);
	};

	class Areas : public Bindable
	{
	public:
		// Ctors
		Areas(Database* db);
		Areas(Database* db, value_type areaid);
		~Areas();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		const std::string& getdescription() const;
		value_type getheight() const;
		value_type getwidth() const;

		// Setters
		void setname(const std::string& value);
		void setdescription(const std::string& value);
		void setheight(value_type value);
		void setwidth(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_areaid;
		std::string m_name;
		std::string m_description;
		value_type m_height;
		value_type m_width;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Areas(const Areas& rhs);
		Areas operator=(const Areas& rhs);
	};

	class Branches : public Bindable
	{
	public:
		// Ctors
		Branches(Database* db);
		Branches(Database* db, value_type branchid);
		~Branches();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		value_type getfkTrees() const;
		value_type getfkStatsPrimary() const;
		value_type getfkStatsSecondary() const;

		// Setters
		void setname(const std::string& value);
		void setfkTrees(value_type value);
		void setfkStatsPrimary(value_type value);
		void setfkStatsSecondary(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_branchid;
		std::string m_name;
		value_type m_fkTrees;
		value_type m_fkStatsPrimary;
		value_type m_fkStatsSecondary;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Branches(const Branches& rhs);
		Branches operator=(const Branches& rhs);
	};

	// Lookup table
	class CharacterAccount : public Bindable
	{
	public:
		// Ctors
		CharacterAccount(Database* db);
		CharacterAccount(Database* db, value_type fkCharacters, value_type fkAccounts);
		~CharacterAccount();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkAccounts() const;

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_fkCharacters;
		value_type m_fkAccounts;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterAccount(const CharacterAccount& rhs);
		CharacterAccount operator=(const CharacterAccount& rhs);
	};

	class CharacterBranch : public Bindable
	{
	public:
		// Ctors
		CharacterBranch(Database* db);
		CharacterBranch(Database* db, value_type characterbranchid);
		~CharacterBranch();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkBranches() const;
		value_type getxp() const;

		// Setters
		void setfkCharacters(value_type value);
		void setfkBranches(value_type value);
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_characterbranchid;
		value_type m_fkCharacters;
		value_type m_fkBranches;
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterBranch(const CharacterBranch& rhs);
		CharacterBranch operator=(const CharacterBranch& rhs);
	};

	class CharacterCluster : public Bindable
	{
	public:
		// Ctors
		CharacterCluster(Database* db);
		CharacterCluster(Database* db, value_type characterclusterid);
		~CharacterCluster();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkClusters() const;
		value_type getxp() const;

		// Setters
		void setfkCharacters(value_type value);
		void setfkClusters(value_type value);
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_characterclusterid;
		value_type m_fkCharacters;
		value_type m_fkClusters;
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterCluster(const CharacterCluster& rhs);
		CharacterCluster operator=(const CharacterCluster& rhs);
	};

	class Characters : public Bindable
	{
	public:
		// Ctors
		Characters(Database* db);
		Characters(Database* db, value_type characterid);
		~Characters();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkRaces() const;
		value_type getfkRooms() const;
		const std::string& getname() const;
		const std::string& getdescription() const;

		// Setters
		void setfkRaces(value_type value);
		void setfkRooms(value_type value);
		void setname(const std::string& value);
		void setdescription(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_characterid;
		value_type m_fkRaces;
		value_type m_fkRooms;
		std::string m_name;
		std::string m_description;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Characters(const Characters& rhs);
		Characters operator=(const Characters& rhs);
	};

	class CharacterSkill : public Bindable
	{
	public:
		// Ctors
		CharacterSkill(Database* db);
		CharacterSkill(Database* db, value_type characterskillid);
		~CharacterSkill();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkBranches() const;
		value_type getxp() const;

		// Setters
		void setfkCharacters(value_type value);
		void setfkBranches(value_type value);
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_characterskillid;
		value_type m_fkCharacters;
		value_type m_fkBranches;
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterSkill(const CharacterSkill& rhs);
		CharacterSkill operator=(const CharacterSkill& rhs);
	};

	class CharacterStat : public Bindable
	{
	public:
		// Ctors
		CharacterStat(Database* db);
		CharacterStat(Database* db, value_type characterstatid);
		~CharacterStat();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkStats() const;
		value_type getcurrent() const;
		value_type getpotential() const;

		// Setters
		void setfkCharacters(value_type value);
		void setfkStats(value_type value);
		void setcurrent(value_type value);
		void setpotential(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_characterstatid;
		value_type m_fkCharacters;
		value_type m_fkStats;
		value_type m_current;
		value_type m_potential;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterStat(const CharacterStat& rhs);
		CharacterStat operator=(const CharacterStat& rhs);
	};

	class CharacterTree : public Bindable
	{
	public:
		// Ctors
		CharacterTree(Database* db);
		CharacterTree(Database* db, value_type charactertreeid);
		~CharacterTree();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkTrees() const;
		value_type getxp() const;

		// Setters
		void setfkCharacters(value_type value);
		void setfkTrees(value_type value);
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_charactertreeid;
		value_type m_fkCharacters;
		value_type m_fkTrees;
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterTree(const CharacterTree& rhs);
		CharacterTree operator=(const CharacterTree& rhs);
	};

	class Clusters : public Bindable
	{
	public:
		// Ctors
		Clusters(Database* db);
		Clusters(Database* db, value_type clusterid);
		~Clusters();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;

		// Setters
		void setname(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_clusterid;
		std::string m_name;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Clusters(const Clusters& rhs);
		Clusters operator=(const Clusters& rhs);
	};

	class Colours : public Bindable
	{
	public:
		// Ctors
		Colours(Database* db);
		Colours(Database* db, value_type colourid);
		~Colours();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		const std::string& getcode() const;
		const std::string& getcolourstring() const;
		value_type getansi() const;

		// Setters
		void setname(const std::string& value);
		void setcode(const std::string& value);
		void setcolourstring(const std::string& value);
		void setansi(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_colourid;
		std::string m_name;
		std::string m_code;
		std::string m_colourstring;
		value_type m_ansi;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Colours(const Colours& rhs);
		Colours operator=(const Colours& rhs);
	};

	class Commands : public Bindable
	{
	public:
		// Ctors
		Commands(Database* db);
		Commands(Database* db, value_type commandid);
		~Commands();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		const std::string& getgrantgroup() const;
		const std::string& gethighforce() const;
		const std::string& getforce() const;
		value_type getlowforce() const;

		// Setters
		void setname(const std::string& value);
		void setgrantgroup(const std::string& value);
		void sethighforce(const std::string& value);
		void setforce(const std::string& value);
		void setlowforce(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_commandid;
		std::string m_name;
		std::string m_grantgroup;
		std::string m_highforce;
		std::string m_force;
		value_type m_lowforce;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Commands(const Commands& rhs);
		Commands operator=(const Commands& rhs);
	};

	class Exits : public Bindable
	{
	public:
		// Ctors
		Exits(Database* db);
		Exits(Database* db, value_type exitid);
		~Exits();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getdir() const;

		// Setters
		void setdir(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_exitid;
		value_type m_dir;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Exits(const Exits& rhs);
		Exits operator=(const Exits& rhs);
	};

	class GrantGroups : public Bindable
	{
	public:
		// Ctors
		GrantGroups(Database* db);
		GrantGroups(Database* db, value_type grantgroupid);
		~GrantGroups();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		value_type getdefaultgrant() const;
		value_type getimplies() const;

		// Setters
		void setname(const std::string& value);
		void setdefaultgrant(value_type value);
		void setimplies(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_grantgroupid;
		std::string m_name;
		value_type m_defaultgrant;
		value_type m_implies;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		GrantGroups(const GrantGroups& rhs);
		GrantGroups operator=(const GrantGroups& rhs);
	};

	class Permissions : public Bindable
	{
	public:
		// Ctors
		Permissions(Database* db);
		Permissions(Database* db, value_type permissionid);
		~Permissions();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		value_type getfkAccounts() const;
		value_type getfkCommands() const;
		value_type getfkGrantGroups() const;
		value_type getgrant() const;

		// Setters
		void setfkAccounts(value_type value);
		void setfkCommands(value_type value);
		void setfkGrantGroups(value_type value);
		void setgrant(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_permissionid;
		value_type m_fkAccounts;
		value_type m_fkCommands;
		value_type m_fkGrantGroups;
		value_type m_grant;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Permissions(const Permissions& rhs);
		Permissions operator=(const Permissions& rhs);
	};

	class Races : public Bindable
	{
	public:
		// Ctors
		Races(Database* db);
		Races(Database* db, value_type raceid);
		~Races();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;

		// Setters
		void setname(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_raceid;
		std::string m_name;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Races(const Races& rhs);
		Races operator=(const Races& rhs);
	};

	class Rooms : public Bindable
	{
	public:
		// Ctors
		Rooms(Database* db);
		Rooms(Database* db, value_type roomid);
		~Rooms();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		const std::string& getdescription() const;
		value_type getfkAreas() const;
		value_type getfkSectors() const;
		value_type getwidth() const;
		value_type getlength() const;
		value_type getheight() const;

		// Setters
		void setname(const std::string& value);
		void setdescription(const std::string& value);
		void setfkAreas(value_type value);
		void setfkSectors(value_type value);
		void setwidth(value_type value);
		void setlength(value_type value);
		void setheight(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_roomid;
		std::string m_name;
		std::string m_description;
		value_type m_fkAreas;
		value_type m_fkSectors;
		value_type m_width;
		value_type m_length;
		value_type m_height;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Rooms(const Rooms& rhs);
		Rooms operator=(const Rooms& rhs);
	};

	class Sectors : public Bindable
	{
	public:
		// Ctors
		Sectors(Database* db);
		Sectors(Database* db, value_type sectorid);
		~Sectors();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		const std::string& getsymbol() const;
		value_type getmovecost() const;
		value_type getwater() const;

		// Setters
		void setname(const std::string& value);
		void setsymbol(const std::string& value);
		void setmovecost(value_type value);
		void setwater(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_sectorid;
		std::string m_name;
		std::string m_symbol;
		value_type m_movecost;
		value_type m_water;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Sectors(const Sectors& rhs);
		Sectors operator=(const Sectors& rhs);
	};

	class Skills : public Bindable
	{
	public:
		// Ctors
		Skills(Database* db);
		Skills(Database* db, value_type skillid);
		~Skills();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		value_type getfkBranches() const;

		// Setters
		void setname(const std::string& value);
		void setfkBranches(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_skillid;
		std::string m_name;
		value_type m_fkBranches;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Skills(const Skills& rhs);
		Skills operator=(const Skills& rhs);
	};

	class Stats : public Bindable
	{
	public:
		// Ctors
		Stats(Database* db);
		Stats(Database* db, value_type statid);
		~Stats();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		const std::string& getshortname() const;

		// Setters
		void setname(const std::string& value);
		void setshortname(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_statid;
		std::string m_name;
		std::string m_shortname;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Stats(const Stats& rhs);
		Stats operator=(const Stats& rhs);
	};

	class Trees : public Bindable
	{
	public:
		// Ctors
		Trees(Database* db);
		Trees(Database* db, value_type treeid);
		~Trees();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getname() const;
		value_type getfkClusters() const;
		value_type getfkStatsPrimary() const;
		value_type getfkStatsSecondary() const;

		// Setters
		void setname(const std::string& value);
		void setfkClusters(value_type value);
		void setfkStatsPrimary(value_type value);
		void setfkStatsSecondary(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_treeid;
		std::string m_name;
		value_type m_fkClusters;
		value_type m_fkStatsPrimary;
		value_type m_fkStatsSecondary;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Trees(const Trees& rhs);
		Trees operator=(const Trees& rhs);
	};

	class Version : public Bindable
	{
	public:
		// Ctors
		Version(Database* db);
		Version(Database* db, value_type versionid);
		~Version();

		// Database interaction
		void save();
		void erase();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3_stmt* stmt);
		void parseSelect(sqlite3_stmt* stmt);
		Table* getTable() const;

		// Getters
		const std::string& getversiontext() const;
		value_type getmajor() const;
		value_type getminor() const;
		value_type getmicro() const;

		// Setters
		void setversiontext(const std::string& value);
		void setmajor(value_type value);
		void setminor(value_type value);
		void setmicro(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_versionid;
		std::string m_versiontext;
		value_type m_major;
		value_type m_minor;
		value_type m_micro;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		Version(const Version& rhs);
		Version operator=(const Version& rhs);
	};

} // end of namespace


