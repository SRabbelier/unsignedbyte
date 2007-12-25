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
#include "CommandObject.h"

class UBSocket;
namespace mud { class Room; }

class EditorRoom : public OLCEditor
{
public:
	typedef CommandObject<EditorRoom> RoomCommand;
	
	EditorRoom(UBSocket* sock);
	~EditorRoom(void);

	std::string name() { return "Room"; };
	std::string prompt() { return "Room> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TablePtr getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);
	
	void showMap(const std::string& argument);
	void activateRoom(const std::string& argument);
	void deactivateRoom(const std::string& argument);
	void goNorth(const std::string& argument);
	void goNorthEast(const std::string& argument);
	void goEast(const std::string& argument);
	void goSouthEast(const std::string& argument);
	void goSouth(const std::string& argument);
	void goSouthWest(const std::string& argument);
	void goWest(const std::string& argument);
	void goNorthWest(const std::string& argument);
	void listAreas(const std::string& argument);
	void editName(const std::string& argument);
	void editDescription(const std::string& argument);
	void editSector(const std::string& argument);
	void saveRoom(const std::string& argument);
	void closeExit(const std::string& argument);
	void openExit(const std::string& argument);

private:
	EditorRoom(const EditorRoom& rhs);
	EditorRoom operator=(const EditorRoom& rhs);

	long m_area;
	long m_xpos;
	long m_ypos;
	SmartPtr<mud::Room> m_room;

	class RoomInterpreter : public Interpreter<RoomCommand>, public Singleton<RoomInterpreter> {
	private:
		RoomInterpreter(void);
		~RoomInterpreter(void);
		friend class Singleton<RoomInterpreter>;
	};

	class DirectionInterpreter : public Interpreter<RoomCommand>, public Singleton<DirectionInterpreter> {
	private:
		DirectionInterpreter(void);
		~DirectionInterpreter(void);
		friend class Singleton<DirectionInterpreter>;
	};
	
	static RoomCommand m_showMap;
	static RoomCommand m_activateRoom;
	static RoomCommand m_deactivateRoom;
	static RoomCommand m_goNorth;
	static RoomCommand m_goNorthEast;
	static RoomCommand m_goEast;
	static RoomCommand m_goSouthEast;
	static RoomCommand m_goSouth;
	static RoomCommand m_goSouthWest;
	static RoomCommand m_goWest;
	static RoomCommand m_goNorthWest;
	static RoomCommand m_listAreas;
	static RoomCommand m_editName;
	static RoomCommand m_editDescription;
	static RoomCommand m_editSector;
	static RoomCommand m_saveRoom;
	static RoomCommand m_closeExit;
	static RoomCommand m_openExit;
};
