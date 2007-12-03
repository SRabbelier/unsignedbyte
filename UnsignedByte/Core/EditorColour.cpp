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

#include "EditorColour.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"
#include "Command.h"
#include "Permission.h"

#include "Action.h"
#include "Account.h"
#include "Colour.h"

using mud::Colour;

EditorColour::ColourCommand EditorColour::m_editName("Name", &EditorColour::editName);
EditorColour::ColourCommand EditorColour::m_editColourString("ColourString", &EditorColour::editColourString);
EditorColour::ColourCommand EditorColour::m_saveColour("Save", &EditorColour::saveColour);
EditorColour::ColourCommand EditorColour::m_showColour("Show", &EditorColour::showColour);

EditorColour::EditorColour(UBSocket* sock) :
OLCEditor(sock),
m_colour(NULL)
{
	SavableCommand* act = &OLCEditor::m_listCommands;
	act->Run(this, Global::Get()->EmptyString);
}

EditorColour::~EditorColour(void)
{

}

std::string EditorColour::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	ColourCommand* act = ColourInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorColour::dispatch(const std::string& action, const std::string& argument)
{
	ColourCommand* act = ColourInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorColour::getEditing()
{
	return m_colour;
}

TablePtr EditorColour::getTable()
{
	return Tables::Get()->COLOURS;
}

long EditorColour::addNew()
{
	return mud::Cache::Get()->AddColour();
	return 0;
}

std::vector<std::string> EditorColour::getList()
{
	return Colour::List();
}

void EditorColour::setEditing(long id)
{
	if(id == 0)
	{
		m_colour = NULL;
		return;
	}
	
	m_colour = mud::Cache::Get()->GetColourByKey(id);
	return;
}

std::vector<std::string> EditorColour::getCommands()
{
	return ColourInterpreter::Get()->getWords();
}

EditorColour::ColourInterpreter::ColourInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("colourstring", &m_editColourString);
	addWord("show", &m_showColour);
	addWord("save", &m_saveColour);
}

EditorColour::ColourInterpreter::~ColourInterpreter(void)
{

}

void EditorColour::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Colour name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Colour name changed from '%s' to '%s'.\n", m_colour->getName().c_str(), argument.c_str());
	m_colour->setName(argument);
	return;
}

void EditorColour::editColourString(const std::string& argument)
{
	if(!m_colour->Exists())
	{
		m_sock->Send("For some reason the colour you are editing does not exist.\n");
		return;
	}

	if(argument.size() == 0)
	{
		m_sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	m_sock->Sendf("Colour ColourString changed from '%s' to '%s'.\n", m_colour->getColourString().c_str(), argument.c_str());
	m_colour->setColourString(argument);
	return;
}

void EditorColour::saveColour(const std::string& argument)
{
	m_sock->Send("Saving...\n");
	m_colour->Save();
	m_sock->Send("Saved.\n");
	return;
}

void EditorColour::showColour(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_colour->Show(), "Colour"));
	return;
}
