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

#include <vector>
#include <string>

#include "EditorArea.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Action.h"

#include "Account.h"
#include "Area.h"
#include "Area.h"

EditorArea::EditorArea(UBSocket* sock) :
OLCEditor(sock),
m_area(NULL)
{
	// TODO - commands
	OnLine(Global::Get()->EmptyString);
}

EditorArea::~EditorArea(void)
{

}

std::string EditorArea::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	AreaAction* act = AreaInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorArea::dispatch(const std::string& action, const std::string& argument)
{
	AreaAction* act = AreaInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_area);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

Savable* EditorArea::getEditing()
{
	return m_area;
}

Table* EditorArea::getTable()
{
	return Tables::Get()->AREAS;
}

long EditorArea::addNew()
{
	return mud::Cache::Get()->AddArea();
}

std::vector<std::string> EditorArea::getList()
{
	return mud::Area::List();
}

void EditorArea::setEditing(long id)
{
	if(id == 0)
	{
		m_area = NULL;
		return;
	}
	
	m_area = mud::Cache::Get()->GetArea(id);
	return;
}

std::vector<std::string> EditorArea::getCommands()
{
	return AreaInterpreter::Get()->getWords();
}

EditorArea::AreaInterpreter::AreaInterpreter(void)
{
	addWord("name", Name::Get());
	addWord("description", Description::Get());
	addWord("height", Height::Get());
	addWord("width", Width::Get());
	addWord("show", Show::Get());
	addWord("save", Save::Get());
}

EditorArea::AreaInterpreter::~AreaInterpreter(void)
{
	Name::Free();
	Description::Free();
	Height::Free();
	Width::Free();
	Show::Free();
	Save::Free();
}

void EditorArea::Name::Run(UBSocket* sock, const std::string& argument, mud::Area* area)
{
	if(argument.size() == 0)
	{
		sock->Send("Area name can't be zero length!\n");
		return;
	}

	sock->Sendf("Area name changed from '%s' to '%s'.\n", area->getName().c_str(), argument.c_str());
	area->setName(argument);
	return;
}

void EditorArea::Description::Run(UBSocket* sock, const std::string& argument, mud::Area* area)
{
	if(!area->Exists())
	{
		sock->Send("For some reason the area you are editing does not exist.\n");
		return;
	}

	if(argument.size() == 0)
	{
		sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	sock->Sendf("Area description changed from '%s' to '%s'.\n", area->getDescription().c_str(), argument.c_str());
	area->setDescription(argument);
	return;
}

void EditorArea::Height::Run(UBSocket* sock, const std::string& argument, mud::Area* area)
{
	if(argument.size() == 0)
	{
		sock->Send("Please specify the area's height!\n");
		return;
	}

	int height = atoi(argument.c_str());
	if(height <= 0)
	{
		sock->Sendf("Please specify a height > 0!\n");
		return;
	}

	sock->Sendf("Area height changed from '%d' to '%d'.\n", area->getHeight(), height);
	area->setHeight(height);
	return;
}

void EditorArea::Width::Run(UBSocket* sock, const std::string& argument, mud::Area* area)
{
	if(argument.size() == 0)
	{
		sock->Send("Please specify the area's width!\n");
		return;
	}

	int width = atoi(argument.c_str());
	if(width <= 0)
	{
		sock->Sendf("Please specify a width > 0!\n");
		return;
	}

	sock->Sendf("Area width changed from '%d' to '%d'.\n", area->getWidth(), width);
	area->setWidth(width);
	return;
}

void EditorArea::Show::Run(UBSocket* sock, const std::string& argument, mud::Area* area)
{
	sock->Send(String::Get()->box(area->Show(), "Area"));
}

void EditorArea::Save::Run(UBSocket* sock, const std::string& argument, mud::Area* area)
{
	sock->Sendf("Saving area '%s'.\n", area->getName().c_str());
	area->Save();
	sock->Send("Saved.\n");
	return;
}
