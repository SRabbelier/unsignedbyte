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
class Area;
class EditorArea;

class EditorArea : public OLCEditor
{
public:
	EditorArea(UBSocket* sock);
	~EditorArea(void);

	std::string name() { return "Area"; };
	std::string prompt() { return "Area> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	Savable* getEditing();
	Table* getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);

private:
	Area* m_area;

	EditorArea(const EditorArea& rhs) : OLCEditor(rhs.m_sock) {};
	EditorArea operator=(const EditorArea& rhs) {return *this;};

	typedef Action<EditorArea> GeneralAction;
	typedef EditorAction<UBSocket, Area> AreaAction;

	class AreaInterpreter : public Interpreter<AreaAction>, public Singleton<AreaInterpreter> {
	private:
		AreaInterpreter(void);
		~AreaInterpreter(void);
		friend class Singleton<AreaInterpreter>;
	};

	class Name : public AreaAction, public Singleton<Name>{
	private:
		Name(void) {};
		~Name(void) {};
		friend class Singleton<Name>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Area* area);
		std::string getName() { return "Name"; };
	};

	class Description : public AreaAction, public Singleton<Description>{
	private:
		Description(void) {};
		~Description(void) {};
		friend class Singleton<Description>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Area* area);
		std::string getName() { return ":Description"; };
	};

	class Height : public AreaAction, public Singleton<Height>{
	private:
		Height(void) {};
		~Height(void) {};
		friend class Singleton<Height>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Area* area);
		std::string getName() { return "Height"; };
	};

	class Width : public AreaAction, public Singleton<Width>{
	private:
		Width(void) {};
		~Width(void) {};
		friend class Singleton<Width>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Area* area);
		std::string getName() { return "Width"; };
	};

	class Show : public AreaAction, public Singleton<Show> {
	private:
		Show(void) {};
		~Show(void) {};
		friend class Singleton<Show>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Area* area);
		std::string getName() { return "Show"; };
	};

	class Save : public AreaAction, public Singleton<Save> {
	private:
		Save(void) {};
		~Save(void) {};
		friend class Singleton<Save>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Area* area);
		std::string getName() { return "Save"; };
	};

};