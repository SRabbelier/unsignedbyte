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

#include "ExitManager.h"
#include "Exit.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

using mud::ExitManager;
using mud::Exit;
using mud::ExitPtr;

std::vector<std::string> ExitManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr ExitManager::GetTable()
{
	return db::TableImpls::Get()->EXITS;
}

KeysPtr ExitManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->EXITS);
	manager->save();
	return manager->getkeys();
}

mud::ExitPtr ExitManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->EXITS));
	KeyPtr key(new Key(db::ExitsFields::Get()->EXITID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	ExitPtr p(new Exit(manager));
	return p;
}
