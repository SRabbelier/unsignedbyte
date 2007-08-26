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
 ****************************** *********************************************/

#pragma once

#include <string>
#include <sqlite3.h>
#include <Database.h>

namespace hp
{
	typedef unsigned long value_type;

	class Accounts
	{
	public:
		// Ctors
		Accounts(Database* db);
		Accounts(Database* db, value_type accountid);
		~Accounts();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		const std::string& getpassword() const;

		// Setters
		void setname(const std::string& value) const;
		void setpassword(const std::string& value) const;

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
		
		class AccountsMgr
		{
			public:
				static AccountsMgr* Get(Database* db);
				static void Free();
			
				void setDatabase(Database* db) { m_db = db; };
			
				value_type doInsert();
				void doErase(value_type account);
				void doUpdate(const std::string& name, const std::string& password, value_type account);
			
			private:
				Database* m_db;
				Database::OPENDB* m_odb;
				const char* m_leftover;
				
				sqlite3_stmt* m_insert;
				sqlite3_stmt* m_erase;
				sqlite3_stmt* m_update;
			
				AccountsMgr(Database* db);
				~AccountsMgr();
				static AccountsMgr* m_instance;
		};
	};

	class Areas
	{
	public:
		// Ctors
		Areas(Database* db);
		Areas(Database* db, value_type areaid);
		~Areas();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		const std::string& getdescription() const;
		value_type getheight() const;
		value_type getwidth() const;

		// Setters
		void setname(const std::string& value) const;
		void setdescription(const std::string& value) const;
		void setheight(value_type value) const;
		void setwidth(value_type value) const;

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

	class Branches
	{
	public:
		// Ctors
		Branches(Database* db);
		Branches(Database* db, value_type branchid);
		~Branches();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		value_type getfkTrees() const;
		value_type getfkStatsPrimary() const;
		value_type getfkStatsSecondary() const;

		// Setters
		void setname(const std::string& value) const;
		void setfkTrees(value_type value) const;
		void setfkStatsPrimary(value_type value) const;
		void setfkStatsSecondary(value_type value) const;

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
	class AccountCharacter
	{
	public:
		// Ctors
		AccountCharacter(Database* db);
		AccountCharacter(Database* db, value_type fkCharacters, value_type fkAccounts);
		~AccountCharacter();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

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
		AccountCharacter(const AccountCharacter& rhs);
		AccountCharacter operator=(const AccountCharacter& rhs);
	};

	// Lookup table
	class CharacterBranch
	{
	public:
		// Ctors
		CharacterBranch(Database* db);
		CharacterBranch(Database* db, value_type fkCharacters, value_type fkBranches);
		~CharacterBranch();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getfkCharacters() const;
		value_type getfkBranches() const;

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_fkCharacters;
		value_type m_fkBranches;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterBranch(const CharacterBranch& rhs);
		CharacterBranch operator=(const CharacterBranch& rhs);
	};

	// Lookup table
	class CharacterCluster
	{
	public:
		// Ctors
		CharacterCluster(Database* db);
		CharacterCluster(Database* db, value_type fkCharacters, value_type fkClusters);
		~CharacterCluster();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getfkCharacters() const;
		value_type getfkClusters() const;

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_fkCharacters;
		value_type m_fkClusters;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterCluster(const CharacterCluster& rhs);
		CharacterCluster operator=(const CharacterCluster& rhs);
	};

	class Characters
	{
	public:
		// Ctors
		Characters(Database* db);
		Characters(Database* db, value_type characterid);
		~Characters();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getfkRaces() const;
		value_type getfkRooms() const;
		const std::string& getname() const;
		const std::string& getdescription() const;

		// Setters
		void setfkRaces(value_type value) const;
		void setfkRooms(value_type value) const;
		void setname(const std::string& value) const;
		void setdescription(const std::string& value) const;

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

	// Lookup table
	class CharacterSkill
	{
	public:
		// Ctors
		CharacterSkill(Database* db);
		CharacterSkill(Database* db, value_type fkCharacters, value_type fkBranches);
		~CharacterSkill();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getfkCharacters() const;
		value_type getfkBranches() const;

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_fkCharacters;
		value_type m_fkBranches;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterSkill(const CharacterSkill& rhs);
		CharacterSkill operator=(const CharacterSkill& rhs);
	};

	// Lookup table
	class CharacterStat
	{
	public:
		// Ctors
		CharacterStat(Database* db);
		CharacterStat(Database* db, value_type fkCharacters, value_type fkStats);
		~CharacterStat();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getfkCharacters() const;
		value_type getfkStats() const;

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_fkCharacters;
		value_type m_fkStats;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterStat(const CharacterStat& rhs);
		CharacterStat operator=(const CharacterStat& rhs);
	};

	// Lookup table
	class CharacterTree
	{
	public:
		// Ctors
		CharacterTree(Database* db);
		CharacterTree(Database* db, value_type fkCharacters, value_type fkTrees);
		~CharacterTree();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getfkCharacters() const;
		value_type getfkTrees() const;

	private:
		// Database pointer
		Database* m_db;

		// Fields
		value_type m_fkCharacters;
		value_type m_fkTrees;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide copy constructor and assignment operator
		CharacterTree(const CharacterTree& rhs);
		CharacterTree operator=(const CharacterTree& rhs);
	};

	class Clusters
	{
	public:
		// Ctors
		Clusters(Database* db);
		Clusters(Database* db, value_type clusterid);
		~Clusters();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;

		// Setters
		void setname(const std::string& value) const;

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

	class Colours
	{
	public:
		// Ctors
		Colours(Database* db);
		Colours(Database* db, value_type colourid);
		~Colours();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		const std::string& getcode() const;
		const std::string& getcolourstring() const;
		value_type getansi() const;

		// Setters
		void setname(const std::string& value) const;
		void setcode(const std::string& value) const;
		void setcolourstring(const std::string& value) const;
		void setansi(value_type value) const;

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

	class Commands
	{
	public:
		// Ctors
		Commands(Database* db);
		Commands(Database* db, value_type commandid);
		~Commands();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		const std::string& getgrantgroup() const;
		const std::string& gethighforce() const;
		const std::string& getforce() const;
		value_type getlowforce() const;

		// Setters
		void setname(const std::string& value) const;
		void setgrantgroup(const std::string& value) const;
		void sethighforce(const std::string& value) const;
		void setforce(const std::string& value) const;
		void setlowforce(value_type value) const;

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

	class Exits
	{
	public:
		// Ctors
		Exits(Database* db);
		Exits(Database* db, value_type exitid);
		~Exits();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getdir() const;

		// Setters
		void setdir(value_type value) const;

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

	class GrantGroups
	{
	public:
		// Ctors
		GrantGroups(Database* db);
		GrantGroups(Database* db, value_type grantgroupid);
		~GrantGroups();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		value_type getdefaultgrant() const;
		value_type getimplies() const;

		// Setters
		void setname(const std::string& value) const;
		void setdefaultgrant(value_type value) const;
		void setimplies(value_type value) const;

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

	class Permissions
	{
	public:
		// Ctors
		Permissions(Database* db);
		Permissions(Database* db, value_type permissionid);
		~Permissions();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		value_type getfkAccounts() const;
		value_type getfkCommands() const;
		value_type getfkGrantGroups() const;
		value_type getgrant() const;

		// Setters
		void setfkAccounts(value_type value) const;
		void setfkCommands(value_type value) const;
		void setfkGrantGroups(value_type value) const;
		void setgrant(value_type value) const;

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

	class Races
	{
	public:
		// Ctors
		Races(Database* db);
		Races(Database* db, value_type raceid);
		~Races();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;

		// Setters
		void setname(const std::string& value) const;

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

	class Rooms
	{
	public:
		// Ctors
		Rooms(Database* db);
		Rooms(Database* db, value_type roomid);
		~Rooms();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		const std::string& getdescription() const;
		value_type getfkAreas() const;
		value_type getfkSectors() const;
		value_type getwidth() const;
		value_type getlength() const;
		value_type getheight() const;

		// Setters
		void setname(const std::string& value) const;
		void setdescription(const std::string& value) const;
		void setfkAreas(value_type value) const;
		void setfkSectors(value_type value) const;
		void setwidth(value_type value) const;
		void setlength(value_type value) const;
		void setheight(value_type value) const;

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

	class Sectors
	{
	public:
		// Ctors
		Sectors(Database* db);
		Sectors(Database* db, value_type sectorid);
		~Sectors();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		const std::string& getsymbol() const;
		value_type getmovecost() const;
		value_type getwater() const;

		// Setters
		void setname(const std::string& value) const;
		void setsymbol(const std::string& value) const;
		void setmovecost(value_type value) const;
		void setwater(value_type value) const;

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

	class Skills
	{
	public:
		// Ctors
		Skills(Database* db);
		Skills(Database* db, value_type skillid);
		~Skills();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		value_type getfkBranches() const;

		// Setters
		void setname(const std::string& value) const;
		void setfkBranches(value_type value) const;

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

	class Stats
	{
	public:
		// Ctors
		Stats(Database* db);
		Stats(Database* db, value_type statid);
		~Stats();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		const std::string& getshortname() const;

		// Setters
		void setname(const std::string& value) const;
		void setshortname(const std::string& value) const;

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

	class Trees
	{
	public:
		// Ctors
		Trees(Database* db);
		Trees(Database* db, value_type treeid);
		~Trees();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getname() const;
		value_type getfkClusters() const;
		value_type getfkStatsPrimary() const;
		value_type getfkStatsSecondary() const;

		// Setters
		void setname(const std::string& value) const;
		void setfkClusters(value_type value) const;
		void setfkStatsPrimary(value_type value) const;
		void setfkStatsSecondary(value_type value) const;

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

	class Version
	{
	public:
		// Ctors
		Version(Database* db);
		Version(Database* db, value_type versionid);
		~Version();

		// Database interaction
		value_type insert();
		void update();
		void save();
		void erase();

		// Getters
		const std::string& getversiontext() const;
		value_type getmajor() const;
		value_type getminor() const;
		value_type getmicro() const;

		// Setters
		void setversiontext(const std::string& value) const;
		void setmajor(value_type value) const;
		void setminor(value_type value) const;
		void setmicro(value_type value) const;

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


