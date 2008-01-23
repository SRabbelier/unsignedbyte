/***************************************************************************
 *   Copyright (C) 2008 by Sverre Rabbelier                                *
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
#include "TableDef.h"
#include "FieldDef.h"
#include "StringUtilities.h"

using std::endl;

ClassSourceGenerator::ClassSourceGenerator(TableDefPtr table, std::ofstream* file) :
m_tabs("\t"),
m_table(table),
m_file(file)
{
	Assert(table);
	
	std::string name = m_table->tableName();
	name.append("Fields");
	m_name = name;
}

ClassSourceGenerator::~ClassSourceGenerator()
{

}

void ClassSourceGenerator::GenerateClass()
{
	if(m_table->keysize() == 0)
		throw std::logic_error("ClassSourceGenerator::GenerateClass(), class has no primary keys!");
		
	try
	{
		AppendCtorGeneral();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		Global::Get()->bugf("Could not generate class '%s'.", m_name.c_str());
	}
}

void ClassSourceGenerator::AppendCtorGeneral()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
			
	(*m_file) << m_name << "::" << m_name << "() :" << endl;
	
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		if(it != m_table->keybegin())
			(*m_file) << "," << endl;
			
		(*m_file) << String::Get()->toupper(it->first) << "(";
		(*m_file) << "new KeyDef(TableImpls::Get()->" << String::Get()->toupper(m_table->tableName()) << ", \"" << it->first << "\"" << "))";
	}
	
	for(FieldDefVector::const_iterator it = m_table->defbegin(); it != m_table->defend(); it++)
	{
		(*m_file) << "," << endl;
			
		(*m_file) << String::Get()->toupper((*it)->getName()) << "(";
		(*m_file) << "new FieldImpl(TableImpls::Get()->" << String::Get()->toupper(m_table->tableName()) << ", \"" << (*it)->getName() << "\"";
		if((*it)->isText())
			(*m_file) << ", true";
		
		(*m_file) << "))";
	}
	(*m_file) << endl;
	
	(*m_file) << "{" << endl;
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		(*m_file) << m_tabs << "TableImpls::Get()->" << String::Get()->toupper(m_table->tableName());
		(*m_file) << "->addKey(" << String::Get()->toupper(it->first) << ");" << endl;
	}
	
	for(FieldDefVector::const_iterator it = m_table->defbegin(); it != m_table->defend(); it++)
	{			
		(*m_file) << m_tabs << "TableImpls::Get()->" << String::Get()->toupper(m_table->tableName());
		(*m_file) << "->addField(" << String::Get()->toupper((*it)->getName()) << ");" << endl;
	}

	(*m_file) << "}" << endl;
	(*m_file) << endl;
}
