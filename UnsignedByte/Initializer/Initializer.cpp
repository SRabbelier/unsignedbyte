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
#include <vector>
#include <stdexcept>

#include "Initializer.h"
#include "sqlite3.h"
#include "Database.h"
#include "Query.h"
#include "Global.h"
#include "Tables.h"
#include "Table.h"
#include "db.h"

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

	db::Version* ver = db::Version::bykey(1);

	if(ver->getmajor() != game::major)
	{
		Global::Get()->logf("Major / Major mismatch.");
		equal = false;
	}
	
	if(ver->getminor() != game::minor)
	{
		Global::Get()->logf("Minor / Minor mismatch.");
		equal = false;
	}
	
	if(ver->getmicro() != game::micro)
	{
		Global::Get()->logf("Micro / Micro mismatch.");
		equal = false;
	}
	
	if(!ver->getversiontext().compare(game::vstring))
	{
		Global::Get()->logf("Versiontext / Vstring mismatch.");
		equal = false;
	}

	delete ver;
	return equal;
}

void Initializer::InitTables()
{
	Query q(*m_db);
	
	for(TableVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		std::string sql = (*it)->creationQuery();
		Global::Get()->logf("%s\n", sql.c_str());
		q.execute(sql);
	}
	
	return;
}

bool Initializer::VerifyTables()
{
	bool good = true;
	
	Query q(*m_db);
	for(TableVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		std::string sql = (*it)->tableQuery();
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
	/*
	hp::Version oldver(1);
	oldver.erase();
	*/
	
	db::Version ver;
	ver.setmajor(game::major);
	ver.setminor(game::minor);
	ver.setmicro(game::micro);
	ver.setversiontext(game::vstring);
	ver.save();
	
	/*
	hp::Accounts oldacc(1);
	oldacc.erase();
	*/

	db::Accounts acc;
	acc.setname(game::vname);
	acc.setpassword("qq");
	acc.save();
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

	/*
	for(int i = 0; i < size; i++)
	{
		hp::Colours col(m_db);
		col.setname(colours[i].name);
		col.setcode(colours[i].code);
		col.setcolourstring(colours[i].cstr);
		col.setansi(1);
		col.save();
	}
	*/
}
