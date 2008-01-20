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

#include "ClassHeaderGenerator.h"
#include "Global.h"
#include "Tables.h"
#include "TableDef.h"
#include "FieldDef.h"
#include "StringUtilities.h"

using std::endl;

ClassHeaderGenerator::ClassHeaderGenerator(TableDefPtr table, std::ofstream* file) :
m_tabs("\t"),
m_table(table),
m_file(file)
{
	std::string name = m_table->tableName();
	name.append("Fields");
	m_name = name;
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
	
	(*m_file) << m_tabs << "class " << m_name << " : public Singleton<" << m_name << ">" << endl;
	(*m_file) << m_tabs << "{" << endl;
	(*m_file) << m_tabs << "public:" << endl;
	
	return;
}

void ClassHeaderGenerator::AppendFields()
{
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		(*m_file) << m_tabs << m_tabs << "KeyDefPtr " << String::Get()->toupper(it->first) << ";" << endl;
	}
	for(FieldDefVector::const_iterator it = m_table->defbegin(); it != m_table->defend(); it++)
	{
		(*m_file) << m_tabs << m_tabs << "FieldImplPtr " << String::Get()->toupper((*it)->getName()) << ";" << endl;
	}
	(*m_file) << endl;
}

void ClassHeaderGenerator::AppendFooter()
{
	if(!m_file)
		throw std::logic_error("Header file is not open for writing.\n");
	
	(*m_file) << m_tabs << "private:" << endl;
	(*m_file) << m_tabs << m_tabs << "// Hide constructor and assignment operator" << endl;
	(*m_file) << m_tabs << m_tabs << m_name << "();" << endl;
	(*m_file) << m_tabs << m_tabs << "~" << m_name << "() { }" << endl;
	(*m_file) << m_tabs << m_tabs << m_name << "(const " << m_name << "& rhs);" << endl;
	(*m_file) << m_tabs << m_tabs << m_name << " operator=(const " << m_name << "& rhs);" << endl;
	(*m_file) << m_tabs << m_tabs << "friend class Singleton<" << m_name << ">;" << endl;
	
	(*m_file) << m_tabs << "};" << endl;
	(*m_file) << endl;
	
	return;
}
