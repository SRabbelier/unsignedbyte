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

#include "EditorArea.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "TableImpls.h"

#include "Account.h"
#include "Area.h"
#include "AreaManager.h"

EditorArea::AreaCommand EditorArea::m_editName("Name", &EditorArea::editName);
EditorArea::AreaCommand EditorArea::m_editDescription("Description", &EditorArea::editDescription);
EditorArea::AreaCommand EditorArea::m_editHeight("Height", &EditorArea::editHeight);
EditorArea::AreaCommand EditorArea::m_editWidth("Width", &EditorArea::editWidth);
EditorArea::AreaCommand EditorArea::m_showArea("Show", &EditorArea::showArea);
EditorArea::AreaCommand EditorArea::m_saveArea("Save", &EditorArea::saveArea);

EditorArea::EditorArea(UBSocket* sock) :
OLCEditor(sock),
m_area()
{
	listCommands(Global::Get()->EmptyString);
}

EditorArea::~EditorArea(void)
{

}

std::string EditorArea::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	AreaCommand* act = AreaInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorArea::dispatch(const std::string& action, const std::string& argument)
{
	AreaCommand* act = AreaInterpreter::Get()->translate(action);
	
	if(act && !m_area)
	{
		m_sock->Send("You need to be editing an area first.\n");
		m_sock->Send("(Use the 'edit' command.)\n");
		return;
	}
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorArea::getEditing()
{
	return m_area;
}

TableImplPtr EditorArea::getTable()
{
	return db::TableImpls::Get()->AREAS;
}

KeysPtr EditorArea::addNew()
{
	return mud::AreaManager::Get()->Add();
}

std::vector<std::string> EditorArea::getList()
{
	return mud::AreaManager::Get()->List();
}

void EditorArea::setEditing(KeysPtr keys)
{
	if(!keys->size())
	{
		m_area.reset();
		return;
	}
	
	m_area = mud::AreaManager::Get()->GetByKey(keys->first()->getValue());
	return;
}

std::vector<std::string> EditorArea::getCommands()
{
	return AreaInterpreter::Get()->getWords();
}

EditorArea::AreaInterpreter::AreaInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("description", &m_editDescription);
	addWord("height", &m_editHeight);
	addWord("width", &m_editWidth);
	addWord("show", &m_showArea);
	addWord("save", &m_saveArea);
}

EditorArea::AreaInterpreter::~AreaInterpreter(void)
{

}

void EditorArea::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Area name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Area name changed from '%s' to '%s'.\n", m_area->getName().c_str(), argument.c_str());
	m_area->setName(argument);
	return;
}

void EditorArea::editDescription(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	m_sock->Sendf("Area description changed from '%s' to '%s'.\n", m_area->getDescription().c_str(), argument.c_str());
	m_area->setDescription(argument);
	return;
}

void EditorArea::editHeight(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Please specify the area's height!\n");
		return;
	}

	int height = atoi(argument.c_str());
	if(height <= 0)
	{
		m_sock->Sendf("Please specify a height > 0!\n");
		return;
	}

	m_sock->Sendf("Area height changed from '%d' to '%d'.\n", m_area->getHeight(), height);
	m_area->setHeight(height);
	return;
}

void EditorArea::editWidth(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Please specify the area's width!\n");
		return;
	}

	int width = atoi(argument.c_str());
	if(width <= 0)
	{
		m_sock->Sendf("Please specify a width > 0!\n");
		return;
	}

	m_sock->Sendf("Area width changed from '%d' to '%d'.\n", m_area->getWidth(), width);
	m_area->setWidth(width);
	return;
}

void EditorArea::showArea(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_area->Show(), "Area"));
}

void EditorArea::saveArea(const std::string& argument)
{
	m_sock->Sendf("Saving area '%s'.\n", m_area->getName().c_str());
	m_area->Save();
	m_sock->Send("Saved.\n");
	return;
}
