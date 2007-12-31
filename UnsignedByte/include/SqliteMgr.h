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

#include <map>
#include <stdexcept>

#include <sqlite3.h>
#include <Database.h>
#include <Bindable.h>
#include <smart_ptr.h>
#include <singleton.h>

class Table;
class Statements;
class Actor;

typedef SmartPtr<Actor> ActorPtr;
typedef SmartPtr<Table> TablePtr;
typedef SmartPtr<Statements> StatementsPtr;

typedef std::map<Table*, StatementsPtr>  TableStatements;
typedef unsigned long value_type;

class RowNotFoundException : public std::runtime_error
{
	public:
		RowNotFoundException(const std::string& arg) : std::runtime_error(arg) { }
};

class SqliteMgr : public Singleton<SqliteMgr>
{
	public:
		void doInsert(Bindable* bindable);
		void doErase(Bindable* bindable);
		void doUpdate(Bindable* bindable);
		void doSelect(Bindable* bindable);
		void doLookup(Bindable* bindable, const std::string& field);
		void doForEach(Table* table, Actor& act);
	
	private:
		Database* m_db;
		Database::OPENDB* m_odb;
		const char* m_leftover;
		
		sqlite3_stmt* m_commitStmt;
		
		TableStatements m_statements;
		
		void commit();
		StatementsPtr getStatements(Table* table);
		sqlite3_stmt* getInsertStmt(Table* table);
		sqlite3_stmt* getEraseStmt(Table* table);
		sqlite3_stmt* getUpdateStmt(Table* table);
		sqlite3_stmt* getSelectStmt(Table* table);
		sqlite3_stmt* getLookupStmt(Table* table, const std::string& field);
		sqlite3_stmt* getForEachStmt(Table* table);		
		
		friend class Singleton<SqliteMgr>;
		SqliteMgr();
		~SqliteMgr();
		bool doStatement(sqlite3_stmt* stmt);
};
