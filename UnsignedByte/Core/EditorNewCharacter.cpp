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

#include "EditorNewCharacter.h"
#include "EditorPlaying.h"
#include "EditorAccount.h"
#include "UBSocket.h"
#include "CharacterManager.h"
#include "PCharacter.h"
#include "PCharacterManager.h"

#include "StringUtilities.h"
#include "db.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "DatabaseMgr.h" // for CountSavable

#include "Account.h"
#include "Race.h"
#include "RaceManager.h"

EditorNewCharacter::EditorNewCharacter(UBSocket* sock) :
Editor(sock),
m_state(0)
{
	OnLine(Global::Get()->EmptyString);
}

EditorNewCharacter::~EditorNewCharacter(void)
{
}

void EditorNewCharacter::OnLine(const std::string &line)
{
	if(!line.compare("quit"))
	{
		m_sock->Send("Ok\n");
		// m_sock->SetEditor(new EditorAccount(m_sock));
		m_sock->PopEditor();
		return;
	}

	switch(m_state)
	{
	default:
		Global::Get()->bug("EditorNewAccount::OnLine(), default m_state!\n");
		m_sock->Send("BUG! Disconnecting you now...\n");
		m_sock->SetCloseAndDelete();
		return;

	case M_FIRST:
		m_state++;
		// fallthrough

	case M_NAME:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Enter a name for your character please: \n");
			return;
		}

		if(mud::CharacterManager::Get()->IllegalName(line))
		{
			m_sock->Sendf("You cannot use the name %s, please pick another name.\n", line.c_str());
			OnLine(Global::Get()->EmptyString);
			return;
		}

		m_name = line;
		m_state++;
		OnLine(Global::Get()->EmptyString);
		break;
	}

	case M_NAMECONFIRM:
		{
			if(line.size() == 0)
			{
				m_sock->Sendf("Create a character named %s?\n", m_name.c_str());
				return;
			}

			if(!line.compare("n") || !line.compare("no"))
			{
				m_sock->Send("Let's try again then.\n");
				m_state = M_FIRST;
				OnLine(Global::Get()->EmptyString);
				return;
			}

			if(line.compare("y") && line.compare("yes"))
			{
				OnLine(Global::Get()->EmptyString);
				m_sock->Send("yes/no?\n");
				return;
			}
	
			m_state++;
			OnLine(Global::Get()->EmptyString);
			return;
		}

	case M_RACE:
		{
			if(line.size() == 0)
			{
				m_sock->Send("Please choose a race: \n");
				m_sock->Send(String::Get()->box(mud::RaceManager::Get()->List(), "Races"));
				return;
			}
			
			try
			{
				int id = mud::RaceManager::Get()->lookupByName(line);
				m_raceid = id;

				m_sock->Sendf("Your race is now %s.\n", line.c_str());
				m_state++;
				OnLine(Global::Get()->EmptyString);
			}
			catch(RowNotFoundException& e)
			{
				m_sock->Send("No such race.\n");
				OnLine(Global::Get()->EmptyString);
			}
			
			return;
		}

	case M_DONE:
		if(line.size() != 0)
		{
			m_sock->Send("Please hit enter to continue.\n");
			return;
		}

		KeysPtr keys(new Keys(db::TableImpls::Get()->ROOMS));
		KeyPtr key(new Key(db::RoomsFields::Get()->ROOMID, 1));
		keys->addKey(key);
		
		if(DatabaseMgr::Get()->CountSavable(db::TableImpls::Get()->ROOMS, keys) <= 0)
		{
			m_sock->Sendf("Could not fetch room 1!\n");
			m_sock->Send("Closing your connection now.\n");
			m_sock->SetCloseAndDelete();
			return;
		}

		mud::Account* Acc = m_sock->GetAccount();
		if(!Acc->Exists())
		{
			m_sock->Send("For some reason your account doesn't exist.\n");
			m_sock->Send("Disconnecting you now.\n");
			m_sock->SetCloseAndDelete();
			return;			
		}

		KeysPtr newchkeys = mud::CharacterManager::Get()->Add();
		value_type id = newchkeys->first()->getValue();
		if(id <= 0)
		{
			m_sock->Send("For some reason your characters newly inserted id is <= 0.\n");
			m_sock->Send("Disconnecting you now.\n");
			m_sock->SetCloseAndDelete();
			return;
		}

		mud::CharacterPtr character = mud::CharacterManager::Get()->GetByKey(id);
		if(!character)
		{
			m_sock->Send("For some reason your new characters could not be retreived.\n");
			m_sock->Send("Disconnecting you now.\n");
			m_sock->SetCloseAndDelete();
			return;
		}

		character->setName(m_name);
		character->setRace(m_raceid);
		character->setRoom(1);
		// character->setAccount(accountid);
		character->Save();
		character.reset();
		
		mud::PCharacterPtr Ch = mud::PCharacterManager::Get()->LoadByKey(m_sock, id);
		m_sock->Sendf("Character %s created, enjoy!\n", m_name.c_str());
		m_sock->SetEditor(new EditorPlaying(m_sock, Ch), true);
		return;
	}

}
