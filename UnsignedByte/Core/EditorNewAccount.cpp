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

#include "EditorNewAccount.h"
#include "EditorAccount.h"
#include "UBSocket.h"
#include "Account.h"
#include "AccountManager.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "db.h"

EditorNewAccount::EditorNewAccount(UBSocket* sock) :
Editor(sock),
m_state(0)
{
	OnLine(Global::Get()->EmptyString);
}

EditorNewAccount::~EditorNewAccount(void)
{
}

void EditorNewAccount::OnLine(const std::string &line)
{
	if(!line.compare("quit"))
	{
		m_sock->Send("Allright, quitting!\n");
		m_sock->SetCloseAndDelete();
		return;
	}

	switch(m_state)
	{
	default:
	{
		Global::Get()->bug("EditorNewAccount::OnLine(), default m_state!\n");
		m_sock->Send("BUG! Disconnecting you now...\n");
		m_sock->SetCloseAndDelete();
		return;
	} /* default */

	case M_FIRST:
	{
		m_state++;
		// fallthrough
	} /* case M_FIRST: */

	case M_NAME:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Enter a name for your account please: \n");
			return;
		}

		if(mud::AccountManager::Get()->IllegalName(line))
		{
			m_sock->Sendf("You cannot use the name %s, please pick another name.\n", line.c_str());
			OnLine(Global::Get()->EmptyString);
			return;
		}

		m_name = line;
		m_state++;
		OnLine(Global::Get()->EmptyString);
		break;
	} /* case M_NAME: */

	case M_NAMECONFIRM:
	{
		if(line.size() == 0)
		{
			m_sock->Sendf("Create an account named %s?\n", m_name.c_str());
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
	} /* case M_NAMECONFIRM: */

	case M_PASSWORD:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Please choose a password: \n");
			return;
		}

		m_password = line;
		m_state++;
		OnLine(Global::Get()->EmptyString);
		return;
	} /* case M_PASSWORD: */

	case M_PASSWORDCONFIRM:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Please confirm your password: \n");
			return;
		}

		if(m_password.compare(line))
		{
			m_sock->Send("Passwords do not match, let's try again!\n");
			m_state = M_PASSWORD;
			OnLine(Global::Get()->EmptyString);
			return;
		}

		m_sock->Sendf("Your password is set.\n", line.c_str());
		m_sock->Send("Please hit enter to continue.\n");
		m_state++;
		return;
	} /* case M_PASSWORDCONFIRM: */

	case M_DONE:
	{
		if(line.size() != 0)
		{
			m_sock->Send("Please hit enter to continue.\n");
			return;
		}

		KeysPtr newaccountkeys = mud::AccountManager::Get()->Add();
		value_type id = newaccountkeys->first()->getValue();
		if(id == 0)
		{
			m_sock->Send("Could not create a new account.\n");
			m_sock->SetCloseAndDelete();
			return;
		}
		
		mud::AccountPtr Acc = mud::AccountManager::Get()->GetByKey(id);
		Acc->setName(m_name);
		Acc->setPassword(m_password);
		Acc->Save();
		
		m_sock->Sendf("Account %s created, enjoy!\n", m_name.c_str());
		m_sock->SetAccount(Acc);
		m_sock->SetEditor(new EditorAccount(m_sock), true);
		return;
	} /* case M_DONE: */
	
	} /* switch(state) */

}
