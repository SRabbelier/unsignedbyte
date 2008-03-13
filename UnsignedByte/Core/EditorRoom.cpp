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
 
#include "EditorRoom.h"
#include "EditorOLC.h"
#include "EditorArea.h"
#include "EditorString.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "Exceptions.h"
#include "TableImpls.h"

#include "Account.h"
#include "Area.h"
#include "AreaManager.h"
#include "Room.h"
#include "RoomManager.h"
#include "Sector.h"
#include "SectorManager.h"

using mud::Room;

EditorRoom::RoomCommand EditorRoom::m_showMap("Map", &EditorRoom::showMap);

/*
EditorRoom::RoomCommand EditorRoom::m_goNorth("North", &EditorRoom::goNorth);
EditorRoom::RoomCommand EditorRoom::m_goNorthEast("NorthEast", &EditorRoom::goNorthEast);
EditorRoom::RoomCommand EditorRoom::m_goEast("East", &EditorRoom::goEast);
EditorRoom::RoomCommand EditorRoom::m_goSouthEast("SouthEast", &EditorRoom::goSouthEast);
EditorRoom::RoomCommand EditorRoom::m_goSouth("South", &EditorRoom::goSouth);
EditorRoom::RoomCommand EditorRoom::m_goSouthWest("SouthWest", &EditorRoom::goSouthWest);
EditorRoom::RoomCommand EditorRoom::m_goWest("West", &EditorRoom::goWest);
EditorRoom::RoomCommand EditorRoom::m_goNorthWest("NorthWest", &EditorRoom::goNorthWest);
*/

EditorRoom::RoomCommand EditorRoom::m_listAreas("Areas", &EditorRoom::listAreas);
EditorRoom::RoomCommand EditorRoom::m_editName("Name", &EditorRoom::editName);
EditorRoom::RoomCommand EditorRoom::m_editDescription("Description", &EditorRoom::editDescription);
EditorRoom::RoomCommand EditorRoom::m_editSector("Sector", &EditorRoom::editSector);
EditorRoom::RoomCommand EditorRoom::m_saveRoom("Room", &EditorRoom::saveRoom);
EditorRoom::RoomCommand EditorRoom::m_closeExit("Close", &EditorRoom::closeExit);
EditorRoom::RoomCommand EditorRoom::m_openExit("Open", &EditorRoom::openExit);
EditorRoom::RoomCommand EditorRoom::m_showRoom("Show", &EditorRoom::showRoom);

EditorRoom::EditorRoom(UBSocket* sock) :
OLCEditor(sock),
m_room(),
m_target(M_NONE)
{
	listCommands(Global::Get()->EmptyString);
}

EditorRoom::~EditorRoom(void)
{

}

void EditorRoom::OnFocus()
{		
	switch(m_target)
	{
		case M_NONE:
			return;
			
		case M_DESCRIPTION:
			m_room->setDescription(m_value);
			break;
	}
	
	m_target = M_NONE;
}

std::string EditorRoom::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	RoomCommand* act = RoomInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorRoom::dispatch(const std::string& action, const std::string& argument)
{
	RoomCommand* act = RoomInterpreter::Get()->translate(action);
	
	if(act) 
	{
		if(!m_room)
		{
			m_sock->Send("You need to be editing a room first.\n");
			m_sock->Send("(Use the 'edit' command.)\n");
			return;
		}
		else
		{
			act->Run(this, argument);
			return;
		}
	}
	
	act = RoomEditingInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else	
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorRoom::getEditing()
{
	return m_room;
}

TableImplPtr EditorRoom::getTable()
{
	return db::TableImpls::Get()->ROOMS;
}

KeysPtr EditorRoom::addNew()
{
	return mud::RoomManager::Get()->Add();
}

std::vector<std::string> EditorRoom::getList()
{
	return mud::RoomManager::Get()->List();
}

void EditorRoom::setEditing(KeysPtr keys)
{
	if(!keys->size())
	{
		m_room.reset();
		return;
	}
	
	m_room = mud::RoomManager::Get()->GetByKey(keys->first()->getValue());
	return;
}

std::vector<std::string> EditorRoom::getCommands()
{
	return RoomInterpreter::Get()->getWords();
}

EditorRoom::RoomInterpreter::RoomInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("description", &m_editDescription);
	addWord("sectors", &m_editSector);
	addWord("save", &m_saveRoom);
	addWord("close", &m_closeExit);
	addWord("show", &m_showRoom);
}

EditorRoom::RoomInterpreter::~RoomInterpreter(void)
{

}

EditorRoom::RoomEditingInterpreter::RoomEditingInterpreter(void)
{
	addWord("area", &m_listAreas);
	addWord("map", &m_showMap);
	
	/*
	addWord("north", North::Get());
	addWord("northeast", NorthEast::Get());
	addWord("ne", NorthEast::Get());
	addWord("east", East::Get());
	addWord("southeast", SouthEast::Get());
	addWord("se", SouthEast::Get());
	addWord("south", South::Get());
	addWord("southwest", SouthWest::Get());
	addWord("sw", SouthWest::Get());
	addWord("west", West::Get());
	addWord("northwest", NorthWest::Get());
	addWord("nw", NorthWest::Get());
	*/
}

EditorRoom::RoomEditingInterpreter::~RoomEditingInterpreter(void)
{

}

void EditorRoom::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Room name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Room name changed from '%s' to '%s'.\n", m_room->getName().c_str(), argument.c_str());
	m_room->setName(argument);
	return;
}

void EditorRoom::editDescription(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("No argument, dropping you into the string editor!\n");
		m_sock->SetEditor(new EditorString(m_sock, m_value));
		m_target = M_DESCRIPTION;
		return;
	}

	m_sock->Sendf("Room description changed from '%s' to '%s'.\n", m_room->getDescription().c_str(), argument.c_str());
	m_room->setDescription(argument);
	return;
}

void EditorRoom::editSector(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Please specify a sector type!\n");
		return;
	}

	try
	{
		long id = mud::SectorManager::Get()->lookupByName(argument);
		mud::SectorPtr sector = mud::SectorManager::Get()->GetByKey(id);
		m_sock->Sendf("Sector type changed from to '%s'.\n", argument.c_str());
		m_room->setSector(id);
	}
	catch(RowNotFoundException& e)
	{
		m_sock->Sendf("'%s' is not a valid sector type!\n", argument.c_str());
		m_sock->Send(String::Get()->box(mud::SectorManager::Get()->List(), "Sectors"));
	}
}

void EditorRoom::saveRoom(const std::string& argument)
{
	m_sock->Sendf("Saving room '%s'.\n", m_room->getName().c_str());
	if(argument.size())
		m_room->Save(m_sock->GetAccount()->getID(), argument);
	else
		m_room->Save(m_sock->GetAccount()->getID(), Global::Get()->EmptyString);
	m_sock->Send("Saved.\n");
	return;
}

void EditorRoom::showRoom(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_room->Show(), "Room"));
}

void EditorRoom::listAreas(const std::string& argument)
{
	m_sock->Send(String::Get()->box(mud::AreaManager::Get()->List(), "Areas"));
}

void EditorRoom::closeExit(const std::string& argument)
{
	m_sock->Send("Temporarily disabled untill the Exit system is implemented.\n");
	m_sock->Send("- Alturin, 17-08-2007\n");
	return;
}

void EditorRoom::openExit(const std::string& argument)
{
	m_sock->Send("Temporarily disabled untill the Exit system is implemented.\n");
	m_sock->Send("- Alturin, 17-08-2007\n");
}

void EditorRoom::showMap(const std::string& argument)
{
	m_sock->Send("Temporarily disabled untill the Exit system is implemented.\n");
	m_sock->Send("- Alturin, 17-08-2007\n");
}

/*
void EditorRoom::North::Run(EditorRoom* editor, const std::string&)
{
	if(editor->m_ypos <= 1)
	{
		editor->m_m_sock->Send("You can't go further north!\n");
		return;
	}
	editor->m_ypos--;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor-> m_ypos));
}

void EditorRoom::NorthEast::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::NorthEast::Run() with areacount <= 0!\n");
		editor->m_m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::NorthEast::Run() with areacount '%d'!\n", count);
		editor->m_m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_ypos <= 1 || editor->m_xpos+1 > area->getWidth())
	{
		editor->m_m_sock->Send("You can't go further northeast!\n");
		return;
	}
	editor->m_ypos--;
	editor->m_xpos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::East::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::East::Run() with areacount <= 0!\n");
		editor->m_m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::East::Run() with areacount '%d'!\n", count);
		editor->m_m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_xpos+1 > area->getWidth())
	{
		editor->m_m_sock->Send("You can't go further east!\n");
		return;
	}
	editor->m_xpos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::SouthEast::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::SouthEast::Run() with areacount <= 0!\n");
		editor->m_m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::SouthEast::Run() with areacount '%d'!\n", count);
		editor->m_m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_ypos+1 > area->getHeight() || editor->m_xpos+1 > area->getWidth())
	{
		editor->m_m_sock->Send("You can't go further southeast!\n");
		return;
	}
	editor->m_ypos++;
	editor->m_xpos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::South::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::South::Run() with areacount <= 0!\n");
		editor->m_m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::South::Run() with areacount '%d'!\n", count);
		editor->m_m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_ypos+1 > area->getHeight())
	{
		editor->m_m_sock->Send("You can't go further south!\n");
		return;
	}
	editor->m_ypos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::SouthWest::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::SouthWest::Run() with areacount <= 0!\n");
		editor->m_m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::SouthWest::Run() with areacount '%d'!\n", count);
		editor->m_m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_xpos <= 1 || editor->m_ypos+1 > area->getHeight())
	{
		editor->m_m_sock->Send("You can't go further southwest!\n");
		return;
	}
	editor->m_xpos--;
	editor->m_ypos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::West::Run(EditorRoom* editor, const std::string& argument)
{
	if(editor->m_xpos <= 1)
	{
		editor->m_m_sock->Send("You can't go further west!\n");
		return;
	}
	editor->m_xpos--;	
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::NorthWest::Run(EditorRoom* editor, const std::string& argument)
{
	if(editor->m_ypos <= 1 || editor->m_xpos <= 1)
	{
		editor->m_m_sock->Send("You can't go further northwest!\n");
		return;
	}
	editor->m_xpos--;	
	editor->m_ypos--;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::activateRoom(const std::string& argument)
{
	m_sock->Send("Temporarily disabled untill the Exit system is implemented.\n");
	m_sock->Send("- Alturin, 17-08-2007\n");	
	return;
}

void EditorRoom::deactivateRoom(const std::string& argument)
{
	m_sock->Sendf("Deleting room '%s'.\n", m_room->getName().c_str());
	m_room->Delete();
	mud::RoomManager::Get()->Close(m_room);
	m_room.reset();
	m_sock->Send("Deleted.\n");
	return;
}

*/
