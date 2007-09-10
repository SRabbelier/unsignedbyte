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

#include "EditorNewCharacter.h"
#include "EditorPlaying.h"
#include "EditorAccount.h"
#include "UBSocket.h"
#include "PCharacter.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "StringUtilities.h"
#include "Cache.h"
#include "Account.h"
#include "db.h"

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
		m_sock->SetEditor(new EditorAccount(m_sock));
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

		if(mud::Character::IllegalName(line))
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
				m_sock->Send(String::Get()->unlines(DatabaseMgr::Get()->GetSavable(Tables::Get()->RACES), "\t", 3));
				return;
			}

			int count = DatabaseMgr::Get()->CountSavable(Tables::Get()->RACES, line);
			if(count <= 0)
			{
				m_sock->Sendf("Unknown race %s, please choose an existing race.\n", line.c_str());
				OnLine(Global::Get()->EmptyString);
				return;
			}

			if(count >= 2)
			{
				m_sock->Sendf("For some reason there is more than one occurance of race %s known!\n", line.c_str());
				m_sock->Send("Closing your connection now.\n");
				m_sock->SetCloseAndDelete();
				return;
			}

			int id = db::Races::lookupname(line);
			if(id <= 0)
			{
				m_sock->Sendf("Got ID %d, which is <= 0, disconnecting you now.\n", id);
				m_sock->SetCloseAndDelete();
				return;
			}

			m_raceid = id;

			m_sock->Sendf("Your race is now %s.\n", line.c_str());
			m_state++;
			OnLine(Global::Get()->EmptyString);
			return;
		}

	case M_DONE:
		if(line.size() != 0)
		{
			m_sock->Send("Please hit enter to continue.\n");
			return;
		}

		if(DatabaseMgr::Get()->CountSavable(Tables::Get()->ROOMS, 1) <= 0)
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

		// long id = mud::Cache::Get()->AddCharacter();
		// TODO - AddCharacter()
		long id = 0;
		if(id <= 0)
		{
			m_sock->Send("For some reason your characters newly inserted id is <= 0.\n");
			m_sock->Send("Disconnecting you now.\n");
			m_sock->SetCloseAndDelete();
			return;
		}

		mud::PCharacter* Ch = mud::Cache::Get()->LoadPCharacterByKey(m_sock, id);
		if(!Ch)
		{
			m_sock->Send("For some reason your new characters could not be retreived.\n");
			m_sock->Send("Disconnecting you now.\n");
			m_sock->SetCloseAndDelete();
			return;
		}

		Ch->setName(m_name);
		Ch->setRace(m_raceid);
		Ch->setRoom(1);
		//Ch->setAccount(accountid);
		Ch->Save();
		m_sock->Sendf("Character %s created, enjoy!\n", m_name.c_str());
		m_sock->SetEditor(new EditorPlaying(m_sock, Ch));
		return;
	}

}
