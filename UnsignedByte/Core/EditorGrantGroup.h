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

#include <string>
#include "OLCEditor.h"
#include "singleton.h"
#include "Interpreter.h"
#include "Action.h"

class UBSocket;
namespace mud { class GrantGroup; }

class EditorGrantGroup : public OLCEditor
{
public:
	EditorGrantGroup(UBSocket* sock);
	~EditorGrantGroup(void);

	std::string name() { return "GrantGroup"; };
	std::string prompt() { return "GrantGroup> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TablePtr getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);

private:
	mud::GrantGroup* m_grantgroup;
	EditorGrantGroup(const EditorGrantGroup& rhs) : OLCEditor(rhs.m_sock) {};
	EditorGrantGroup operator=(const EditorGrantGroup& rhs) { return *this; };

	typedef EditorAction<UBSocket, mud::GrantGroup> GrantGroupAction;

	class GrantGroupInterpreter : public Interpreter<GrantGroupAction>, public Singleton<GrantGroupInterpreter> {
	private:
		GrantGroupInterpreter(void);
		~GrantGroupInterpreter(void);
		friend class Singleton<GrantGroupInterpreter>;
	};

	class Name : public GrantGroupAction, public Singleton<Name>{
	private:
		Name(void) {};
		~Name(void) {};
		friend class Singleton<Name>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::GrantGroup* area);
		std::string getName() { return "Name"; };
	};
		
	class Implication : public GrantGroupAction, public Singleton<Implication>{
	private:
		Implication(void) {};
		~Implication(void) {};
		friend class Singleton<Implication>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::GrantGroup* area);
		std::string getName() { return "Implication"; };
	};

	class Show : public GrantGroupAction, public Singleton<Show> {
	private:
		Show(void) {};
		~Show(void) {};
		friend class Singleton<Show>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::GrantGroup* area);
		std::string getName() { return "Show"; };
	};

	class Save : public GrantGroupAction, public Singleton<Save> {
	private:
		Save(void) {};
		~Save(void) {};
		friend class Singleton<Save>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::GrantGroup* area);
		std::string getName() { return "Save"; };
	};
	
};
