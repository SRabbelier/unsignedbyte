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

ClassHeaderGenerator::ClassHeaderGenerator(Table* table, std::ofstream* file) :
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
	if(m_table->size() == 0)
		throw std::logic_error("ClassHeaderGenerator::GenerateClass(), class has no fields!");
		
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
	
	if(m_table->isLookupTable())
		(*m_file) << m_tabs << "// Lookup table" << endl;
	
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
	(*m_file) << m_tabs << m_tabs << name << "(Database* db);" << endl;
	
	if(!m_table->isLookupTable())
	{
		(*m_file) << m_tabs << m_tabs << name << "(Database* db, value_type ";
		(*m_file) << m_table->tableID();
		(*m_file) << ");" << endl;
	}
	else
	{
		(*m_file) << m_tabs << m_tabs << name << "(Database* db";
		
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
			(*m_file) << ", value_type " << (*it)->getName();

		(*m_file) << ");" << endl;
	}
	
	
	(*m_file) << m_tabs << m_tabs << "~" << name << "();" << endl;
	(*m_file) << endl;
	
	return;
}

void ClassHeaderGenerator::AppendBody()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");

	(*m_file) << m_tabs << m_tabs << "// Database interaction" << endl;
	(*m_file) << m_tabs << m_tabs << "value_type insert();" << endl;
	(*m_file) << m_tabs << m_tabs << "void update();" << endl;
	(*m_file) << m_tabs << m_tabs << "void save();" << endl;
	(*m_file) << m_tabs << m_tabs << "void erase();" << endl;
	(*m_file) << endl;

	return;
}

void ClassHeaderGenerator::AppendFields()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
		
	(*m_file) << m_tabs << m_tabs << "// Getters" << endl;
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		Field* field = *it;
		if(field->isText())
			(*m_file) << m_tabs << m_tabs << "const std::string& get" << field->getName() << "() const;" << endl;
		else
			(*m_file) << m_tabs << m_tabs << "value_type get" << field->getName() << "() const;" << endl;
	}
	(*m_file) << endl;

	// Only add setters if it's not a lookup table
	if(!m_table->isLookupTable())
	{
		(*m_file) << m_tabs << m_tabs << "// Setters" << endl;
		for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
		{
			Field* field = *it;
			if(field->isText())
				(*m_file) << m_tabs << m_tabs << "void set" << field->getName() << "(const std::string& value) const;" << endl;
			else
				(*m_file) << m_tabs << m_tabs << "void set" << field->getName() << "(value_type value) const;" << endl;
		}
		(*m_file) << endl;
	}
	
	(*m_file) << m_tabs << "private:" << endl;
	(*m_file) << m_tabs << m_tabs << "// Database pointer" << endl;
	(*m_file) << m_tabs << m_tabs << "Database* m_db;" << endl;
	(*m_file) << endl;
	
	(*m_file) << m_tabs << m_tabs << "// Fields" << endl;
		
	if(!m_table->isLookupTable())
	{
		(*m_file) << m_tabs << m_tabs << "value_type m_" << m_table->tableID() << ";" << endl;
	}
	
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		Field* field = *it;
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
	
	(*m_file) << m_tabs << m_tabs << "// Hide copy constructor and assignment operator" << endl;
	(*m_file) << m_tabs << m_tabs << name << "(const " << name << "& rhs);" << endl;
	(*m_file) << m_tabs << m_tabs << name << " operator=(const " << name << "& rhs);" << endl;
	
	(*m_file) << m_tabs << "};" << endl;
	(*m_file) << endl;
	
	return;
}
