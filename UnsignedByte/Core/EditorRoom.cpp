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

#include "EditorRoom.h"
#include "EditorOLC.h"
#include "EditorArea.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Action.h"

#include "Account.h"
#include "Area.h"
#include "Room.h"
#include "Sector.h"

using mud::Room;

EditorRoom::EditorRoom(UBSocket* sock) :
OLCEditor(sock),
m_area(1),
m_xpos(1),
m_ypos(1),
m_room(NULL)
{
	Action<OLCEditor>* act = Commands::Get();
	act->Run(this, Global::Get()->EmptyString);
	OnLine(Global::Get()->EmptyString);
}

EditorRoom::~EditorRoom(void)
{

}

std::string EditorRoom::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	/*
	PermissionAction* act = PermissionInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
	*/
	// TODO - EditorRoom::lookup
		
	return Global::Get()->EmptyString;
}

void EditorRoom::dispatch(const std::string& action, const std::string& argument)
{
	/*
	PermissionAction* act = PermissionInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument, m_permission);
	else
	*/
		OLCEditor::dispatch(action, argument);
		// TODO - EditorRoom::dispatch
		
	return;
}

Savable* EditorRoom::getEditing()
{
	return m_room;
}

Table* EditorRoom::getTable()
{
	return Tables::Get()->ROOMS;
}

long EditorRoom::addNew()
{
	// return mud::Cache::Get()->AddRoom();
	// TODO - addNew()
	return 0;
}

std::vector<std::string> EditorRoom::getList()
{
	return Room::List();
}

void EditorRoom::setEditing(long id)
{
	if(id == 0)
	{
		m_room = NULL;
		return;
	}
	
	m_room = mud::Cache::Get()->GetRoomByKey(id);
	return;
}

std::vector<std::string> EditorRoom::getCommands()
{
	return RoomInterpreter::Get()->getWords();
}

EditorRoom::RoomInterpreter::RoomInterpreter(void)
{
	addWord("name", Name::Get());
	addWord("description", Description::Get());
	addWord("sectors", Sectors::Get());
	addWord("save", Save::Get());
	addWord("deactivate", Deactivate::Get());
	addWord("open", Open::Get());
	addWord("close", Close::Get());
}

EditorRoom::RoomInterpreter::~RoomInterpreter(void)
{
	Name::Free();
	Description::Free();
	Sectors::Free();
	Save::Free();
	Deactivate::Free();
	Open::Free();
	Close::Free();
}

EditorRoom::DirectionInterpreter::DirectionInterpreter(void)
{
	// addWord("activate", Activate::Get());
	addWord("area", AreaList::Get());
/*	addWord("north", North::Get());
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
	addWord("nw", NorthWest::Get());*/
	addWord("map", Map::Get());
}

EditorRoom::DirectionInterpreter::~DirectionInterpreter(void)
{
	// Activate::Free();
	AreaList::Free();
	/*North::Free();
	NorthEast::Free();
	East::Free();
	SouthEast::Free();
	South::Free();
	SouthWest::Free();
	West::Free();
	NorthWest::Free();*/
	Map::Free();
}

/*
void EditorRoom::getRoom(const std::string&)
{
	long id = Cache::Get()->GetRoomID(m_area, m_xpos, m_ypos);
	if(id)
		m_room = Cache::Get()->GetRoom(id);
	else
		m_room = NULL;
	return;
}
*/

void EditorRoom::Name::Run(UBSocket* sock, const std::string& argument, Room* room)
{
	if(argument.size() == 0)
	{
		sock->Send("Room name can't be zero length!\n");
		return;
	}

	sock->Sendf("Room name changed from '%s' to '%s'.\n", room->getName().c_str(), argument.c_str());
	room->setName(argument);
	return;
}

void EditorRoom::Description::Run(UBSocket* sock, const std::string& argument, Room* room)
{
	if(!room->Exists())
	{
		sock->Send("For some reason the room you are editing does not exist.\n");
		return;
	}

	if(argument.size() == 0)
	{
		sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	sock->Sendf("Room description changed from '%s' to '%s'.\n", room->getDescription().c_str(), argument.c_str());
	room->setDescription(argument);
	return;
}

void EditorRoom::Sectors::Run(UBSocket* sock, const std::string& argument, Room* room)
{
	if(argument.size() == 0)
	{
		sock->Send("Please specify a sector type!\n");
		return;
	}

	long id = db::Sectors::lookupname(argument);
	if(!id)
	{
		sock->Sendf("'%s' is not a valid sector type!\n", argument.c_str());
		sock->Send(String::Get()->box(mud::Sector::List(), "Sectors"));
		return;
	}
	
	mud::Sector* sector = mud::Cache::Get()->GetSectorByKey(id);
	sock->Sendf("Sector type changed from '%s' to '%s'.\n", sector->getName().c_str(), argument.c_str());
		
	room->setSector(id);
	return;
}

void EditorRoom::Save::Run(UBSocket* sock, const std::string&, Room* room)
{
	sock->Sendf("Saving room '%s'.\n", room->getName().c_str());
	room->Save();
	sock->Send("Saved.\n");
	return;
}

void EditorRoom::Deactivate::Run(UBSocket* sock, const std::string&, Room* room)
{
	sock->Sendf("Deleting room '%s'.\n", room->getName().c_str());
	room->Delete();
	Room::Close(room);
	room = NULL;
	sock->Send("Deleted.\n");
	return;
}

void EditorRoom::Close::Run(UBSocket* sock, const std::string& argument, Room* room)
{
	sock->Send("Temporarily disabled untill the Exit system is implemented.\n");
	sock->Send("- Alturin, 17-08-2007\n");
	return;
}

void EditorRoom::Open::Run(UBSocket* sock, const std::string& argument, Room* room)
{
	sock->Send("Temporarily disabled untill the Exit system is implemented.\n");
	sock->Send("- Alturin, 17-08-2007\n");
}

void EditorRoom::Map::Run(EditorRoom* editor, const std::string&)
{
	editor->m_sock->Send("Temporarily disabled untill the Exit system is implemented.\n");
	editor->m_sock->Send("- Alturin, 17-08-2007\n");
}

/*
void EditorRoom::North::Run(EditorRoom* editor, const std::string&)
{
	if(editor->m_ypos <= 1)
	{
		editor->m_sock->Send("You can't go further north!\n");
		return;
	}
	editor->m_ypos--;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor-> m_ypos));
}

void EditorRoom::NorthEast::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::NorthEast::Run() with areacount <= 0!\n");
		editor->m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::NorthEast::Run() with areacount '%d'!\n", count);
		editor->m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_ypos <= 1 || editor->m_xpos+1 > area->getWidth())
	{
		editor->m_sock->Send("You can't go further northeast!\n");
		return;
	}
	editor->m_ypos--;
	editor->m_xpos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::East::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::East::Run() with areacount <= 0!\n");
		editor->m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::East::Run() with areacount '%d'!\n", count);
		editor->m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_xpos+1 > area->getWidth())
	{
		editor->m_sock->Send("You can't go further east!\n");
		return;
	}
	editor->m_xpos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::SouthEast::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::SouthEast::Run() with areacount <= 0!\n");
		editor->m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::SouthEast::Run() with areacount '%d'!\n", count);
		editor->m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_ypos+1 > area->getHeight() || editor->m_xpos+1 > area->getWidth())
	{
		editor->m_sock->Send("You can't go further southeast!\n");
		return;
	}
	editor->m_ypos++;
	editor->m_xpos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::South::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::South::Run() with areacount <= 0!\n");
		editor->m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::South::Run() with areacount '%d'!\n", count);
		editor->m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_ypos+1 > area->getHeight())
	{
		editor->m_sock->Send("You can't go further south!\n");
		return;
	}
	editor->m_ypos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::SouthWest::Run(EditorRoom* editor, const std::string& argument)
{
	long count = DatabaseMgr::Get()->CountSavable(Tables::Get()->AREAS, editor->m_area);
	if(count <= 0) {
		Global::Get()->bug("EditorMap::SouthWest::Run() with areacount <= 0!\n");
		editor->m_sock->Send("For some reason the area number of the room you are belongs to, does not correspond with anything in the database?!\n");
		return;
	}
	if(count >= 2) {
		Global::Get()->bugf("EditorMap::SouthWest::Run() with areacount '%d'!\n", count);
		editor->m_sock->Sendf("For some reason the area the room you are in exists multiple times in the database?!n");
		return;
	}
	Area* area = Cache::Get()->GetArea(editor->m_area);
	if(editor->m_xpos <= 1 || editor->m_ypos+1 > area->getHeight())
	{
		editor->m_sock->Send("You can't go further southwest!\n");
		return;
	}
	editor->m_xpos--;
	editor->m_ypos++;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::West::Run(EditorRoom* editor, const std::string& argument)
{
	if(editor->m_xpos <= 1)
	{
		editor->m_sock->Send("You can't go further west!\n");
		return;
	}
	editor->m_xpos--;	
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}

void EditorRoom::NorthWest::Run(EditorRoom* editor, const std::string& argument)
{
	if(editor->m_ypos <= 1 || editor->m_xpos <= 1)
	{
		editor->m_sock->Send("You can't go further northwest!\n");
		return;
	}
	editor->m_xpos--;	
	editor->m_ypos--;
	editor->getRoom(Global::Get()->EmptyString);
	editor->m_sock->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
}
*/

void EditorRoom::AreaList::Run(EditorRoom* editor, const std::string& argument)
{
	int area = atoi(argument.c_str());
	if(area <= 0)
	{
		editor->m_sock->Send("Please specify an area id to change to.\n");
		editor->m_sock->Sendf("'%s' is not a valid area.\n", argument.c_str());
		editor->m_sock->Send(String::Get()->box(mud::Area::List(), "Areas"));
		return;
	}
	editor->m_area = area;	
	editor->m_xpos = 1;
	editor->m_ypos = 1;
	// editor->getRoom(Global::Get()->EmptyString);
}

/*
void EditorRoom::Activate::Run(EditorRoom* editor, const std::string&)
{
	long id = Cache::Get()->GetRoomID(editor->m_area, editor->m_xpos, editor->m_ypos);
	if(id)
	{
		editor->m_sock->Send("The room you are in is already active.\n");
		return;
	}

	id = Cache::Get()->AddRoom();
	if(!id)
	{
		editor->m_sock->Send("Could not activate this room!\n");
		return;
	}
	
	Room* room = Cache::Get()->GetRoom(id);
	if(!room)
	{
		editor->Send("Could not activate this room!\n");
		return;
	}
	
	// TODO, set coordinates

	editor->Send("Room activated! Please give it at least a name!\n");
	editor->getRoom(Global::Get()->EmptyString);
	editor->Send(Room::CreateMap(editor->m_area, editor->m_xpos, editor->m_ypos));
	return;
}
*/
