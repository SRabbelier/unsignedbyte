/*
 **	Database.cpp
 **
 **	Published / author: 2005-08-12 / grymse@alhem.net
 **/

/*
Copyright (C) 2001-2006  Anders Hedstrom

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include <stdio.h>
#ifdef _WIN32
#ifndef __MINGW32__
#pragma warning(disable:4786)
#endif
#endif

#include <map>
#include <stdexcept>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <stdarg.h>

#include "Assert.h"
#include "Database.h"


#ifdef SQLITEW_NAMESPACE
namespace SQLITEW_NAMESPACE {
#endif


Database::Database(const std::string& d)
:database(d)
,m_embedded(true)
{
}

Database::~Database()
{
	for (opendb_v::iterator it = m_opendbs.begin(); it != m_opendbs.end(); it++)
	{
		OPENDB *p = *it;
		sqlite3_close(p -> db);
	}
	while (m_opendbs.size())
	{
		opendb_v::iterator it = m_opendbs.begin();
		OPENDB *p = *it;
		/* If we're busy, it's YOUR fault you didn't delete the
		 * query object. Therefore, you take the consequences too. */
		Assert(!p->busy);
		delete p;
		m_opendbs.erase(it);
	}
}

Database::OPENDB *Database::grabdb()
{
	OPENDB *odb = NULL;

	for (opendb_v::iterator it = m_opendbs.begin(); it != m_opendbs.end(); it++)
	{
		odb = *it;
		if (!odb -> busy)
		{
			break;
		}
		else
		{
			odb = NULL;
		}
	}
	if (!odb)
	{
		odb = new OPENDB;
		if (!odb)
			throw std::runtime_error("grabdb: OPENDB struct "
				"couldn't be created");

		int rc = sqlite3_open(database.c_str(), &odb -> db);
		if (rc) {
			std::string msg(sqlite3_errmsg(odb->db));
			sqlite3_close(odb -> db);
			delete odb;
			throw std::runtime_error("Can't open database: " + msg);
		}
		odb -> busy = true;
		m_opendbs.push_back(odb);
	}
	else
	{
		odb -> busy = true;
	}
	return odb;
}


void Database::freedb(Database::OPENDB *odb)
{
	if (odb)
	{
		odb -> busy = false;
	}
}

bool Database::Connected()
{
	OPENDB *odb = grabdb();
	if (!odb)
	{
		return false;
	}
	freedb(odb);
	return true;
}

std::string Database::safestr(const std::string& str)
{
	std::string str2;
	for (size_t i = 0; i < str.size(); i++)
	{
		switch (str[i])
		{
		case '\'':
		case '\\':
		case 34:
			str2 += '\'';
		default:
			str2 += str[i];
		}
	}
	return str2;
}


std::string Database::xmlsafestr(const std::string& str)
{
	std::string str2;
	for (size_t i = 0; i < str.size(); i++)
	{
		switch (str[i])
		{
		case '&':
			str2 += "&amp;";
			break;
		case '<':
			str2 += "&lt;";
			break;
		case '>':
			str2 += "&gt;";
			break;
		case '"':
			str2 += "&quot;";
			break;
		case '\'':
			str2 += "&apos;";
			break;
		default:
			str2 += str[i];
		}
	}
	return str2;
}


int64_t Database::a2bigint(const std::string& str)
{
	int64_t val = 0;
	bool sign = false;
	size_t i = 0;
	if (str[i] == '-')
	{
		sign = true;
		i++;
	}
	for (; i < str.size(); i++)
	{
		val = val * 10 + (str[i] - 48);
	}
	return sign ? -val : val;
}


uint64_t Database::a2ubigint(const std::string& str)
{
	uint64_t val = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		val = val * 10 + (str[i] - 48);
	}
	return val;
}


#ifdef SQLITEW_NAMESPACE
} // namespace SQLITEW_NAMESPACE {
#endif

