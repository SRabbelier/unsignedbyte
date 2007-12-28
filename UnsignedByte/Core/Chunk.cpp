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

#include "Chunk.h"
#include "Global.h"
#include "Cache.h"

using mud::Chunk;

Chunk::Chunk(db::Chunks* chunk) :
m_chunk(chunk)
{
	if(m_chunk == NULL)
		throw new std::invalid_argument("Chunk::Chunk(), m_chunk == NULL!");
}

Chunk::~Chunk(void)
{
	delete m_chunk;
	m_chunk = NULL;
}

void Chunk::Delete()
{
	m_chunk->erase();
}

void Chunk::Save()
{
	m_chunk->save();
}

bool Chunk::Exists()
{
	return m_chunk->exists();
}

std::vector<std::string> Chunk::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Name: '%s'.", getName().c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.", getDescription().c_str()));
	
	return result;
}

std::string Chunk::ShowShort()
{
	return Global::Get()->sprintf("%s: %s\n", 
			getName().c_str(),
			getDescription().c_str());
}

TablePtr Chunk::getTable() const
{
	return Tables::Get()->AREAS;
}
