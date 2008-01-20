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

#include "DetailManager.h"
#include "Detail.h"
#include "TableImpls.h"
#include "db.h"

using mud::DetailManager;
using mud::Detail;
using mud::DetailPtr;

std::vector<std::string> DetailManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr DetailManager::GetTable()
{
	return db::TableImpls::Get()->DETAILS;
}

KeysPtr DetailManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->DETAILS);
	manager->save();
	return manager->getkeys();
}

mud::DetailPtr DetailManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->DETAILS));
	KeyPtr key(new Key(db::DetailsFields::Get()->DETAILID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	DetailPtr p(new Detail(manager));
	return p;
}
