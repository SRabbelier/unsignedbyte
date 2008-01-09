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

#include "ChunkManager.h"
#include "Chunk.h"
#include "Global.h"

#include "Table.h"
#include "Tables.h"

using mud::ChunkManager;
using mud::Chunk;
using mud::ChunkPtr;

std::vector<std::string> ChunkManager::List()
{
	return GetTable()->tableList();
}

TablePtr ChunkManager::GetTable()
{
	return Tables::Get()->CHUNKS;
}

value_type ChunkManager::Add()
{
	db::Chunks d;
	d.save();
	value_type id = d.getchunkid();
	if(id == 0)
		Global::Get()->bug("ChunkManager::AddChunk(), id = 0");
		
	return id;
}

mud::ChunkPtr ChunkManager::GetByKey(value_type id)
{
	ChunkPtr p = m_byKey[id];
	if(p)
		return p;

	db::Chunks* d = db::Chunks::bykey(id);
	p = cacheChunk(d);
	return p;
}

void ChunkManager::Close(value_type id)
{
	chunks_m::iterator key = m_byKey.find(id);
	m_byKey.erase(key);
}

ChunkPtr ChunkManager::cacheChunk(db::Chunks* d)
{
	ChunkPtr p(new Chunk(d));
	m_byKey[d->getchunkid()] = p;
	return p;
}
