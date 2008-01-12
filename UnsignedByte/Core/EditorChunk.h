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
#pragma once

#include <string>
#include "OLCEditor.h"
#include "singleton.h"
#include "Interpreter.h"
#include "CommandObject.h"
#include "smart_ptr.h"

class UBSocket;
namespace mud 
{ 
	class Chunk; 
	typedef SmartPtr<Chunk> ChunkPtr;
};

class ChunkImporter;
typedef SmartPtr<ChunkImporter> ChunkImporterPtr;

class EditorChunk : public OLCEditor
{
public:
	typedef CommandObject<EditorChunk> ChunkCommand;

	EditorChunk(UBSocket* sock);
	~EditorChunk(void);
	
	void OnFocus();

	std::string name() { return "Chunk"; };
	std::string prompt() { return "Chunk> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	SavablePtr getEditing();
	TableImplPtr getTable();
	KeysPtr addNew();
	std::vector<std::string> getList();
	std::vector<std::string> getCommands();
	void setEditing(KeysPtr keys);
	
	void editName(const std::string& argument);
	void editDescription(const std::string& argument);
	void editRoom(const std::string& argument);
	void listDetails(const std::string& argument);
	void importChunk(const std::string& argument);
	void showChunk(const std::string& argument);
	void saveChunk(const std::string& argument);

private:
	EditorChunk(const EditorChunk& rhs);
	EditorChunk operator=(const EditorChunk& rhs);
	
	enum E_TARGET
	{
		M_NONE,
		M_IMPORT,
		M_IMPORTACCEPT,
		M_IMPORTSAVECHUNK,
	};
	
	mud::ChunkPtr m_chunk;
	std::string m_value;
	bool m_yesno;
	EditorChunk::E_TARGET m_target;
	ChunkImporterPtr m_importer;
	
	class ChunkInterpreter : public Interpreter<ChunkCommand>, public Singleton<ChunkInterpreter> {
	private:
		ChunkInterpreter(void);
		~ChunkInterpreter(void);
		friend class Singleton<ChunkInterpreter>;
	};

	static ChunkCommand m_editName;
	static ChunkCommand m_editDescription;
	static ChunkCommand m_editRoom;
	static ChunkCommand m_importChunk;
	static ChunkCommand m_listDetails;
	static ChunkCommand m_showChunk;
	static ChunkCommand m_saveChunk;
};
