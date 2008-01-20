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

#include "EditorSector.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "TableImpls.h"

#include "Account.h"
#include "Sector.h"
#include "SectorManager.h"

using mud::Sector;

EditorSector::SectorCommand EditorSector::m_editName("Name", &EditorSector::editName);
EditorSector::SectorCommand EditorSector::m_editSymbol("Description", &EditorSector::editSymbol);
EditorSector::SectorCommand EditorSector::m_editMoveCost("Height", &EditorSector::editMoveCost);
EditorSector::SectorCommand EditorSector::m_editWater("Width", &EditorSector::editWater);
EditorSector::SectorCommand EditorSector::m_showSector("Show", &EditorSector::showSector);
EditorSector::SectorCommand EditorSector::m_saveSector("Save", &EditorSector::saveSector);

EditorSector::EditorSector(UBSocket* sock) :
OLCEditor(sock),
m_sector()
{
	listCommands(Global::Get()->EmptyString);
}

EditorSector::~EditorSector(void)
{

}

std::string EditorSector::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	SectorCommand* act = SectorInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorSector::dispatch(const std::string& action, const std::string& argument)
{
	SectorCommand* act = SectorInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorSector::getEditing()
{
	return m_sector;
}

TableImplPtr EditorSector::getTable()
{
	return db::TableImpls::Get()->SECTORS;
}

KeysPtr EditorSector::addNew()
{
	return mud::SectorManager::Get()->Add();
}

std::vector<std::string> EditorSector::getList()
{
	return mud::SectorManager::Get()->List();
}

void EditorSector::setEditing(KeysPtr keys)
{
	if(!keys->size())
	{
		m_sector.reset();
		return;
	}
	
	m_sector = mud::SectorManager::Get()->GetByKey(keys->first()->getValue());
	return;
}

std::vector<std::string> EditorSector::getCommands()
{
	return SectorInterpreter::Get()->getWords();
}

EditorSector::SectorInterpreter::SectorInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("symbol", &m_editSymbol);
	addWord("movecost", &m_editMoveCost);
	addWord("water", &m_editWater);
	addWord("show", &m_showSector);
	addWord("save", &m_saveSector);
}

EditorSector::SectorInterpreter::~SectorInterpreter(void)
{

}

void EditorSector::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Sector name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Sector name changed from '%s' to '%s'.\n", m_sector->getName().c_str(), argument.c_str());
	m_sector->setName(argument);
	return;
}

void EditorSector::editMoveCost(const std::string& argument)
{
	long movecost = atoi(argument.c_str());

	if(movecost < 0)
	{
		m_sock->Sendf("%s is not a valid movecost!", argument.c_str());
		return;
	}

	m_sock->Sendf("Sector movecost changed from '%d' to '%d'.\n", m_sector->getMoveCost(), movecost);
	m_sector->setMoveCost(movecost);
	return;
}

void EditorSector::editWater(const std::string& argument)
{
	m_sock->Sendf("Sector water flag toggled.\n");
	if(m_sector->isWater())
		m_sector->setWater(false);
	else
		m_sector->setWater(true);
	return;
}


void EditorSector::editSymbol(const std::string& argument)
{
	if(!m_sector->Exists())
	{
		m_sock->Send("For some reason the sector you are editing does not exist.\n");
		return;
	}

	if(argument.size() != 1)
	{
		m_sock->Send("Please provide one character to set as symbol!");
		return;
	}

	m_sock->Sendf("Sector symbol changed from '%s' to '%s'.\n", m_sector->getSymbol().c_str(), argument.c_str());
	m_sector->setSymbol(argument);
	return;
}

void EditorSector::showSector(const std::string& argument)
{
	if(!argument.compare("compact"))
	{
		m_sock->Sendf("%s(%s): %d%s", 
			m_sector->getName().c_str(),
			m_sector->getSymbol().c_str(),
			m_sector->getMoveCost(),
			(m_sector->isWater() ? " (water)\n" : "\n"));
	}
	else
	{
		m_sock->Sendf("Name: '%s'.\n", m_sector->getName().c_str());
		m_sock->Sendf("Symbol: '%s'.\n", m_sector->getSymbol().c_str());
		m_sock->Sendf("Movecost: '%d'.\n", m_sector->getMoveCost());
		if(m_sector->isWater())
			m_sock->Send("Sector is water type.\n");
	}
	return;
}

void EditorSector::saveSector(const std::string& argument)
{
	m_sock->Sendf("Saving sector '%s'.\n", m_sector->getName().c_str());
	m_sector->Save();
	m_sock->Send("Saved.\n");
	return;
}
