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
#include "Action.h"

class UBSocket;

class EditorBool : public Editor
{
public:
	EditorBool(UBSocket* sock, bool& target);
	~EditorBool(void);

	void OnLine(const std::string& line);
	std::string name() { return "Bool"; };
	
private:
	EditorBool(const EditorBool& rhs);
	EditorBool operator=(const EditorBool& rhs);
	
	enum E_STATE
	{
		M_FIRST,
		M_WAITNG_FOR_CHOICE,
		M_DONE,
	};
	
	E_STATE m_state;
	bool& m_target;
	bool m_result;
};