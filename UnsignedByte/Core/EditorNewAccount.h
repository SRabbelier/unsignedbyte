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

class UBSocket;

class EditorNewAccount : public Editor
{
public:
	EditorNewAccount(UBSocket* sock);
	~EditorNewAccount(void);

	void OnLine(const std::string& line);
	std::string name() { return "AccountCreation"; };

private:
	EditorNewAccount(const EditorNewAccount& rhs) : Editor(rhs.m_sock) { };
	EditorNewAccount operator=(const EditorNewAccount& rhs) { return *this; };

	enum E_STATE
	{
		M_FIRST,
		M_NAME,
		M_NAMECONFIRM,
		M_PASSWORD,
		M_PASSWORDCONFIRM,
		M_DONE,
	};

	int m_state;
	std::string m_name;
	std::string m_password;
};
