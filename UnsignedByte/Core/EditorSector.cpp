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

#include "EditorSector.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Action.h"

#include "Account.h"
#include "Sector.h"

using mud::Sector;

EditorSector::EditorSector(UBSocket* sock) :
OLCEditor(sock),
m_sector(NULL)
{
	GeneralAction* act = Commands::Get();
	act->Run(this, Global::Get()->EmptyString);
	OnLine(Global::Get()->EmptyString);
}

EditorSector::~EditorSector(void)
{

}

std::string EditorSector::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	SectorAction* act = SectorInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorSector::dispatch(const std::string& action, const std::string& argument)
{
	SectorAction* act = SectorInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_sector);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

Savable* EditorSector::getEditing()
{
	return m_sector;
}

Table* EditorSector::getTable()
{
	return Tables::Get()->SECTORS;
}

long EditorSector::addNew()
{
	return mud::Cache::Get()->AddSector();
}

std::vector<std::string> EditorSector::getList()
{
	return Sector::List();
}

void EditorSector::setEditing(long id)
{
	if(id == 0)
	{
		m_sector = NULL;
		return;
	}
	
	m_sector = mud::Cache::Get()->GetSector(id);
	return;
}

std::vector<std::string> EditorSector::getCommands()
{
	return SectorInterpreter::Get()->getWords();
}

EditorSector::SectorInterpreter::SectorInterpreter(void)
{
	addWord("name", Name::Get());
	addWord("symbol", Symbol::Get());
	addWord("movecost", MoveCost::Get());
	addWord("water", Water::Get());
	addWord("show", Show::Get());
	addWord("save", Save::Get());
}

EditorSector::SectorInterpreter::~SectorInterpreter(void)
{
	Name::Free();
	Symbol::Free();
	MoveCost::Free();
	Water::Free();
	Show::Free();
	Save::Free();
}

void EditorSector::Name::Run(UBSocket* sock, const std::string& argument, Sector* sector)
{
	if(argument.size() == 0)
	{
		sock->Send("Sector name can't be zero length!\n");
		return;
	}

	sock->Sendf("Sector name changed from '%s' to '%s'.\n", sector->getName().c_str(), argument.c_str());
	sector->setName(argument);
	return;
}

void EditorSector::MoveCost::Run(UBSocket* sock, const std::string& argument, Sector* sector)
{
	long movecost = atoi(argument.c_str());

	if(movecost < 0)
	{
		sock->Sendf("%s is not a valid movecost!", argument.c_str());
		return;
	}

	sock->Sendf("Sector movecost changed from '%d' to '%d'.\n", sector->getMoveCost(), movecost);
	sector->setMoveCost(movecost);
	return;
}

void EditorSector::Water::Run(UBSocket* sock, const std::string& argument, Sector* sector)
{
	sock->Sendf("Sector water flag toggled.\n");
	if(sector->isWater())
		sector->setWater(false);
	else
		sector->setWater(true);
	return;
}


void EditorSector::Symbol::Run(UBSocket* sock, const std::string& argument, Sector* sector)
{
	if(!sector->Exists())
	{
		sock->Send("For some reason the sector you are editing does not exist.\n");
		return;
	}

	if(argument.size() != 1)
	{
		sock->Send("Please provide one character to set as symbol!");
		return;
	}

	sock->Sendf("Sector symbol changed from '%s' to '%s'.\n", sector->getSymbol().c_str(), argument.c_str());
	sector->setSymbol(argument);
	return;
}

void EditorSector::Show::Run(UBSocket* sock, const std::string& argument, Sector* sector)
{
	if(!argument.compare("compact"))
	{
		sock->Sendf("%s(%s): %d%s", 
			sector->getName().c_str(),
			sector->getSymbol().c_str(),
			sector->getMoveCost(),
			(sector->isWater() ? " (water)\n" : "\n"));
	}
	else
	{
		sock->Sendf("Name: '%s'.\n", sector->getName().c_str());
		sock->Sendf("Symbol: '%s'.\n", sector->getSymbol().c_str());
		sock->Sendf("Movecost: '%d'.\n", sector->getMoveCost());
		if(sector->isWater())
			sock->Send("Sector is water type.\n");
	}
	return;
}

void EditorSector::Save::Run(UBSocket* sock, const std::string& argument, Sector* sector)
{
	sock->Sendf("Saving sector '%s'.\n", sector->getName().c_str());
	sector->Save();
	sock->Send("Saved.\n");
	return;
}
