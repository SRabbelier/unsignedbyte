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

#include "EchoManager.h"
#include "Echo.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

using mud::EchoManager;
using mud::Echo;
using mud::EchoPtr;

std::vector<std::string> EchoManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr EchoManager::GetTable()
{
	return db::TableImpls::Get()->AREAS;
}

KeysPtr EchoManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->ECHOS);
	manager->save();
	return manager->getkeys();
}

mud::EchoPtr EchoManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->ECHOS));
	KeyPtr key(new Key(db::EchosFields::Get()->ECHOID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	EchoPtr p(new Echo(manager));
	return p;
}
