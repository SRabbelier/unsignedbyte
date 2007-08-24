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
class Colour;

class EditorColour : public OLCEditor
{
public:
	EditorColour(UBSocket* sock);
	~EditorColour(void);

	std::string name() { return "Colour"; };
	std::string prompt() { return "Colour> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	Savable* getEditing();
	Table* getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);

private:
	Colour* m_colour;
	
	EditorColour(const EditorColour& rhs) : OLCEditor(rhs.m_sock) {};
	EditorColour operator=(const EditorColour& rhs) {return *this;};

private:
	typedef EditorAction<UBSocket, Colour> ColourAction;

	class ColourInterpreter : public Interpreter<ColourAction>, public Singleton<ColourInterpreter> {
	private:
		ColourInterpreter(void);
		~ColourInterpreter(void);
		friend class Singleton<ColourInterpreter>;
	};
	
	class Name : public ColourAction, public Singleton<Name>{
	private:
		Name(void) {};
		~Name(void) {};
		friend class Singleton<Name>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Colour* colour);
		std::string getName() { return "Name"; };
	};

	class ColourString : public ColourAction, public Singleton<ColourString>{
	private:
		ColourString(void) {};
		~ColourString(void) {};
		friend class Singleton<ColourString>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Colour* colour);
		std::string getName() { return "ColourString"; };
	};
	
	class Save : public ColourAction, public Singleton<Save> {
	private:
		Save(void) {};
		~Save(void) {};
		friend class Singleton<Save>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Colour* colour);
		std::string getName() { return "Save"; };
	};
	
	class Show : public ColourAction, public Singleton<Show> {
	private:
		Show(void) {};
		~Show(void) {};
		friend class Singleton<Show>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Colour* colour);
		std::string getName() { return "Show"; };
	};
};
