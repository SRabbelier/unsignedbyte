/***************************************************************************
 *   Copyright (C) 2008 by Sverre Rabbelier                                *
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

#include "OLCEditor.h"
#include "Interpreter.h"
#include "CommandObject.h"

namespace mud 
{ 
	class Race; 
	typedef SmartPtr<mud::Race> RacePtr;
};

class EditorRace : public OLCEditor
{
public:
	typedef CommandObject<EditorRace> RaceCommand;

	EditorRace(UBSocket* sock);
	~EditorRace(void);

	std::string name() { return "Race"; };
	std::string prompt() { return "Race> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TableImplPtr getTable();
	KeysPtr addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(KeysPtr keys);
	
	void editName(const std::string& argument);
	void editDescription(const std::string& argument);
	void editHeight(const std::string& argument);
	void editWidth(const std::string& argument);
	void showRace(const std::string& argument);
	void saveRace(const std::string& argument);

private:
	mud::RacePtr m_race;

	EditorRace(const EditorRace& rhs);
	EditorRace operator=(const EditorRace& rhs);
	
	class RaceInterpreter : public Interpreter<RaceCommand>, public Singleton<RaceInterpreter> {
	private:
		RaceInterpreter(void);
		~RaceInterpreter(void);
		friend class Singleton<RaceInterpreter>;
	};

	static RaceCommand m_editName;
	static RaceCommand m_editDescription;
	static RaceCommand m_editHeight;
	static RaceCommand m_editWidth;
	static RaceCommand m_showRace;
	static RaceCommand m_saveRace;
};
