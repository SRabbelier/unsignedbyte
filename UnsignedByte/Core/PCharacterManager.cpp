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
#include <sstream>

#include "PCharacterManager.h"
#include "PCharacter.h"
#include "Global.h"
#include "PCharacter.h"

using mud::PCharacterManager;
using mud::PCharacter;
using mud::PCharacterPtr;

void PCharacterManager::Close(PCharacterPtr Ch)
{
	if(!Ch)
		throw std::invalid_argument("PCharacter::Close(), Ch == NULL!");
	
	Close(Ch->getID());
}

bool PCharacterManager::isActive(value_type id)
{
	return m_pcharactersByKey.find(id) != m_pcharactersByKey.end();
}

bool PCharacterManager::isActive(cstring value)
{
	return m_pcharactersByName.find(value) != m_pcharactersByName.end();
}

mud::PCharacterPtr PCharacterManager::GetByKey(value_type id)
{
	PCharacterPtr p = m_byKey[id];
	if(p)
		return p;
		
	std::ostringstream err;
	err << "PCharacterManager::GetPCharacterByKey(), The id '" << id << "' has not been loaded yet.";
	throw std::invalid_argument(err.str());
}

mud::PCharacterPtr PCharacterManager::GetByName(cstring value)
{
	PCharacterPtr p = m_byName[value];
	if(p)
		return p;
		
	std::ostringstream err;
	err << "PCharacterManager::GetPCharacterByKey(), No character with name '" << value << "' has not been loaded yet.";
	throw std::invalid_argument(err.str());	
}

mud::PCharacterPtr PCharacterManager::LoadByKey(UBSocket* sock, value_type id)
{
	PCharacterPtr p = m_byKey[id];
	if(p)
	{
		std::ostringstream err;
		err << "PCharacterManager::LoadPCharacterByKey(), id '" << id << "' has already been loaded.";
		throw std::invalid_argument(err.str());
	}
	
	db::Characters* d = db::Characters::bykey(id);
	p = cachePCharacter(sock, d);
	return p;
}

mud::PCharacterPtr PCharacterManager::LoadByName(UBSocket* sock, cstring value)
{
	PCharacterPtr p = m_byName[value];
	if(p)
	{
		std::ostringstream err;
		err << "PCharacterManager::LoadPCharacterByKey(), A character with name '" << value << "' has already been loaded.";
		throw std::invalid_argument(err.str());
	}	
	
	db::Characters* d = db::Characters::byname(value);
	p = cachePCharacter(sock, d);
	return p;
}

void PCharacterManager::Close(value_type id)
{
	players_m::iterator key = m_byKey.find(id);
	players_ms::iterator name = m_byName.find(key->second->getName());
	m_byKey.erase(key);
	m_byName.erase(name);
}

PCharacterPtr PCharacterManager::cachePCharacter(UBSocket* sock, db::Characters* d)
{
	PCharacterPtr p(new PCharacter(sock, d));
	m_byKey[d->getcharacterid()] = p;
	m_pcharactersByKey.insert(d->getcharacterid());
	m_byName[d->getname()] = p;
	m_pcharactersByName.insert(d->getname());
	return p;
}
