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
 
#include <iostream>
#include "SavableHeaders.h"

#include "Database.h"
#include "Query.h"
#include "IError.h"
#include "StderrLog.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "SqliteMgr.h"

#include "Initializer.h"

const int MAXSIZE = (1<<16);
char m_workspace[MAXSIZE];

void exitfunc()
{
	printf("Freeing global...\n");
	Global::Free();
	printf("Freeing tables...\n");
	Tables::Free();
	printf("Freeing sqlitemgr...\n");
	SqliteMgr::Free();
	printf("Exiting...\n");
	// std::cin.get();
	return;
}

int main()
{	
	atexit(exitfunc);
	
	db::TableImpls::Get();
	
	printf("%s database initializer for db v%s.\n", game::vname, game::vstring);
	std::string dbname = game::vname;
	dbname.append(".db");

	printf("Opening or creating '%s'...\n", dbname.c_str());
	DatabaseMgr::Initialize(dbname);
	
	Initializer init(DatabaseMgr::Get()->DB());
	
	printf("Checking if database exists...\n");
	bool initialized = false;
	bool succes;
	succes = init.DatabasePopulated();
	if(!succes)
	{
		printf("Database does not exist...\n");
		printf("Creating tables...\n");
		init.InitTables();
		initialized = true;
	}
	
	printf("checking if database version matches...\n");
	succes = initialized || init.VerifyDatabaseVersion();
	if(!succes)
	{
		printf("Database version does not match!\n");
		printf("(Move the existing database if you wish to create a fresh copy)\n");
		return 1;
	}

	printf("Database is of most recent version!\n");	
	
	printf("Checking if tables match...\n");
	succes = init.VerifyTables();
	if(!succes)
	{
		printf("Database tables are not up to date!\n");
		printf("(Move the existing database if you wish to create a fresh copy)\n");
		return 1;
	}

	printf("Initializing database...\n");
	init.InitDatabase();

	printf("Initializing colours...\n");
	init.InitColours();

	return 0;
}
