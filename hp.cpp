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
m_accountid(),
m_db(db),
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
	value_type result = AccountsMgr::Get(m_db)->doInsert();
}

void Accounts::update()
{
	AccountsMgr::Get(m_db)->doUpdate(m_name, m_password, m_accountid);
}

void Accounts::erase()
{
	AccountsMgr::Get(m_db)->doErase(m_accountid);
}

void Accounts::save()
{
	if(m_newentry)
		insert();
	else
		update();
}

/**
 * Begin of implementation
 * private class AccountsMgr
 **/

Accounts::AccountsMgr* Accounts::AccountsMgr::Get(Database* db)
{
	if(!m_instance)
		m_instance = new AccountsMgr(db);
	else
		m_instance->setDatabase(db);
		
	return m_instance;
}

void Accounts::AccountsMgr::Free()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = 0;
	}
}

value_type Accounts::AccountsMgr::doInsert()
{
	int rc = sqlite3_step(m_insert);
	switch (rc)
	{
	default:
		throw new std::runtime_error("AccountsMgr::doInsert(), Unknown error code!");
	case SQLITE_BUSY:
		throw new std::runtime_error("AccountsMgr::doInsert(), The database is busy.");
	case SQLITE_ERROR:
		throw new std::runtime_error(sqlite3_errmsg(m_odb->db));
	case SQLITE_MISUSE:
		throw new std::runtime_error("AccountsMgr::doInsert(), Database misuse.");
		
	case SQLITE_DONE:
	case SQLITE_ROW:
		break;
	}
	
	value_type result = sqlite3_last_insert_rowid(m_odb->db);
	sqlite3_reset(m_insert);
	
	return result;
}

void Accounts::AccountsMgr::doErase(value_type account)
{
	sqlite3_bind_int64(m_erase, 1, account);
	
	int rc = sqlite3_step(m_erase);
	
	switch (rc)
	{
	default:
		throw new std::runtime_error("AccountsMgr::doErase(), Unknown error code!");
	case SQLITE_BUSY:
		throw new std::runtime_error("AccountsMgr::doErase(), The database is busy.");
	case SQLITE_ERROR:
		throw new std::runtime_error(sqlite3_errmsg(m_odb->db));
	case SQLITE_MISUSE:
		throw new std::runtime_error("AccountsMgr::doErase(), Database misuse.");
		
	case SQLITE_DONE:
	case SQLITE_ROW:
		break;
	}
	
	sqlite3_reset(m_erase);
	sqlite3_clear_bindings(m_erase);
}

void Accounts::AccountsMgr::doUpdate(const std::string& name, const std::string& password, value_type account)
{
	sqlite3_bind_text(m_update, 1, name.c_str(), name.size(), SQLITE_TRANSIENT);
	sqlite3_bind_text(m_update, 2, password.c_str(), password.size(), SQLITE_TRANSIENT);
	sqlite3_bind_int64(m_update, 3, account);
	
	int rc = sqlite3_step(m_update);
	
	switch (rc)
	{
	default:
		throw new std::runtime_error("AccountsMgr::doUpdate(), Unknown error code!");
	case SQLITE_BUSY:
		throw new std::runtime_error("AccountsMgr::doUpdate(), The database is busy.");
	case SQLITE_ERROR:
		throw new std::runtime_error(sqlite3_errmsg(m_odb->db));
	case SQLITE_MISUSE:
		throw new std::runtime_error("AccountsMgr::doUpdate(), Database misuse.");
		
	case SQLITE_DONE:
	case SQLITE_ROW:
		break;
	}
	
	sqlite3_reset(m_update);
	sqlite3_clear_bindings(m_update);
}

Accounts::AccountsMgr::AccountsMgr(Database* db) :
m_db(db)
{	
	m_odb = m_db->grabdb();
	std::string sql; 
	int errorcode;
	
	// Insert query
	sql = "INSERT INTO Accounts (accountid) values(NULL);";
	errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &m_insert, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("AccountsMgr::AccountsMgr(), Could not prepare insertion query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("AccountsMgr::AccountsMgr(), Leftover from insertion is not NULL!");
	
	// Erase query
	sql = "DELETE Accounts where accountid=?;";
	errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &m_erase, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("AccountsMgr::AccountsMgr(), Could not prepare erasure query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("AccountsMgr::AccountsMgr(), Leftover from erasure is not NULL!");
			
	// Update query
	sql = "Update Accounts set name=?, password=? where accountid=?;";
	errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &m_update, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("AccountsMgr::AccountsMgr(), Could not prepare update query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("AccountsMgr::AccountsMgr(), Leftover from update is not NULL!");
}

Accounts::AccountsMgr::~AccountsMgr()
{
	sqlite3_finalize(m_insert);
	sqlite3_finalize(m_erase);
	sqlite3_finalize(m_update);
	
	m_db->freedb(m_odb);
}

/**
 * End of implementation
 * private class AccountsMgr
 **/

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
m_areaid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Areas (areaid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	value_type result = sqlite3_last_insert_rowid(db->db);
	return result;
}

void Areas::update()
{
	return;
}

void Areas::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Areas::erase()
{
	return;
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
m_branchid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Branches (branchid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Branches::update()
{
	return;
}

void Branches::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Branches::erase()
{
	return;
}


/**
 * End of implementation
 * class Branches
 **/


/**
 * Begin of implementation
 * class AccountCharacter
 **/

// Ctors
AccountCharacter::AccountCharacter(Database* db) :
m_db(db),
m_fkCharacters(0),
m_fkAccounts(0)
{

}

AccountCharacter::AccountCharacter(Database* db, value_type fkCharacters, value_type fkAccounts) :
m_db(db)
,
m_fkCharacters(fkCharacters),
m_fkAccounts(fkAccounts){

}

AccountCharacter::~AccountCharacter()
{

}

value_type AccountCharacter::insert()
{
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO AccountCharacter (fkCharacters,fkAccounts) values (NULL,NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void AccountCharacter::update()
{
	return;
}

void AccountCharacter::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void AccountCharacter::erase()
{
	return;
}


/**
 * End of implementation
 * class AccountCharacter
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
m_db(db)
,
m_fkCharacters(fkCharacters),
m_fkBranches(fkBranches){

}

CharacterBranch::~CharacterBranch()
{

}

value_type CharacterBranch::insert()
{
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO CharacterBranch (fkCharacters,fkBranches) values (NULL,NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void CharacterBranch::update()
{
	return;
}

void CharacterBranch::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterBranch::erase()
{
	return;
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
m_db(db)
,
m_fkCharacters(fkCharacters),
m_fkClusters(fkClusters){

}

CharacterCluster::~CharacterCluster()
{

}

value_type CharacterCluster::insert()
{
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO CharacterCluster (fkCharacters,fkClusters) values (NULL,NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void CharacterCluster::update()
{
	return;
}

void CharacterCluster::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterCluster::erase()
{
	return;
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
m_characterid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Characters (characterid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Characters::update()
{
	return;
}

void Characters::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Characters::erase()
{
	return;
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
m_db(db)
,
m_fkCharacters(fkCharacters),
m_fkBranches(fkBranches){

}

CharacterSkill::~CharacterSkill()
{

}

value_type CharacterSkill::insert()
{
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO CharacterSkill (fkCharacters,fkBranches) values (NULL,NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void CharacterSkill::update()
{
	return;
}

void CharacterSkill::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterSkill::erase()
{
	return;
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
m_db(db)
,
m_fkCharacters(fkCharacters),
m_fkStats(fkStats){

}

CharacterStat::~CharacterStat()
{

}

value_type CharacterStat::insert()
{
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO CharacterStat (fkCharacters,fkStats) values (NULL,NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void CharacterStat::update()
{
	return;
}

void CharacterStat::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterStat::erase()
{
	return;
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
m_db(db)
,
m_fkCharacters(fkCharacters),
m_fkTrees(fkTrees){

}

CharacterTree::~CharacterTree()
{

}

value_type CharacterTree::insert()
{
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO CharacterTree (fkCharacters,fkTrees) values (NULL,NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void CharacterTree::update()
{
	return;
}

void CharacterTree::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void CharacterTree::erase()
{
	return;
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
m_clusterid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Clusters (clusterid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Clusters::update()
{
	return;
}

void Clusters::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Clusters::erase()
{
	return;
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
m_colourid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Colours (colourid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Colours::update()
{
	return;
}

void Colours::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Colours::erase()
{
	return;
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
m_commandid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Commands (commandid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Commands::update()
{
	return;
}

void Commands::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Commands::erase()
{
	return;
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
m_exitid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Exits (exitid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Exits::update()
{
	return;
}

void Exits::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Exits::erase()
{
	return;
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
m_grantgroupid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO GrantGroups (grantgroupid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void GrantGroups::update()
{
	return;
}

void GrantGroups::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void GrantGroups::erase()
{
	return;
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
m_permissionid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Permissions (permissionid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Permissions::update()
{
	return;
}

void Permissions::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Permissions::erase()
{
	return;
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
m_raceid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Races (raceid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Races::update()
{
	return;
}

void Races::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Races::erase()
{
	return;
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
m_roomid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Rooms (roomid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Rooms::update()
{
	return;
}

void Rooms::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Rooms::erase()
{
	return;
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
m_sectorid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Sectors (sectorid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Sectors::update()
{
	return;
}

void Sectors::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Sectors::erase()
{
	return;
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
m_skillid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Skills (skillid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Skills::update()
{
	return;
}

void Skills::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Skills::erase()
{
	return;
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
m_statid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Stats (statid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Stats::update()
{
	return;
}

void Stats::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Stats::erase()
{
	return;
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
m_treeid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Trees (treeid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Trees::update()
{
	return;
}

void Trees::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Trees::erase()
{
	return;
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
m_versionid(),
m_db(db),
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
	sqlite3_stmt* res; // pointer to the result
	const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'

	Database::OPENDB* db = m_db->grabdb();

	if(db == NULL)
		throw std::runtime_error("insert(), Could not open database!\n");
	
	std::string sql = "INSERT INTO Version (versionid) values(NULL);";
	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);

	if(rc != SQLITE_OK)
		throw std::runtime_error("insert(), Could not prepare query!");

	if(leftover != NULL && strlen(leftover) > 0)
		throw std::runtime_error("insert(), Leftover is not NULL!");

	return sqlite3_last_insert_rowid(db->db);
}

void Version::update()
{
	return;
}

void Version::save()
{
	if(m_newentry)
		insert();
	else
		update();

	return;
}

void Version::erase()
{
	return;
}


/**
 * End of implementation
 * class Version
 **/

