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

#include <string>
#include <stdexcept>

#include "MCharacterManager.h"
#include "MCharacter.h"
#include "Global.h"
#include "MCharacter.h"

using mud::MCharacterManager;
using mud::MCharacter;
using mud::MCharacterPtr;

mud::MCharacterPtr MCharacterManager::GetByKey(value_type id)
{
	MCharacterPtr p = m_byKey[id];
	if(p)
		return p;
		
	db::Characters* d = db::Characters::bykey(id);
	p = cacheMCharacter(d);
	return p;
}

mud::MCharacterPtr MCharacterManager::GetByName(cstring value)
{
	MCharacterPtr p = m_byName[value];
	if(p)
		return p;
		
	db::Characters* d = db::Characters::byname(value);
	p = cacheMCharacter(d);
	return p;
}

void MCharacterManager::Close(value_type id)
{
	mobiles_m::iterator key = m_byKey.find(id);
	mobiles_ms::iterator name = m_byName.find(key->second->getName());
	m_byKey.erase(key);
	m_byName.erase(name);
}

MCharacterPtr MCharacterManager::cacheMCharacter(db::Characters* d)
{
	MCharacterPtr p(new MCharacter(d));
	m_byKey[d->getcharacterid()] = p;
	m_byName[d->getname()] = p;
	return p;
}
