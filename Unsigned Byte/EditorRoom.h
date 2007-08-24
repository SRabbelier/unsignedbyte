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
class Room;
class EditorRoom;

class EditorRoom : public OLCEditor
{
public:
	EditorRoom(UBSocket* sock);
	~EditorRoom(void);

	std::string name() { return "Room"; };
	std::string prompt() { return "Room> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	Savable* getEditing();
	Table* getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);

private:
	EditorRoom(const EditorRoom& rhs) : OLCEditor(rhs.m_sock) {};
	EditorRoom operator=(const EditorRoom& rhs) { return *this; };

	long m_area;
	long m_xpos;
	long m_ypos;
	Room* m_room;
	// void getRoom(const std::string&);

	typedef Action<EditorRoom> GeneralAction;
	typedef EditorAction<UBSocket, Room> RoomAction;

	class RoomInterpreter : public Interpreter<RoomAction>, public Singleton<RoomInterpreter> {
	private:
		RoomInterpreter(void);
		~RoomInterpreter(void);
		friend class Singleton<RoomInterpreter>;
	};

	class DirectionInterpreter : public Interpreter<GeneralAction>, public Singleton<DirectionInterpreter> {
	private:
		DirectionInterpreter(void);
		~DirectionInterpreter(void);
		friend class Singleton<DirectionInterpreter>;
	};

	/*
	class Activate : public GeneralAction, public Singleton<Activate> {
	private:
		Activate(void) {};
		~Activate(void) {};
		friend class Singleton<Activate>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "Activate"; };
	};
	*/

	class Map : public GeneralAction, public Singleton<Map> {
	private:
		Map(void) {};
		~Map(void) {};
		friend class Singleton<Map>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "Map"; };
	};

	/*
	class North : public GeneralAction, public Singleton<North> {
	private:
		North(void) {};
		~North(void) {};
		friend class Singleton<North>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "North"; };
	};
	
	class NorthEast : public GeneralAction, public Singleton<NorthEast> {
	private:
		NorthEast(void) {};
		~NorthEast(void) {};
		friend class Singleton<NorthEast>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "NorthEast"; };
	};

	class East : public GeneralAction, public Singleton<East> {
	private:
		East(void) {};
		~East(void) {};
		friend class Singleton<East>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "East"; };
	};

	class SouthEast : public GeneralAction, public Singleton<SouthEast> {
	private:
		SouthEast(void) {};
		~SouthEast(void) {};
		friend class Singleton<SouthEast>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "SouthEast"; };
	}; 

	class South : public GeneralAction, public Singleton<South> {
	private:
		South(void) {};
		~South(void) {};
		friend class Singleton<South>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "South"; };
	};
	
	class SouthWest : public GeneralAction, public Singleton<SouthWest> {
	private:
		SouthWest(void) {};
		~SouthWest(void) {};
		friend class Singleton<SouthWest>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "SouthWest"; };
	};

	class West : public GeneralAction, public Singleton<West> {
	private:
		West(void) {};
		~West(void) {};
		friend class Singleton<West>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "West"; };
	};	
	
	class NorthWest : public GeneralAction, public Singleton<NorthWest> {
	private:
		NorthWest(void) {};
		~NorthWest(void) {};
		friend class Singleton<NorthWest>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "NorthWest"; };
	};
	*/
	
	class AreaList : public GeneralAction, public Singleton<AreaList> {
	private:
		AreaList(void) {};
		~AreaList(void) {};
		friend class Singleton<AreaList>;
	public: 
		void Run(EditorRoom* editor, const std::string& argument);
		std::string getName() { return "Areas"; };
	};
	class Name : public RoomAction, public Singleton<Name>{
	private:
		Name(void) {};
		~Name(void) {};
		friend class Singleton<Name>;
	public: 
		void Run(UBSocket* sock, const std::string& argument, Room* room);
		std::string getName() { return "Name"; };
	};

	class Description : public RoomAction, public Singleton<Description>{
	private:
		Description(void) {};
		~Description(void) {};
		friend class Singleton<Description>;
	public: 
		void Run(UBSocket* sock, const std::string& argument, Room* room);
		std::string getName() { return "Description"; };
	};

	class Sectors : public RoomAction, public Singleton<Sectors> {
	private:
		Sectors(void) {};
		~Sectors(void) {};
		friend class Singleton<Sectors>;
	public: 
		void Run(UBSocket* sock, const std::string& argument, Room* room);
		std::string getName() { return ":Sectors"; };
	};

	class Save : public RoomAction, public Singleton<Save> {
	private:
		Save(void) {};
		~Save(void) {};
		friend class Singleton<Save>;
	public: 
		void Run(UBSocket* sock, const std::string& argument, Room* room);
		std::string getName() { return "Save"; };
	};

	class Close : public RoomAction, public Singleton<Close> {
	private:
		Close(void) {};
		~Close(void) {};
		friend class Singleton<Close>;
	public: 
		void Run(UBSocket* sock, const std::string& argument, Room* room);
		std::string getName() { return "Close"; };
	};

	class Open : public RoomAction, public Singleton<Open> {
	private:
		Open(void) {};
		~Open(void) {};
		friend class Singleton<Open>;
	public: 
		void Run(UBSocket* sock, const std::string& argument, Room* room);
		std::string getName() { return "Open"; };
	};

	class Deactivate : public RoomAction, public Singleton<Deactivate> {
	private:
		Deactivate(void) {};
		~Deactivate(void) {};
		friend class Singleton<Deactivate>;
	public:
		void Run(UBSocket* sock, const std::string& argument, Room* room);
		std::string getName() { return "Deactivate"; };
	};

};
