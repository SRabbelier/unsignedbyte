/***************************************************************************
 *   Copyright (C) 2008 by Vegard Nossum                                   *
 *   vegard.nossum@gmail.com                                               *
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

#include <sstream>

#include "Assert.h"

Assertion::Assertion(const char* expr,
	const char* file, unsigned int line,
	const char* func, const char* pretty_func)
{
	std::ostringstream ss;

	ss << "Assertion `" << expr << "' failed at "
		<< file << ":" << line << ", "
		<< func << " (" << pretty_func << ")";
	m_msg = ss.str();
}

Assertion::~Assertion() throw ()
{
}

const char *
Assertion::what() const throw()
{
	return m_msg.c_str();
}
