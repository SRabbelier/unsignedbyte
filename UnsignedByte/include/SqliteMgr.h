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

#include "Types.h"
#include <Database.h>

class Statements;
typedef SmartPtr<Statements> StatementsPtr;

class StatementStrings;
typedef SmartPtr<StatementStrings> StatementStringsPtr;

typedef std::map<TableImpl*, StatementsPtr>  TableStatements;
typedef std::map<TableImpl*, StatementStringsPtr>  TableStatementStrings;

class SqliteMgr : public Singleton<SqliteMgr>
{
	public:
		void doInsert(SavableManager* bindable);
		void doErase(SavableManager* bindable);
		void doUpdate(SavableManager* bindable);
		void doSelect(SavableManagerPtr bindable);
		void doLookup(SavableManagerPtr bindable, FieldPtr field);
		void doForEach(TableImpl* table, Actor& act);
		
		std::string tableQuery(TableDefPtr table) const;
		std::string creationQuery(TableDefPtr table, bool verify = false) const;
		std::string creationString(FieldDefPtr table) const;
	
	private:
		Database* m_db;
		Database::OPENDB* m_odb;
		const char* m_leftover;
		
		TableStatements m_statements;
		TableStatementStrings m_statementstrings;
		
		void commit(TableImpl* table);
		
		StatementsPtr getStatements(TableImpl* table);
		StatementStringsPtr getStatementStrings(TableImpl* table);
		
		sqlite3_stmt* getInsertStmt(TableImpl* table);
		sqlite3_stmt* getEraseStmt(TableImpl* table);
		sqlite3_stmt* getUpdateStmt(TableImpl* table);
		sqlite3_stmt* getSelectStmt(TableImpl* table);
		sqlite3_stmt* getLookupStmt(TableImpl* table, FieldPtr field);
		sqlite3_stmt* getForEachStmt(TableImpl* table);		
		
		friend class Singleton<SqliteMgr>;
		SqliteMgr();
		~SqliteMgr();
		bool doStatement(sqlite3_stmt* stmt);
};
