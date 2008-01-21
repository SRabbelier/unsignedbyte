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
	class Area; 
	typedef SmartPtr<mud::Area> AreaPtr;
};

class EditorArea : public OLCEditor
{
public:
	typedef CommandObject<EditorArea> AreaCommand;

	EditorArea(UBSocket* sock);
	~EditorArea(void);

	std::string name() { return "Area"; };
	std::string prompt() { return "Area> "; };
	
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
	void showArea(const std::string& argument);
	void saveArea(const std::string& argument);

private:
	mud::AreaPtr m_area;

	EditorArea(const EditorArea& rhs);
	EditorArea operator=(const EditorArea& rhs);
	
	class AreaInterpreter : public Interpreter<AreaCommand>, public Singleton<AreaInterpreter> {
	private:
		AreaInterpreter(void);
		~AreaInterpreter(void);
		friend class Singleton<AreaInterpreter>;
	};

	static AreaCommand m_editName;
	static AreaCommand m_editDescription;
	static AreaCommand m_editHeight;
	static AreaCommand m_editWidth;
	static AreaCommand m_showArea;
	static AreaCommand m_saveArea;
};
