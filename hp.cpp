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

#include <string>
#include <stdexcept>

#include "hp.h"

#include <sqlite3.h>
#include <Database.h>
#include <Query.h>

using namespace hp;


/**
 * Begin of implementation
 * class Accounts
 **/

// Ctors
Accounts::Accounts(Database* db) :
m_db(db),
m_accountid(),
m_name(),
m_password()
{

}

Accounts::Accounts(Database* db, value_type accountid) :
m_db(db),
m_accountid(accountid)
{

}

Accounts::~Accounts()
{

}

value_type Accounts::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Accounts::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Accounts::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Accounts::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Accounts::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_accountid);
}

void Accounts::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_password.c_str(), m_password.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_accountid);
}

Table* Accounts::getTable() const
{
	return Tables::Get()->ACCOUNTS;
}

const std::string& Accounts::getname() const
{
	return m_name;
}

const std::string& Accounts::getpassword() const
{
	return m_password;
}

void Accounts::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Accounts::setpassword(const std::string& value)
{
	m_password = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Accounts
 **/


/**
 * Begin of implementation
 * class Areas
 **/

// Ctors
Areas::Areas(Database* db) :
m_db(db),
m_areaid(),
m_name(),
m_description(),
m_height(0),
m_width(0)
{

}

Areas::Areas(Database* db, value_type areaid) :
m_db(db),
m_areaid(areaid)
{

}

Areas::~Areas()
{

}

value_type Areas::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Areas::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Areas::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Areas::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Areas::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_areaid);
}

void Areas::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_description.c_str(), m_description.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_height);
	sqlite3_bind_int64(stmt, 4, m_width);
	sqlite3_bind_int64(stmt, 5, m_areaid);
}

Table* Areas::getTable() const
{
	return Tables::Get()->AREAS;
}

const std::string& Areas::getname() const
{
	return m_name;
}

const std::string& Areas::getdescription() const
{
	return m_description;
}

value_type Areas::getheight() const
{
	return m_height;
}

value_type Areas::getwidth() const
{
	return m_width;
}

void Areas::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Areas::setdescription(const std::string& value)
{
	m_description = value;
	m_dirty = true;
}

void Areas::setheight(value_type value)
{
	m_height = value;
	m_dirty = true;
}

void Areas::setwidth(value_type value)
{
	m_width = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Areas
 **/


/**
 * Begin of implementation
 * class Branches
 **/

// Ctors
Branches::Branches(Database* db) :
m_db(db),
m_branchid(),
m_name(),
m_fkTrees(0),
m_fkStatsPrimary(0),
m_fkStatsSecondary(0)
{

}

Branches::Branches(Database* db, value_type branchid) :
m_db(db),
m_branchid(branchid)
{

}

Branches::~Branches()
{

}

value_type Branches::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Branches::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Branches::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Branches::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Branches::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_branchid);
}

void Branches::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_fkTrees);
	sqlite3_bind_int64(stmt, 3, m_fkStatsPrimary);
	sqlite3_bind_int64(stmt, 4, m_fkStatsSecondary);
	sqlite3_bind_int64(stmt, 5, m_branchid);
}

Table* Branches::getTable() const
{
	return Tables::Get()->BRANCHES;
}

const std::string& Branches::getname() const
{
	return m_name;
}

value_type Branches::getfkTrees() const
{
	return m_fkTrees;
}

value_type Branches::getfkStatsPrimary() const
{
	return m_fkStatsPrimary;
}

value_type Branches::getfkStatsSecondary() const
{
	return m_fkStatsSecondary;
}

void Branches::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Branches::setfkTrees(value_type value)
{
	m_fkTrees = value;
	m_dirty = true;
}

void Branches::setfkStatsPrimary(value_type value)
{
	m_fkStatsPrimary = value;
	m_dirty = true;
}

void Branches::setfkStatsSecondary(value_type value)
{
	m_fkStatsSecondary = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Branches
 **/


/**
 * Begin of implementation
 * class CharacterAccount
 **/

// Ctors
CharacterAccount::CharacterAccount(Database* db) :
m_db(db),
m_fkCharacters(0),
m_fkAccounts(0)
{

}

CharacterAccount::CharacterAccount(Database* db, value_type fkCharacters, value_type fkAccounts) :
m_db(db),
m_fkCharacters(fkCharacters),
m_fkAccounts(fkAccounts){

}

CharacterAccount::~CharacterAccount()
{

}

value_type CharacterAccount::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void CharacterAccount::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterAccount::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterAccount::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkAccounts);
}

void CharacterAccount::bindUpdate(sqlite3_stmt* stmt) const
{
	throw std::logic_error("CharacterAccount::bindUpdate(), in a lookup table!");
}

Table* CharacterAccount::getTable() const
{
	return Tables::Get()->CHARACTERACCOUNT;
}

value_type CharacterAccount::getfkCharacters() const
{
	return m_fkCharacters;
}

value_type CharacterAccount::getfkAccounts() const
{
	return m_fkAccounts;
}


/**
 * End of implementation
 * class CharacterAccount
 **/


/**
 * Begin of implementation
 * class CharacterBranch
 **/

// Ctors
CharacterBranch::CharacterBranch(Database* db) :
m_db(db),
m_fkCharacters(0),
m_fkBranches(0)
{

}

CharacterBranch::CharacterBranch(Database* db, value_type fkCharacters, value_type fkBranches) :
m_db(db),
m_fkCharacters(fkCharacters),
m_fkBranches(fkBranches){

}

CharacterBranch::~CharacterBranch()
{

}

value_type CharacterBranch::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void CharacterBranch::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterBranch::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterBranch::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkBranches);
}

void CharacterBranch::bindUpdate(sqlite3_stmt* stmt) const
{
	throw std::logic_error("CharacterBranch::bindUpdate(), in a lookup table!");
}

Table* CharacterBranch::getTable() const
{
	return Tables::Get()->CHARACTERBRANCH;
}

value_type CharacterBranch::getfkCharacters() const
{
	return m_fkCharacters;
}

value_type CharacterBranch::getfkBranches() const
{
	return m_fkBranches;
}


/**
 * End of implementation
 * class CharacterBranch
 **/


/**
 * Begin of implementation
 * class CharacterCluster
 **/

// Ctors
CharacterCluster::CharacterCluster(Database* db) :
m_db(db),
m_fkCharacters(0),
m_fkClusters(0)
{

}

CharacterCluster::CharacterCluster(Database* db, value_type fkCharacters, value_type fkClusters) :
m_db(db),
m_fkCharacters(fkCharacters),
m_fkClusters(fkClusters){

}

CharacterCluster::~CharacterCluster()
{

}

value_type CharacterCluster::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void CharacterCluster::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterCluster::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterCluster::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkClusters);
}

void CharacterCluster::bindUpdate(sqlite3_stmt* stmt) const
{
	throw std::logic_error("CharacterCluster::bindUpdate(), in a lookup table!");
}

Table* CharacterCluster::getTable() const
{
	return Tables::Get()->CHARACTERCLUSTER;
}

value_type CharacterCluster::getfkCharacters() const
{
	return m_fkCharacters;
}

value_type CharacterCluster::getfkClusters() const
{
	return m_fkClusters;
}


/**
 * End of implementation
 * class CharacterCluster
 **/


/**
 * Begin of implementation
 * class Characters
 **/

// Ctors
Characters::Characters(Database* db) :
m_db(db),
m_characterid(),
m_fkRaces(0),
m_fkRooms(0),
m_name(),
m_description()
{

}

Characters::Characters(Database* db, value_type characterid) :
m_db(db),
m_characterid(characterid)
{

}

Characters::~Characters()
{

}

value_type Characters::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Characters::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Characters::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Characters::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Characters::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_characterid);
}

void Characters::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkRaces);
	sqlite3_bind_int64(stmt, 2, m_fkRooms);
	sqlite3_bind_text(stmt, 3, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, m_description.c_str(), m_description.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 5, m_characterid);
}

Table* Characters::getTable() const
{
	return Tables::Get()->CHARACTERS;
}

value_type Characters::getfkRaces() const
{
	return m_fkRaces;
}

value_type Characters::getfkRooms() const
{
	return m_fkRooms;
}

const std::string& Characters::getname() const
{
	return m_name;
}

const std::string& Characters::getdescription() const
{
	return m_description;
}

void Characters::setfkRaces(value_type value)
{
	m_fkRaces = value;
	m_dirty = true;
}

void Characters::setfkRooms(value_type value)
{
	m_fkRooms = value;
	m_dirty = true;
}

void Characters::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Characters::setdescription(const std::string& value)
{
	m_description = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Characters
 **/


/**
 * Begin of implementation
 * class CharacterSkill
 **/

// Ctors
CharacterSkill::CharacterSkill(Database* db) :
m_db(db),
m_fkCharacters(0),
m_fkBranches(0)
{

}

CharacterSkill::CharacterSkill(Database* db, value_type fkCharacters, value_type fkBranches) :
m_db(db),
m_fkCharacters(fkCharacters),
m_fkBranches(fkBranches){

}

CharacterSkill::~CharacterSkill()
{

}

value_type CharacterSkill::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void CharacterSkill::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterSkill::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterSkill::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkBranches);
}

void CharacterSkill::bindUpdate(sqlite3_stmt* stmt) const
{
	throw std::logic_error("CharacterSkill::bindUpdate(), in a lookup table!");
}

Table* CharacterSkill::getTable() const
{
	return Tables::Get()->CHARACTERSKILL;
}

value_type CharacterSkill::getfkCharacters() const
{
	return m_fkCharacters;
}

value_type CharacterSkill::getfkBranches() const
{
	return m_fkBranches;
}


/**
 * End of implementation
 * class CharacterSkill
 **/


/**
 * Begin of implementation
 * class CharacterStat
 **/

// Ctors
CharacterStat::CharacterStat(Database* db) :
m_db(db),
m_fkCharacters(0),
m_fkStats(0)
{

}

CharacterStat::CharacterStat(Database* db, value_type fkCharacters, value_type fkStats) :
m_db(db),
m_fkCharacters(fkCharacters),
m_fkStats(fkStats){

}

CharacterStat::~CharacterStat()
{

}

value_type CharacterStat::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void CharacterStat::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterStat::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterStat::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkStats);
}

void CharacterStat::bindUpdate(sqlite3_stmt* stmt) const
{
	throw std::logic_error("CharacterStat::bindUpdate(), in a lookup table!");
}

Table* CharacterStat::getTable() const
{
	return Tables::Get()->CHARACTERSTAT;
}

value_type CharacterStat::getfkCharacters() const
{
	return m_fkCharacters;
}

value_type CharacterStat::getfkStats() const
{
	return m_fkStats;
}


/**
 * End of implementation
 * class CharacterStat
 **/


/**
 * Begin of implementation
 * class CharacterTree
 **/

// Ctors
CharacterTree::CharacterTree(Database* db) :
m_db(db),
m_fkCharacters(0),
m_fkTrees(0)
{

}

CharacterTree::CharacterTree(Database* db, value_type fkCharacters, value_type fkTrees) :
m_db(db),
m_fkCharacters(fkCharacters),
m_fkTrees(fkTrees){

}

CharacterTree::~CharacterTree()
{

}

value_type CharacterTree::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void CharacterTree::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterTree::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterTree::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkTrees);
}

void CharacterTree::bindUpdate(sqlite3_stmt* stmt) const
{
	throw std::logic_error("CharacterTree::bindUpdate(), in a lookup table!");
}

Table* CharacterTree::getTable() const
{
	return Tables::Get()->CHARACTERTREE;
}

value_type CharacterTree::getfkCharacters() const
{
	return m_fkCharacters;
}

value_type CharacterTree::getfkTrees() const
{
	return m_fkTrees;
}


/**
 * End of implementation
 * class CharacterTree
 **/


/**
 * Begin of implementation
 * class Clusters
 **/

// Ctors
Clusters::Clusters(Database* db) :
m_db(db),
m_clusterid(),
m_name()
{

}

Clusters::Clusters(Database* db, value_type clusterid) :
m_db(db),
m_clusterid(clusterid)
{

}

Clusters::~Clusters()
{

}

value_type Clusters::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Clusters::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Clusters::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Clusters::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Clusters::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_clusterid);
}

void Clusters::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_clusterid);
}

Table* Clusters::getTable() const
{
	return Tables::Get()->CLUSTERS;
}

const std::string& Clusters::getname() const
{
	return m_name;
}

void Clusters::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Clusters
 **/


/**
 * Begin of implementation
 * class Colours
 **/

// Ctors
Colours::Colours(Database* db) :
m_db(db),
m_colourid(),
m_name(),
m_code(),
m_colourstring(),
m_ansi(0)
{

}

Colours::Colours(Database* db, value_type colourid) :
m_db(db),
m_colourid(colourid)
{

}

Colours::~Colours()
{

}

value_type Colours::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Colours::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Colours::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Colours::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Colours::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_colourid);
}

void Colours::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_code.c_str(), m_code.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, m_colourstring.c_str(), m_colourstring.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 4, m_ansi);
	sqlite3_bind_int64(stmt, 5, m_colourid);
}

Table* Colours::getTable() const
{
	return Tables::Get()->COLOURS;
}

const std::string& Colours::getname() const
{
	return m_name;
}

const std::string& Colours::getcode() const
{
	return m_code;
}

const std::string& Colours::getcolourstring() const
{
	return m_colourstring;
}

value_type Colours::getansi() const
{
	return m_ansi;
}

void Colours::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Colours::setcode(const std::string& value)
{
	m_code = value;
	m_dirty = true;
}

void Colours::setcolourstring(const std::string& value)
{
	m_colourstring = value;
	m_dirty = true;
}

void Colours::setansi(value_type value)
{
	m_ansi = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Colours
 **/


/**
 * Begin of implementation
 * class Commands
 **/

// Ctors
Commands::Commands(Database* db) :
m_db(db),
m_commandid(),
m_name(),
m_grantgroup(),
m_highforce(),
m_force(),
m_lowforce(0)
{

}

Commands::Commands(Database* db, value_type commandid) :
m_db(db),
m_commandid(commandid)
{

}

Commands::~Commands()
{

}

value_type Commands::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Commands::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Commands::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Commands::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Commands::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_commandid);
}

void Commands::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_grantgroup.c_str(), m_grantgroup.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, m_highforce.c_str(), m_highforce.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, m_force.c_str(), m_force.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 5, m_lowforce);
	sqlite3_bind_int64(stmt, 6, m_commandid);
}

Table* Commands::getTable() const
{
	return Tables::Get()->COMMANDS;
}

const std::string& Commands::getname() const
{
	return m_name;
}

const std::string& Commands::getgrantgroup() const
{
	return m_grantgroup;
}

const std::string& Commands::gethighforce() const
{
	return m_highforce;
}

const std::string& Commands::getforce() const
{
	return m_force;
}

value_type Commands::getlowforce() const
{
	return m_lowforce;
}

void Commands::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Commands::setgrantgroup(const std::string& value)
{
	m_grantgroup = value;
	m_dirty = true;
}

void Commands::sethighforce(const std::string& value)
{
	m_highforce = value;
	m_dirty = true;
}

void Commands::setforce(const std::string& value)
{
	m_force = value;
	m_dirty = true;
}

void Commands::setlowforce(value_type value)
{
	m_lowforce = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Commands
 **/


/**
 * Begin of implementation
 * class Exits
 **/

// Ctors
Exits::Exits(Database* db) :
m_db(db),
m_exitid(),
m_dir(0)
{

}

Exits::Exits(Database* db, value_type exitid) :
m_db(db),
m_exitid(exitid)
{

}

Exits::~Exits()
{

}

value_type Exits::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Exits::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Exits::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Exits::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Exits::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_exitid);
}

void Exits::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_dir);
	sqlite3_bind_int64(stmt, 2, m_exitid);
}

Table* Exits::getTable() const
{
	return Tables::Get()->EXITS;
}

value_type Exits::getdir() const
{
	return m_dir;
}

void Exits::setdir(value_type value)
{
	m_dir = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Exits
 **/


/**
 * Begin of implementation
 * class GrantGroups
 **/

// Ctors
GrantGroups::GrantGroups(Database* db) :
m_db(db),
m_grantgroupid(),
m_name(),
m_defaultgrant(0),
m_implies(0)
{

}

GrantGroups::GrantGroups(Database* db, value_type grantgroupid) :
m_db(db),
m_grantgroupid(grantgroupid)
{

}

GrantGroups::~GrantGroups()
{

}

value_type GrantGroups::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void GrantGroups::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void GrantGroups::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void GrantGroups::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void GrantGroups::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_grantgroupid);
}

void GrantGroups::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_defaultgrant);
	sqlite3_bind_int64(stmt, 3, m_implies);
	sqlite3_bind_int64(stmt, 4, m_grantgroupid);
}

Table* GrantGroups::getTable() const
{
	return Tables::Get()->GRANTGROUPS;
}

const std::string& GrantGroups::getname() const
{
	return m_name;
}

value_type GrantGroups::getdefaultgrant() const
{
	return m_defaultgrant;
}

value_type GrantGroups::getimplies() const
{
	return m_implies;
}

void GrantGroups::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void GrantGroups::setdefaultgrant(value_type value)
{
	m_defaultgrant = value;
	m_dirty = true;
}

void GrantGroups::setimplies(value_type value)
{
	m_implies = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class GrantGroups
 **/


/**
 * Begin of implementation
 * class Permissions
 **/

// Ctors
Permissions::Permissions(Database* db) :
m_db(db),
m_permissionid(),
m_fkAccounts(0),
m_fkCommands(0),
m_fkGrantGroups(0),
m_grant(0)
{

}

Permissions::Permissions(Database* db, value_type permissionid) :
m_db(db),
m_permissionid(permissionid)
{

}

Permissions::~Permissions()
{

}

value_type Permissions::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Permissions::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Permissions::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Permissions::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Permissions::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_permissionid);
}

void Permissions::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkAccounts);
	sqlite3_bind_int64(stmt, 2, m_fkCommands);
	sqlite3_bind_int64(stmt, 3, m_fkGrantGroups);
	sqlite3_bind_int64(stmt, 4, m_grant);
	sqlite3_bind_int64(stmt, 5, m_permissionid);
}

Table* Permissions::getTable() const
{
	return Tables::Get()->PERMISSIONS;
}

value_type Permissions::getfkAccounts() const
{
	return m_fkAccounts;
}

value_type Permissions::getfkCommands() const
{
	return m_fkCommands;
}

value_type Permissions::getfkGrantGroups() const
{
	return m_fkGrantGroups;
}

value_type Permissions::getgrant() const
{
	return m_grant;
}

void Permissions::setfkAccounts(value_type value)
{
	m_fkAccounts = value;
	m_dirty = true;
}

void Permissions::setfkCommands(value_type value)
{
	m_fkCommands = value;
	m_dirty = true;
}

void Permissions::setfkGrantGroups(value_type value)
{
	m_fkGrantGroups = value;
	m_dirty = true;
}

void Permissions::setgrant(value_type value)
{
	m_grant = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Permissions
 **/


/**
 * Begin of implementation
 * class Races
 **/

// Ctors
Races::Races(Database* db) :
m_db(db),
m_raceid(),
m_name()
{

}

Races::Races(Database* db, value_type raceid) :
m_db(db),
m_raceid(raceid)
{

}

Races::~Races()
{

}

value_type Races::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Races::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Races::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Races::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Races::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_raceid);
}

void Races::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_raceid);
}

Table* Races::getTable() const
{
	return Tables::Get()->RACES;
}

const std::string& Races::getname() const
{
	return m_name;
}

void Races::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Races
 **/


/**
 * Begin of implementation
 * class Rooms
 **/

// Ctors
Rooms::Rooms(Database* db) :
m_db(db),
m_roomid(),
m_name(),
m_description(),
m_fkAreas(0),
m_fkSectors(0),
m_width(0),
m_length(0),
m_height(0)
{

}

Rooms::Rooms(Database* db, value_type roomid) :
m_db(db),
m_roomid(roomid)
{

}

Rooms::~Rooms()
{

}

value_type Rooms::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Rooms::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Rooms::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Rooms::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Rooms::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_roomid);
}

void Rooms::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_description.c_str(), m_description.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_fkAreas);
	sqlite3_bind_int64(stmt, 4, m_fkSectors);
	sqlite3_bind_int64(stmt, 5, m_width);
	sqlite3_bind_int64(stmt, 6, m_length);
	sqlite3_bind_int64(stmt, 7, m_height);
	sqlite3_bind_int64(stmt, 8, m_roomid);
}

Table* Rooms::getTable() const
{
	return Tables::Get()->ROOMS;
}

const std::string& Rooms::getname() const
{
	return m_name;
}

const std::string& Rooms::getdescription() const
{
	return m_description;
}

value_type Rooms::getfkAreas() const
{
	return m_fkAreas;
}

value_type Rooms::getfkSectors() const
{
	return m_fkSectors;
}

value_type Rooms::getwidth() const
{
	return m_width;
}

value_type Rooms::getlength() const
{
	return m_length;
}

value_type Rooms::getheight() const
{
	return m_height;
}

void Rooms::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Rooms::setdescription(const std::string& value)
{
	m_description = value;
	m_dirty = true;
}

void Rooms::setfkAreas(value_type value)
{
	m_fkAreas = value;
	m_dirty = true;
}

void Rooms::setfkSectors(value_type value)
{
	m_fkSectors = value;
	m_dirty = true;
}

void Rooms::setwidth(value_type value)
{
	m_width = value;
	m_dirty = true;
}

void Rooms::setlength(value_type value)
{
	m_length = value;
	m_dirty = true;
}

void Rooms::setheight(value_type value)
{
	m_height = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Rooms
 **/


/**
 * Begin of implementation
 * class Sectors
 **/

// Ctors
Sectors::Sectors(Database* db) :
m_db(db),
m_sectorid(),
m_name(),
m_symbol(),
m_movecost(0),
m_water(0)
{

}

Sectors::Sectors(Database* db, value_type sectorid) :
m_db(db),
m_sectorid(sectorid)
{

}

Sectors::~Sectors()
{

}

value_type Sectors::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Sectors::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Sectors::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Sectors::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Sectors::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_sectorid);
}

void Sectors::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_symbol.c_str(), m_symbol.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_movecost);
	sqlite3_bind_int64(stmt, 4, m_water);
	sqlite3_bind_int64(stmt, 5, m_sectorid);
}

Table* Sectors::getTable() const
{
	return Tables::Get()->SECTORS;
}

const std::string& Sectors::getname() const
{
	return m_name;
}

const std::string& Sectors::getsymbol() const
{
	return m_symbol;
}

value_type Sectors::getmovecost() const
{
	return m_movecost;
}

value_type Sectors::getwater() const
{
	return m_water;
}

void Sectors::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Sectors::setsymbol(const std::string& value)
{
	m_symbol = value;
	m_dirty = true;
}

void Sectors::setmovecost(value_type value)
{
	m_movecost = value;
	m_dirty = true;
}

void Sectors::setwater(value_type value)
{
	m_water = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Sectors
 **/


/**
 * Begin of implementation
 * class Skills
 **/

// Ctors
Skills::Skills(Database* db) :
m_db(db),
m_skillid(),
m_name(),
m_fkBranches(0)
{

}

Skills::Skills(Database* db, value_type skillid) :
m_db(db),
m_skillid(skillid)
{

}

Skills::~Skills()
{

}

value_type Skills::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Skills::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Skills::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Skills::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Skills::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_skillid);
}

void Skills::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_fkBranches);
	sqlite3_bind_int64(stmt, 3, m_skillid);
}

Table* Skills::getTable() const
{
	return Tables::Get()->SKILLS;
}

const std::string& Skills::getname() const
{
	return m_name;
}

value_type Skills::getfkBranches() const
{
	return m_fkBranches;
}

void Skills::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Skills::setfkBranches(value_type value)
{
	m_fkBranches = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Skills
 **/


/**
 * Begin of implementation
 * class Stats
 **/

// Ctors
Stats::Stats(Database* db) :
m_db(db),
m_statid(),
m_name(),
m_shortname()
{

}

Stats::Stats(Database* db, value_type statid) :
m_db(db),
m_statid(statid)
{

}

Stats::~Stats()
{

}

value_type Stats::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Stats::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Stats::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Stats::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Stats::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_statid);
}

void Stats::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_shortname.c_str(), m_shortname.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_statid);
}

Table* Stats::getTable() const
{
	return Tables::Get()->STATS;
}

const std::string& Stats::getname() const
{
	return m_name;
}

const std::string& Stats::getshortname() const
{
	return m_shortname;
}

void Stats::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Stats::setshortname(const std::string& value)
{
	m_shortname = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Stats
 **/


/**
 * Begin of implementation
 * class Trees
 **/

// Ctors
Trees::Trees(Database* db) :
m_db(db),
m_treeid(),
m_name(),
m_fkClusters(0),
m_fkStatsPrimary(0),
m_fkStatsSecondary(0)
{

}

Trees::Trees(Database* db, value_type treeid) :
m_db(db),
m_treeid(treeid)
{

}

Trees::~Trees()
{

}

value_type Trees::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Trees::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Trees::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Trees::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Trees::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_treeid);
}

void Trees::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_fkClusters);
	sqlite3_bind_int64(stmt, 3, m_fkStatsPrimary);
	sqlite3_bind_int64(stmt, 4, m_fkStatsSecondary);
	sqlite3_bind_int64(stmt, 5, m_treeid);
}

Table* Trees::getTable() const
{
	return Tables::Get()->TREES;
}

const std::string& Trees::getname() const
{
	return m_name;
}

value_type Trees::getfkClusters() const
{
	return m_fkClusters;
}

value_type Trees::getfkStatsPrimary() const
{
	return m_fkStatsPrimary;
}

value_type Trees::getfkStatsSecondary() const
{
	return m_fkStatsSecondary;
}

void Trees::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Trees::setfkClusters(value_type value)
{
	m_fkClusters = value;
	m_dirty = true;
}

void Trees::setfkStatsPrimary(value_type value)
{
	m_fkStatsPrimary = value;
	m_dirty = true;
}

void Trees::setfkStatsSecondary(value_type value)
{
	m_fkStatsSecondary = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Trees
 **/


/**
 * Begin of implementation
 * class Version
 **/

// Ctors
Version::Version(Database* db) :
m_db(db),
m_versionid(),
m_versiontext(),
m_major(0),
m_minor(0),
m_micro(0)
{

}

Version::Version(Database* db, value_type versionid) :
m_db(db),
m_versionid(versionid)
{

}

Version::~Version()
{

}

value_type Version::insert()
{
	value_type result = SqliteMgr::Get()->doInsert(getTable());
	return result;
}

void Version::update()
{
	SqliteMgr::Get()->doUpdate(this);
}

void Version::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Version::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Version::bindErase(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_versionid);
}

void Version::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_versiontext.c_str(), m_versiontext.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_major);
	sqlite3_bind_int64(stmt, 3, m_minor);
	sqlite3_bind_int64(stmt, 4, m_micro);
	sqlite3_bind_int64(stmt, 5, m_versionid);
}

Table* Version::getTable() const
{
	return Tables::Get()->VERSION;
}

const std::string& Version::getversiontext() const
{
	return m_versiontext;
}

value_type Version::getmajor() const
{
	return m_major;
}

value_type Version::getminor() const
{
	return m_minor;
}

value_type Version::getmicro() const
{
	return m_micro;
}

void Version::setversiontext(const std::string& value)
{
	m_versiontext = value;
	m_dirty = true;
}

void Version::setmajor(value_type value)
{
	m_major = value;
	m_dirty = true;
}

void Version::setminor(value_type value)
{
	m_minor = value;
	m_dirty = true;
}

void Version::setmicro(value_type value)
{
	m_micro = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Version
 **/

