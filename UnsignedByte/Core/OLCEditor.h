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
#include "Global.h"
#include "Editor.h"
#include "Interpreter.h"
#include "singleton.h"
#include "Action.h"

class Savable;
class Table;

class OLCEditor : public Editor
{
public:
	OLCEditor(UBSocket* sock) : Editor(sock) {};
	virtual ~OLCEditor(void) {};
	
	virtual std::string lookup(const std::string& action);
	virtual void dispatch(const std::string& action, const std::string& argument);
	
	virtual Savable* getEditing() = 0;
	virtual Table* getTable() = 0;
	virtual long addNew() = 0;

	virtual std::vector<std::string> getList() = 0;
	virtual std::vector<std::string> getCommands() = 0;
	
	virtual void setEditing(long id) = 0;
	
private:
	OLCEditor(const OLCEditor& rhs) : Editor(rhs.m_sock) {};
	
protected:	
	typedef Action<OLCEditor> GeneralAction;
	typedef EditorAction<UBSocket, Savable> SavableAction;
	
	class GeneralInterpreter : public Interpreter<GeneralAction>, public Singleton<GeneralInterpreter> {
	private:
		GeneralInterpreter(void);
		~GeneralInterpreter(void);
		friend class Singleton<GeneralInterpreter>;
	};

	class Commands : public GeneralAction, public Singleton<Commands> {
	private:
		Commands(void) {};
		~Commands(void) {};
		friend class Singleton<Commands>;
	public:
		void Run(OLCEditor* editor, const std::string& argument);
		std::string getName() { return "Commands"; };
	};

	class New : public GeneralAction, public Singleton<New> {
	private:
		New(void) {};
		~New(void) {};
		friend class Singleton<New>;
	public:
		void Run(OLCEditor* editor, const std::string& argument);
		std::string getName() { return "New"; };
	};

	class Edit : public GeneralAction, public Singleton<Edit> {
	private:
		Edit(void) {};
		~Edit(void) {};
		friend class Singleton<Edit>;
	public:
		void Run(OLCEditor* editor, const std::string& argument);
		std::string getName() { return "Edit"; };
	};

	class Quit : public GeneralAction, public Singleton<Quit> {
	private:
		Quit(void) {};
		~Quit(void) {};
		friend class Singleton<Quit>;
	public:
		void Run(OLCEditor* editor, const std::string& argument);
		std::string getName() { return "Quit"; };
	};
	
	class Done : public GeneralAction, public Singleton<Done> {
	private:
		Done(void) {};
		~Done(void) {};
		friend class Singleton<Done>;
	public:
		void Run(OLCEditor* editor, const std::string& argument);
		std::string getName() { return "Done"; };
	};
	
	class List : public GeneralAction, public Singleton<List> {
	private:
		List(void) {};
		~List(void) {};
		friend class Singleton<List>;
	public:
		void Run(OLCEditor* editor, const std::string& argument);
		std::string getName() { return "List"; };
	};
};
