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

#include "OLCEditor.h"
#include "Interpreter.h"
#include "CommandObject.h"

namespace mud { class Command; }

class EditorCommand : public OLCEditor
{
public:
	typedef CommandObject<EditorCommand> CommandCommand;

	EditorCommand(UBSocket* sock);
	~EditorCommand(void);

	std::string name() { return "Command"; };
	std::string prompt() { return "Command> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TableImplPtr getTable();
	KeysPtr addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(KeysPtr id);
	
	void editName(const std::string& argument);
	void editGrantGroups(const std::string& argument);
	void editHighForce(const std::string& argument);
	void editForce(const std::string& argument);
	void editLowForce(const std::string& argument);
	void showCommand(const std::string& argument);
	void saveCommand(const std::string& argument);

private:
	SmartPtr<mud::Command> m_command;
	
	EditorCommand(const EditorCommand& rhs);
	EditorCommand operator=(const EditorCommand& rhs);

	class CommandInterpreter : public Interpreter<CommandCommand>, public Singleton<CommandInterpreter> {
	private:
		CommandInterpreter(void);
		~CommandInterpreter(void);
		friend class Singleton<CommandInterpreter>;
	};

	static CommandCommand m_editName;
	static CommandCommand m_editGrantGroups;
	static CommandCommand m_editHighForce;
	static CommandCommand m_editForce;
	static CommandCommand m_editLowForce;
	static CommandCommand m_showCommand;
	static CommandCommand m_saveCommand;
};
