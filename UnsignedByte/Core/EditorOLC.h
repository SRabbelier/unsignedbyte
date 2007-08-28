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

class EditorOLC : public Editor
{
public:
	EditorOLC(UBSocket* sock);
	~EditorOLC(void);

	std::string name() { return "OLC"; };
	std::string prompt() { return "OLC> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);

private:
	EditorOLC(const EditorOLC& rhs) : Editor(rhs.m_sock) {};
	EditorOLC operator=(const EditorOLC& rhs) { return *this; };

	class OLCInterpreter : public Interpreter<UBAction>, public Singleton<OLCInterpreter> {
	private:
		OLCInterpreter(void);
		~OLCInterpreter(void);
		friend class Singleton<OLCInterpreter>;
	};

	class Areas : public UBAction, public Singleton<Areas>{
	private:
		Areas(void) {};
		~Areas(void) {};
		friend class Singleton<Areas>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Areas"; };
	};

	class Rooms : public UBAction, public Singleton<Rooms>{
	private:
		Rooms(void) {};
		~Rooms(void) {};
		friend class Singleton<Rooms>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Rooms"; };
	};

	class Scripts : public UBAction, public Singleton<Scripts> {
	private:
		Scripts(void) {};
		~Scripts(void) {};
		friend class Singleton<Scripts>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Scripts"; };
	};

	class Mobiles : public UBAction, public Singleton<Mobiles> {
	private:
		Mobiles(void) {};
		~Mobiles(void) {};
		friend class Singleton<Mobiles>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Mobiles"; };
	};

	class Sectors : public UBAction, public Singleton<Sectors> {
	private:
		Sectors(void) {};
		~Sectors(void) {};
		friend class Singleton<Sectors>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Sectors"; };
	};

	class Colours : public UBAction, public Singleton<Colours> {
	private:
		Colours(void) {};
		~Colours(void) {};
		friend class Singleton<Colours>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Colours"; };
	};

	class Commands : public UBAction, public Singleton<Commands> {
	private:
		Commands(void) {};
		~Commands(void) {};
		friend class Singleton<Commands>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "Commands"; };
	};
	
	class ComEdit : public UBAction, public Singleton<ComEdit> {
	private:
		ComEdit(void) {};
		~ComEdit(void) {};
		friend class Singleton<ComEdit>;
	public:
		void Run(UBSocket* ch, const std::string& argument);
		std::string getName() { return "ComEdit"; };
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

};
