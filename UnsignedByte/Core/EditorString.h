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

class EditorString : public Editor
{
public:
	EditorString(UBSocket* sock, std::string& target);
	~EditorString(void);

	void OnLine(const std::string& line);
	std::string name() { return "String"; };
	
private:
	EditorString(const EditorString& rhs);
	EditorString operator=(const EditorString& rhs);
	
	enum E_STATE
	{
		M_FIRST,
		M_WAITING_FOR_INPUT,
		M_APPEND,
		M_REPLACE,
		M_VIEW,
		M_DONE,
	};
	
	EditorString::E_STATE ParseMode(char mode, bool silent = false);
	void ParseDot(const std::string& line);
	
	std::vector<std::string> m_strings;
	E_STATE m_state;
	std::string& m_target;
};
