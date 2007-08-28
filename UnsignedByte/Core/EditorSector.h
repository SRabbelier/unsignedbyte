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
class Sector;

class EditorSector : public OLCEditor
{
public:
	EditorSector(UBSocket* sock);
	~EditorSector(void);

	std::string name() { return "Sector"; };
	std::string prompt() { return "Sector> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	Savable* getEditing();
	Table* getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);

private:
	Sector* m_sector;
	EditorSector(const EditorSector& rhs) : OLCEditor(rhs.m_sock) {};
	EditorSector operator=(const EditorSector& rhs) { return *this; };

private:
	typedef EditorAction<UBSocket, Sector> SectorAction;

	class SectorInterpreter : public Interpreter<SectorAction>, public Singleton<SectorInterpreter> {
	private:
		SectorInterpreter(void);
		~SectorInterpreter(void);
		friend class Singleton<SectorInterpreter>;
	};
	
	class Name : public SectorAction, public Singleton<Name>{
	private:
		Name(void) {};
		~Name(void) {};
		friend class Singleton<Name>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Sector* area);
		std::string getName() { return "Name"; };
	};

	class Symbol : public SectorAction, public Singleton<Symbol>{
	private:
		Symbol(void) {};
		~Symbol(void) {};
		friend class Singleton<Symbol>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Sector* area);
		std::string getName() { return "Symbol"; };
	};

	class MoveCost : public SectorAction, public Singleton<MoveCost>{
	private:
		MoveCost(void) {};
		~MoveCost(void) {};
		friend class Singleton<MoveCost>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Sector* area);
		std::string getName() { return "MoveCost"; };
	};

	class Water : public SectorAction, public Singleton<Water>{
	private:
		Water(void) {};
		~Water(void) {};
		friend class Singleton<Water>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Sector* area);
		std::string getName() { return "Water"; };
	};

	class Show : public SectorAction, public Singleton<Show> {
	private:
		Show(void) {};
		~Show(void) {};
		friend class Singleton<Show>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Sector* area);
		std::string getName() { return "Show"; };
	};

	class Save : public SectorAction, public Singleton<Save> {
	private:
		Save(void) {};
		~Save(void) {};
		friend class Singleton<Save>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Sector* area);
		std::string getName() { return "Save"; };
	};
	
};
