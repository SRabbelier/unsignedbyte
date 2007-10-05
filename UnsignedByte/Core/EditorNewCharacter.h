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

class EditorNewCharacter : public Editor
{
public:
	EditorNewCharacter(UBSocket* sock);
	~EditorNewCharacter(void);

	void OnLine(const std::string &line);
	std::string name() { return "CharacterCreation"; };

private:
	EditorNewCharacter(const EditorNewCharacter& rhs);
	EditorNewCharacter operator=(const EditorNewCharacter& rhs);

	enum E_STATE
	{
		M_FIRST,
		M_NAME,
		M_NAMECONFIRM,
		M_RACE,
		M_DONE,
	};

	int m_state;
	std::string m_name;
	long m_raceid;
};
