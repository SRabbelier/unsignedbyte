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

#include "ChunkManager.h"
#include "Chunk.h"
#include "TableImpls.h"
#include "db.h"

using mud::ChunkManager;
using mud::Chunk;
using mud::ChunkPtr;

std::vector<std::string> ChunkManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr ChunkManager::GetTable()
{
	return db::TableImpls::Get()->CHUNKS;
}

KeysPtr ChunkManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->CHUNKS);
	manager->save();
	return manager->getkeys();
}

mud::ChunkPtr ChunkManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->CHUNKS));
	KeyPtr key(new Key(db::ChunksFields::Get()->CHUNKID, id));
	keys->addKey(key);
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	ChunkPtr p(new Chunk(manager));
	return p;
}
