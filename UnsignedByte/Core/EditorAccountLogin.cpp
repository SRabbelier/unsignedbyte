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
#include "EditorAccountLogin.h"
#include "EditorAccount.h"

#include "UBSocket.h"
#include "Channel.h"

#include "Account.h"
#include "AccountManager.h"

#include "Global.h"
#include "Exceptions.h"

class DoCmd;

EditorAccountLogin::EditorAccountLogin(UBSocket* sock) :
Editor(sock),
m_state(M_FIRST),
m_account()
{
	OnLine(Global::Get()->EmptyString);
}

EditorAccountLogin::~EditorAccountLogin(void)
{
}

void EditorAccountLogin::OnLine(const std::string &line)
{
	if(!line.compare("quit"))
	{
		m_sock->Send("Goodbye!\n");
		m_sock->SetCloseAndDelete();
		return;
	}
	
	switch(m_state)
	{
	default:
	{
		Global::Get()->bug("EditorAccountLogin::OnLine(), default m_state!\n");
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
		if(!line.compare("new"))
		{
			m_sock->Send("Starting account creation...\n");
			m_sock->SetEditor(new EditorNewAccount(m_sock));
			return;
		}
		
		if(line.size() == 0)
		{
			m_sock->Send("Please enter your name:\n");
			return;
		}
		
		try
		{
			m_account = mud::AccountManager::Get()->GetByName(line);
			m_state++;
			OnLine(Global::Get()->EmptyString);
		}
		catch(RowNotFoundException& e)
		{
			m_sock->Send("No such account.\n");
			OnLine(Global::Get()->EmptyString);
		}

		return;
	} /* case M_NAME: */
		
	case M_PASSWORD:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Please enter your password: \n");
			return;
		}

		if(line.compare(m_account->getPassword()))
		{
			m_sock->Send("Password incorrect, try again.\n");
			// TODO: log
			OnLine(Global::Get()->EmptyString);
			return;
		}

		m_sock->Sendf("Welcome back, %s\n", m_account->getName().c_str());
		m_sock->Send("\n");
		m_sock->SetAccount(m_account);
		m_sock->SetEditor(new EditorAccount(m_sock));
		return;
	} /* case M_PASSWORD: */
	
	} /* switch(state) */
	
}

bool EditorAccountLogin::canReceiveChannel(mud::ChannelPtr channel) const
{	
	if(!channel->needLogin())
		return true;

	return false;
}
