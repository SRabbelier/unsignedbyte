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

namespace mud 
{ 
	class Detail; 
	typedef SmartPtr<mud::Detail> DetailPtr;
};

class EditorDetail : public Editor
{
public:
	typedef CommandObject<EditorDetail> DetailCommand;

	EditorDetail(UBSocket* sock, mud::DetailPtr detail);
	~EditorDetail(void);
	
	void OnFocus();

	std::string name() { return "Detail"; };
	std::string prompt() { return "Detail> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	void listCommands(const std::string& argument);
	void editKey(const std::string& argument);
	void editDescription(const std::string& argument);
	void showDetail(const std::string& argument);
	void saveDetail(const std::string& argument);

private:
	EditorDetail(const EditorDetail& rhs);
	EditorDetail operator=(const EditorDetail& rhs);
	
	enum E_TARGET
	{
		M_NONE,
		M_DESCRIPTION,
	};
	
	mud::DetailPtr m_detail;
	std::string m_value;
	EditorDetail::E_TARGET m_target;
	
	class DetailInterpreter : public Interpreter<DetailCommand>, public Singleton<DetailInterpreter> {
	private:
		DetailInterpreter(void);
		~DetailInterpreter(void);
		friend class Singleton<DetailInterpreter>;
	};

	static DetailCommand m_listCommands;
	static DetailCommand m_editKey;
	static DetailCommand m_editDescription;
	static DetailCommand m_showDetail;
	static DetailCommand m_saveDetail;
};
