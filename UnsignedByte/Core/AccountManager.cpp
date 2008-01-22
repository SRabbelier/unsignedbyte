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

#include "AccountManager.h"
#include "Account.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

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

TableImplPtr AccountManager::GetTable()
{
	return db::TableImpls::Get()->ACCOUNTS;
}

KeysPtr AccountManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->ACCOUNTS);
	manager->save();
	return manager->getkeys();
}

AccountPtr AccountManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->ACCOUNTS));
	KeyPtr key(new Key(db::AccountsFields::Get()->ACCOUNTID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	AccountPtr p(new Account(manager));
	return p;
}

AccountPtr AccountManager::GetByName(cstring value)
{	
	ValuePtr val(new Value(db::AccountsFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	AccountPtr p(new Account(manager));
	return p;
}

value_type AccountManager::lookupByName(cstring value)
{
	ValuePtr val(new Value(db::AccountsFields::Get()->NAME, value));
	KeysPtr keys = SavableManager::lookupvalue(val);
	value_type id = keys->getKey(db::AccountsFields::Get()->ACCOUNTID)->getValue();
	return id;
}
