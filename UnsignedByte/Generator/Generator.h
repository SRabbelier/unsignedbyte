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
#pragma once

#include "Types.h"

#include <fstream>

class Generator
{
public:
	Generator(const std::string& name);
	~Generator();
	
	void GenerateDAL();

private:
	Generator(const Generator& rhs) : m_name(rhs.m_name) { };
	Generator operator=(const Generator& rhs) { return *this; };
	
	void AppendLicense(std::ofstream& file);
	void AppendGeneratorNotice(std::ofstream& file);
	
	void AppendHeaderIncludes();
	void AppendHeaderClass(TableDefPtr table);
	void AppendHeaderFooter();
	void CreateHeader();
	
	void AppendSourceIncludes();
	void AppendSourceClass(TableDefPtr table);
	void AppendSourceFooter();
	void CreateSource();
	
	void AppendHeaderTableImpls();
	void AppendSourceTableImpls();
	void CreateTI();
	
	std::string m_name;
	std::string m_tabs;
	std::ofstream m_headerfile;
	std::ofstream m_sourcefile;
	std::ofstream m_tiheaderfile;
	std::ofstream m_tisourcefile;
};
