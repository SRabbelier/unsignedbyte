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
namespace mud { class Permission; }

class EditorPermission : public OLCEditor
{
public:
	typedef CommandObject<EditorPermission> PermissionCommand;
	
	EditorPermission(UBSocket* sock);
	~EditorPermission(void);

	std::string name() { return "Permission"; };
	std::string prompt() { return "Permission> "; };

	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TableImplPtr getTable();
	KeysPtr addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(KeysPtr keys);
	
	void editAccount(const std::string& argument);
	void editGrantGroup(const std::string& argument);
	void editGrant(const std::string& argument);
	void editLogging(const std::string& argument);
	void showPermission(const std::string& argument);
	void savePermission(const std::string& argument);

private:
	SmartPtr<mud::Permission> m_permission;
	value_type m_account;
	value_type m_grantgroup;
	
	EditorPermission(const EditorPermission& rhs);
	EditorPermission operator=(const EditorPermission& rhs);

	class PermissionInterpreter : public Interpreter<PermissionCommand>, public Singleton<PermissionInterpreter> {
	private:
		PermissionInterpreter(void);
		~PermissionInterpreter(void);
		friend class Singleton<PermissionInterpreter>;
	};
	
	static PermissionCommand m_editAccount;
	static PermissionCommand m_editGrantGroup;
	static PermissionCommand m_editGrant;
	static PermissionCommand m_editLogging;
	static PermissionCommand m_showPermission;
	static PermissionCommand m_savePermission;
};
