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

#include <sqlite3.h>
#include <Database.h>
#include <Bindable.h>

class Table;
class Statements;
class Actor;

typedef std::map<Table*, Statements*>  TableStatements;
typedef unsigned long value_type;	

class SqliteMgr
{
	public:
		static SqliteMgr* Get();
		static void Free();
	
		void doInsert(Bindable* bindable);
		void doErase(Bindable* bindable);
		void doUpdate(Bindable* bindable);
		void doSelect(Bindable* bindable);
		void doLookup(Bindable* bindable, const std::string& field);
		void doForEach(const Table* table, Actor* act);
	
	private:
		Database* m_db;
		Database::OPENDB* m_odb;
		const char* m_leftover;
		
		TableStatements m_statements;
		
		Statements* getStatements(const Table* table);
		sqlite3_stmt* getInsertStmt(const Table* table);
		sqlite3_stmt* getEraseStmt(const Table* table);
		sqlite3_stmt* getUpdateStmt(const Table* table);
		sqlite3_stmt* getSelectStmt(const Table* table);
		sqlite3_stmt* getLookupStmt(const Table* table, const std::string& field);
		sqlite3_stmt* getForEachStmt(const Table* table);		
	
		SqliteMgr();
		~SqliteMgr();
		bool doStatement(sqlite3_stmt* stmt);
		static SqliteMgr* m_instance;
};
