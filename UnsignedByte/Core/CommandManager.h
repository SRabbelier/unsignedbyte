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

#include "SavableHeaders.h"

namespace mud 
{ 
	class Command; 
	typedef SmartPtr<Command> CommandPtr;
}

namespace mud
{
	class CommandManager : public Singleton<mud::CommandManager>
	{
	public:
		bool defaultHighForce;
		bool defaultForce;
		bool defaultLowForce;
	
		TableImplPtr GetTable();
		std::vector<std::string> List();
		
		KeysPtr Add();
		mud::CommandPtr GetByKey(value_type id);
		mud::CommandPtr GetByName(cstring name);
		
		value_type lookupByName(cstring value);

	private:
		CommandManager(void);
		CommandManager(const CommandManager& rhs);
		CommandManager operator=(const CommandManager& rhs);
		~CommandManager(void);
		
		friend class Singleton<mud::CommandManager>;
	};
}
