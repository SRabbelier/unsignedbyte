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

#include "Account.h"
#include "SavableHeaders.h"
#include "db.h"

using mud::Account;

Account::Account(SavableManagerPtr dbaccount) :
m_account(dbaccount)
{
	if(!m_account)
		throw std::invalid_argument("Account::Account(), m_account == NULL!");
}

Account::~Account(void)
{

}

value_type Account::getID() const
{
	return m_account->getkey(db::AccountsFields::Get()->ACCOUNTID)->getValue();
}

const std::string& Account::getName() const
{
	return m_account->getfield(db::AccountsFields::Get()->NAME)->getStringValue();
}

const std::string& Account::getPassword() const
{
	return m_account->getfield(db::AccountsFields::Get()->PASSWORD)->getStringValue();
}

void Account::setName(const std::string& name)
{
	ValuePtr value(new Value(db::AccountsFields::Get()->NAME, name));
	m_account->setvalue(value);
}

void Account::setPassword(const std::string& password)
{
	ValuePtr value(new Value(db::AccountsFields::Get()->PASSWORD, password));
	m_account->setvalue(value);
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

TablePtr Account::getTable() const
{
	return m_account->getTable();
}
