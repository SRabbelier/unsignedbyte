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
#include "singleton.h"
#include "Interpreter.h"
#include "CommandObject.h"

class UBSocket;

class EditorAccount : public Editor
{
public:
	typedef CommandObject<EditorAccount> AccountCommand;

	EditorAccount(UBSocket* sock);
	~EditorAccount(void);
	
	std::string name() { return "Account"; };
	std::string prompt() { return "Account> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	void listCommands(const std::string& argument);
	void beginLogin(const std::string& argument);
	void beginOLC(const std::string& argument);
	void beginCreation(const std::string& argument);
	void beginOOC(const std::string& argument);
	void quitEditor(const std::string& argument);
	void shutdownGame(const std::string& argument);
	void listCharacters(const std::string& argument);
	

private: 
	EditorAccount(const EditorAccount& rhs);
	EditorAccount operator=(const EditorAccount& rhs);

	class AccountInterpreter : public Interpreter<AccountCommand>, public Singleton<AccountInterpreter> {
	private:
		AccountInterpreter(void);
		~AccountInterpreter(void);
		friend class Singleton<AccountInterpreter>;
	};
	
	static AccountCommand m_listCommands;
	static AccountCommand m_beginLogin;
	static AccountCommand m_beginOLC;
	static AccountCommand m_beginOOC;
	static AccountCommand m_beginCreation;
	static AccountCommand m_quitEditor;
	static AccountCommand m_shutdownGame;
	static AccountCommand m_listCharacters;
};
