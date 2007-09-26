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

#include "ClassHeaderGenerator.h"
#include "Global.h"
#include "Tables.h"
#include "Table.h"
#include "Field.h"

using std::endl;

ClassHeaderGenerator::ClassHeaderGenerator(TablePtr table, std::ofstream* file) :
m_tabs("\t"),
m_table(table),
m_file(file)
{

}

ClassHeaderGenerator::~ClassHeaderGenerator()
{

}

void ClassHeaderGenerator::GenerateClass()
{
	if(m_table->keysize() == 0)
		throw std::logic_error("ClassHeaderGenerator::GenerateClass(), class has no keys!");
		
	try
	{
		AppendHeader();
		AppendCtor();
		AppendBody();
		AppendFields();
		AppendFooter();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		Global::Get()->bugf("Could not generate class '%s'.\n", m_table->tableName().c_str());
	}
}

void ClassHeaderGenerator::AppendHeader()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
	
	(*m_file) << m_tabs << "class " << m_table->tableName() << " : public Bindable" << endl;
	(*m_file) << m_tabs << "{" << endl;
	(*m_file) << m_tabs << "public:" << endl;
	
	return;
}

void ClassHeaderGenerator::AppendCtor()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
	
	std::string name = m_table->tableName();
	
	(*m_file) << m_tabs << m_tabs << "// Ctors" << endl;
	
	// Empty ctor for creating new objects
	if(m_table->hasSinglularPrimaryKey())
		(*m_file) << m_tabs << m_tabs << name << "();" << endl;
	
	// Destructor
	(*m_file) << m_tabs << m_tabs << "~" << name << "();" << endl;
	(*m_file) << endl;
		
	// Factories
	(*m_file) << m_tabs << m_tabs << "// Factories" << endl;
	(*m_file) << m_tabs << m_tabs << "static " << name << "* bykey" << "(";
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		if(it != m_table->keybegin())
			(*m_file) << ", ";
		
		(*m_file) << "value_type " << it->first;
	}
	(*m_file) << ");" << endl;

	for(Fields::const_iterator it = m_table->lookupbegin(); it != m_table->lookupend(); it++)
	{
		(*m_file) << m_tabs << m_tabs << "static " << name << "* by" << (*it)->getName() << "(";
		if((*it)->isText())
			(*m_file) << "const std::string& value);" << endl;
		else
			(*m_file) << "value_type value);" << endl;
	}
	
	// Lookup
	if(m_table->hasSinglularPrimaryKey())
	{
		for(Fields::const_iterator it = m_table->lookupbegin(); it != m_table->lookupend(); it++)
		{
			(*m_file) << m_tabs << m_tabs << "static value_type lookup";
			(*m_file) << (*it)->getName() << "(";
			if((*it)->isText())
				(*m_file) << "const std::string& value);" << endl;
			else
				(*m_file) << "value_type value);" << endl;;
		}
	}
	(*m_file) << endl;
	
	return;
}

void ClassHeaderGenerator::AppendBody()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");

	(*m_file) << m_tabs << m_tabs << "// Database interaction" << endl;
	(*m_file) << m_tabs << m_tabs << "void erase();" << endl;
	(*m_file) << m_tabs << m_tabs << "void save();" << endl;
	(*m_file) << m_tabs << m_tabs << "bool exists();" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << m_tabs << "// Bindable interface" << endl;
	(*m_file) << m_tabs << m_tabs << "void bindKeys(sqlite3_stmt* stmt) const;" << endl;
	(*m_file) << m_tabs << m_tabs << "void bindUpdate(sqlite3_stmt* stmt) const;" << endl;
	(*m_file) << m_tabs << m_tabs << "void bindLookup(sqlite3_stmt* stmt) const;" << endl;
	(*m_file) << m_tabs << m_tabs << "void parseInsert(sqlite3* db);" << endl;
	(*m_file) << m_tabs << m_tabs << "void parseSelect(sqlite3_stmt* stmt);" << endl;
	(*m_file) << m_tabs << m_tabs << "void parseLookup(sqlite3_stmt* stmt);" << endl;
	(*m_file) << m_tabs << m_tabs << "TablePtr getTable() const;" << endl;
	(*m_file) << endl;

	return;
}

void ClassHeaderGenerator::AppendFields()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
	
	(*m_file) << m_tabs << m_tabs << "// Getters" << endl;

	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
		(*m_file) << m_tabs << m_tabs << "value_type get" << it->first << "() const;" << endl;
		
	if(m_table->size() != 0)
	{
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			FieldPtr field = *it;
			if(field->isText())
				(*m_file) << m_tabs << m_tabs << "const std::string& get" << field->getName() << "() const;" << endl;
			else
				(*m_file) << m_tabs << m_tabs << "value_type get" << field->getName() << "() const;" << endl;
		}
		(*m_file) << endl;

		(*m_file) << m_tabs << m_tabs << "// Setters" << endl;
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			FieldPtr field = *it;
			if(field->isText())
				(*m_file) << m_tabs << m_tabs << "void set" << field->getName() << "(const std::string& value);" << endl;
			else
				(*m_file) << m_tabs << m_tabs << "void set" << field->getName() << "(value_type value);" << endl;
		}
	}
	(*m_file) << endl;
	
	(*m_file) << m_tabs << "private:" << endl;
	(*m_file) << m_tabs << m_tabs << "// Database pointer" << endl;
	(*m_file) << m_tabs << m_tabs << "Database* m_db;" << endl;
	(*m_file) << endl;
	
	if(m_table->lookupsize())
	{
		(*m_file) << m_tabs << m_tabs << "// Lookup" << endl;
		(*m_file) << m_tabs << m_tabs << "std::string m_lookupvalue;" << endl;
		(*m_file) << endl;
	}
	
	(*m_file) << m_tabs << m_tabs << "// Keys" << endl;
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
		(*m_file) << m_tabs << m_tabs << "value_type m_" << it->first << ";" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << m_tabs << "// Fields" << endl;
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		FieldPtr field = *it;
		if(field->isText())
			(*m_file) << m_tabs << m_tabs << "std::string m_" << field->getName() << ";" << endl;
		else
			(*m_file) << m_tabs << m_tabs << "value_type m_" << field->getName() << ";" << endl;
	}
	(*m_file) << endl;

	(*m_file) << m_tabs << m_tabs << "// State flags" << endl;
	(*m_file) << m_tabs << m_tabs << "bool m_newentry;" << endl;
	(*m_file) << m_tabs << m_tabs << "bool m_dirty;" << endl;
	(*m_file) << endl;
		
	return;
}

void ClassHeaderGenerator::AppendFooter()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
		
	std::string name = m_table->tableName();
	
	(*m_file) << m_tabs << m_tabs << "// Hide constructor and assignment operator" << endl;
	if(!m_table->hasSinglularPrimaryKey())
		(*m_file) << m_tabs << m_tabs << name << "();" << endl;
	(*m_file) << m_tabs << m_tabs << name << "(const " << name << "& rhs);" << endl;
	(*m_file) << m_tabs << m_tabs << name << " operator=(const " << name << "& rhs);" << endl;
	
	(*m_file) << m_tabs << "};" << endl;
	(*m_file) << endl;
	
	return;
}
