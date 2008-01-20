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

#include "EditorChunk.h"
#include "EditorString.h"
#include "EditorBool.h"

#include "UBSocket.h"

#include "StringUtilities.h"
#include "Exceptions.h"
#include "TableImpls.h"

#include "Account.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "Room.h"
#include "RoomManager.h"

#include "chunkimporter.h"

EditorChunk::ChunkCommand EditorChunk::m_editName("Name", &EditorChunk::editName);
EditorChunk::ChunkCommand EditorChunk::m_editDescription("Description", &EditorChunk::editDescription);
EditorChunk::ChunkCommand EditorChunk::m_editRoom("Room", &EditorChunk::editRoom);
EditorChunk::ChunkCommand EditorChunk::m_listDetails("Details", &EditorChunk::listDetails);
EditorChunk::ChunkCommand EditorChunk::m_importChunk("Import", &EditorChunk::importChunk);
EditorChunk::ChunkCommand EditorChunk::m_showChunk("Show", &EditorChunk::showChunk);
EditorChunk::ChunkCommand EditorChunk::m_saveChunk("Save", &EditorChunk::saveChunk);

EditorChunk::EditorChunk(UBSocket* sock) :
OLCEditor(sock),
m_chunk(),
m_target(M_NONE)
{
	listCommands(Global::Get()->EmptyString);
}

EditorChunk::~EditorChunk(void)
{

}

void EditorChunk::OnFocus()
{		
	switch(m_target)
	{
		case M_NONE:
			return;
			
		case M_IMPORT:
			m_target = M_NONE;
			importChunk(m_value);
			break;
			
		case M_IMPORTACCEPT:
			m_target = M_NONE;
			importChunk(m_yesno ? "accept" : "reject");
			break;
			
		case M_IMPORTSAVECHUNK:
			m_target = M_NONE;
			importChunk(m_yesno ? "save" : "discard");
			break;
	}
	
	// m_target = M_NONE; // has to happen -before- importChunk is called since importChunk might set it to something else
}

std::string EditorChunk::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	ChunkCommand* act = ChunkInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorChunk::dispatch(const std::string& action, const std::string& argument)
{
	ChunkCommand* act = ChunkInterpreter::Get()->translate(action);
	
	if(act && !m_chunk)
	{
		m_sock->Send("You need to be editing a chunk first.\n");
		m_sock->Send("(Use the 'edit' command.)\n");
		return;
	}
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorChunk::getEditing()
{
	return m_chunk;
}

TableImplPtr EditorChunk::getTable()
{
	return db::TableImpls::Get()->CHUNKS;
}

KeysPtr EditorChunk::addNew()
{
	return mud::ChunkManager::Get()->Add();
}

std::vector<std::string> EditorChunk::getList()
{
	return mud::ChunkManager::Get()->List();
}

void EditorChunk::setEditing(KeysPtr keys)
{
	if(!keys->size())
	{
		m_chunk.reset();
		return;
	}
	
	m_chunk = mud::ChunkManager::Get()->GetByKey(keys->first()->getValue());
	return;
}

std::vector<std::string> EditorChunk::getCommands()
{
	return ChunkInterpreter::Get()->getWords();
}

EditorChunk::ChunkInterpreter::ChunkInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("description", &m_editDescription);
	addWord("room", &m_editRoom);
	addWord("import", &m_importChunk);
	addWord("show", &m_showChunk);
	addWord("save", &m_saveChunk);
}

EditorChunk::ChunkInterpreter::~ChunkInterpreter(void)
{

}

void EditorChunk::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Chunk name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Chunk name changed from '%s' to '%s'.\n", m_chunk->getName().c_str(), argument.c_str());
	m_chunk->setName(argument);
	return;
}

void EditorChunk::editDescription(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	m_sock->Sendf("Chunk description changed from '%s' to '%s'.\n", m_chunk->getDescription().c_str(), argument.c_str());
	m_chunk->setDescription(argument);
	return;
}

void EditorChunk::editRoom(const std::string& argument)
{	
	int id = atoi(argument.c_str());
	if(id <= 0)
	{
		m_sock->Send("Please specify a room this Chunk belongs to.\n");
	}
	
	try
	{
		mud::RoomPtr room = mud::RoomManager::Get()->GetByKey(id);
		m_sock->Sendf("Room changed from '%s' to '%s'.\n", room->getName().c_str(), argument.c_str());
		m_chunk->setRoom(id);
	}
	catch(RowNotFoundException& e) 
	{
		m_sock->Sendf("'%s' is not a valid room!\n", argument.c_str());
		m_sock->Send(String::Get()->box(mud::RoomManager::Get()->List(), "Rooms"));
		return;
	}
}

void EditorChunk::importChunk(const std::string& argument)
{
	bool createdImporter = false;
	
	/** 
	 * There is no argument and no importer yes, create one
	 */ 
	if(argument.size() == 0 && !m_importer)
	{
		m_sock->Send("No argument, dropping you into the String Editor.\n");
		m_sock->Send("Paste your description there, when done the chunk will be imported.\n");
		m_sock->SetEditor(new EditorString(m_sock, m_value));
		m_target = M_IMPORT;
		return;
	}
	
	if(!m_importer)
	{
		ChunkImporterPtr importer(new ChunkImporter(argument));
		m_importer = importer;
		createdImporter = true;
		m_sock->Send("Import complete.\n");
	}
	
	if(argument.size() == 0 || createdImporter)
	{
		m_sock->Send("Importing would result in the following Chunk:\n");
		m_sock->Send(m_importer->getResult());
		m_sock->Send("Do you want to accept these changes?\n");
		m_sock->SetEditor(new EditorBool(m_sock, m_yesno));
		m_target = M_IMPORTACCEPT;
		return; 
	}
	
	if(!argument.compare("accept") || !argument.compare("reject"))
	{
		if(!argument.compare("accept"))
		{
			m_importer->Apply(m_chunk);
			m_sock->Send("Would you like to apply this import to another chunk as well?\n");
		}
		else		
		{
			m_sock->Send("Ok, canceled.\n");
			m_sock->Send("Would you like to apply this import to another chunk instead?\n");
		}
		
		m_sock->Send("(If so, this import will be saved while you remain in the chunk editor.\n");
		m_sock->Send("The next time you run import, even on another chunk, this import will be applied again.)\n");
		m_sock->SetEditor(new EditorBool(m_sock, m_yesno));
		m_target = M_IMPORTSAVECHUNK;
		return;
	}
	
	if(!argument.compare("save") || !argument.compare("discard"))
	{
		if(!argument.compare("save"))
		{
			m_sock->Send("Allright, this import will not be deleted till you change editors (e.g., type 'quit').\n");
			return;
		}
		else
		{
			m_sock->Send("Allright, import discarded.\n");
			m_importer.reset();
			return;
		}
	}
	
	m_sock->Send("Unknown action.\n");
}

void EditorChunk::listDetails(const std::string& argument)
{
	
}

void EditorChunk::showChunk(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_chunk->Show(), "Chunk"));
}

void EditorChunk::saveChunk(const std::string& argument)
{
	m_sock->Sendf("Saving chunk '%s'.\n", m_chunk->getName().c_str());
	m_chunk->Save();
	m_sock->Send("Saved.\n");
	return;
}
