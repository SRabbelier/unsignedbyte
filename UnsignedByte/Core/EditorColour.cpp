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

EditorColour::EditorColour(UBSocket* sock) :
OLCEditor(sock),
m_colour(NULL)
{
	GeneralAction* act = Commands::Get();
	act->Run(this, Global::Get()->EmptyString);
	OnLine(Global::Get()->EmptyString);
}

EditorColour::~EditorColour(void)
{

}

std::string EditorColour::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	ColourAction* act = ColourInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorColour::dispatch(const std::string& action, const std::string& argument)
{
	ColourAction* act = ColourInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_colour);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

Savable* EditorColour::getEditing()
{
	return m_colour;
}

Table* EditorColour::getTable()
{
	return Tables::Get()->COLOURS;
}

long EditorColour::addNew()
{
	return Cache::Get()->AddColour();
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
	
	m_colour = Cache::Get()->GetColour(id);
	return;
}

std::vector<std::string> EditorColour::getCommands()
{
	return ColourInterpreter::Get()->getWords();
}

EditorColour::ColourInterpreter::ColourInterpreter(void)
{
	addWord("name", Name::Get());
	addWord("colourstring", ColourString::Get());
	addWord("show", Show::Get());
	addWord("save", Save::Get());
}

EditorColour::ColourInterpreter::~ColourInterpreter(void)
{
	Name::Free();
	ColourString::Free();
	Show::Free();
}

void EditorColour::Name::Run(UBSocket* sock, const std::string& argument, Colour* colour)
{
	if(argument.size() == 0)
	{
		sock->Send("Colour name can't be zero length!\n");
		return;
	}

	sock->Sendf("Colour name changed from '%s' to '%s'.\n", colour->getName().c_str(), argument.c_str());
	colour->setName(argument);
	return;
}

void EditorColour::ColourString::Run(UBSocket* sock, const std::string& argument, Colour* colour)
{
	if(!colour->Exists())
	{
		sock->Send("For some reason the colour you are editing does not exist.\n");
		return;
	}

	if(argument.size() == 0)
	{
		sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	sock->Sendf("Colour ColourString changed from '%s' to '%s'.\n", colour->getColourString().c_str(), argument.c_str());
	colour->setColourString(argument);
	return;
}

void EditorColour::Save::Run(UBSocket* sock, const std::string& argument, Colour* colour)
{
	sock->Send("Saving...\n");
	colour->Save();
	sock->Send("Saved.\n");
	return;
}

void EditorColour::Show::Run(UBSocket* sock, const std::string& argument, Colour* colour)
{
	sock->Send(String::Get()->box(colour->Show(), "Colour"));
	return;
}
