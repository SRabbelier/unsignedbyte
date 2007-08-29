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
	SqliteMgr::Get()->doSelect(this);
}

Accounts::~Accounts()
{

}

void Accounts::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Accounts::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Accounts::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_accountid);
}

void Accounts::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_password.c_str(), m_password.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_accountid);
}

void Accounts::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_password = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_accountid = sqlite3_column_int64(stmt, 2);
}

void Accounts::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_password = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_accountid = sqlite3_column_int64(stmt, 2);
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
	SqliteMgr::Get()->doSelect(this);
}

Areas::~Areas()
{

}

void Areas::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Areas::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Areas::bindKeys(sqlite3_stmt* stmt) const
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

void Areas::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_description = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_height = sqlite3_column_int64(stmt, 2);
	m_width = sqlite3_column_int64(stmt, 3);
	m_areaid = sqlite3_column_int64(stmt, 4);
}

void Areas::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_description = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_height = sqlite3_column_int64(stmt, 2);
	m_width = sqlite3_column_int64(stmt, 3);
	m_areaid = sqlite3_column_int64(stmt, 4);
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
m_name()
{

}

Branches::Branches(Database* db, value_type branchid) :
m_db(db),
m_branchid(branchid)
{
	SqliteMgr::Get()->doSelect(this);
}

Branches::~Branches()
{

}

void Branches::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Branches::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Branches::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_branchid);
}

void Branches::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_branchid);
}

void Branches::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_branchid = sqlite3_column_int64(stmt, 1);
}

void Branches::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_branchid = sqlite3_column_int64(stmt, 1);
}

Table* Branches::getTable() const
{
	return Tables::Get()->BRANCHES;
}

const std::string& Branches::getname() const
{
	return m_name;
}

void Branches::setname(const std::string& value)
{
	m_name = value;
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

CharacterAccount::CharacterAccount(Database* db, value_type fkAccounts, value_type fkCharacters) :
m_db(db),
m_fkAccounts(fkAccounts),
m_fkCharacters(fkCharacters)
{
	SqliteMgr::Get()->doSelect(this);
}

CharacterAccount::~CharacterAccount()
{

}

void CharacterAccount::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterAccount::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void CharacterAccount::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkAccounts);
	sqlite3_bind_int64(stmt, 2, m_fkCharacters);
}

void CharacterAccount::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkAccounts);
	sqlite3_bind_int64(stmt, 2, m_fkCharacters);
}

void CharacterAccount::parseInsert(sqlite3_stmt* stmt)
{
}

void CharacterAccount::parseSelect(sqlite3_stmt* stmt)
{
}

Table* CharacterAccount::getTable() const
{
	return Tables::Get()->CHARACTERACCOUNT;
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
m_characterbranchid(),
m_xp(0)
{

}

CharacterBranch::CharacterBranch(Database* db, value_type characterbranchid) :
m_db(db),
m_characterbranchid(characterbranchid)
{
	SqliteMgr::Get()->doSelect(this);
}

CharacterBranch::~CharacterBranch()
{

}

void CharacterBranch::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterBranch::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void CharacterBranch::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_characterbranchid);
}

void CharacterBranch::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_characterbranchid);
}

void CharacterBranch::parseInsert(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_characterbranchid = sqlite3_column_int64(stmt, 1);
}

void CharacterBranch::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_characterbranchid = sqlite3_column_int64(stmt, 1);
}

Table* CharacterBranch::getTable() const
{
	return Tables::Get()->CHARACTERBRANCH;
}

value_type CharacterBranch::getxp() const
{
	return m_xp;
}

void CharacterBranch::setxp(value_type value)
{
	m_xp = value;
	m_dirty = true;
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
m_characterclusterid(),
m_xp(0)
{

}

CharacterCluster::CharacterCluster(Database* db, value_type characterclusterid) :
m_db(db),
m_characterclusterid(characterclusterid)
{
	SqliteMgr::Get()->doSelect(this);
}

CharacterCluster::~CharacterCluster()
{

}

void CharacterCluster::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterCluster::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void CharacterCluster::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_characterclusterid);
}

void CharacterCluster::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_characterclusterid);
}

void CharacterCluster::parseInsert(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_characterclusterid = sqlite3_column_int64(stmt, 1);
}

void CharacterCluster::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_characterclusterid = sqlite3_column_int64(stmt, 1);
}

Table* CharacterCluster::getTable() const
{
	return Tables::Get()->CHARACTERCLUSTER;
}

value_type CharacterCluster::getxp() const
{
	return m_xp;
}

void CharacterCluster::setxp(value_type value)
{
	m_xp = value;
	m_dirty = true;
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
m_name(),
m_description()
{

}

Characters::Characters(Database* db, value_type characterid) :
m_db(db),
m_characterid(characterid)
{
	SqliteMgr::Get()->doSelect(this);
}

Characters::~Characters()
{

}

void Characters::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Characters::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Characters::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_characterid);
}

void Characters::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_description.c_str(), m_description.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_characterid);
}

void Characters::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_description = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_characterid = sqlite3_column_int64(stmt, 2);
}

void Characters::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_description = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_characterid = sqlite3_column_int64(stmt, 2);
}

Table* Characters::getTable() const
{
	return Tables::Get()->CHARACTERS;
}

const std::string& Characters::getname() const
{
	return m_name;
}

const std::string& Characters::getdescription() const
{
	return m_description;
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
m_characterskillid(),
m_xp(0)
{

}

CharacterSkill::CharacterSkill(Database* db, value_type characterskillid) :
m_db(db),
m_characterskillid(characterskillid)
{
	SqliteMgr::Get()->doSelect(this);
}

CharacterSkill::~CharacterSkill()
{

}

void CharacterSkill::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterSkill::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void CharacterSkill::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_characterskillid);
}

void CharacterSkill::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_characterskillid);
}

void CharacterSkill::parseInsert(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_characterskillid = sqlite3_column_int64(stmt, 1);
}

void CharacterSkill::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_characterskillid = sqlite3_column_int64(stmt, 1);
}

Table* CharacterSkill::getTable() const
{
	return Tables::Get()->CHARACTERSKILL;
}

value_type CharacterSkill::getxp() const
{
	return m_xp;
}

void CharacterSkill::setxp(value_type value)
{
	m_xp = value;
	m_dirty = true;
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
m_characterstatid(),
m_current(0),
m_potential(0)
{

}

CharacterStat::CharacterStat(Database* db, value_type characterstatid) :
m_db(db),
m_characterstatid(characterstatid)
{
	SqliteMgr::Get()->doSelect(this);
}

CharacterStat::~CharacterStat()
{

}

void CharacterStat::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterStat::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void CharacterStat::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_characterstatid);
}

void CharacterStat::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_current);
	sqlite3_bind_int64(stmt, 2, m_potential);
	sqlite3_bind_int64(stmt, 3, m_characterstatid);
}

void CharacterStat::parseInsert(sqlite3_stmt* stmt)
{
	m_current = sqlite3_column_int64(stmt, 0);
	m_potential = sqlite3_column_int64(stmt, 1);
	m_characterstatid = sqlite3_column_int64(stmt, 2);
}

void CharacterStat::parseSelect(sqlite3_stmt* stmt)
{
	m_current = sqlite3_column_int64(stmt, 0);
	m_potential = sqlite3_column_int64(stmt, 1);
	m_characterstatid = sqlite3_column_int64(stmt, 2);
}

Table* CharacterStat::getTable() const
{
	return Tables::Get()->CHARACTERSTAT;
}

value_type CharacterStat::getcurrent() const
{
	return m_current;
}

value_type CharacterStat::getpotential() const
{
	return m_potential;
}

void CharacterStat::setcurrent(value_type value)
{
	m_current = value;
	m_dirty = true;
}

void CharacterStat::setpotential(value_type value)
{
	m_potential = value;
	m_dirty = true;
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
m_charactertreeid(),
m_xp(0)
{

}

CharacterTree::CharacterTree(Database* db, value_type charactertreeid) :
m_db(db),
m_charactertreeid(charactertreeid)
{
	SqliteMgr::Get()->doSelect(this);
}

CharacterTree::~CharacterTree()
{

}

void CharacterTree::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void CharacterTree::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void CharacterTree::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_charactertreeid);
}

void CharacterTree::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_charactertreeid);
}

void CharacterTree::parseInsert(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_charactertreeid = sqlite3_column_int64(stmt, 1);
}

void CharacterTree::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_charactertreeid = sqlite3_column_int64(stmt, 1);
}

Table* CharacterTree::getTable() const
{
	return Tables::Get()->CHARACTERTREE;
}

value_type CharacterTree::getxp() const
{
	return m_xp;
}

void CharacterTree::setxp(value_type value)
{
	m_xp = value;
	m_dirty = true;
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
	SqliteMgr::Get()->doSelect(this);
}

Clusters::~Clusters()
{

}

void Clusters::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Clusters::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Clusters::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_clusterid);
}

void Clusters::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_clusterid);
}

void Clusters::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_clusterid = sqlite3_column_int64(stmt, 1);
}

void Clusters::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_clusterid = sqlite3_column_int64(stmt, 1);
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
	SqliteMgr::Get()->doSelect(this);
}

Colours::~Colours()
{

}

void Colours::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Colours::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Colours::bindKeys(sqlite3_stmt* stmt) const
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

void Colours::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_code = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_colourstring = std::string((const char *)sqlite3_column_text(stmt, 2));
	m_ansi = sqlite3_column_int64(stmt, 3);
	m_colourid = sqlite3_column_int64(stmt, 4);
}

void Colours::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_code = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_colourstring = std::string((const char *)sqlite3_column_text(stmt, 2));
	m_ansi = sqlite3_column_int64(stmt, 3);
	m_colourid = sqlite3_column_int64(stmt, 4);
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
	SqliteMgr::Get()->doSelect(this);
}

Commands::~Commands()
{

}

void Commands::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Commands::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Commands::bindKeys(sqlite3_stmt* stmt) const
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

void Commands::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_grantgroup = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_highforce = std::string((const char *)sqlite3_column_text(stmt, 2));
	m_force = std::string((const char *)sqlite3_column_text(stmt, 3));
	m_lowforce = sqlite3_column_int64(stmt, 4);
	m_commandid = sqlite3_column_int64(stmt, 5);
}

void Commands::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_grantgroup = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_highforce = std::string((const char *)sqlite3_column_text(stmt, 2));
	m_force = std::string((const char *)sqlite3_column_text(stmt, 3));
	m_lowforce = sqlite3_column_int64(stmt, 4);
	m_commandid = sqlite3_column_int64(stmt, 5);
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
	SqliteMgr::Get()->doSelect(this);
}

Exits::~Exits()
{

}

void Exits::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Exits::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Exits::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_exitid);
}

void Exits::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_dir);
	sqlite3_bind_int64(stmt, 2, m_exitid);
}

void Exits::parseInsert(sqlite3_stmt* stmt)
{
	m_dir = sqlite3_column_int64(stmt, 0);
	m_exitid = sqlite3_column_int64(stmt, 1);
}

void Exits::parseSelect(sqlite3_stmt* stmt)
{
	m_dir = sqlite3_column_int64(stmt, 0);
	m_exitid = sqlite3_column_int64(stmt, 1);
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
	SqliteMgr::Get()->doSelect(this);
}

GrantGroups::~GrantGroups()
{

}

void GrantGroups::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void GrantGroups::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void GrantGroups::bindKeys(sqlite3_stmt* stmt) const
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

void GrantGroups::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_defaultgrant = sqlite3_column_int64(stmt, 1);
	m_implies = sqlite3_column_int64(stmt, 2);
	m_grantgroupid = sqlite3_column_int64(stmt, 3);
}

void GrantGroups::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_defaultgrant = sqlite3_column_int64(stmt, 1);
	m_implies = sqlite3_column_int64(stmt, 2);
	m_grantgroupid = sqlite3_column_int64(stmt, 3);
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
m_grant(0)
{

}

Permissions::Permissions(Database* db, value_type permissionid) :
m_db(db),
m_permissionid(permissionid)
{
	SqliteMgr::Get()->doSelect(this);
}

Permissions::~Permissions()
{

}

void Permissions::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Permissions::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Permissions::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_permissionid);
}

void Permissions::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_grant);
	sqlite3_bind_int64(stmt, 2, m_permissionid);
}

void Permissions::parseInsert(sqlite3_stmt* stmt)
{
	m_grant = sqlite3_column_int64(stmt, 0);
	m_permissionid = sqlite3_column_int64(stmt, 1);
}

void Permissions::parseSelect(sqlite3_stmt* stmt)
{
	m_grant = sqlite3_column_int64(stmt, 0);
	m_permissionid = sqlite3_column_int64(stmt, 1);
}

Table* Permissions::getTable() const
{
	return Tables::Get()->PERMISSIONS;
}

value_type Permissions::getgrant() const
{
	return m_grant;
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
	SqliteMgr::Get()->doSelect(this);
}

Races::~Races()
{

}

void Races::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Races::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Races::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_raceid);
}

void Races::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_raceid);
}

void Races::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_raceid = sqlite3_column_int64(stmt, 1);
}

void Races::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_raceid = sqlite3_column_int64(stmt, 1);
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
m_width(0),
m_length(0),
m_height(0)
{

}

Rooms::Rooms(Database* db, value_type roomid) :
m_db(db),
m_roomid(roomid)
{
	SqliteMgr::Get()->doSelect(this);
}

Rooms::~Rooms()
{

}

void Rooms::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Rooms::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Rooms::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_roomid);
}

void Rooms::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_description.c_str(), m_description.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_width);
	sqlite3_bind_int64(stmt, 4, m_length);
	sqlite3_bind_int64(stmt, 5, m_height);
	sqlite3_bind_int64(stmt, 6, m_roomid);
}

void Rooms::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_description = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_width = sqlite3_column_int64(stmt, 2);
	m_length = sqlite3_column_int64(stmt, 3);
	m_height = sqlite3_column_int64(stmt, 4);
	m_roomid = sqlite3_column_int64(stmt, 5);
}

void Rooms::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_description = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_width = sqlite3_column_int64(stmt, 2);
	m_length = sqlite3_column_int64(stmt, 3);
	m_height = sqlite3_column_int64(stmt, 4);
	m_roomid = sqlite3_column_int64(stmt, 5);
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
	SqliteMgr::Get()->doSelect(this);
}

Sectors::~Sectors()
{

}

void Sectors::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Sectors::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Sectors::bindKeys(sqlite3_stmt* stmt) const
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

void Sectors::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_symbol = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_movecost = sqlite3_column_int64(stmt, 2);
	m_water = sqlite3_column_int64(stmt, 3);
	m_sectorid = sqlite3_column_int64(stmt, 4);
}

void Sectors::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_symbol = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_movecost = sqlite3_column_int64(stmt, 2);
	m_water = sqlite3_column_int64(stmt, 3);
	m_sectorid = sqlite3_column_int64(stmt, 4);
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
m_name()
{

}

Skills::Skills(Database* db, value_type skillid) :
m_db(db),
m_skillid(skillid)
{
	SqliteMgr::Get()->doSelect(this);
}

Skills::~Skills()
{

}

void Skills::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Skills::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Skills::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_skillid);
}

void Skills::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_skillid);
}

void Skills::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_skillid = sqlite3_column_int64(stmt, 1);
}

void Skills::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_skillid = sqlite3_column_int64(stmt, 1);
}

Table* Skills::getTable() const
{
	return Tables::Get()->SKILLS;
}

const std::string& Skills::getname() const
{
	return m_name;
}

void Skills::setname(const std::string& value)
{
	m_name = value;
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
	SqliteMgr::Get()->doSelect(this);
}

Stats::~Stats()
{

}

void Stats::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Stats::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Stats::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_statid);
}

void Stats::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_shortname.c_str(), m_shortname.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_statid);
}

void Stats::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_shortname = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_statid = sqlite3_column_int64(stmt, 2);
}

void Stats::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_shortname = std::string((const char *)sqlite3_column_text(stmt, 1));
	m_statid = sqlite3_column_int64(stmt, 2);
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
m_name()
{

}

Trees::Trees(Database* db, value_type treeid) :
m_db(db),
m_treeid(treeid)
{
	SqliteMgr::Get()->doSelect(this);
}

Trees::~Trees()
{

}

void Trees::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Trees::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Trees::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_treeid);
}

void Trees::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_treeid);
}

void Trees::parseInsert(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_treeid = sqlite3_column_int64(stmt, 1);
}

void Trees::parseSelect(sqlite3_stmt* stmt)
{
	m_name = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_treeid = sqlite3_column_int64(stmt, 1);
}

Table* Trees::getTable() const
{
	return Tables::Get()->TREES;
}

const std::string& Trees::getname() const
{
	return m_name;
}

void Trees::setname(const std::string& value)
{
	m_name = value;
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
	SqliteMgr::Get()->doSelect(this);
}

Version::~Version()
{

}

void Version::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Version::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	SqliteMgr::Get()->doUpdate(this);
}

void Version::bindKeys(sqlite3_stmt* stmt) const
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

void Version::parseInsert(sqlite3_stmt* stmt)
{
	m_versiontext = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_major = sqlite3_column_int64(stmt, 1);
	m_minor = sqlite3_column_int64(stmt, 2);
	m_micro = sqlite3_column_int64(stmt, 3);
	m_versionid = sqlite3_column_int64(stmt, 4);
}

void Version::parseSelect(sqlite3_stmt* stmt)
{
	m_versiontext = std::string((const char *)sqlite3_column_text(stmt, 0));
	m_major = sqlite3_column_int64(stmt, 1);
	m_minor = sqlite3_column_int64(stmt, 2);
	m_micro = sqlite3_column_int64(stmt, 3);
	m_versionid = sqlite3_column_int64(stmt, 4);
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

