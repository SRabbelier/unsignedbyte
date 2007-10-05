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
#include "Editor.h"
#include "Action.h"
#include "singleton.h"
#include "Interpreter.h"

class UBSocket;

class EditorAccount : public Editor
{
public:
	EditorAccount(UBSocket* sock);
	~EditorAccount(void);
	
	std::string name() { return "Account"; };
	std::string prompt() { return "Account> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);

private: 
	EditorAccount(const EditorAccount& rhs);
	EditorAccount operator=(const EditorAccount& rhs);

	class AccountInterpreter : public Interpreter<UBAction>, public Singleton<AccountInterpreter> {
	private:
		AccountInterpreter(void);
		~AccountInterpreter(void);
		friend class Singleton<AccountInterpreter>;
	};

	class Commands: public UBAction, public Singleton<Commands> {
	private:
		Commands(void) {};
		~Commands(void) {};
		friend class Singleton<Commands>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Commands"; };
	};

	class Login : public UBAction, public Singleton<Login> {
	private:
		Login(void) {};
		~Login(void) {};
		friend class Singleton<Login>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Login"; };
	};

	class OLC : public UBAction, public Singleton<OLC> {
	private:
		OLC(void) {};
		~OLC(void) {};
		friend class Singleton<OLC>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "OLC"; };
	};

	class New : public UBAction, public Singleton<New> {
	private:
		New(void) {};
		~New(void) {};
		friend class Singleton<New>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "New"; };
	};

	class Quit : public UBAction, public Singleton<Quit> {
	private:
		Quit(void) {};
		~Quit(void) {};
		friend class Singleton<Quit>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Quit"; };		
	};

	class Shutdown : public UBAction, public Singleton<Shutdown> {
	private:
		Shutdown(void) {};
		~Shutdown(void) {};
		friend class Singleton<Shutdown>;
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Shutdown"; };
	};

	class List : public UBAction, public Singleton<List> {
	private:
		List(void) {};
		~List(void) {};
		friend class Singleton<List>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "List"; };
	};

};
