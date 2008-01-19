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

class EditorOOC : public Editor
{
public:
	typedef CommandObject<EditorOOC> OOCCommand;
	
	EditorOOC(UBSocket* sock);
	~EditorOOC(void);

	std::string name() { return "OOC"; };
	std::string prompt() { return "OOC> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	void listCommands(const std::string& argument);
	void sendOOCMessage(const std::string& argument);
	void listOnlineCharacters(const std::string& argument);
	void listCharacters(const std::string& argument);
	
private:
	EditorOOC(const EditorOOC& rhs);
	EditorOOC operator=(const EditorOOC& rhs);
	
	class OOCInterpreter : public Interpreter<OOCCommand>, public Singleton<OOCInterpreter> {
	private:
		OOCInterpreter(void);
		~OOCInterpreter(void);
		friend class Singleton<OOCInterpreter>;
	};
	
	static OOCCommand m_listCommands;
	static OOCCommand m_sendOOCMessage;
	static OOCCommand m_listOnlineCharacters;
	static OOCCommand m_listCharacters;
};
