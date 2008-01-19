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

#include "Types.h"

#include "Editor.h"
#include "Interpreter.h"
#include "CommandObject.h"

class EditorOLC : public Editor
{
public:
	typedef CommandObject<EditorOLC> OLCCommand;

	EditorOLC(UBSocket* sock);
	~EditorOLC(void);

	std::string name() { return "OLC"; };
	std::string prompt() { return "OLC> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	void startAreas(const std::string& argument);
	void startRooms(const std::string& argument);
	void startScripts(const std::string& argument);
	void startMobiles(const std::string& argument);
	void startSectors(const std::string& argument);
	void startColours(const std::string& argument);
	void startCommands(const std::string& argument);
	void startChunks(const std::string& argument);
	void listCommands(const std::string& argument);
	void quitEditor(const std::string& argument);

private:
	EditorOLC(const EditorOLC& rhs);
	EditorOLC operator=(const EditorOLC& rhs);

	class OLCInterpreter : public Interpreter<OLCCommand>, public Singleton<OLCInterpreter> {
	private:
		OLCInterpreter(void);
		~OLCInterpreter(void);
		friend class Singleton<OLCInterpreter>;
	};
	
	static OLCCommand m_startAreas;
	static OLCCommand m_startRooms;
	static OLCCommand m_startScripts;
	static OLCCommand m_startMobiles;
	static OLCCommand m_startSectors;
	static OLCCommand m_startColours;
	static OLCCommand m_startCommands;
	static OLCCommand m_startChunks;
	static OLCCommand m_listCommands;
	static OLCCommand m_quitEditor;
};
