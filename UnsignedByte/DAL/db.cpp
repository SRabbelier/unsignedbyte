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

#include <string>
#include <stdexcept>

#include "db.h"

#include <sqlite3.h>
#include <Database.h>
#include <Query.h>

using namespace db;


/**
 * Begin of implementation
 * class Accounts
 **/

// Ctors
Accounts::Accounts() :
m_accountid(),
m_name(),
m_password(),
m_newentry(true),
m_dirty(false)
{

}

Accounts::~Accounts()
{

}

Accounts* Accounts::bykey(value_type accountid)
{
	Accounts* result = new Accounts();
	result->m_accountid = accountid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Accounts* Accounts::byname(const std::string& value)
{
	Accounts* result = new Accounts();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Accounts::lookupname(const std::string& value)
{
	SmartPtr<Accounts> result(new Accounts()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getaccountid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Accounts::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Accounts::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Accounts::parseInsert(sqlite3* db)
{
	m_accountid = sqlite3_last_insert_rowid(db);
}

void Accounts::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_password = std::string((const char *)text);
	m_newentry = false;
}

void Accounts::parseLookup(sqlite3_stmt* stmt)
{
	m_accountid = sqlite3_column_int64(stmt, 0);
}

TablePtr Accounts::getTable() const
{
	return Tables::Get()->ACCOUNTS;
}

value_type Accounts::getaccountid() const
{
	return m_accountid;
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
Areas::Areas() :
m_areaid(),
m_name(),
m_description(),
m_height(0),
m_width(0),
m_newentry(true),
m_dirty(false)
{

}

Areas::~Areas()
{

}

Areas* Areas::bykey(value_type areaid)
{
	Areas* result = new Areas();
	result->m_areaid = areaid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Areas* Areas::byname(const std::string& value)
{
	Areas* result = new Areas();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Areas::lookupname(const std::string& value)
{
	SmartPtr<Areas> result(new Areas()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getareaid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Areas::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Areas::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Areas::parseInsert(sqlite3* db)
{
	m_areaid = sqlite3_last_insert_rowid(db);
}

void Areas::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_description = std::string((const char *)text);
	m_height = sqlite3_column_int64(stmt, 2);
	m_width = sqlite3_column_int64(stmt, 3);
	m_newentry = false;
}

void Areas::parseLookup(sqlite3_stmt* stmt)
{
	m_areaid = sqlite3_column_int64(stmt, 0);
}

TablePtr Areas::getTable() const
{
	return Tables::Get()->AREAS;
}

value_type Areas::getareaid() const
{
	return m_areaid;
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
Branches::Branches() :
m_branchid(),
m_name(),
m_fkTrees(0),
m_fkStatsPrimary(0),
m_fkStatsSecondary(0),
m_newentry(true),
m_dirty(false)
{

}

Branches::~Branches()
{

}

Branches* Branches::bykey(value_type branchid)
{
	Branches* result = new Branches();
	result->m_branchid = branchid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Branches* Branches::byname(const std::string& value)
{
	Branches* result = new Branches();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Branches::lookupname(const std::string& value)
{
	SmartPtr<Branches> result(new Branches()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getbranchid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Branches::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Branches::bindKeys(sqlite3_stmt* stmt) const
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

void Branches::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Branches::parseInsert(sqlite3* db)
{
	m_branchid = sqlite3_last_insert_rowid(db);
}

void Branches::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	m_fkTrees = sqlite3_column_int64(stmt, 1);
	m_fkStatsPrimary = sqlite3_column_int64(stmt, 2);
	m_fkStatsSecondary = sqlite3_column_int64(stmt, 3);
	m_newentry = false;
}

void Branches::parseLookup(sqlite3_stmt* stmt)
{
	m_branchid = sqlite3_column_int64(stmt, 0);
}

TablePtr Branches::getTable() const
{
	return Tables::Get()->BRANCHES;
}

value_type Branches::getbranchid() const
{
	return m_branchid;
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
CharacterAccount::CharacterAccount() :
m_fkAccounts(),
m_newentry(true),
m_dirty(false)
{

}

CharacterAccount::~CharacterAccount()
{

}

CharacterAccount* CharacterAccount::bykey(value_type fkAccounts, value_type fkCharacters)
{
	CharacterAccount* result = new CharacterAccount();
	result->m_fkAccounts = fkAccounts;
	result->m_fkCharacters = fkCharacters;
	SqliteMgr::Get()->doSelect(result);
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
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool CharacterAccount::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void CharacterAccount::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void CharacterAccount::parseInsert(sqlite3* db)
{
	// Do nothing
}

void CharacterAccount::parseSelect(sqlite3_stmt* stmt)
{
	// Do nothing
}

void CharacterAccount::parseLookup(sqlite3_stmt* stmt)
{
	m_fkAccounts = sqlite3_column_int64(stmt, 0);
	m_fkCharacters = sqlite3_column_int64(stmt, 1);
}

TablePtr CharacterAccount::getTable() const
{
	return Tables::Get()->CHARACTERACCOUNT;
}

value_type CharacterAccount::getfkAccounts() const
{
	return m_fkAccounts;
}

value_type CharacterAccount::getfkCharacters() const
{
	return m_fkCharacters;
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
CharacterBranch::CharacterBranch() :
m_fkBranches(),
m_xp(0),
m_newentry(true),
m_dirty(false)
{

}

CharacterBranch::~CharacterBranch()
{

}

CharacterBranch* CharacterBranch::bykey(value_type fkBranches, value_type fkCharacters)
{
	CharacterBranch* result = new CharacterBranch();
	result->m_fkBranches = fkBranches;
	result->m_fkCharacters = fkCharacters;
	SqliteMgr::Get()->doSelect(result);
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
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool CharacterBranch::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void CharacterBranch::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkBranches);
	sqlite3_bind_int64(stmt, 2, m_fkCharacters);
}

void CharacterBranch::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_fkBranches);
	sqlite3_bind_int64(stmt, 3, m_fkCharacters);
}

void CharacterBranch::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void CharacterBranch::parseInsert(sqlite3* db)
{
	// Do nothing
}

void CharacterBranch::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_newentry = false;
}

void CharacterBranch::parseLookup(sqlite3_stmt* stmt)
{
	m_fkBranches = sqlite3_column_int64(stmt, 0);
	m_fkCharacters = sqlite3_column_int64(stmt, 1);
}

TablePtr CharacterBranch::getTable() const
{
	return Tables::Get()->CHARACTERBRANCH;
}

value_type CharacterBranch::getfkBranches() const
{
	return m_fkBranches;
}

value_type CharacterBranch::getfkCharacters() const
{
	return m_fkCharacters;
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
CharacterCluster::CharacterCluster() :
m_fkCharacters(),
m_xp(0),
m_newentry(true),
m_dirty(false)
{

}

CharacterCluster::~CharacterCluster()
{

}

CharacterCluster* CharacterCluster::bykey(value_type fkCharacters, value_type fkClusters)
{
	CharacterCluster* result = new CharacterCluster();
	result->m_fkCharacters = fkCharacters;
	result->m_fkClusters = fkClusters;
	SqliteMgr::Get()->doSelect(result);
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
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool CharacterCluster::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void CharacterCluster::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkClusters);
}

void CharacterCluster::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_fkCharacters);
	sqlite3_bind_int64(stmt, 3, m_fkClusters);
}

void CharacterCluster::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void CharacterCluster::parseInsert(sqlite3* db)
{
	// Do nothing
}

void CharacterCluster::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_newentry = false;
}

void CharacterCluster::parseLookup(sqlite3_stmt* stmt)
{
	m_fkCharacters = sqlite3_column_int64(stmt, 0);
	m_fkClusters = sqlite3_column_int64(stmt, 1);
}

TablePtr CharacterCluster::getTable() const
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
Characters::Characters() :
m_characterid(),
m_fkRaces(0),
m_fkRooms(0),
m_name(),
m_description(),
m_newentry(true),
m_dirty(false)
{

}

Characters::~Characters()
{

}

Characters* Characters::bykey(value_type characterid)
{
	Characters* result = new Characters();
	result->m_characterid = characterid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Characters* Characters::byname(const std::string& value)
{
	Characters* result = new Characters();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Characters::lookupname(const std::string& value)
{
	SmartPtr<Characters> result(new Characters()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getcharacterid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Characters::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Characters::bindKeys(sqlite3_stmt* stmt) const
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

void Characters::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Characters::parseInsert(sqlite3* db)
{
	m_characterid = sqlite3_last_insert_rowid(db);
}

void Characters::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	m_fkRaces = sqlite3_column_int64(stmt, 0);
	m_fkRooms = sqlite3_column_int64(stmt, 1);
	text = sqlite3_column_text(stmt, 2);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 3);
	if(text != 0)
		m_description = std::string((const char *)text);
	m_newentry = false;
}

void Characters::parseLookup(sqlite3_stmt* stmt)
{
	m_characterid = sqlite3_column_int64(stmt, 0);
}

TablePtr Characters::getTable() const
{
	return Tables::Get()->CHARACTERS;
}

value_type Characters::getcharacterid() const
{
	return m_characterid;
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
CharacterSkill::CharacterSkill() :
m_fkBranches(),
m_xp(0),
m_newentry(true),
m_dirty(false)
{

}

CharacterSkill::~CharacterSkill()
{

}

CharacterSkill* CharacterSkill::bykey(value_type fkBranches, value_type fkCharacters)
{
	CharacterSkill* result = new CharacterSkill();
	result->m_fkBranches = fkBranches;
	result->m_fkCharacters = fkCharacters;
	SqliteMgr::Get()->doSelect(result);
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
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool CharacterSkill::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void CharacterSkill::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkBranches);
	sqlite3_bind_int64(stmt, 2, m_fkCharacters);
}

void CharacterSkill::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_fkBranches);
	sqlite3_bind_int64(stmt, 3, m_fkCharacters);
}

void CharacterSkill::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void CharacterSkill::parseInsert(sqlite3* db)
{
	// Do nothing
}

void CharacterSkill::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_newentry = false;
}

void CharacterSkill::parseLookup(sqlite3_stmt* stmt)
{
	m_fkBranches = sqlite3_column_int64(stmt, 0);
	m_fkCharacters = sqlite3_column_int64(stmt, 1);
}

TablePtr CharacterSkill::getTable() const
{
	return Tables::Get()->CHARACTERSKILL;
}

value_type CharacterSkill::getfkBranches() const
{
	return m_fkBranches;
}

value_type CharacterSkill::getfkCharacters() const
{
	return m_fkCharacters;
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
CharacterStat::CharacterStat() :
m_fkCharacters(),
m_xp(0),
m_newentry(true),
m_dirty(false)
{

}

CharacterStat::~CharacterStat()
{

}

CharacterStat* CharacterStat::bykey(value_type fkCharacters, value_type fkStats)
{
	CharacterStat* result = new CharacterStat();
	result->m_fkCharacters = fkCharacters;
	result->m_fkStats = fkStats;
	SqliteMgr::Get()->doSelect(result);
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
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool CharacterStat::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void CharacterStat::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkStats);
}

void CharacterStat::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_fkCharacters);
	sqlite3_bind_int64(stmt, 3, m_fkStats);
}

void CharacterStat::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void CharacterStat::parseInsert(sqlite3* db)
{
	// Do nothing
}

void CharacterStat::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_newentry = false;
}

void CharacterStat::parseLookup(sqlite3_stmt* stmt)
{
	m_fkCharacters = sqlite3_column_int64(stmt, 0);
	m_fkStats = sqlite3_column_int64(stmt, 1);
}

TablePtr CharacterStat::getTable() const
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

value_type CharacterStat::getxp() const
{
	return m_xp;
}

void CharacterStat::setxp(value_type value)
{
	m_xp = value;
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
CharacterTree::CharacterTree() :
m_fkCharacters(),
m_xp(0),
m_newentry(true),
m_dirty(false)
{

}

CharacterTree::~CharacterTree()
{

}

CharacterTree* CharacterTree::bykey(value_type fkCharacters, value_type fkTrees)
{
	CharacterTree* result = new CharacterTree();
	result->m_fkCharacters = fkCharacters;
	result->m_fkTrees = fkTrees;
	SqliteMgr::Get()->doSelect(result);
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
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool CharacterTree::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void CharacterTree::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkCharacters);
	sqlite3_bind_int64(stmt, 2, m_fkTrees);
}

void CharacterTree::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_xp);
	sqlite3_bind_int64(stmt, 2, m_fkCharacters);
	sqlite3_bind_int64(stmt, 3, m_fkTrees);
}

void CharacterTree::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void CharacterTree::parseInsert(sqlite3* db)
{
	// Do nothing
}

void CharacterTree::parseSelect(sqlite3_stmt* stmt)
{
	m_xp = sqlite3_column_int64(stmt, 0);
	m_newentry = false;
}

void CharacterTree::parseLookup(sqlite3_stmt* stmt)
{
	m_fkCharacters = sqlite3_column_int64(stmt, 0);
	m_fkTrees = sqlite3_column_int64(stmt, 1);
}

TablePtr CharacterTree::getTable() const
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
Clusters::Clusters() :
m_clusterid(),
m_name(),
m_newentry(true),
m_dirty(false)
{

}

Clusters::~Clusters()
{

}

Clusters* Clusters::bykey(value_type clusterid)
{
	Clusters* result = new Clusters();
	result->m_clusterid = clusterid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Clusters* Clusters::byname(const std::string& value)
{
	Clusters* result = new Clusters();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Clusters::lookupname(const std::string& value)
{
	SmartPtr<Clusters> result(new Clusters()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getclusterid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Clusters::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Clusters::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Clusters::parseInsert(sqlite3* db)
{
	m_clusterid = sqlite3_last_insert_rowid(db);
}

void Clusters::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	m_newentry = false;
}

void Clusters::parseLookup(sqlite3_stmt* stmt)
{
	m_clusterid = sqlite3_column_int64(stmt, 0);
}

TablePtr Clusters::getTable() const
{
	return Tables::Get()->CLUSTERS;
}

value_type Clusters::getclusterid() const
{
	return m_clusterid;
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
 * class Chunks
 **/

// Ctors
Chunks::Chunks() :
m_chunkid(),
m_fkRooms(0),
m_name(),
m_description(),
m_newentry(true),
m_dirty(false)
{

}

Chunks::~Chunks()
{

}

Chunks* Chunks::bykey(value_type chunkid)
{
	Chunks* result = new Chunks();
	result->m_chunkid = chunkid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

void Chunks::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Chunks::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Chunks::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Chunks::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_chunkid);
}

void Chunks::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkRooms);
	sqlite3_bind_text(stmt, 2, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, m_description.c_str(), m_description.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 4, m_chunkid);
}

void Chunks::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void Chunks::parseInsert(sqlite3* db)
{
	m_chunkid = sqlite3_last_insert_rowid(db);
}

void Chunks::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	m_fkRooms = sqlite3_column_int64(stmt, 0);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 2);
	if(text != 0)
		m_description = std::string((const char *)text);
	m_newentry = false;
}

void Chunks::parseLookup(sqlite3_stmt* stmt)
{
	m_chunkid = sqlite3_column_int64(stmt, 0);
}

TablePtr Chunks::getTable() const
{
	return Tables::Get()->CHUNKS;
}

value_type Chunks::getchunkid() const
{
	return m_chunkid;
}

value_type Chunks::getfkRooms() const
{
	return m_fkRooms;
}

const std::string& Chunks::getname() const
{
	return m_name;
}

const std::string& Chunks::getdescription() const
{
	return m_description;
}

void Chunks::setfkRooms(value_type value)
{
	m_fkRooms = value;
	m_dirty = true;
}

void Chunks::setname(const std::string& value)
{
	m_name = value;
	m_dirty = true;
}

void Chunks::setdescription(const std::string& value)
{
	m_description = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Chunks
 **/


/**
 * Begin of implementation
 * class Colours
 **/

// Ctors
Colours::Colours() :
m_colourid(),
m_name(),
m_code(),
m_colourstring(),
m_ansi(0),
m_newentry(true),
m_dirty(false)
{

}

Colours::~Colours()
{

}

Colours* Colours::bykey(value_type colourid)
{
	Colours* result = new Colours();
	result->m_colourid = colourid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Colours* Colours::byname(const std::string& value)
{
	Colours* result = new Colours();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

Colours* Colours::bycode(const std::string& value)
{
	Colours* result = new Colours();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"code");
	return result;
}

value_type Colours::lookupname(const std::string& value)
{
	SmartPtr<Colours> result(new Colours()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getcolourid();
	} catch(Bindable* result) {	}

	return key;
}

value_type Colours::lookupcode(const std::string& value)
{
	SmartPtr<Colours> result(new Colours()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "code");
		key = result->getcolourid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Colours::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Colours::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Colours::parseInsert(sqlite3* db)
{
	m_colourid = sqlite3_last_insert_rowid(db);
}

void Colours::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_code = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 2);
	if(text != 0)
		m_colourstring = std::string((const char *)text);
	m_ansi = sqlite3_column_int64(stmt, 3);
	m_newentry = false;
}

void Colours::parseLookup(sqlite3_stmt* stmt)
{
	m_colourid = sqlite3_column_int64(stmt, 0);
}

TablePtr Colours::getTable() const
{
	return Tables::Get()->COLOURS;
}

value_type Colours::getcolourid() const
{
	return m_colourid;
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
Commands::Commands() :
m_commandid(),
m_name(),
m_grantgroup(0),
m_highforce(0),
m_force(0),
m_lowforce(0),
m_newentry(true),
m_dirty(false)
{

}

Commands::~Commands()
{

}

Commands* Commands::bykey(value_type commandid)
{
	Commands* result = new Commands();
	result->m_commandid = commandid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Commands* Commands::byname(const std::string& value)
{
	Commands* result = new Commands();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Commands::lookupname(const std::string& value)
{
	SmartPtr<Commands> result(new Commands()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getcommandid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Commands::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Commands::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_commandid);
}

void Commands::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_grantgroup);
	sqlite3_bind_int64(stmt, 3, m_highforce);
	sqlite3_bind_int64(stmt, 4, m_force);
	sqlite3_bind_int64(stmt, 5, m_lowforce);
	sqlite3_bind_int64(stmt, 6, m_commandid);
}

void Commands::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Commands::parseInsert(sqlite3* db)
{
	m_commandid = sqlite3_last_insert_rowid(db);
}

void Commands::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	m_grantgroup = sqlite3_column_int64(stmt, 1);
	m_highforce = sqlite3_column_int64(stmt, 2);
	m_force = sqlite3_column_int64(stmt, 3);
	m_lowforce = sqlite3_column_int64(stmt, 4);
	m_newentry = false;
}

void Commands::parseLookup(sqlite3_stmt* stmt)
{
	m_commandid = sqlite3_column_int64(stmt, 0);
}

TablePtr Commands::getTable() const
{
	return Tables::Get()->COMMANDS;
}

value_type Commands::getcommandid() const
{
	return m_commandid;
}

const std::string& Commands::getname() const
{
	return m_name;
}

value_type Commands::getgrantgroup() const
{
	return m_grantgroup;
}

value_type Commands::gethighforce() const
{
	return m_highforce;
}

value_type Commands::getforce() const
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

void Commands::setgrantgroup(value_type value)
{
	m_grantgroup = value;
	m_dirty = true;
}

void Commands::sethighforce(value_type value)
{
	m_highforce = value;
	m_dirty = true;
}

void Commands::setforce(value_type value)
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
 * class Details
 **/

// Ctors
Details::Details() :
m_detailid(),
m_key(),
m_description(),
m_newentry(true),
m_dirty(false)
{

}

Details::~Details()
{

}

Details* Details::bykey(value_type detailid)
{
	Details* result = new Details();
	result->m_detailid = detailid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Details* Details::bykey(const std::string& value)
{
	Details* result = new Details();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"key");
	return result;
}

value_type Details::lookupkey(const std::string& value)
{
	SmartPtr<Details> result(new Details()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "key");
		key = result->getdetailid();
	} catch(Bindable* result) {	}

	return key;
}

void Details::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void Details::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Details::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Details::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_detailid);
}

void Details::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_key.c_str(), m_key.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, m_description.c_str(), m_description.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, m_detailid);
}

void Details::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Details::parseInsert(sqlite3* db)
{
	m_detailid = sqlite3_last_insert_rowid(db);
}

void Details::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_key = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_description = std::string((const char *)text);
	m_newentry = false;
}

void Details::parseLookup(sqlite3_stmt* stmt)
{
	m_detailid = sqlite3_column_int64(stmt, 0);
}

TablePtr Details::getTable() const
{
	return Tables::Get()->DETAILS;
}

value_type Details::getdetailid() const
{
	return m_detailid;
}

const std::string& Details::getkey() const
{
	return m_key;
}

const std::string& Details::getdescription() const
{
	return m_description;
}

void Details::setkey(const std::string& value)
{
	m_key = value;
	m_dirty = true;
}

void Details::setdescription(const std::string& value)
{
	m_description = value;
	m_dirty = true;
}


/**
 * End of implementation
 * class Details
 **/


/**
 * Begin of implementation
 * class Exits
 **/

// Ctors
Exits::Exits() :
m_exitid(),
m_dir(0),
m_newentry(true),
m_dirty(false)
{

}

Exits::~Exits()
{

}

Exits* Exits::bykey(value_type exitid)
{
	Exits* result = new Exits();
	result->m_exitid = exitid;
	SqliteMgr::Get()->doSelect(result);
	return result;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Exits::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Exits::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void Exits::parseInsert(sqlite3* db)
{
	m_exitid = sqlite3_last_insert_rowid(db);
}

void Exits::parseSelect(sqlite3_stmt* stmt)
{
	m_dir = sqlite3_column_int64(stmt, 0);
	m_newentry = false;
}

void Exits::parseLookup(sqlite3_stmt* stmt)
{
	m_exitid = sqlite3_column_int64(stmt, 0);
}

TablePtr Exits::getTable() const
{
	return Tables::Get()->EXITS;
}

value_type Exits::getexitid() const
{
	return m_exitid;
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
GrantGroups::GrantGroups() :
m_grantgroupid(),
m_name(),
m_defaultgrant(0),
m_implies(0),
m_newentry(true),
m_dirty(false)
{

}

GrantGroups::~GrantGroups()
{

}

GrantGroups* GrantGroups::bykey(value_type grantgroupid)
{
	GrantGroups* result = new GrantGroups();
	result->m_grantgroupid = grantgroupid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

GrantGroups* GrantGroups::byname(const std::string& value)
{
	GrantGroups* result = new GrantGroups();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type GrantGroups::lookupname(const std::string& value)
{
	SmartPtr<GrantGroups> result(new GrantGroups()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getgrantgroupid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool GrantGroups::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void GrantGroups::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void GrantGroups::parseInsert(sqlite3* db)
{
	m_grantgroupid = sqlite3_last_insert_rowid(db);
}

void GrantGroups::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	m_defaultgrant = sqlite3_column_int64(stmt, 1);
	m_implies = sqlite3_column_int64(stmt, 2);
	m_newentry = false;
}

void GrantGroups::parseLookup(sqlite3_stmt* stmt)
{
	m_grantgroupid = sqlite3_column_int64(stmt, 0);
}

TablePtr GrantGroups::getTable() const
{
	return Tables::Get()->GRANTGROUPS;
}

value_type GrantGroups::getgrantgroupid() const
{
	return m_grantgroupid;
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
Permissions::Permissions() :
m_fkAccounts(),
m_grant(0),
m_newentry(true),
m_dirty(false)
{

}

Permissions::~Permissions()
{

}

Permissions* Permissions::bykey(value_type fkAccounts, value_type fkGrantGroups)
{
	Permissions* result = new Permissions();
	result->m_fkAccounts = fkAccounts;
	result->m_fkGrantGroups = fkGrantGroups;
	SqliteMgr::Get()->doSelect(result);
	return result;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Permissions::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Permissions::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_fkAccounts);
	sqlite3_bind_int64(stmt, 2, m_fkGrantGroups);
}

void Permissions::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_grant);
	sqlite3_bind_int64(stmt, 2, m_fkAccounts);
	sqlite3_bind_int64(stmt, 3, m_fkGrantGroups);
}

void Permissions::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void Permissions::parseInsert(sqlite3* db)
{
	// Do nothing
}

void Permissions::parseSelect(sqlite3_stmt* stmt)
{
	m_grant = sqlite3_column_int64(stmt, 0);
	m_newentry = false;
}

void Permissions::parseLookup(sqlite3_stmt* stmt)
{
	m_fkAccounts = sqlite3_column_int64(stmt, 0);
	m_fkGrantGroups = sqlite3_column_int64(stmt, 1);
}

TablePtr Permissions::getTable() const
{
	return Tables::Get()->PERMISSIONS;
}

value_type Permissions::getfkAccounts() const
{
	return m_fkAccounts;
}

value_type Permissions::getfkGrantGroups() const
{
	return m_fkGrantGroups;
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
Races::Races() :
m_raceid(),
m_name(),
m_newentry(true),
m_dirty(false)
{

}

Races::~Races()
{

}

Races* Races::bykey(value_type raceid)
{
	Races* result = new Races();
	result->m_raceid = raceid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Races* Races::byname(const std::string& value)
{
	Races* result = new Races();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Races::lookupname(const std::string& value)
{
	SmartPtr<Races> result(new Races()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getraceid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Races::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Races::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Races::parseInsert(sqlite3* db)
{
	m_raceid = sqlite3_last_insert_rowid(db);
}

void Races::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	m_newentry = false;
}

void Races::parseLookup(sqlite3_stmt* stmt)
{
	m_raceid = sqlite3_column_int64(stmt, 0);
}

TablePtr Races::getTable() const
{
	return Tables::Get()->RACES;
}

value_type Races::getraceid() const
{
	return m_raceid;
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
Rooms::Rooms() :
m_roomid(),
m_name(),
m_description(),
m_fkAreas(0),
m_fkSectors(0),
m_width(0),
m_length(0),
m_height(0),
m_newentry(true),
m_dirty(false)
{

}

Rooms::~Rooms()
{

}

Rooms* Rooms::bykey(value_type roomid)
{
	Rooms* result = new Rooms();
	result->m_roomid = roomid;
	SqliteMgr::Get()->doSelect(result);
	return result;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Rooms::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Rooms::bindKeys(sqlite3_stmt* stmt) const
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

void Rooms::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void Rooms::parseInsert(sqlite3* db)
{
	m_roomid = sqlite3_last_insert_rowid(db);
}

void Rooms::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_description = std::string((const char *)text);
	m_fkAreas = sqlite3_column_int64(stmt, 2);
	m_fkSectors = sqlite3_column_int64(stmt, 3);
	m_width = sqlite3_column_int64(stmt, 4);
	m_length = sqlite3_column_int64(stmt, 5);
	m_height = sqlite3_column_int64(stmt, 6);
	m_newentry = false;
}

void Rooms::parseLookup(sqlite3_stmt* stmt)
{
	m_roomid = sqlite3_column_int64(stmt, 0);
}

TablePtr Rooms::getTable() const
{
	return Tables::Get()->ROOMS;
}

value_type Rooms::getroomid() const
{
	return m_roomid;
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
Sectors::Sectors() :
m_sectorid(),
m_name(),
m_symbol(),
m_movecost(0),
m_water(0),
m_newentry(true),
m_dirty(false)
{

}

Sectors::~Sectors()
{

}

Sectors* Sectors::bykey(value_type sectorid)
{
	Sectors* result = new Sectors();
	result->m_sectorid = sectorid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Sectors* Sectors::byname(const std::string& value)
{
	Sectors* result = new Sectors();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Sectors::lookupname(const std::string& value)
{
	SmartPtr<Sectors> result(new Sectors()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getsectorid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Sectors::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Sectors::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Sectors::parseInsert(sqlite3* db)
{
	m_sectorid = sqlite3_last_insert_rowid(db);
}

void Sectors::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_symbol = std::string((const char *)text);
	m_movecost = sqlite3_column_int64(stmt, 2);
	m_water = sqlite3_column_int64(stmt, 3);
	m_newentry = false;
}

void Sectors::parseLookup(sqlite3_stmt* stmt)
{
	m_sectorid = sqlite3_column_int64(stmt, 0);
}

TablePtr Sectors::getTable() const
{
	return Tables::Get()->SECTORS;
}

value_type Sectors::getsectorid() const
{
	return m_sectorid;
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
Skills::Skills() :
m_skillid(),
m_name(),
m_fkBranches(0),
m_newentry(true),
m_dirty(false)
{

}

Skills::~Skills()
{

}

Skills* Skills::bykey(value_type skillid)
{
	Skills* result = new Skills();
	result->m_skillid = skillid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Skills* Skills::byname(const std::string& value)
{
	Skills* result = new Skills();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Skills::lookupname(const std::string& value)
{
	SmartPtr<Skills> result(new Skills()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getskillid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Skills::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Skills::bindKeys(sqlite3_stmt* stmt) const
{
	sqlite3_bind_int64(stmt, 1, m_skillid);
}

void Skills::bindUpdate(sqlite3_stmt* stmt) const
{
	sqlite3_bind_text(stmt, 1, m_name.c_str(), m_name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 2, m_fkBranches);
	sqlite3_bind_int64(stmt, 3, m_skillid);
}

void Skills::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Skills::parseInsert(sqlite3* db)
{
	m_skillid = sqlite3_last_insert_rowid(db);
}

void Skills::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	m_fkBranches = sqlite3_column_int64(stmt, 1);
	m_newentry = false;
}

void Skills::parseLookup(sqlite3_stmt* stmt)
{
	m_skillid = sqlite3_column_int64(stmt, 0);
}

TablePtr Skills::getTable() const
{
	return Tables::Get()->SKILLS;
}

value_type Skills::getskillid() const
{
	return m_skillid;
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
Stats::Stats() :
m_statid(),
m_name(),
m_shortname(),
m_newentry(true),
m_dirty(false)
{

}

Stats::~Stats()
{

}

Stats* Stats::bykey(value_type statid)
{
	Stats* result = new Stats();
	result->m_statid = statid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Stats* Stats::byname(const std::string& value)
{
	Stats* result = new Stats();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

Stats* Stats::byshortname(const std::string& value)
{
	Stats* result = new Stats();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"shortname");
	return result;
}

value_type Stats::lookupname(const std::string& value)
{
	SmartPtr<Stats> result(new Stats()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->getstatid();
	} catch(Bindable* result) {	}

	return key;
}

value_type Stats::lookupshortname(const std::string& value)
{
	SmartPtr<Stats> result(new Stats()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "shortname");
		key = result->getstatid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Stats::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Stats::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Stats::parseInsert(sqlite3* db)
{
	m_statid = sqlite3_last_insert_rowid(db);
}

void Stats::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	text = sqlite3_column_text(stmt, 1);
	if(text != 0)
		m_shortname = std::string((const char *)text);
	m_newentry = false;
}

void Stats::parseLookup(sqlite3_stmt* stmt)
{
	m_statid = sqlite3_column_int64(stmt, 0);
}

TablePtr Stats::getTable() const
{
	return Tables::Get()->STATS;
}

value_type Stats::getstatid() const
{
	return m_statid;
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
Trees::Trees() :
m_treeid(),
m_name(),
m_fkClusters(0),
m_fkStatsPrimary(0),
m_fkStatsSecondary(0),
m_newentry(true),
m_dirty(false)
{

}

Trees::~Trees()
{

}

Trees* Trees::bykey(value_type treeid)
{
	Trees* result = new Trees();
	result->m_treeid = treeid;
	SqliteMgr::Get()->doSelect(result);
	return result;
}

Trees* Trees::byname(const std::string& value)
{
	Trees* result = new Trees();
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result,"name");
	return result;
}

value_type Trees::lookupname(const std::string& value)
{
	SmartPtr<Trees> result(new Trees()); // will handle deletion of ptr
	result->m_lookupvalue = value;
	value_type key = 0;
	try {
		SqliteMgr::Get()->doLookup(result.get(), "name");
		key = result->gettreeid();
	} catch(Bindable* result) {	}

	return key;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Trees::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void Trees::bindKeys(sqlite3_stmt* stmt) const
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

void Trees::bindLookup(sqlite3_stmt* stmt) const
{
	int rc;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SqliteMgr::bindLookup(), rc != SQLITE_OK.");
}

void Trees::parseInsert(sqlite3* db)
{
	m_treeid = sqlite3_last_insert_rowid(db);
}

void Trees::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_name = std::string((const char *)text);
	m_fkClusters = sqlite3_column_int64(stmt, 1);
	m_fkStatsPrimary = sqlite3_column_int64(stmt, 2);
	m_fkStatsSecondary = sqlite3_column_int64(stmt, 3);
	m_newentry = false;
}

void Trees::parseLookup(sqlite3_stmt* stmt)
{
	m_treeid = sqlite3_column_int64(stmt, 0);
}

TablePtr Trees::getTable() const
{
	return Tables::Get()->TREES;
}

value_type Trees::gettreeid() const
{
	return m_treeid;
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
Version::Version() :
m_versionid(),
m_versiontext(),
m_major(0),
m_minor(0),
m_micro(0),
m_newentry(true),
m_dirty(false)
{

}

Version::~Version()
{

}

Version* Version::bykey(value_type versionid)
{
	Version* result = new Version();
	result->m_versionid = versionid;
	SqliteMgr::Get()->doSelect(result);
	return result;
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

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		getTable()->modify();
		m_dirty = false;
	}
}

bool Version::exists()
{
	if(m_newentry)
		return false;

	return true;
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

void Version::bindLookup(sqlite3_stmt* stmt) const
{
	// Do nothing
}

void Version::parseInsert(sqlite3* db)
{
	m_versionid = sqlite3_last_insert_rowid(db);
}

void Version::parseSelect(sqlite3_stmt* stmt)
{
	const unsigned char * text;
	text = sqlite3_column_text(stmt, 0);
	if(text != 0)
		m_versiontext = std::string((const char *)text);
	m_major = sqlite3_column_int64(stmt, 1);
	m_minor = sqlite3_column_int64(stmt, 2);
	m_micro = sqlite3_column_int64(stmt, 3);
	m_newentry = false;
}

void Version::parseLookup(sqlite3_stmt* stmt)
{
	m_versionid = sqlite3_column_int64(stmt, 0);
}

TablePtr Version::getTable() const
{
	return Tables::Get()->VERSION;
}

value_type Version::getversionid() const
{
	return m_versionid;
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

