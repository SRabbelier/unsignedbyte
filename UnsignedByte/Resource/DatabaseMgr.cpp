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

#include "DatabaseMgr.h"
#include "sqlite3.h"
#include "Database.h"
#include "IError.h"
#include "StderrLog.h"
#include "Query.h"
#include "Global.h"

#include "SPKCriteria.h"
#include "CountActor.h"
#include "SqliteMgr.h"

std::string DatabaseMgr::m_staticpath = Global::Get()->EmptyString;

void DatabaseMgr::Initialize(const std::string& path)
{
	Free();
	m_staticpath = path;
	Get();
	m_staticpath = Global::Get()->EmptyString;
}

DatabaseMgr::DatabaseMgr() :
m_path(m_staticpath == Global::Get()->EmptyString ? "new.db" : m_staticpath),
m_db(new Database(m_path, new StderrLog()))
{
	if(m_staticpath == Global::Get()->EmptyString)
		abort();
}

DatabaseMgr::~DatabaseMgr()
{
	delete m_db;
}

Database* DatabaseMgr::DB()
{
	return m_db;
}

Database& DatabaseMgr::DBref()
{
	return *m_db;
}

long DatabaseMgr::CountSavable(const TableImplPtr table, const long id)
{
	long count = 0;
	
	SPKCriteria crit(id);
	CountActor act(&crit);
	SqliteMgr::Get()->doForEach(table.get(), act);
	count = act.getCount();
	
	return count;
}
