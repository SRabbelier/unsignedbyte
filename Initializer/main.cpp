#include <string>
#include <vector>
#include <iostream>

#include "sqlite3.h"
#include "Database.h"
#include "Query.h"
#include "IError.h"
#include "StderrLog.h"
#include "Global.h"
#include "Tables.h"

#include "Initializer.h"
#include "Generator.h"

const int MAXSIZE = (1<<16);
char m_workspace[MAXSIZE];

void exitfunc()
{
	printf("Freeing global...\n");
	Global::Free();
	printf("Freeing tables...\n");
	Tables::Free();
	printf("Exiting...\n");
	// std::cin.get();
	return;
}

int maingenerator()
{
	printf("Generating DAL...\n");
	Generator gen(game::vname);
	
	bool succes;
	succes = gen.GenerateDAL();
	if(!succes)
	{
		printf("Could not generate DAL!\n");
		std::cin.get();
		return 0;
	}
	
	return 0;
}
	
int maininitializer()
{	
	printf("%s database initializer for db v%s.\n", game::vname, game::vstring);
	std::string dbname = game::vname;
	dbname.append(".db");

	printf("Opening or creating '%s'...\n", dbname.c_str());
	Database db(dbname, new StderrLog());
	Initializer init(&db);
	
	printf("Checking if database exists...\n");
	bool initialized = false;
	bool succes;
	succes = init.DatabasePopulated();
	if(succes)
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
		std::cin.get();
		return 0;
	}

	printf("Database is of most recent version!\n");	
	
	printf("Checking if tables match...\n");
	succes = init.VerifyTables();
	if(!succes)
	{
		printf("Database tables are not up to date!\n");
		printf("(Move the existing database if you wish to create a fresh copy)\n");
		std::cin.get();
		return 0;
	}

	printf("Initializing database...\n");
	init.InitDatabase();

	printf("Initializing colours...\n");
	init.InitColours();

	return 0;
}

int main()
{
	atexit(exitfunc);
	return maingenerator();
}
