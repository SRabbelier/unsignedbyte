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

#include "Detail.h"
#include "Global.h"
#include "db.h"
#include "Trace.h"
#include "TraceManager.h"
#include "TableImpls.h"

using mud::Detail;

Detail::Detail(SavableManagerPtr detail) :
m_detail(detail)
{
	Assert(detail);
}

Detail::~Detail(void)
{

}

value_type Detail::getID() const
{
	return m_detail->getkey(db::DetailsFields::Get()->DETAILID)->getValue();
}

const std::string& Detail::getKey() const
{
	return m_detail->getfield(db::DetailsFields::Get()->KEY)->getStringValue();	
}

const std::string& Detail::getDescription() const
{
	return m_detail->getfield(db::DetailsFields::Get()->DESCRIPTION)->getStringValue();	
}

void Detail::setKey(const std::string& key)
{
	ValuePtr value(new Value(db::DetailsFields::Get()->KEY, key));
	m_detail->setvalue(value);
}

void Detail::setDescription(const std::string& description)
{
	ValuePtr value(new Value(db::DetailsFields::Get()->DESCRIPTION, description));
	m_detail->setvalue(value);
}

void Detail::Delete()
{
	m_detail->erase();
}

void Detail::Save()
{
	m_detail->save();
}

void mud::Detail::Delete(value_type accountid, const std::string& description)
{
	
}

void mud::Detail::Save(value_type accountid, const std::string& description)
{	
	if(!m_detail->isDirty())
		return;
	
	KeysPtr keys = mud::TraceManager::Get()->Add();
	mud::TracePtr trace = mud::TraceManager::Get()->GetByKey(keys->first()->getValue());
	
	if(accountid)
	{
		trace->setAccount(accountid);
		
		if(description != Global::Get()->EmptyString)
			trace->setDescription(description);
	}
	
	trace->setDiff(m_detail->getDiff());
	trace->setTime(time(NULL));
	trace->Save(); // create the Trace
	
	RelationPtr relation(new Relation(db::TableImpls::Get()->TRACEDETAIL));
	relation->addKey(db::TraceDetailFields::Get()->FKDETAILS, getID());
	relation->addKey(db::TraceDetailFields::Get()->FKTRACES, keys->first()->getValue());
	relation->save(); // create the relation
	
	m_detail->save(); // save the room
}

bool Detail::Exists()
{
	return m_detail->exists();
}

std::vector<std::string> Detail::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Key: '%s'.", getKey().c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.", getDescription().c_str()));
	
	return result;
}

std::string Detail::ShowShort()
{
	return Global::Get()->sprintf("%s: %s\n", 
			getKey().c_str(),
			getDescription().c_str());
}

TableImplPtr Detail::getTable() const
{
	return m_detail->getTable();
}
