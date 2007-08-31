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
namespace mud { class Permission; }

class EditorPermission : public OLCEditor
{
public:
	EditorPermission(UBSocket* sock);
	~EditorPermission(void);

	std::string name() { return "Permission"; };
	std::string prompt() { return "Permission> "; };

	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	Savable* getEditing();
	Table* getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);

private:
	mud::Permission* m_permission;
	EditorPermission(const EditorPermission& rhs) : OLCEditor(rhs.m_sock) {};
	EditorPermission operator=(const EditorPermission& rhs) { return *this; };

	typedef EditorAction<UBSocket, mud::Permission> PermissionAction;

	class PermissionInterpreter : public Interpreter<PermissionAction>, public Singleton<PermissionInterpreter> {
	private:
		PermissionInterpreter(void);
		~PermissionInterpreter(void);
		friend class Singleton<PermissionInterpreter>;
	};
	
	class Accounts : public PermissionAction, public Singleton<Accounts>{
	private:
		Accounts(void) {};
		~Accounts(void) {};
		friend class Singleton<Accounts>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::Permission* area);
		std::string getName() { return "Account"; };
	};
	
	class GrantGroups : public PermissionAction, public Singleton<GrantGroups>{
	private:
		GrantGroups(void) {};
		~GrantGroups(void) {};
		friend class Singleton<GrantGroups>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::Permission* area);
		std::string getName() { return "GrantGroup"; };
	};
	
	class Grants : public PermissionAction, public Singleton<Grants>{
	private:
		Grants(void) {};
		~Grants(void) {};
		friend class Singleton<Grants>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::Permission* area);
		std::string getName() { return "Grant"; };
	};
	
	class Logging : public PermissionAction, public Singleton<Logging>{
	private:
		Logging(void) {};
		~Logging(void) {};
		friend class Singleton<Logging>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::Permission* area);
		std::string getName() { return "Logging"; };
	};

	class Show : public PermissionAction, public Singleton<Show> {
	private:
		Show(void) {};
		~Show(void) {};
		friend class Singleton<Show>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::Permission* permission);
		std::string getName() { return "Show"; };
	};

	class Save : public PermissionAction, public Singleton<Save> {
	private:
		Save(void) {};
		~Save(void) {};
		friend class Singleton<Save>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::Permission* area);
		std::string getName() { return "Save"; };
	};

};
