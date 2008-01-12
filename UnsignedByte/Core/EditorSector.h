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
namespace mud { class Sector; }

class EditorSector : public OLCEditor
{
public:
	typedef CommandObject<EditorSector> SectorCommand;

	EditorSector(UBSocket* sock);
	~EditorSector(void);

	std::string name() { return "Sector"; };
	std::string prompt() { return "Sector> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TableImplPtr getTable();
	long addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(long id);
	
	void editName(const std::string& argument);
	void editSymbol(const std::string& argument);
	void editMoveCost(const std::string& argument);
	void editWater(const std::string& argument);
	void showSector(const std::string& argument);
	void saveSector(const std::string& argument);

private:
	SmartPtr<mud::Sector> m_sector;
	EditorSector(const EditorSector& rhs);
	EditorSector operator=(const EditorSector& rhs);

private:

	class SectorInterpreter : public Interpreter<SectorCommand>, public Singleton<SectorInterpreter> {
	private:
		SectorInterpreter(void);
		~SectorInterpreter(void);
		friend class Singleton<SectorInterpreter>;
	};
	
	static SectorCommand m_editName;
	static SectorCommand m_editSymbol;
	static SectorCommand m_editMoveCost;
	static SectorCommand m_editWater;
	static SectorCommand m_showSector;
	static SectorCommand m_saveSector;
};
