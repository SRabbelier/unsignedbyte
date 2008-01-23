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

#include "EditorAccount.h"
#include "EditorOLC.h"
#include "EditorNewCharacter.h"
#include "EditorPlaying.h"
#include "EditorOOC.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

#include "Account.h"
#include "Command.h"
#include "Permission.h"
#include "PCharacter.h"
#include "PCharacterManager.h"
#include "CharacterManager.h"
#include "Room.h"

extern bool m_quit;

EditorAccount::AccountCommand EditorAccount::m_listCommands("Commands", &EditorAccount::listCommands);
EditorAccount::AccountCommand EditorAccount::m_beginLogin("Login", &EditorAccount::beginLogin);
EditorAccount::AccountCommand EditorAccount::m_beginOLC("OLC", &EditorAccount::beginOLC);
EditorAccount::AccountCommand EditorAccount::m_beginOOC("OOC", &EditorAccount::beginOOC);
EditorAccount::AccountCommand EditorAccount::m_beginCreation("New", &EditorAccount::beginCreation);
EditorAccount::AccountCommand EditorAccount::m_quitEditor("Quit", &EditorAccount::quitEditor);
EditorAccount::AccountCommand EditorAccount::m_shutdownGame("Shutdown", &EditorAccount::shutdownGame);
EditorAccount::AccountCommand EditorAccount::m_listCharacters("List", &EditorAccount::listCharacters);

EditorAccount::EditorAccount(UBSocket* sock) :
Editor(sock)
{
	listCommands(Global::Get()->EmptyString);
}

EditorAccount::~EditorAccount(void)
{

}

std::string EditorAccount::lookup(const std::string& action)
{
	AccountCommand* act = AccountInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorAccount::dispatch(const std::string& action, const std::string& argument)
{
	AccountCommand* act = AccountInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		Global::Get()->bugf("EditorAccount::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}

EditorAccount::AccountInterpreter::AccountInterpreter(void)
{
	addWord("new", &m_beginCreation);
	addWord("login", &m_beginLogin);
	addWord("commands", &m_listCommands);
	addWord("quit", &m_quitEditor);
	addWord("shutdown", &m_shutdownGame);
	addWord("list", &m_listCharacters);
	addWord("olc", &m_beginOLC);
}

EditorAccount::AccountInterpreter::~AccountInterpreter(void)
{

}

void EditorAccount::beginLogin(const std::string &argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Please choose a character:\n");
		m_listCharacters.Run(this, Global::Get()->EmptyString);
		return;
	}

	if(mud::PCharacterManager::Get()->isActive(argument))
	{
		m_sock->Send("You are already playing that character!\n");
		return;
	}

	int id = 0;

	try
	{
		id = mud::CharacterManager::Get()->lookupByName(argument);
	}
	catch(RowNotFoundException& e)
	{
		m_sock->Send("No such character.\n");
		m_beginLogin.Run(this, Global::Get()->EmptyString);
		return;
	}
	
	KeysPtr keys(new Keys(db::TableImpls::Get()->CHARACTERACCOUNT));
	KeyPtr key;
	
	key = KeyPtr(new Key(db::CharacterAccountFields::Get()->FKACCOUNTS, id));
	keys->addKey(key);
	key = KeyPtr(new Key(db::CharacterAccountFields::Get()->FKENTITIES, m_sock->GetAccount()->getID()));
	keys->addKey(key);
	
	bool hasAccount = false;
	try
	{
		SavableManagerPtr manager = SavableManager::bykeys(keys);
		hasAccount = true;
	} catch(RowNotFoundException& e) { }
	
	if(hasAccount)
	{
		m_sock->Sendf("You don't have a character named '%s'!\n", argument.c_str());
		m_beginLogin.Run(this, Global::Get()->EmptyString);
		return;
	}

	mud::PCharacterPtr Ch = mud::PCharacterManager::Get()->LoadByKey(m_sock, id);
	m_sock->Sendf("Welcome back, %s\n", argument.c_str());
	m_sock->SetEditor(new EditorPlaying(m_sock, Ch));
	return;
}

void EditorAccount::listCharacters(const std::string &argument)
{
	mud::Account* account = m_sock->GetAccount();
	if(!account->Exists())
	{
		m_sock->Send("For some reason your account does not exist?!");
		m_sock->Send("Closing your connection now.\n");
		m_sock->SetCloseAndDelete();
		return;
	}
	
	// TODO - add character listing
	/*
	Strings characters = DatabaseMgr::Get()->GetSavable(
		Tables::Get()->CHARACTERS, account->getID(), 
		Tables::Get()->ACCOUNTS->tableID());
	
	if(characters.size() == 0)
	{
		sock->Send("You have no characters yet!\n");
		return;
	}
	
	sock->Send(String::Get()->box(characters));
	*/
	m_sock->Send("Character listing for Account not yet implemented!");
	m_sock->Send("\n");
	return;
}

void EditorAccount::listCommands(const std::string &argument)
{
	m_sock->Send(String::Get()->box(AccountInterpreter::Get()->getWords(), "Account"));
	m_sock->Send("\n");
	return;
}

void EditorAccount::beginOLC(const std::string &argument)
{
	m_sock->Send("Dropping you into OLC mode!\n");
	m_sock->SetEditor(new EditorOLC(m_sock));
	return;
}

void EditorAccount::beginOOC(const std::string& argument)
{
	m_sock->Send("Dropping you into OOC mode!\n");
	m_sock->SetEditor(new EditorOOC(m_sock));
}

void EditorAccount::beginCreation(const std::string &argument)
{
	m_sock->Send("Dropping you into Character Creation mode!\n");
	m_sock->SetEditor(new EditorNewCharacter(m_sock));
	return;
}

void EditorAccount::quitEditor(const std::string &argument)
{
	m_sock->Send("Thank you for visiting.\n");
	m_sock->SetCloseAndDelete();
	return;
}

void EditorAccount::shutdownGame(const std::string &argument)
{
	m_sock->Send("Shutting down...\n");
	m_quit = true;
	m_sock->Send("Game will shut down after this loop!\n");
	return;
}
