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

#include <stdarg.h>
#include <string>
#include "Global.h"

Global::Global() :
EmptyString(),
EmptyLong()
{
	
}

Global::~Global()
{

}

std::string Global::sprintf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf(m_workspace, MAXSIZE, format, args);
	va_end(args);

	return m_workspace;
}

std::string Global::sprint(va_list& args, const char* format)
{
	vsnprintf(m_workspace, MAXSIZE, format, args);
	return m_workspace;
}

void Global::bugf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf(m_workspace, MAXSIZE, format, args);
	va_end(args);

	bug(m_workspace);
	m_workspace[0] = '\0';
	return;
}

void Global::bug(const char* msg)
{
	printf("***BUG: %s ***BUG\n", msg);
	return;
}

void Global::logf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf(m_workspace, MAXSIZE, format, args);
	va_end(args);

	log(m_workspace);
	m_workspace[0] = '\0';
	return;

}

void Global::log(const char *msg)
{
	printf(msg);
}
