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

#include "ClassSourceGenerator.h"
#include "Global.h"
#include "Tables.h"
#include "Table.h"
#include "Field.h"

using std::endl;

ClassSourceGenerator::ClassSourceGenerator(Table* table, std::ofstream* file) :
m_tabs("\t"),
m_table(table),
m_file(file),
m_name(m_table->tableName())
{

}

ClassSourceGenerator::~ClassSourceGenerator()
{

}

void ClassSourceGenerator::GenerateClass()
{
	if(m_table->size() == 0)
		throw std::logic_error("ClassHeaderGenerator::GenerateClass(), class has no fields!");
		
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
		Global::Get()->bugf("Could not generate class '%s'.\n", m_name.c_str());
	}
}

void ClassSourceGenerator::AppendHeader()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
	
	(*m_file) << endl;
	(*m_file) << "/**" << endl;
	(*m_file) << " * Begin of implementation" << endl;
	(*m_file) << " * class " << m_name << endl;
	(*m_file) << " **/" << endl;
	(*m_file) << endl;
	
	return;
}

void ClassSourceGenerator::AppendCtor()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	// Empty constructor for creating new entries
	(*m_file) << "// Ctors" << endl;
	(*m_file) << m_name << "::" << m_name << "(Database* db) :" << endl;
	(*m_file) << "m_db(db)";
	if(!m_table->isLookupTable())	
		(*m_file) << "," << endl << "m_" << m_table->tableID() << "()";
		
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		(*m_file) << "," << endl;
		if((*it)->isText())
			(*m_file) << "m_" << (*it)->getName() << "()";
		else
			(*m_file) << "m_" << (*it)->getName() << "(0)";
	}
	(*m_file) << endl;
	
	(*m_file) << "{" << endl;
	(*m_file) << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
	
	// Specific constructor
	if(!m_table->isLookupTable())
	{
		(*m_file) << m_name << "::" << m_name << "(Database* db, value_type " << m_table->tableID() << ") :" << endl;
		(*m_file) << "m_db(db)," << endl;
		(*m_file) << "m_" << m_table->tableID() << "(" << m_table->tableID() << ")" << endl;
	}
	else
	{
		(*m_file) << m_name << "::" << m_name << "(Database* db";

		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
			(*m_file) << ", value_type " << (*it)->getName();

		(*m_file) << ") :" << endl;
		(*m_file) << "m_db(db)" << endl;
		
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			(*m_file) << "," << endl;
			(*m_file) << "m_" << (*it)->getName() << "(" << (*it)->getName() << ")";
		}
	}
	(*m_file) << "{" << endl;
	(*m_file) << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
	
	// Destructor
	(*m_file) << m_name << "::~" << m_name << "()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
	
	return;
}

void ClassSourceGenerator::AppendBodyInsert()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << "value_type " << m_name <<  "::insert()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "sqlite3_stmt* res; // pointer to the result" << endl;
	(*m_file) << m_tabs << "const char* leftover = NULL; // pointer to a constant char array storing the 'leftovers'" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "Database::OPENDB* db = m_db->grabdb();" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "if(db == NULL)" << endl;
	(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"insert(), Could not open database!\\n\");" << endl;
	(*m_file) << m_tabs << endl;
	
	(*m_file) << m_tabs << "std::string sql = \"INSERT INTO " << m_name << " (";
	if(m_table->isLookupTable())
	{
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			if(it != m_table->begin())
				(*m_file) << ",";
				
			(*m_file) << (*it)->getName();
		}
		(*m_file)  << ") values (";
		for(size_t i = 0; i < m_table->size(); i++)
		{
			if(i != 0)
				(*m_file) << ",";
				
			(*m_file) << "NULL";
		}
		(*m_file) << ");";
	}
	else
	{
		(*m_file) << m_table->tableID() << ") values(NULL);";
	}
	(*m_file) << "\";" << endl;
	
	(*m_file) << m_tabs << "int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &leftover);" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "if(rc != SQLITE_OK)" << endl;
	(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"insert(), Could not prepare query!\");" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "if(leftover != NULL && strlen(leftover) > 0)" << endl;
	(*m_file) << m_tabs << m_tabs << "throw std::runtime_error(\"insert(), Leftover is not NULL!\");" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "return sqlite3_last_insert_rowid(db->db);" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendBodyUpdate()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	(*m_file) << "void " << m_name << "::update()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "return;" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendBodySave()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	(*m_file) << "void " << m_name << "::save()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "if(m_newentry)" << endl;
	(*m_file) << m_tabs << m_tabs << "insert();" << endl;
	(*m_file) << m_tabs << "else" << endl;
	(*m_file) << m_tabs << m_tabs << "update();" << endl;
	(*m_file) << endl;
	(*m_file) << m_tabs << "return;" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendBodyErase()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	(*m_file) << "void " << m_name << "::erase()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "if (new_object)" << endl;
	(*m_file) << m_tabs << m_tabs << "return;" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "return;" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendBody()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");

	try
	{
		AppendBodyInsert();
		AppendBodyUpdate();
		AppendBodySave();
		AppendBodyErase();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		throw std::logic_error("Could not Append Source Body.");
	}
}

void ClassSourceGenerator::AppendFooter()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
	
	(*m_file) << endl;
	(*m_file) << "/**" << endl;
	(*m_file) << " * End of implementation" << endl;
	(*m_file) << " * class " << m_name << endl;
	(*m_file) << " **/" << endl;
	(*m_file) << endl;

	return;
}
