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

#include "Relation.h"
#include "KeyDef.h"
#include "Key.h"
#include "Keys.h"
#include "SavableManager.h"
#include "TableImpl.h"
#include "FieldImpl.h"

Relation::Relation(TableImplPtr table) :
m_table(table),
m_keys(new Keys(table))
{
	m_manager = SavableManager::getnew(table);
	Assert(table);
}

Relation::~Relation()
{
	
}

void Relation::addKey(KeyDefPtr keydef, value_type value)
{
	Assert(keydef);
	Assert(value);
	
	KeyPtr key;
	key = KeyPtr(new Key(keydef, value));
	m_keys->addKey(key);
}

void Relation::save()
{
	m_manager->setkeys(m_keys);
	m_manager->save();
}
