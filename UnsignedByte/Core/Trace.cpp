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

#include "Exceptions.h"
#include "Trace.h"
#include "Global.h"
#include "db.h"
#include "Account.h"
#include "AccountManager.h"

using mud::Trace;
using namespace mud;

Trace::Trace(SavableManagerPtr trace) :
m_trace(trace)
{
	Assert(trace);
}

Trace::~Trace(void)
{

}

const std::string& Trace::getDiff() const
{
	return m_trace->getfield(db::TracesFields::Get()->DIFF)->getStringValue();
}

const std::string& Trace::getDescription() const
{
	return m_trace->getfield(db::TracesFields::Get()->DESCRIPTION)->getStringValue();
}

value_type Trace::getAccount() const
{
	return m_trace->getfield(db::TracesFields::Get()->FKACCOUNTS)->getIntegerValue();
}

time_t Trace::getTime() const
{
	return m_trace->getfield(db::TracesFields::Get()->TIME)->getIntegerValue();
}

void Trace::setDiff(const std::string& diff)
{
	ValuePtr value(new Value(db::TracesFields::Get()->DIFF, diff));
	m_trace->setvalue(value);
}

void Trace::setDescription(const std::string& description)
{
	ValuePtr value(new Value(db::TracesFields::Get()->DESCRIPTION, description));
	m_trace->setvalue(value);
}

void Trace::setTime(time_t time)
{
	ValuePtr value(new Value(db::TracesFields::Get()->TIME, time));
	m_trace->setvalue(value);
}

void Trace::setAccount(value_type account)
{
	ValuePtr value(new Value(db::TracesFields::Get()->FKACCOUNTS, account));
	m_trace->setvalue(value);
}


void Trace::Delete()
{
	m_trace->erase();
}

void Trace::Save()
{
	m_trace->save();
}

bool Trace::Exists()
{
	return m_trace->exists();
}

std::vector<std::string> Trace::Show()
{
	std::vector<std::string> result;
	std::string editedby = "unknown";
	
	try {
		AccountPtr account = mud::AccountManager::Get()->GetByKey(getAccount());
		editedby = account->getName();
	} catch(RowNotFoundException& e) {
		
	}
	
	result.push_back(Global::Get()->sprintf("Account: '%s'.", editedby.c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.", getDescription().c_str()));
	result.push_back(Global::Get()->sprintf("Diff: %s.", getDiff().c_str()));
	result.push_back(Global::Get()->sprintf("Time: %ld.", getTime()));
	
	return result;
}

std::string Trace::ShowShort()
{
	std::string editedby = "unknown";
	
	try {
		AccountPtr account = mud::AccountManager::Get()->GetByKey(getAccount());
		editedby = account->getName();
	} catch(RowNotFoundException& e) {
		
	}
	
	return Global::Get()->sprintf("%s (%ld): %s\n", 
			editedby.c_str(),
			getTime(),
			getDescription().c_str());
}

TableImplPtr Trace::getTable() const
{
	return m_trace->getTable();
}
