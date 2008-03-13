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

#include "EditorOOC.h"
#include "Character.h"
#include "CharacterManager.h"
#include "UBSocket.h"
#include "UBHandler.h"
#include "StringUtilities.h"
#include "Account.h"
#include "Channel.h"
#include "ChannelManager.h"
#include "Exceptions.h"

EditorOOC::OOCCommand EditorOOC::m_listCommands("Commands", &EditorOOC::listCommands);
EditorOOC::OOCCommand EditorOOC::m_sendOOCMessage("OOC", &EditorOOC::sendOOCMessage);
EditorOOC::OOCCommand EditorOOC::m_listOnlineCharacters("Who", &EditorOOC::listOnlineCharacters);
EditorOOC::OOCCommand EditorOOC::m_listCharacters("Laston", &EditorOOC::listCharacters);

EditorOOC::EditorOOC(UBSocket* sock) :
Editor(sock)
{

}

EditorOOC::~EditorOOC()
{
	
}

std::string EditorOOC::lookup(const std::string& action)
{	
	OOCCommand* act = OOCInterpreter::Get()->translate(action);
	if(act)
		return act->getName();

	std::string actionstripped = action;
	actionstripped.erase(0, 1);
	act = OOCInterpreter::Get()->translate(actionstripped);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorOOC::dispatch(const std::string& action, const std::string& argument)
{
	OOCCommand* act = OOCInterpreter::Get()->translate(action);
	
	if(act)
	{
		act->Run(this, argument);
		return;
	}
	
	std::string actionstripped = action;
	actionstripped.erase(0, 1);
	act = OOCInterpreter::Get()->translate(actionstripped);
	if(act)
	{
		act->Run(this, argument);
		return;
	}
	
	Global::Get()->bugf("EditorOOC::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
	return;
}

EditorOOC::OOCInterpreter::OOCInterpreter(void)
{
	addWord("Commands", &m_listCommands);
	addWord("OOC", &m_sendOOCMessage);
	addWord("Who", &m_listOnlineCharacters);
	addWord("Laston", &m_listCharacters);
}

EditorOOC::OOCInterpreter::~OOCInterpreter(void)
{

}

void EditorOOC::listCommands(const std::string& argument)
{
	m_sock->Send(String::Get()->box(OOCInterpreter::Get()->getWords(), "Account"));
	m_sock->Send("\n");
	return;
}

void EditorOOC::sendOOCMessage(const std::string& argument)
{
	try {
		mud::ChannelPtr channel = mud::ChannelManager::Get()->GetByName("ooc");
		std::map<SOCKET,Socket *> ref = UBHandler::Get()->Sockets();
		for (std::map<SOCKET,Socket *>::iterator it = ref.begin(); it != ref.end(); it++)
		{
			UBSocket* sock = UBSocket::Cast(it->second, false);
			if(sock && sock->canReceiveChannel(channel)) {
					sock->Sendf("%s ooc> '%s'.\n", m_sock->GetAccount()->getName().c_str(), argument.c_str());			
			}
		}
	} catch(RowNotFoundException& e) {
		Global::Get()->bug("Could not retreive the OOC chan!");
	}
	
	return;	
}

void EditorOOC::listOnlineCharacters(const std::string& argument)
{
	std::map<SOCKET,Socket *> ref = UBHandler::Get()->Sockets();
	for (std::map<SOCKET,Socket *>::iterator it = ref.begin(); it != ref.end(); it++)
	{
		UBSocket* sock = UBSocket::Cast(it->second, false);
		if(sock)
			m_sock->Sendf("- %s -\n", sock->GetAccount()->getName().c_str());
	}
	return;
}

void EditorOOC::listCharacters(const std::string& argument)
{
	m_sock->Send(String::Get()->box(mud::CharacterManager::Get()->List(), "Characters"));
}
