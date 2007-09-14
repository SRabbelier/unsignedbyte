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

#include <stdexcept>

#include "SqliteMgr.h"
#include "DatabaseMgr.h"
#include "Bindable.h"
#include "Statements.h"
#include "Field.h"

SqliteMgr* SqliteMgr::m_instance = NULL;

SqliteMgr::SqliteMgr()
{	
	m_db = DatabaseMgr::Get()->DB();
	m_odb = m_db->grabdb();
}

SqliteMgr::~SqliteMgr()
{
	for(TableStatements::iterator it = m_statements.begin(); it != m_statements.end(); it++)
	{
		delete it->second;
	}
	
	m_db->freedb(m_odb);
}

SqliteMgr* SqliteMgr::Get()
{
	if(!m_instance)
		m_instance = new SqliteMgr();
		
	return m_instance;
}

void SqliteMgr::Free()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = 0;
	}
}

void SqliteMgr::doInsert(Bindable* bindable)
{
	Table* table = bindable->getTable();
	sqlite3_stmt* insert = getInsertStmt(table);
	
	bindable->bindKeys(insert);	
	doStatement(insert);
	bindable->parseInsert(m_odb->db);
}

void SqliteMgr::doErase(Bindable* bindable)
{
	Table* table = bindable->getTable();
	sqlite3_stmt* erase = getEraseStmt(table);
	
	bindable->bindKeys(erase);
	doStatement(erase);	
}

void SqliteMgr::doUpdate(Bindable* bindable)
{
	Table* table = bindable->getTable();
	sqlite3_stmt* update = getUpdateStmt(table);
	
	bindable->bindUpdate(update);
	doStatement(update);
}

void SqliteMgr::doSelect(Bindable* bindable)
{
	Table* table = bindable->getTable();
	sqlite3_stmt* select = getSelectStmt(table);
	
	bindable->bindKeys(select);
	doStatement(select);
	bindable->parseSelect(select);
}

void SqliteMgr::doLookup(Bindable* bindable, const std::string& field)
{
	Table* table = bindable->getTable();
	sqlite3_stmt* lookup = getLookupStmt(table, field);
	
	bindable->bindLookup(lookup);
	bool row = doStatement(lookup);
	if(row)
		bindable->parseSelect(lookup);
	else
		throw new std::runtime_error("SqliteMgr::doLookup(), no row returned.");
}

void SqliteMgr::doList(Table* table)
{
	sqlite3_stmt* list = getListStmt(table);
	bool good = true;
	for(int i = 0; good; i++)
	{
		printf("%d\n", i);
		good = doStatement(list);
		table->parseList(list);
	}
}

bool SqliteMgr::doStatement(sqlite3_stmt* stmt)
{
	int rc = sqlite3_step(stmt);
	
	switch (rc)
	{
	default:
		throw new std::runtime_error("SqliteMgr::doUpdate(), Unknown error code!");
	case SQLITE_BUSY:
		throw new std::runtime_error("SqliteMgr::doUpdate(), The database is busy.");
	case SQLITE_ERROR:
		throw new std::runtime_error(sqlite3_errmsg(m_odb->db));
	case SQLITE_MISUSE:
		throw new std::runtime_error("SqliteMgr::doUpdate(), Database misuse.");
		
	case SQLITE_DONE:
		return false;

	case SQLITE_ROW:
		return true;
	}
}

Statements* SqliteMgr::getStatements(Table* table)
{
	Statements* statements = m_statements[table];
	if(statements)
		return statements;
	
	statements = new Statements();
	
	m_statements[table] = statements;
	return statements;
}

sqlite3_stmt* SqliteMgr::getInsertStmt(Table* table)
{
	Statements* statements = getStatements(table);
	sqlite3_stmt* statement = statements->getInsert();
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("INSERT INTO ");
	sql.append(table->tableName());
	sql.append(" (");
	for(TableMap::const_iterator it = table->keybegin(); it != table->keyend(); it++)
	{
		   if(it != table->keybegin())
				   sql.append(", ");

		   sql.append(it->first);
	}
	sql.append(") values(");
	for(TableMap::const_iterator it = table->keybegin(); it != table->keyend(); it++)
	{
		   if(it != table->keybegin())
				   sql.append(", ");

		   sql.append("NULL");
	}
	sql.append(");");
	
	Global::Get()->logf("SQL is: %s\n", sql.c_str());
	
	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &statement, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::getInsertStmt(), Could not prepare insertion query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getInsertStmt(), Leftover from insertion is not NULL!");
		
	statements->setInsert(statement);
	return statement;
}

sqlite3_stmt* SqliteMgr::getEraseStmt(Table* table)
{
	Statements* statements = getStatements(table);
	sqlite3_stmt* statement = statements->getErase();
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("DELETE ");
	sql.append(table->tableName());
	sql.append(" where ");
	for(TableMap::const_iterator it = table->keybegin(); it != table->keyend(); it++)
	{
		if(it != table->keybegin())
			sql.append(", ");

		sql.append(it->first);
		sql.append("=?");
	}
	sql.append(";");
	
	Global::Get()->logf("SQL is: %s\n", sql.c_str());
	
	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &statement, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::getInsertStmt(), Could not prepare insertion query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getInsertStmt(), Leftover from insertion is not NULL!");
		
	
	statements->setErase(statement);
	return statement;
}

sqlite3_stmt* SqliteMgr::getUpdateStmt(Table* table)
{
	Statements* statements = getStatements(table);
	sqlite3_stmt* statement = statements->getUpdate();
	if(statement)
		return statement;

	std::string sql;
	sql.append("Update ");
	sql.append(table->tableName());
	sql.append(" set ");
	for(Fields::const_iterator it = table->begin(); it != table->end(); it++)
	{
		if(it != table->begin())
			sql.append(", ");

		sql.append((*it)->getName());
		sql.append("=?");
	}
	sql.append(" where ");
	for(TableMap::const_iterator it = table->keybegin(); it != table->keyend(); it++)
	{
		if(it != table->keybegin())
			sql.append(", ");

		sql.append(it->first);
		sql.append("=?");
	}	
	sql.append(";");
	
	Global::Get()->logf("SQL is: %s\n", sql.c_str());

	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &statement, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::getInsertStmt(), Could not prepare insertion query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getInsertStmt(), Leftover from insertion is not NULL!");

		
	statements->setUpdate(statement);
	return statement;
}

sqlite3_stmt* SqliteMgr::getSelectStmt(Table* table)
{
	Statements* statements = getStatements(table);
	sqlite3_stmt* statement = statements->getSelect();
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("Select ");
	for(Fields::const_iterator it = table->begin(); it != table->end(); it++)
	{
		if(it != table->begin())
			sql.append(", ");

		sql.append((*it)->getName());
	}
	 
	sql.append(" from ");
	sql.append(table->tableName());
	sql.append(" where ");
	
	for(TableMap::const_iterator it = table->keybegin(); it != table->keyend(); it++)
	{
		if(it != table->keybegin())
			sql.append(", ");

		sql.append(it->first);
		sql.append("=?");
	}
	sql.append(";");
	
	Global::Get()->logf("SQL is: %s\n", sql.c_str());
		
	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &statement, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::getSelectStmt(), Could not prepare selection query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getSelectStmt(), Leftover from selection is not NULL!");
		
	statements->setSelect(statement);
	return statement;
}

sqlite3_stmt* SqliteMgr::getLookupStmt(Table* table, const std::string& field)
{
	Statements* statements = getStatements(table);
	sqlite3_stmt* statement = statements->getLookup(field);
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("Select ");
	for(Fields::const_iterator it = table->begin(); it != table->end(); it++)
	{
		if(it != table->begin())
			sql.append(", ");

		sql.append((*it)->getName());
	}
	 
	sql.append(" from ");
	sql.append(table->tableName());
	sql.append(" where ");
	sql.append(field);
	sql.append("=?");
	sql.append(";");
	
	Global::Get()->logf("SQL is: %s\n", sql.c_str());
		
	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &statement, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::getLookupStmt(), Could not prepare lookup query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getLookupStmt(), Leftover from lookup is not NULL!");
		
	statements->setLookup(field, statement);
	return statement;
}

sqlite3_stmt* SqliteMgr::getListStmt(Table* table)
{
	Statements* statements = getStatements(table);
	sqlite3_stmt* statement = statements->getList();
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("Select ");
	for(Fields::const_iterator it = table->begin(); it != table->end(); it++)
	{
		if(it != table->begin())
			sql.append(", ");

		sql.append((*it)->getName());
	}
	 
	sql.append(" from ");
	sql.append(table->tableName());
	sql.append(";");
	
	Global::Get()->logf("SQL is: %s\n", sql.c_str());
		
	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &statement, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::getSelectStmt(), Could not prepare list query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getSelectStmt(), Leftover from list is not NULL!");
		
	statements->setList(statement);
	return statement;
}
