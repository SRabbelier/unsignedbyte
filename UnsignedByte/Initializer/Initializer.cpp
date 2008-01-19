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

#include "Initializer.h"
#include "SavableHeaders.h"
#include "db.h"
#include "TableImpls.h"
#include "Database.h"
#include "Query.h"
#include "Global.h"
#include "GameVersion.h"
#include "Exceptions.h"

bool Initializer::DatabasePopulated()
{
	Query q(*m_db);
	q.get_result("SELECT * FROM SQLITE_MASTER;");
	
	bool populated = false;
	
	if(q.fetch_row())
		populated = true;
		
	q.free_result();
	return populated;
}

bool Initializer::VerifyDatabaseVersion()
{
	bool equal = true;

	KeyPtr key(new Key(db::VersionFields::Get()->VERSIONID, 1));
	SavableManagerPtr manager = SavableManager::bykeys(key);

	if(manager->getfield(db::VersionFields::Get()->MAJOR)->getIntegerValue() != game::major)
	{
		Global::Get()->logf("Major / Major mismatch.\n");
		equal = false;
	}
	
	if(manager->getfield(db::VersionFields::Get()->MINOR)->getIntegerValue() != game::minor)
	{
		Global::Get()->logf("Minor / Minor mismatch.\n");
		equal = false;
	}
	
	if(manager->getfield(db::VersionFields::Get()->MICRO)->getIntegerValue() != game::micro)
	{
		Global::Get()->logf("Micro / Micro mismatch.\n");
		equal = false;
	}
	
	if(manager->getfield(db::VersionFields::Get()->VERSIONTEXT)->getStringValue().compare(game::vstring))
	{
		Global::Get()->logf("Versiontext / Vstring mismatch.\n");
		Global::Get()->logf("dbversion is: '%s', ours is '%s'\n", 
			manager->getfield(db::VersionFields::Get()->VERSIONTEXT)->getStringValue().c_str(), game::vstring);
		equal = false;
	}

	return equal;
}

void Initializer::InitTables()
{
	Query q(*m_db);
	
	for(TableDefVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		std::string sql = SqliteMgr::Get()->creationQuery(*it);
		Global::Get()->logf("%s\n", sql.c_str());
		q.execute(sql);
	}
	
	return;
}

bool Initializer::VerifyTables()
{
	bool good = true;
	
	Query q(*m_db);
	for(TableDefVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		std::string sql = SqliteMgr::Get()->tableQuery(*it);
		std::string result = q.get_string(sql);
		if(result.compare("table"))
		{
			Global::Get()->bugf("Table %s's creation query does not match the one from the input database!\n", (*it)->tableName().c_str());
			good = false;
		}
	}
	
	return good;
}

void Initializer::InitDatabase()
{	
	try
	{
		KeyPtr key(new Key(db::VersionFields::Get()->VERSIONID, 1));
		SavableManagerPtr manager = SavableManager::bykeys(key);
	}
	catch(RowNotFoundException& e)
	{
		SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->VERSION);
		
		ValuePtr value;
		
		value = new Value(db::VersionFields::Get()->MAJOR, game::major);
		manager->setvalue(value);

		value = new Value(db::VersionFields::Get()->MINOR, game::minor);
		manager->setvalue(value);

		value = new Value(db::VersionFields::Get()->MICRO, game::micro);
		manager->setvalue(value);
		
		value = new Value(db::VersionFields::Get()->VERSIONTEXT, std::string(game::vstring));
		manager->setvalue(value);
		
		manager->save();
	}
		
	try
	{
		KeyPtr key(new Key(db::AccountsFields::Get()->ACCOUNTID, 1));
		SavableManagerPtr manager = SavableManager::bykeys(key);
	}
	catch(RowNotFoundException& e)
	{
		SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->ACCOUNTS);
		
		ValuePtr value = new Value(db::AccountsFields::Get()->NAME, game::vname);
		manager->setvalue(value);
		
		value = new Value(db::AccountsFields::Get()->PASSWORD, "qq");
		manager->setvalue(value);
		
		manager->save();
	}
	
	try
	{
		KeyPtr key(new Key(db::RoomsFields::Get()->ROOMID, 1));
		SavableManagerPtr manager = SavableManager::bykeys(key);
	}
	catch(RowNotFoundException& e)
	{
		SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->ROOMS);
		
		ValuePtr value = new Value(db::RoomsFields::Get()->NAME, "The Void");
		manager->setvalue(value);
		
		value = new Value(db::RoomsFields::Get()->DESCRIPTION, "You are in The Void.");
		manager->setvalue(value);
		
		manager->save();
	}
}

void Initializer::InitColours()
{
	const struct colour colours[] = 
	{
		{ "Restore", "^", "0;0m" },
		{ "Dark Red", "r", "31m" },
		{ "Dark Green", "g", "32m" },
		{ "Dark Yellow", "y", "33m"},
		{ "Dark Blue", "b", "34m" },
		{ "Dark Purple", "m", "35m" },
		{ "Dark Cyan", "c", "36m" },
		{ "Gray", "w", "37m" },
		{ "Black", "l", "30m" },
		// Light colours
		{ "Light Red", "R", "1;31m" },
		{ "Light blue", "G", "1;32m" },
		{ "Light Yellow", "Y", "1;33m" },
		{ "Light Blue", "B", "1;34m" },
		{ "Light Magenta", "M", "1;35m" },
		{ "Light Cyan", "C", "1;36m" },
		{ "White", "W", "1;37m" },
		{ "Gray", "L", "1;30m" },
	};

	int size = sizeof(colours) / sizeof(colours[0]);
	printf("Colours: %d.\n", size);

	for(int i = 0; i < size; i++)
	{
		try
		{
			ValuePtr value = new Value(db::ColoursFields::Get()->CODE, colours[i].code);
			SavableManagerPtr manager = SavableManager::byvalue(value);
		}
		catch(RowNotFoundException& e)
		{
			SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->COLOURS);
		
			ValuePtr value;
			
			value = new Value(db::ColoursFields::Get()->NAME, colours[i].name);
			manager->setvalue(value);
			
			value = new Value(db::ColoursFields::Get()->CODE, colours[i].code);
			manager->setvalue(value);
		
			value = new Value(db::ColoursFields::Get()->COLOURSTRING, colours[i].cstr);
			manager->setvalue(value);

			value = new Value(db::ColoursFields::Get()->ANSI, 1);
			manager->setvalue(value);
			
			manager->save();
		}
	}
}
