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
// #include "ub.h"

std::string DatabaseMgr::m_staticpath = Global::Get()->EmptyString;

void DatabaseMgr::Initialize(std::string path)
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

/**
 * Savable Interaction
 */
Longs DatabaseMgr::GetSavableIDS(const Table* table, const long& value, const std::string& field)
{
	Longs result;
	std::string condition;
	if(field != Global::Get()->EmptyString)
	{
		condition = Global::Get()->sprintf("WHERE %s=%d", field.c_str(), value);
	}

	Query q(DBref());
	/*
	q.get_result(Global::Get()->sprintf(
		"SELECT %s FROM %s %s ORDER BY %s ASC;",
		table->tableID().c_str(),
		table->tableName().c_str(),
		condition.c_str(),
		table->tableID().c_str()
		));
	*/
	// TODO - BLOCKER

	while(q.fetch_row())
	{
		result.push_back(q.getval());
	}

	q.free_result();
	return result;
}

Strings DatabaseMgr::GetSavable(const Table* table, const long& value, const std::string& field)
{
	Strings result;
	std::string condition;
	if(field != Global::Get()->EmptyString)
	{
		condition = Global::Get()->sprintf("WHERE %s=%d", field.c_str(), value);
	}

	Query q(DBref());
	q.get_result(Global::Get()->sprintf(
		"SELECT name FROM %s %s ORDER BY name ASC;",
		table->tableName().c_str(),
		condition.c_str()
		));

	while(q.fetch_row())
	{
		result.push_back(q.getstr(0));
	}

	q.free_result();
	return result;
}

long DatabaseMgr::GetSavableID(const Table* table, const std::string& value, const std::string& field)
{
	Query q(DBref());
	double num = 0;
	/*
	num = q.get_num(Global::Get()->sprintf(
		"select %s from %s where %s='%s';", 
		table->tableID().c_str(), 
		table->tableName().c_str(), 
		field.c_str(),
		value.c_str()));
	*/
	// TODO - BLOCKER

	return (long)num;
}

long DatabaseMgr::CountSavable(const Table* table, const std::string& value, const std::string& field)
{
	Query q(DBref());
	long count = 
	q.get_count(Global::Get()->sprintf(
		"SELECT COUNT(*) FROM %s WHERE %s='%s';",
		table->tableName().c_str(),
		field.c_str(),
		value.c_str()
		));

	return count;
}

long DatabaseMgr::CountSavable(const Table* table, const long id)
{
	Query q(DBref());
	long count = 0;
	/*
	count = q.get_count(Global::Get()->sprintf(
		"SELECT COUNT(*) FROM %s WHERE %s='%d';",
		table->tableName().c_str(),
		table->tableID().c_str(), 
		id
		));
	*/
	// TODO - Blocker

	return count;
}
