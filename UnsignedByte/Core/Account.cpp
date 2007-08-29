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

#include <string>
#include <stdexcept>

class UBSocket;
#include "Cache.h"
#include "Account.h"
#include "DatabaseMgr.h"
#include "db.h"

using namespace mud;

Account::Account(db::Accounts* dbaccount) :
m_account(dbaccount)
{
	if(m_account == NULL)
		throw std::invalid_argument("Account::Account(), m_account == NULL!");
}

Account::~Account(void)
{
	delete m_account;
	m_account = 0;
}

void Account::Delete()
{
	m_account->erase();
}

void Account::Save()
{
	m_account->save();
}

bool Account::Exists()
{
	return m_account->exists();
}


bool Account::IllegalName(const std::string& name)
{
	if(DatabaseMgr::Get()->CountSavable(Tables::Get()->ACCOUNTS, name) > 0)
		return true;

	return false;
}

std::vector<std::string> Account::Show()
{
	std::vector<std::string> result;
	
	return result;
}

std::string Account::ShowShort()
{
	std::string result;
	
	return result;
}

std::vector<std::string> Account::List()
{
	std::vector<std::string> result;
	
	return result;
}

void Account::Close(Account* account)
{
	if(account == NULL)
	{
		throw std::invalid_argument("Account::Close(), Ch == NULL");
		return;	
	}
		
	Cache::Get()->CloseAccount(account->getID());
	delete account;
}

Table* Account::getTable() const
{
	return Tables::Get()->ACCOUNTS;
}
