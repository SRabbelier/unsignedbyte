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

#include "TraceManager.h"
#include "Trace.h"
#include "TableImpls.h"
#include "db.h"

using mud::TraceManager;
using mud::Trace;
using mud::TracePtr;

std::vector<std::string> TraceManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr TraceManager::GetTable()
{
	return db::TableImpls::Get()->TRACES;
}

KeysPtr TraceManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->TRACES);
	manager->save();
	return manager->getkeys();
}

mud::TracePtr TraceManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->TRACES));
	KeyPtr key(new Key(db::TracesFields::Get()->TRACEID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	TracePtr p(new Trace(manager));
	return p;
}
