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

#include <stdexcept>

#include "ClassSourceManagerGenerator.h"
#include "Global.h"
#include "Tables.h"
#include "Table.h"
#include "Field.h"

using std::endl;

ClassSourceManagerGenerator::ClassSourceManagerGenerator(Table* table, std::ofstream* file) :
m_tabs("\t"),
m_table(table),
m_file(file),
m_basename(m_table->tableName()),
m_name(table->tableName())
{
	m_name.append("Mgr");
}

ClassSourceManagerGenerator::~ClassSourceManagerGenerator()
{

}

void ClassSourceManagerGenerator::GenerateClass()
{
	if(m_table->size() == 0)
		throw std::logic_error("ClassSourceManagerGenerator::GenerateClass(), class has no fields!");
		
	try
	{
		AppendHeader();
		AppendCtor();
		AppendBody();
		AppendFooter();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		Global::Get()->bugf("Could not generate manager class '%s'.\n", m_name.c_str());
	}
}

void ClassSourceManagerGenerator::AppendHeader()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
	
	(*m_file) << endl;
	(*m_file) << "/**" << endl;
	(*m_file) << " * Begin of implementation" << endl;
	(*m_file) << " * private class " << m_name << endl;
	(*m_file) << " **/" << endl;
	(*m_file) << endl;
	
	return;
}

void ClassSourceManagerGenerator::AppendCtor()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");

	// Empty constructor for creating new entries
	(*m_file) << "// Ctor" << endl;
	(*m_file) << m_basename << "::" << m_name << "::" << m_name << "(Database* db) :" << endl;
	(*m_file) << "m_db(db)" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "m_odb = m_db->grabdb();" << endl;
	(*m_file) << m_tabs << "std::string sql;" << endl;
	(*m_file) << m_tabs << "int errorcode;" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "// Insert query" << endl;
	if(!m_table->isLookupTable())
	{
		(*m_file) << m_tabs << "sql = \"INSERT INTO " << m_basename << " (accountid) values(NULL);\"" << endl;
	}
	else
	{			
		(*m_file) << m_tabs << "sql = \"INSERT INTO " << m_basename << " (";
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			if(it != m_table->begin())
				(*m_file) << ", ";
				
			(*m_file) << (*it)->getName();
		}
		(*m_file) << ") values(";
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			if(it != m_table->begin())
				(*m_file) << ", ";
				
			(*m_file) << "NULL";
		}
		(*m_file) << ");\"" << endl;
	}

	(*m_file) << m_tabs << "errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &m_insert, &m_leftover);" << endl;
	(*m_file) << endl;

	(*m_file) << m_tabs << "if(errorcode != SQLITE_OK)" << endl;
	(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"" << m_name << "::" << m_name << "(), Could not prepare insertion query!\");" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "if(m_leftover != NULL && strlen(m_leftover) > 0)" << endl;
	(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"" << m_name << "::" << m_name << "(), Leftover from insertion is not NULL!\");" << endl;
	(*m_file) << endl;
	
	
	(*m_file) << m_tabs << "// Erase query" << endl;
	if(!m_table->isLookupTable())
	{
		(*m_file) << m_tabs << "sql = \"DELETE " << m_basename << " where " << m_table->tableID() << "=?;\"" << endl;
	}
	else
	{
		(*m_file) << m_tabs << "sql = \"DELETE " << m_basename << " where ";
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			if(it != m_table->begin())
				(*m_file) << ", ";
				
			(*m_file) << (*it)->getName() << "=?";
		}
		(*m_file) << ";\"" << endl;
	}
	
	(*m_file) << m_tabs << "errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &m_erase, &m_leftover);" << endl;
	(*m_file) << endl;

	(*m_file) << m_tabs << "if(errorcode != SQLITE_OK)" << endl;
	(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"" << m_name << "::" << m_name << "(), Could not prepare erasure query!\");" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "if(m_leftover != NULL && strlen(m_leftover) > 0)" << endl;
	(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"" << m_name << "::" << m_name << "(), Leftover from erasure is not NULL!\");" << endl;
	(*m_file) << endl;
	
	
	if(!m_table->isLookupTable())
	{
		(*m_file) << m_tabs << "// Update query" << endl;
		(*m_file) << m_tabs << "sql = \"Update " << m_basename << " set name=?, password=? where accountid=?;\";" << endl;
		(*m_file) << m_tabs << "errorcode = sqlite3_prepare_v2(m_odb->db, sql.c_str(), (int)sql.size(), &m_update, &m_leftover);" << endl;
		(*m_file) << endl;

		(*m_file) << m_tabs << "if(errorcode != SQLITE_OK)" << endl;
		(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"" << m_name << "::" << m_name << "(), Could not prepare update query!\");" << endl;
		(*m_file) << endl;
	
		(*m_file) << m_tabs << "if(m_leftover != NULL && strlen(m_leftover) > 0)" << endl;
		(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"" << m_name << "::" << m_name << "(), Leftover from update is not NULL!\");" << endl;
		(*m_file) << endl;
	}
	
	(*m_file) << "}" << endl;
	(*m_file) << endl;
	
	
	
	// Destructor
	(*m_file) << m_basename << "::" << m_name << "::~" << m_name << "()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "sqlite3_finalize(m_insert);" << endl;
	(*m_file) << m_tabs << "sqlite3_finalize(m_erase);" << endl;
	(*m_file) << m_tabs << "sqlite3_finalize(m_update);" << endl;
	(*m_file) << endl;
	(*m_file) << m_tabs << "m_db->freedb(m_odb);" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
	
	return;
}

void ClassSourceManagerGenerator::AppendBodyInsert()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << "value_type " << m_basename << "::" << m_name <<  "::doInsert(";
	if(m_table->isLookupTable())
	{
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			if(it != m_table->begin())
				(*m_file) << ", ";
			
			(*m_file) << "value_type " << (*it)->getName();
		}
	}
	(*m_file) << ")" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "int rc = sqlite3_step(m_insert);" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "switch (rc)" << endl;
	(*m_file) << m_tabs << "{" << endl;
	(*m_file) << m_tabs << "default:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), Unknown error code!\");" << endl;
	(*m_file) << m_tabs << "case SQLITE_BUSY:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), The database is busy.\");" << endl;
	(*m_file) << m_tabs << "case SQLITE_ERROR:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(sqlite3_errmsg(m_odb->db));" << endl;
	(*m_file) << m_tabs << "case SQLITE_MISUSE:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), Database misuse.\");" << endl;
	(*m_file) << endl;
	(*m_file) << m_tabs << "case SQLITE_DONE:" << endl;
	(*m_file) << m_tabs << "case SQLITE_ROW:" << endl;
	(*m_file) << m_tabs << m_tabs << "break;" << endl;
	(*m_file) << m_tabs << "}" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "value_type result = sqlite3_last_insert_rowid(m_odb->db);" << endl;
	(*m_file) << m_tabs << "sqlite3_reset(m_insert);" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "return result;" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceManagerGenerator::AppendBodyErase()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	(*m_file) << "void " << m_basename << "::" << m_name << "::doErase()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "sqlite3_bind_int64(m_erase, 1, account);" << endl;
	(*m_file) << m_tabs << "int rc = sqlite3_step(m_erase);" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "switch (rc)" << endl;
	(*m_file) << m_tabs << "{" << endl;
	(*m_file) << m_tabs << "default:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), Unknown error code!\");" << endl;
	(*m_file) << m_tabs << "case SQLITE_BUSY:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), The database is busy.\");" << endl;
	(*m_file) << m_tabs << "case SQLITE_ERROR:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(sqlite3_errmsg(m_odb->db));" << endl;
	(*m_file) << m_tabs << "case SQLITE_MISUSE:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), Database misuse.\");" << endl;
	(*m_file) << endl;
	(*m_file) << m_tabs << "case SQLITE_DONE:" << endl;
	(*m_file) << m_tabs << "case SQLITE_ROW:" << endl;
	(*m_file) << m_tabs << m_tabs << "break;" << endl;
	(*m_file) << m_tabs << "}" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "sqlite3_reset(m_erase);" << endl;
	(*m_file) << m_tabs << "sqlite3_clear_bindings(m_erase);" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceManagerGenerator::AppendBodyUpdate()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	if(m_table->isLookupTable())
		return;
		
	(*m_file) << "void " << m_basename << "::" << m_name << "::doUpdate(";
		
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		if(it != m_table->begin())
			(*m_file) << ", ";
		
		if((*it)->isText())
			(*m_file) << "const std::string& " << (*it)->getName();
		else
			(*m_file) << "value_type " << (*it)->getName();
	}
	(*m_file) << ", value_type " << m_table->tableID() << ")" << endl;
	(*m_file) << "{" << endl;
	int count = 1;
	
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		if((*it)->isText())
		{
			(*m_file) << m_tabs << "sqlite3_bind_text(m_update, ";
			(*m_file) << count;
			(*m_file) << ", " << (*it)->getName() << ".c_str(), " << (*it)->getName() << ".size(), SQLITE_TRANSIENT);" << endl;
		}
		else
		{
			(*m_file) << m_tabs << "sqlite3_bind_int64(m_update, ";
			(*m_file) << count;
			(*m_file) << ", " << (*it)->getName() << ");" << endl;
		}
		count++;
	}
	
	
	(*m_file) << m_tabs << "sqlite3_bind_int64(m_update, " << count << ", " << m_table->tableID() << ");" << endl;
	(*m_file) << m_tabs << "int rc = sqlite3_step(m_update);" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "switch (rc)" << endl;
	(*m_file) << m_tabs << "{" << endl;
	(*m_file) << m_tabs << "default:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), Unknown error code!\");" << endl;
	(*m_file) << m_tabs << "case SQLITE_BUSY:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), The database is busy.\");" << endl;
	(*m_file) << m_tabs << "case SQLITE_ERROR:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(sqlite3_errmsg(m_odb->db));" << endl;
	(*m_file) << m_tabs << "case SQLITE_MISUSE:" << endl;
	(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"" << m_name << "::doErase(), Database misuse.\");" << endl;
	(*m_file) << endl;
	(*m_file) << m_tabs << "case SQLITE_DONE:" << endl;
	(*m_file) << m_tabs << "case SQLITE_ROW:" << endl;
	(*m_file) << m_tabs << m_tabs << "break;" << endl;
	(*m_file) << m_tabs << "}" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "sqlite3_reset(m_update);" << endl;
	(*m_file) << m_tabs << "sqlite3_clear_bindings(m_update);" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceManagerGenerator::AppendBody()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");

	try
	{
		AppendBodyInsert();
		AppendBodyErase();
		AppendBodyUpdate();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		throw std::logic_error("Could not Append Source Body.");
	}
}

void ClassSourceManagerGenerator::AppendFooter()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << endl;
	(*m_file) << "/**" << endl;
	(*m_file) << " * End of implementation" << endl;
	(*m_file) << " * private class " << m_name << endl;
	(*m_file) << " **/" << endl;
	(*m_file) << endl;

	return;
}
