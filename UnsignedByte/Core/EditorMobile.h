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
namespace mud { class MCharacter; }

class EditorMobile : public OLCEditor
{
public:
	EditorMobile(UBSocket* sock);
	~EditorMobile(void);

	std::string name() { return "Mobile"; };
	std::string prompt() { return "Mobile> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TablePtr getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);

private:
	mud::MCharacter* m_mobile;
	EditorMobile(const EditorMobile& rhs) : OLCEditor(rhs.m_sock) {};
	EditorMobile operator=(const EditorMobile& rhs) { return *this; };

	typedef EditorAction<UBSocket, mud::MCharacter> MobileAction;

	class MobileInterpreter : public Interpreter<MobileAction>, public Singleton<MobileInterpreter> {
	private:
		MobileInterpreter(void);
		~MobileInterpreter(void);
		friend class Singleton<MobileInterpreter>;
	};
	
	class Name : public MobileAction, public Singleton<Name>{
	private:
		Name(void) {};
		~Name(void) {};
		friend class Singleton<Name>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::MCharacter* area);
		std::string getName() { return "Name"; };
	};

	class Description : public MobileAction, public Singleton<Description>{
	private:
		Description(void) {};
		~Description(void) {};
		friend class Singleton<Description>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::MCharacter* area);
		std::string getName() { return "Description"; };
	};

	class Show : public MobileAction, public Singleton<Show> {
	private:
		Show(void) {};
		~Show(void) {};
		friend class Singleton<Show>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::MCharacter* area);
		std::string getName() { return "Show"; };
	};

	class Save : public MobileAction, public Singleton<Save> {
	private:
		Save(void) {};
		~Save(void) {};
		friend class Singleton<Save>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::MCharacter* area);
		std::string getName() { return "Save"; };
	};
};
