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

#include <string>
#include <vector>
#include <map>

#include "singleton.h"
#include "sqlite3.h"
#include "Database.h"
#include "Global.h"
#include "Tables.h"

typedef std::vector<std::string> Strings;
typedef std::vector<long> Longs;
class IError;

class DatabaseMgr : public Singleton<DatabaseMgr>
{
public:
	// allow to set a specific path
	static void Initialize(std::string path);
	friend class Singleton<DatabaseMgr>;
	Database* DB();
	Database& DBref();

	/**
	 * Savable Interaction
	 */
	Strings GetSavable(const Table* table, const long& value = Global::Get()->EmptyLong, const std::string& field = Global::Get()->EmptyString);
	//long GetSavableID(const Table* table, const std::string& value, const std::string& field = "name");
	long CountSavable(const Table* table, const std::string& value, const std::string& field = "name");
	long CountSavable(const Table* table, const long id);

private: // functions
	DatabaseMgr();
	DatabaseMgr(const DatabaseMgr& rhs) {};
	DatabaseMgr operator=(const DatabaseMgr& rhs) { return *this; };
	~DatabaseMgr();

	std::string m_path;
	Database* m_db;

	static std::string m_staticpath;
};
