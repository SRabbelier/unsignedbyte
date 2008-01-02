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
#ifdef _WIN32
	#pragma warning (disable:4800)
#endif

#include <string>
#include <sqlite3.h>
#include <Database.h>
#include <Tables.h>
#include <SqliteMgr.h>
#include <Bindable.h>

namespace db
{
	class Accounts : public Bindable
	{
	public:
		// Ctors
		Accounts();
		~Accounts();

		// Factories
		static Accounts* bykey(value_type accountid);
		static Accounts* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getaccountid() const;
		const std::string& getname() const;
		const std::string& getpassword() const;

		// Setters
		void setname(const std::string& value);
		void setpassword(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_accountid;

		// Fields
		std::string m_name;
		std::string m_password;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Accounts(const Accounts& rhs);
		Accounts operator=(const Accounts& rhs);
	};

	class Areas : public Bindable
	{
	public:
		// Ctors
		Areas();
		~Areas();

		// Factories
		static Areas* bykey(value_type areaid);
		static Areas* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getareaid() const;
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

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_areaid;

		// Fields
		std::string m_name;
		std::string m_description;
		value_type m_height;
		value_type m_width;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Areas(const Areas& rhs);
		Areas operator=(const Areas& rhs);
	};

	class Branches : public Bindable
	{
	public:
		// Ctors
		Branches();
		~Branches();

		// Factories
		static Branches* bykey(value_type branchid);
		static Branches* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getbranchid() const;
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

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_branchid;

		// Fields
		std::string m_name;
		value_type m_fkTrees;
		value_type m_fkStatsPrimary;
		value_type m_fkStatsSecondary;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Branches(const Branches& rhs);
		Branches operator=(const Branches& rhs);
	};

	class CharacterAccount : public Bindable
	{
	public:
		// Ctors
		~CharacterAccount();

		// Factories
		static CharacterAccount* bykey(value_type fkAccounts, value_type fkCharacters);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkAccounts() const;
		value_type getfkCharacters() const;

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkAccounts;
		value_type m_fkCharacters;

		// Fields

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		CharacterAccount();
		CharacterAccount(const CharacterAccount& rhs);
		CharacterAccount operator=(const CharacterAccount& rhs);
	};

	class CharacterBranch : public Bindable
	{
	public:
		// Ctors
		~CharacterBranch();

		// Factories
		static CharacterBranch* bykey(value_type fkBranches, value_type fkCharacters);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkBranches() const;
		value_type getfkCharacters() const;
		value_type getxp() const;

		// Setters
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkBranches;
		value_type m_fkCharacters;

		// Fields
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		CharacterBranch();
		CharacterBranch(const CharacterBranch& rhs);
		CharacterBranch operator=(const CharacterBranch& rhs);
	};

	class CharacterCluster : public Bindable
	{
	public:
		// Ctors
		~CharacterCluster();

		// Factories
		static CharacterCluster* bykey(value_type fkCharacters, value_type fkClusters);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkClusters() const;
		value_type getxp() const;

		// Setters
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkCharacters;
		value_type m_fkClusters;

		// Fields
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		CharacterCluster();
		CharacterCluster(const CharacterCluster& rhs);
		CharacterCluster operator=(const CharacterCluster& rhs);
	};

	class Characters : public Bindable
	{
	public:
		// Ctors
		Characters();
		~Characters();

		// Factories
		static Characters* bykey(value_type characterid);
		static Characters* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getcharacterid() const;
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

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_characterid;

		// Fields
		value_type m_fkRaces;
		value_type m_fkRooms;
		std::string m_name;
		std::string m_description;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Characters(const Characters& rhs);
		Characters operator=(const Characters& rhs);
	};

	class CharacterSkill : public Bindable
	{
	public:
		// Ctors
		~CharacterSkill();

		// Factories
		static CharacterSkill* bykey(value_type fkBranches, value_type fkCharacters);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkBranches() const;
		value_type getfkCharacters() const;
		value_type getxp() const;

		// Setters
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkBranches;
		value_type m_fkCharacters;

		// Fields
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		CharacterSkill();
		CharacterSkill(const CharacterSkill& rhs);
		CharacterSkill operator=(const CharacterSkill& rhs);
	};

	class CharacterStat : public Bindable
	{
	public:
		// Ctors
		~CharacterStat();

		// Factories
		static CharacterStat* bykey(value_type fkCharacters, value_type fkStats);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkStats() const;
		value_type getxp() const;

		// Setters
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkCharacters;
		value_type m_fkStats;

		// Fields
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		CharacterStat();
		CharacterStat(const CharacterStat& rhs);
		CharacterStat operator=(const CharacterStat& rhs);
	};

	class CharacterTree : public Bindable
	{
	public:
		// Ctors
		~CharacterTree();

		// Factories
		static CharacterTree* bykey(value_type fkCharacters, value_type fkTrees);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkTrees() const;
		value_type getxp() const;

		// Setters
		void setxp(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkCharacters;
		value_type m_fkTrees;

		// Fields
		value_type m_xp;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		CharacterTree();
		CharacterTree(const CharacterTree& rhs);
		CharacterTree operator=(const CharacterTree& rhs);
	};

	class Clusters : public Bindable
	{
	public:
		// Ctors
		Clusters();
		~Clusters();

		// Factories
		static Clusters* bykey(value_type clusterid);
		static Clusters* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getclusterid() const;
		const std::string& getname() const;

		// Setters
		void setname(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_clusterid;

		// Fields
		std::string m_name;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Clusters(const Clusters& rhs);
		Clusters operator=(const Clusters& rhs);
	};

	class Chunks : public Bindable
	{
	public:
		// Ctors
		Chunks();
		~Chunks();

		// Factories
		static Chunks* bykey(value_type chunkid);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getchunkid() const;
		value_type getfkRooms() const;
		const std::string& getname() const;
		const std::string& getdescription() const;
		const std::string& gettags() const;

		// Setters
		void setfkRooms(value_type value);
		void setname(const std::string& value);
		void setdescription(const std::string& value);
		void settags(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_chunkid;

		// Fields
		value_type m_fkRooms;
		std::string m_name;
		std::string m_description;
		std::string m_tags;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Chunks(const Chunks& rhs);
		Chunks operator=(const Chunks& rhs);
	};

	class Colours : public Bindable
	{
	public:
		// Ctors
		Colours();
		~Colours();

		// Factories
		static Colours* bykey(value_type colourid);
		static Colours* byname(const std::string& value);
		static Colours* bycode(const std::string& value);
		static value_type lookupname(const std::string& value);
		static value_type lookupcode(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getcolourid() const;
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

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_colourid;

		// Fields
		std::string m_name;
		std::string m_code;
		std::string m_colourstring;
		value_type m_ansi;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Colours(const Colours& rhs);
		Colours operator=(const Colours& rhs);
	};

	class Commands : public Bindable
	{
	public:
		// Ctors
		Commands();
		~Commands();

		// Factories
		static Commands* bykey(value_type commandid);
		static Commands* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getcommandid() const;
		const std::string& getname() const;
		value_type getgrantgroup() const;
		value_type gethighforce() const;
		value_type getforce() const;
		value_type getlowforce() const;

		// Setters
		void setname(const std::string& value);
		void setgrantgroup(value_type value);
		void sethighforce(value_type value);
		void setforce(value_type value);
		void setlowforce(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_commandid;

		// Fields
		std::string m_name;
		value_type m_grantgroup;
		value_type m_highforce;
		value_type m_force;
		value_type m_lowforce;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Commands(const Commands& rhs);
		Commands operator=(const Commands& rhs);
	};

	class Details : public Bindable
	{
	public:
		// Ctors
		Details();
		~Details();

		// Factories
		static Details* bykey(value_type detailid);
		static Details* bykey(const std::string& value);
		static value_type lookupkey(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getdetailid() const;
		const std::string& getkey() const;
		const std::string& getdescription() const;

		// Setters
		void setkey(const std::string& value);
		void setdescription(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_detailid;

		// Fields
		std::string m_key;
		std::string m_description;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Details(const Details& rhs);
		Details operator=(const Details& rhs);
	};

	class DetailRoom : public Bindable
	{
	public:
		// Ctors
		~DetailRoom();

		// Factories
		static DetailRoom* bykey(value_type fkDetails, value_type fkRooms);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkDetails() const;
		value_type getfkRooms() const;

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkDetails;
		value_type m_fkRooms;

		// Fields

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		DetailRoom();
		DetailRoom(const DetailRoom& rhs);
		DetailRoom operator=(const DetailRoom& rhs);
	};

	class DetailChunk : public Bindable
	{
	public:
		// Ctors
		~DetailChunk();

		// Factories
		static DetailChunk* bykey(value_type fkChunks, value_type fkDetails);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkChunks() const;
		value_type getfkDetails() const;

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkChunks;
		value_type m_fkDetails;

		// Fields

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		DetailChunk();
		DetailChunk(const DetailChunk& rhs);
		DetailChunk operator=(const DetailChunk& rhs);
	};

	class DetailCharacter : public Bindable
	{
	public:
		// Ctors
		~DetailCharacter();

		// Factories
		static DetailCharacter* bykey(value_type fkCharacters, value_type fkDetails);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkCharacters() const;
		value_type getfkDetails() const;

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkCharacters;
		value_type m_fkDetails;

		// Fields

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		DetailCharacter();
		DetailCharacter(const DetailCharacter& rhs);
		DetailCharacter operator=(const DetailCharacter& rhs);
	};

	class DetailDetail : public Bindable
	{
	public:
		// Ctors
		~DetailDetail();

		// Factories
		static DetailDetail* bykey(value_type fkDetailsPrimary, value_type fkDetailsSecondary);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkDetailsPrimary() const;
		value_type getfkDetailsSecondary() const;

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkDetailsPrimary;
		value_type m_fkDetailsSecondary;

		// Fields

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		DetailDetail();
		DetailDetail(const DetailDetail& rhs);
		DetailDetail operator=(const DetailDetail& rhs);
	};

	class Exits : public Bindable
	{
	public:
		// Ctors
		Exits();
		~Exits();

		// Factories
		static Exits* bykey(value_type exitid);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getexitid() const;
		value_type getdir() const;

		// Setters
		void setdir(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_exitid;

		// Fields
		value_type m_dir;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Exits(const Exits& rhs);
		Exits operator=(const Exits& rhs);
	};

	class GrantGroups : public Bindable
	{
	public:
		// Ctors
		GrantGroups();
		~GrantGroups();

		// Factories
		static GrantGroups* bykey(value_type grantgroupid);
		static GrantGroups* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getgrantgroupid() const;
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

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_grantgroupid;

		// Fields
		std::string m_name;
		value_type m_defaultgrant;
		value_type m_implies;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		GrantGroups(const GrantGroups& rhs);
		GrantGroups operator=(const GrantGroups& rhs);
	};

	class Permissions : public Bindable
	{
	public:
		// Ctors
		~Permissions();

		// Factories
		static Permissions* bykey(value_type fkAccounts, value_type fkGrantGroups);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getfkAccounts() const;
		value_type getfkGrantGroups() const;
		value_type getgrant() const;

		// Setters
		void setgrant(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Keys
		value_type m_fkAccounts;
		value_type m_fkGrantGroups;

		// Fields
		value_type m_grant;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Permissions();
		Permissions(const Permissions& rhs);
		Permissions operator=(const Permissions& rhs);
	};

	class Races : public Bindable
	{
	public:
		// Ctors
		Races();
		~Races();

		// Factories
		static Races* bykey(value_type raceid);
		static Races* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getraceid() const;
		const std::string& getname() const;

		// Setters
		void setname(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_raceid;

		// Fields
		std::string m_name;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Races(const Races& rhs);
		Races operator=(const Races& rhs);
	};

	class Rooms : public Bindable
	{
	public:
		// Ctors
		Rooms();
		~Rooms();

		// Factories
		static Rooms* bykey(value_type roomid);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getroomid() const;
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

		// Keys
		value_type m_roomid;

		// Fields
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

		// Hide constructor and assignment operator
		Rooms(const Rooms& rhs);
		Rooms operator=(const Rooms& rhs);
	};

	class Sectors : public Bindable
	{
	public:
		// Ctors
		Sectors();
		~Sectors();

		// Factories
		static Sectors* bykey(value_type sectorid);
		static Sectors* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getsectorid() const;
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

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_sectorid;

		// Fields
		std::string m_name;
		std::string m_symbol;
		value_type m_movecost;
		value_type m_water;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Sectors(const Sectors& rhs);
		Sectors operator=(const Sectors& rhs);
	};

	class Skills : public Bindable
	{
	public:
		// Ctors
		Skills();
		~Skills();

		// Factories
		static Skills* bykey(value_type skillid);
		static Skills* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getskillid() const;
		const std::string& getname() const;
		value_type getfkBranches() const;

		// Setters
		void setname(const std::string& value);
		void setfkBranches(value_type value);

	private:
		// Database pointer
		Database* m_db;

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_skillid;

		// Fields
		std::string m_name;
		value_type m_fkBranches;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Skills(const Skills& rhs);
		Skills operator=(const Skills& rhs);
	};

	class Stats : public Bindable
	{
	public:
		// Ctors
		Stats();
		~Stats();

		// Factories
		static Stats* bykey(value_type statid);
		static Stats* byname(const std::string& value);
		static Stats* byshortname(const std::string& value);
		static value_type lookupname(const std::string& value);
		static value_type lookupshortname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getstatid() const;
		const std::string& getname() const;
		const std::string& getshortname() const;

		// Setters
		void setname(const std::string& value);
		void setshortname(const std::string& value);

	private:
		// Database pointer
		Database* m_db;

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_statid;

		// Fields
		std::string m_name;
		std::string m_shortname;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Stats(const Stats& rhs);
		Stats operator=(const Stats& rhs);
	};

	class Trees : public Bindable
	{
	public:
		// Ctors
		Trees();
		~Trees();

		// Factories
		static Trees* bykey(value_type treeid);
		static Trees* byname(const std::string& value);
		static value_type lookupname(const std::string& value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type gettreeid() const;
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

		// Lookup
		std::string m_lookupvalue;

		// Keys
		value_type m_treeid;

		// Fields
		std::string m_name;
		value_type m_fkClusters;
		value_type m_fkStatsPrimary;
		value_type m_fkStatsSecondary;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Trees(const Trees& rhs);
		Trees operator=(const Trees& rhs);
	};

	class Version : public Bindable
	{
	public:
		// Ctors
		Version();
		~Version();

		// Factories
		static Version* bykey(value_type versionid);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);
		TablePtr getTable() const;

		// Getters
		value_type getversionid() const;
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

		// Keys
		value_type m_versionid;

		// Fields
		std::string m_versiontext;
		value_type m_major;
		value_type m_minor;
		value_type m_micro;

		// State flags
		bool m_newentry;
		bool m_dirty;

		// Hide constructor and assignment operator
		Version(const Version& rhs);
		Version operator=(const Version& rhs);
	};

} // end of namespace


