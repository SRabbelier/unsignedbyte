/*
 **	Database.h
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

#ifndef _DATABASE_H_SQLITE
#define _DATABASE_H_SQLITE

#include <string>
#include <list>

#include <stdint.h>

#ifdef SQLITEW_NAMESPACE
namespace SQLITEW_NAMESPACE {
#endif


class Query;


/** Connection information and pool. */
class Database 
{
public:
	/** Connection pool struct. */
	struct OPENDB {
		OPENDB() : busy(false) {}
		sqlite3 *db;
		bool busy;
	};
	typedef std::list<OPENDB *> opendb_v;

public:
	/** Use file */
	Database(const std::string& database);

	virtual ~Database();

	/** try to establish connection with given host */
	bool Connected();

	/** Request a database connection.
The "grabdb" method is used by the Query class, so that each object instance of Query gets a unique
database connection. I will reimplement your connection check logic in the Query class, as that's where
the database connection is really used.
It should be used something like this.
{
		Query q(db);
		if (!q.Connected())
			 return false;
		q.execute("delete * from user"); // well maybe not
}

When the Query object is deleted, then "freedb" is called - the database connection stays open in the
m_opendbs vector. New Query objects can then reuse old connections.
	*/
	OPENDB *grabdb();
	void freedb(OPENDB *odb);

	/** Escape string - change all ' to ''. */
	std::string safestr(const std::string& );
	/** Make string xml safe. */
	std::string xmlsafestr(const std::string& );

	/** Convert string to 64-bit integer. */
	int64_t a2bigint(const std::string& );
	/** Convert string to unsigned 64-bit integer. */
	uint64_t a2ubigint(const std::string& );

private:
	Database(const Database& ) {}
	Database& operator=(const Database& ) { return *this; }
	void error(const char *format, ...);

	std::string database;
	opendb_v m_opendbs;
	bool m_embedded;
};


#ifdef SQLITEW_NAMESPACE
} // namespace SQLITEW_NAMESPACE {
#endif

#endif // _DATABASE_H
