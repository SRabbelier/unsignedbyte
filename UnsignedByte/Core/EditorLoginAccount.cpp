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

#include "EditorNewAccount.h"
#include "EditorLoginAccount.h"
#include "EditorAccount.h"
#include "UBSocket.h"
#include "Account.h"
#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"

class DoCmd;

EditorLoginAccount::EditorLoginAccount(UBSocket* sock) :
Editor(sock)
{
	OnLine(Global::Get()->EmptyString);
}

EditorLoginAccount::~EditorLoginAccount(void)
{
}

void EditorLoginAccount::OnLine(const std::string &line)
{
	if(line.size() == 0)
	{
		m_sock->Send("Please enter your name:\n");
		return;
	}

	if(!line.compare("quit"))
	{
		m_sock->Send("Goodbye!\n");
		m_sock->SetCloseAndDelete();
		return;
	}

	if(!line.compare("new"))
	{
		m_sock->Send("Starting account creation...\n");
		m_sock->SetEditor(new EditorNewAccount(m_sock));
		return;
	}

	printf("Name: '%s'\n", line.c_str());
	int count = DatabaseMgr::Get()->CountSavable(Tables::Get()->ACCOUNTS, line);
	if(count <= 0)
	{
		m_sock->Sendf("Unknown account %s! Type 'new' to create a new account!\n", line.c_str());
		OnLine(Global::Get()->EmptyString);
		return;
	}

	if(count >= 2)
	{
		m_sock->Sendf("For some reason there are %d account named '%s' known, please contact administration!\n", count, line.c_str());
		m_sock->Send("Disconnecting you now.\n");
		m_sock->SetCloseAndDelete();
		return;
	}

	int id = db::Accounts::lookupname(line);
	if(id == 0)
	{
		m_sock->Send("Got ID 0, disconnecting you now.\n");
		m_sock->SetCloseAndDelete();
		return;
	}

	mud::Account* Acc = mud::Cache::Get()->GetAccountByKey(id);

	m_sock->Sendf("Welcome back, %s\n", line.c_str());
	m_sock->Send("\n");
	m_sock->SetAccount(Acc);
	m_sock->SetEditor(new EditorAccount(m_sock));
	return;
}
