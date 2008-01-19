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
#pragma once

#include "Types.h"

template <class T>
class CommandObject
{
    public:
		typedef void (T::*CommandFunction)(const std::string& argument);
		
		CommandObject(const std::string& name, CommandFunction command, bool fullname = false);
		~CommandObject();
        void Run(T* owner, const std::string& argument);
		const std::string& getName() const;
		bool fullName() const; // only add the full name

    protected:
		CommandObject(const CommandObject& rhs);
		
		std::string m_name;
		CommandFunction m_command;
		bool m_fullName;
};

template <class T> 
const std::string& CommandObject<T>::getName() const
{ 
	return m_name; 
}

template <class T> 
bool CommandObject<T>::fullName() const
{ 
	return m_fullName; 
}

template <class T> 
CommandObject<T>::CommandObject(const std::string& name, CommandFunction command, bool fullname) :
m_name(name),
m_command(command),
m_fullName(fullname)
{
	
}

template <class T> 
CommandObject<T>::~CommandObject()
{
	
}

template <class T> 
void CommandObject<T>::Run(T* owner, const std::string& argument)
{ 
	(owner->*m_command)(argument);
}
