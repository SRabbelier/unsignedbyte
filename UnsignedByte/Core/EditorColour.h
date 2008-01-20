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

namespace mud { class Colour; }

class EditorColour : public OLCEditor
{
public:
	typedef CommandObject<EditorColour> ColourCommand;

	EditorColour(UBSocket* sock);
	~EditorColour(void);

	std::string name() { return "Colour"; };
	std::string prompt() { return "Colour> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TableImplPtr getTable();
	KeysPtr addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(KeysPtr keys);
	
	void editName(const std::string& argument);
	void editColourString(const std::string& argument);
	void saveColour(const std::string& argument);
	void showColour(const std::string& argument);

private:
	SmartPtr<mud::Colour> m_colour;
	
	EditorColour(const EditorColour& rhs);
	EditorColour operator=(const EditorColour& rhs);

private:
	class ColourInterpreter : public Interpreter<ColourCommand>, public Singleton<ColourInterpreter> {
	private:
		ColourInterpreter(void);
		~ColourInterpreter(void);
		friend class Singleton<ColourInterpreter>;
	};
	
	static ColourCommand m_editName;
	static ColourCommand m_editColourString;
	static ColourCommand m_saveColour;
	static ColourCommand m_showColour;

};
