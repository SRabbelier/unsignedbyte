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

#include "AccountManager.h"
#include "Account.h"
#include "Global.h"

#include "Table.h"
#include "Tables.h"

using mud::AccountManager;
using mud::Account;
using mud::AccountPtr;

bool AccountManager::IllegalName(const std::string& name)
{
	try
	{
		lookupByName(name);
		return true;
	} catch(RowNotFoundException& e) {}

	return false;
}

std::vector<std::string> AccountManager::List()
{
	return GetTable()->tableList();
}

TablePtr AccountManager::GetTable()
{
	return Tables::Get()->ACCOUNTS;
}

value_type AccountManager::Add()
{
	db::Accounts d;
	d.save();
	value_type id = d.getaccountid();
	if(id == 0)
		Global::Get()->bug("AccountManager::AddAcount(), id = 0");
		
	return id;
}

void AccountManager::Close(AccountPtr account)
{
	if(!account)
	{
		throw std::invalid_argument("Account::Close(), Ch == NULL");
		return;	
	}

	Close(account->getID());
}

void AccountManager::Close(value_type id)
{
	accounts_m::iterator key = m_byKey.find(id);
	if(key != m_byKey.end())
	{
		m_byKey.erase(key);
		accounts_ms::iterator name = m_byName.find(key->second->getName());
		if(name != m_byName.end())
			m_byName.erase(name);
	}
}

AccountPtr AccountManager::GetByKey(value_type id)
{
	AccountPtr p = m_byKey[id];
	if (p)
		return p;

	db::Accounts* d = db::Accounts::bykey(id);
	p = cacheAccount(d);
	return p;
}

AccountPtr AccountManager::GetByName(cstring value)
{
	AccountPtr p = m_byName[value];
	if(p)
		return p;

	db::Accounts* d = db::Accounts::byname(value);
	p = cacheAccount(d);
	
	return p;
}

value_type AccountManager::lookupByName(cstring value)
{
	reverseStringKey::iterator it = m_lookupByName.find(value);
	if(it != m_lookupByName.end())
		return it->second;
	
	value_type id = db::Accounts::lookupname(value);
	m_lookupByName[value] = id;
	return id;
}

AccountPtr AccountManager::cacheAccount(db::Accounts* d)
{
	AccountPtr p(new Account(d));
	m_byKey[d->getaccountid()] = p;
	m_byName[d->getname()] = p;
	return p;
}
