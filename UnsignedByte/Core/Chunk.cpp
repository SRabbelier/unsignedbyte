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

#include "Chunk.h"
#include "Global.h"
#include "db.h"

using mud::Chunk;

Chunk::Chunk(SavableManagerPtr chunk) :
m_chunk(chunk)
{
	Assert(chunk);
}

Chunk::~Chunk(void)
{

}

value_type Chunk::getID() const
{
	return m_chunk->getkey(db::ChunksFields::Get()->CHUNKID)->getValue();
}

const std::string& Chunk::getName() const
{
	return m_chunk->getfield(db::ChunksFields::Get()->NAME)->getStringValue();	
}

const std::string& Chunk::getDescription() const
{
	return m_chunk->getfield(db::ChunksFields::Get()->DESCRIPTION)->getStringValue();	
}

const std::string& Chunk::getTags() const
{
	return m_chunk->getfield(db::ChunksFields::Get()->TAGS)->getStringValue();	
}

value_type Chunk::getRoom() const
{
	return m_chunk->getfield(db::ChunksFields::Get()->FKROOMS)->getIntegerValue();
}

void Chunk::setName(const std::string& name)
{
	ValuePtr value(new Value(db::ChunksFields::Get()->NAME, name));
	m_chunk->setvalue(value);
}

void Chunk::setDescription(const std::string& description)
{
	ValuePtr value(new Value(db::ChunksFields::Get()->DESCRIPTION, description));
	m_chunk->setvalue(value);
}

void Chunk::setTags(const std::string& tags)
{
	ValuePtr value(new Value(db::ChunksFields::Get()->TAGS, tags));
	m_chunk->setvalue(value);
}

void Chunk::setRoom(value_type room)
{
	ValuePtr value(new Value(db::ChunksFields::Get()->FKROOMS, room));
	m_chunk->setvalue(value);
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
	result.push_back(Global::Get()->sprintf("Tags: '%s'.", getTags().c_str()));
	result.push_back(Global::Get()->sprintf("Roomid: '%d'.", getRoom()));
	
	return result;
}

std::string Chunk::ShowShort()
{
	return Global::Get()->sprintf("%s: %s\n", 
			getName().c_str(),
			getDescription().c_str());
}

TableImplPtr Chunk::getTable() const
{
	return m_chunk->getTable();
}
