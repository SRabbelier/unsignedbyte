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

#include "EditorOLC.h"
#include "EditorArea.h"
#include "EditorRoom.h"
#include "EditorMobile.h"
#include "EditorAccount.h"
#include "EditorSector.h"
#include "EditorColour.h"
#include "EditorCommand.h"

#include "UBSocket.h"
#include "Account.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "Action.h"
#include "StringUtilities.h"

EditorOLC::EditorOLC(UBSocket* sock) :
Editor(sock)
{
	UBAction* act = Commands::Get();
	act->Run(sock, Global::Get()->EmptyString);
}

EditorOLC::~EditorOLC(void)
{

}

std::string EditorOLC::lookup(const std::string& action)
{
	UBAction* act = OLCInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorOLC::dispatch(const std::string& action, const std::string& argument)
{
	UBAction* act = OLCInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument);
	else
		Global::Get()->bugf("EditorOLC::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}

EditorOLC::OLCInterpreter::OLCInterpreter(void)
{
	addWord("areas", Areas::Get());
	addWord("rooms", Rooms::Get());
	addWord("mobiles", Mobiles::Get());
	addWord("scripts", Scripts::Get());
	addWord("sectors", Sectors::Get());
	addWord("colour", Colours::Get());
	addWord("comedit", ComEdit::Get());
	addWord("commands", Commands::Get());
	addWord("quit", Quit::Get());

	/*
	addWord("ooc", DoOOC::Get());
	addWord("note", DoNote::Get());
	addWord("help", DoHelp::Get());
	*/
}

EditorOLC::OLCInterpreter::~OLCInterpreter(void)
{
	Areas::Free();
	Commands::Free();
	Rooms::Free();
	Mobiles::Free();
	Scripts::Free();
	Sectors::Free();
	Colours::Free();
	ComEdit::Free();
	Quit::Free();
}

void EditorOLC::Areas::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Area Edit mode!\n");
	sock->SetEditor(new EditorArea(sock));
	return;
}


void EditorOLC::Rooms::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Room Edit mode!\n");
	sock->SetEditor(new EditorRoom(sock));
	return;
}

void EditorOLC::Mobiles::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Mobile Edit mode!\n");
	sock->SetEditor(new EditorMobile(sock));
	return;
}

void EditorOLC::Sectors::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Sector Edit mode!\n");
	sock->SetEditor(new EditorSector(sock));
	return;
}

void EditorOLC::Colours::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Colours Edit mode!\n");
	sock->SetEditor(new EditorColour(sock));
	return;
}

void EditorOLC::ComEdit::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Command Edit mode!\n");
	sock->SetEditor(new EditorCommand(sock));
	return;
}

void EditorOLC::Scripts::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Script Edit mode!\n");
	sock->Send("Scripting is not yet implemented, sorry.\n");
	// sock->SetEditor(new EditorScript(sock));
	return;
}

void EditorOLC::Commands::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send(String::Get()->box(OLCInterpreter::Get()->getWords(), "OLC"));
	sock->Send("\n");
	return;
}

void EditorOLC::Quit::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Ok.\n");
	sock->SetEditor(new EditorAccount(sock));
	return;
}
