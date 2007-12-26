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

#include "smart_ptr.h"

#include "Editor.h"
#include "singleton.h"
#include "Interpreter.h"
#include "CommandObject.h"

class UBSocket;

namespace mud 
{ 
	class PCharacter; 
	typedef SmartPtr<PCharacter> PCharacterPtr;
};

class EditorPlaying : public Editor
{
public:
	typedef CommandObject<EditorPlaying> PlayingCommand;

	EditorPlaying(UBSocket* sock, mud::PCharacterPtr character);
	~EditorPlaying(void);

	std::string name() { return "Playing"; };
	std::string prompt() { return "> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);
	
	void listAreas(const std::string& argument);
	void listColours(const std::string& argument);
	void listCommands(const std::string& argument);
	void listRooms(const std::string& argument);
	void listRaces(const std::string& argument);
	void showScore(const std::string& argument);
	void look(const std::string& argument);
	void say(const std::string& argument);
	void deleteCharacter(const std::string& argument);
	void quitEditor(const std::string& argument);

private:
	mud::PCharacterPtr m_char; // current active PCharacter
	EditorPlaying(const EditorPlaying& rhs);
	EditorPlaying operator=(const EditorPlaying& rhs);

	class PlayingInterpreter : public Interpreter<PlayingCommand>, public Singleton<PlayingInterpreter> {
	private:
		PlayingInterpreter(void);
		~PlayingInterpreter(void);
		friend class Singleton<PlayingInterpreter>;
	};

	static PlayingCommand m_listAreas;
	static PlayingCommand m_listColours;
	static PlayingCommand m_listCommands;
	static PlayingCommand m_listPlayers;
	static PlayingCommand m_listRaces;
	static PlayingCommand m_listRooms;
	static PlayingCommand m_showScore;
	static PlayingCommand m_look;
	static PlayingCommand m_say;
	static PlayingCommand m_deleteCharacter;
	static PlayingCommand m_quitEditor;
	static PlayingCommand m_listOnlinePlayers;
};
