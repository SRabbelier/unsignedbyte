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
#include "Actor.h"
#include "Statements.h"
#include "Field.h"

SqliteMgr::SqliteMgr()
{	
	m_db = DatabaseMgr::Get()->DB();
	m_odb = m_db->grabdb();
	
	std::string sql = "COMMIT;";
	
	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &m_commitStmt, &m_leftover);
	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::SqliteMgr(), Could not prepare save query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getForEachStmt(), Leftover from save query is not NULL!");
}

SqliteMgr::~SqliteMgr()
{
	m_db->freedb(m_odb);
	sqlite3_finalize(m_commitStmt);
}

void SqliteMgr::doInsert(Bindable* bindable)
{
	Table* table = bindable->getTable().get();
	sqlite3_stmt* insert = getInsertStmt(table);
	sqlite3_reset(insert);
	
	if(!table->hasSinglularPrimaryKey())
		bindable->bindKeys(insert);	
		
	doStatement(insert);
	bindable->parseInsert(m_odb->db);
	
	commit();
}

void SqliteMgr::doErase(Bindable* bindable)
{
	Table* table = bindable->getTable().get();
	sqlite3_stmt* erase = getEraseStmt(table);
	sqlite3_reset(erase);
	
	bindable->bindKeys(erase);
	doStatement(erase);	
	
	commit();
}

void SqliteMgr::doUpdate(Bindable* bindable)
{
	Table* table = bindable->getTable().get();
	sqlite3_stmt* update = getUpdateStmt(table);
	sqlite3_reset(update);
	
	bindable->bindUpdate(update);
	doStatement(update);
	
	commit();
}

void SqliteMgr::doSelect(Bindable* bindable)
{
	Table* table = bindable->getTable().get();
	sqlite3_stmt* select = getSelectStmt(table);
	sqlite3_reset(select);
	
	bindable->bindKeys(select);
	bool row = doStatement(select);
	if(row)
		bindable->parseSelect(select);
	else
		throw std::runtime_error("SqliteMgr::doSelect(), no row.");
}

void SqliteMgr::doLookup(Bindable* bindable, const std::string& field)
{
	Table* table = bindable->getTable().get();
	sqlite3_stmt* lookup = getLookupStmt(table, field);
	sqlite3_reset(lookup);
	
	bindable->bindLookup(lookup);
	bool row = doStatement(lookup);
	if(row)
	{
		bindable->parseLookup(lookup);
		doSelect(bindable);
	}
	else
		throw bindable;
}

void SqliteMgr::doForEach(Table* table, Actor& act)
{
	sqlite3_stmt* forEach = getForEachStmt(table);
	sqlite3_reset(forEach);
	
	bool good = true;
	for(int i = 0; good; i++)
	{
		good = doStatement(forEach);
		act.parseRow(forEach, table);
	}
}

void SqliteMgr::commit()
{
	sqlite3_reset(m_commitStmt);
	doStatement(m_commitStmt);
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

StatementsPtr SqliteMgr::getStatements(Table* table)
{
	StatementsPtr statements = m_statements[table];
	if(statements)
		return statements;
	
	statements = StatementsPtr(new Statements());
	
	m_statements[table] = statements;
	return statements;
}

sqlite3_stmt* SqliteMgr::getInsertStmt(Table* table)
{
	StatementsPtr statements = getStatements(table);
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
	sql.append(") VALUES(");
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
	StatementsPtr statements = getStatements(table);
	sqlite3_stmt* statement = statements->getErase();
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("DELETE ");
	sql.append(table->tableName());
	sql.append(" WHERE ");
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
	StatementsPtr statements = getStatements(table);
	sqlite3_stmt* statement = statements->getUpdate();
	if(statement)
		return statement;

	std::string sql;
	sql.append("UPDATE ");
	sql.append(table->tableName());
	sql.append(" SET ");
	for(Fields::const_iterator it = table->begin(); it != table->end(); it++)
	{
		if(it != table->begin())
			sql.append(", ");

		sql.append((*it)->getName());
		sql.append("=?");
	}
	sql.append(" WHERE ");
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
	StatementsPtr statements = getStatements(table);
	sqlite3_stmt* statement = statements->getSelect();
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("SELECT ");
	for(Fields::const_iterator it = table->begin(); it != table->end(); it++)
	{
		if(it != table->begin())
			sql.append(", ");

		sql.append((*it)->getName());
	}
	 
	sql.append(" FROM ");
	sql.append(table->tableName());
	sql.append(" WHERE ");
	
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
	StatementsPtr statements = getStatements(table);
	sqlite3_stmt* statement = statements->getLookup(field);
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("SELECT ");
	for(TableMap::const_iterator it = table->keybegin(); it != table->keyend(); it++)
	{
		if(it != table->keybegin())
			sql.append(", ");

		sql.append(it->first);
	}
	sql.append(" FROM ");
	sql.append(table->tableName());
	sql.append(" WHERE ");
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

sqlite3_stmt* SqliteMgr::getForEachStmt(Table* table)
{
	StatementsPtr statements = getStatements(table);
	sqlite3_stmt* statement = statements->getForEach();
	if(statement)
		return statement;
		
	std::string sql;
	sql.append("SELECT ");
	bool comspace = false;
	for(TableMap::const_iterator it = table->keybegin(); it != table->keyend(); it++)
	{
		if(comspace)
			sql.append(", ");

		sql.append(it->first);
		comspace = true;
	}
	for(Fields::const_iterator it = table->begin(); it != table->end(); it++)
	{
		if(comspace)
			sql.append(", ");

		sql.append((*it)->getName());
		comspace = true;
	}
	 
	sql.append(" FROM ");
	sql.append(table->tableName());
	sql.append(";");
	
	Global::Get()->logf("SQL is: %s\n", sql.c_str());
		
	int errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &statement, &m_leftover);

	if(errorcode != SQLITE_OK)
		throw std::runtime_error("SqliteMgr::getForEachStmt(), Could not prepare forEach query!");
		
	if(m_leftover != NULL && strlen(m_leftover) > 0)
		throw std::runtime_error("SqliteMgr::getForEachStmt(), Leftover from forEach is not NULL!");
		
	statements->setForEach(statement);
	return statement;
}
