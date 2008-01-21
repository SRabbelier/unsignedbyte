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

#include "EditorOLC.h"
#include "EditorArea.h"
#include "EditorRoom.h"
#include "EditorMobile.h"
#include "EditorOLC.h"
#include "EditorSector.h"
#include "EditorColour.h"
#include "EditorCommand.h"
#include "EditorAccount.h"
#include "EditorChunk.h"
#include "EditorRace.h"

#include "UBSocket.h"
#include "Account.h"
#include "StringUtilities.h"

EditorOLC::OLCCommand EditorOLC::m_startAreas("Areas", &EditorOLC::startAreas);
EditorOLC::OLCCommand EditorOLC::m_startRooms("Rooms", &EditorOLC::startRooms);
EditorOLC::OLCCommand EditorOLC::m_startChunks("Chunks", &EditorOLC::startChunks);
EditorOLC::OLCCommand EditorOLC::m_startScripts("Scripts", &EditorOLC::startScripts);
EditorOLC::OLCCommand EditorOLC::m_startMobiles("Mobiles", &EditorOLC::startMobiles);
EditorOLC::OLCCommand EditorOLC::m_startSectors("Sectors", &EditorOLC::startSectors);
EditorOLC::OLCCommand EditorOLC::m_startColours("Colours", &EditorOLC::startColours);
EditorOLC::OLCCommand EditorOLC::m_startCommands("Commands", &EditorOLC::startCommands);
EditorOLC::OLCCommand EditorOLC::m_startRaces("Races", &EditorOLC::startRaces);
EditorOLC::OLCCommand EditorOLC::m_listCommands("?", &EditorOLC::listCommands);
EditorOLC::OLCCommand EditorOLC::m_quitEditor("Quit", &EditorOLC::quitEditor);

EditorOLC::EditorOLC(UBSocket* sock) :
Editor(sock)
{
	listCommands(Global::Get()->EmptyString);
}

EditorOLC::~EditorOLC(void)
{

}

std::string EditorOLC::lookup(const std::string& action)
{
	OLCCommand* act = OLCInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorOLC::dispatch(const std::string& action, const std::string& argument)
{
	OLCCommand* act = OLCInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		Global::Get()->bugf("EditorOLC::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}
	
EditorOLC::OLCInterpreter::OLCInterpreter(void)
{
	addWord("areas", &m_startAreas);
	addWord("rooms", &m_startRooms);
	addWord("scripts", &m_startScripts);
	addWord("mobiles", &m_startMobiles);
	addWord("sectors", &m_startSectors);
	addWord("colour", &m_startColours);
	addWord("commands", &m_startCommands);
	addWord("chunks", &m_startChunks);
	addWord("races", &m_startRaces);
	addWord("?", &m_listCommands);
	addWord("quit", &m_quitEditor);
}

EditorOLC::OLCInterpreter::~OLCInterpreter(void)
{

}

void EditorOLC::startAreas(const std::string& argument)
{
	m_sock->Send("Dropping you into Area Edit mode!\n");
	m_sock->SetEditor(new EditorArea(m_sock));
	return;
}


void EditorOLC::startRooms(const std::string& argument)
{
	m_sock->Send("Dropping you into Room Edit mode!\n");
	m_sock->SetEditor(new EditorRoom(m_sock));
	return;
}

void EditorOLC::startMobiles(const std::string& argument)
{
	m_sock->Send("Dropping you into Mobile Edit mode!\n");
	m_sock->SetEditor(new EditorMobile(m_sock));
	return;
}

void EditorOLC::startSectors(const std::string& argument)
{
	m_sock->Send("Dropping you into Sector Edit mode!\n");
	m_sock->SetEditor(new EditorSector(m_sock));
	return;
}

void EditorOLC::startColours(const std::string& argument)
{
	m_sock->Send("Dropping you into Colours Edit mode!\n");
	m_sock->SetEditor(new EditorColour(m_sock));
	return;
}

void EditorOLC::startCommands(const std::string& argument)
{
	m_sock->Send("Dropping you into Command Edit mode!\n");
	m_sock->SetEditor(new EditorCommand(m_sock));
	return;
}

void EditorOLC::startChunks(const std::string& argument)
{
	m_sock->Send("Dropping you into Chunk Edit mode!\n");
	m_sock->SetEditor(new EditorChunk(m_sock));
	return;
}

void EditorOLC::startRaces(const std::string& argument)
{
	m_sock->Send("Dropping you into Race Edit mode!\n");
	m_sock->SetEditor(new EditorRace(m_sock));
	return;
}

void EditorOLC::startScripts(const std::string& argument)
{
	m_sock->Send("Dropping you into Script Edit mode!\n");
	m_sock->Send("Scripting is not yet implemented, sorry.\n");
	// m_sock->SetEditor(new EditorScript(m_sock));
	return;
}

void EditorOLC::listCommands(const std::string& argument)
{
	m_sock->Send(String::Get()->box(OLCInterpreter::Get()->getWords(), "OLC"));
	m_sock->Send("\n");
	return;
}

void EditorOLC::quitEditor(const std::string& argument)
{
	m_sock->Send("Ok.\n");
	// m_sock->SetEditor(new EditorAccount(m_sock));
	m_sock->PopEditor();
	return;
}
