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
#include "Editor.h"
#include "Interpreter.h"
#include "singleton.h"
#include "Action.h"

class UBSocket;

namespace mud { class PCharacter; };

class EditorPlaying : public Editor
{
public:
	EditorPlaying(UBSocket* sock, mud::PCharacter* character);
	~EditorPlaying(void);

	std::string name() { return "Playing"; };
	std::string prompt() { return "> "; };
	
	std::string lookup(const std::string& action);
	void dispatch(const std::string& action, const std::string& argument);

private:
	mud::PCharacter* m_char; // current active PCharacter
	EditorPlaying(const EditorPlaying& rhs) : Editor(rhs.m_sock) {};
	EditorPlaying operator=(const EditorPlaying& rhs) {return *this;};

	typedef EditorAction<UBSocket, mud::PCharacter> PlayingAction;
	
	class PlayingInterpreter : public Interpreter<PlayingAction>, public Singleton<PlayingInterpreter> {
	private:
		PlayingInterpreter(void);
		~PlayingInterpreter(void);
		friend class Singleton<PlayingInterpreter>;
	};

	class Areas : public PlayingAction, public Singleton<Areas> {
	private:
		Areas(void) {};
		~Areas(void) {};
		friend class Singleton<Areas>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Areas"; };
	};

	class Colours : public PlayingAction, public Singleton<Colours> {
	private:
		Colours(void) {};
		~Colours(void) {};
		friend class Singleton<Colours>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Colours"; };
	};

	class Commands : public PlayingAction, public Singleton<Commands> {
	private:
		Commands(void) {};
		~Commands(void) {};
		friend class Singleton<Commands>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Commands"; };
	};

	class Laston : public PlayingAction, public Singleton<Laston> {
	private:
		Laston(void) {};
		~Laston(void) {};
		friend class Singleton<Laston>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Laston"; };
	};

	class Look : public PlayingAction, public Singleton<Look> {
	private:
		Look(void) {};
		~Look(void) {};
		friend class Singleton<Look>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Look"; };
	};

	class Races : public PlayingAction, public Singleton<Races> {
	private:
		Races(void) {};
		~Races(void) {};
		friend class Singleton<Races>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Races"; };
	};

	class Rooms : public PlayingAction, public Singleton<Rooms> {
	private:
		Rooms(void) {};
		~Rooms(void) {};
		friend class Singleton<Rooms>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Rooms"; };
	};

	class Score : public PlayingAction, public Singleton<Score> {
	private:
		Score(void) {};
		~Score(void) {};
		friend class Singleton<Score>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Score"; };
	};

	class Say : public PlayingAction, public Singleton<Say> {
	private:
		Say(void) {};
		~Say(void) {};
		friend class Singleton<Say>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Say"; };
	};
	
	class Delete : public PlayingAction, public Singleton<Delete> {
	private:
		Delete(void) {};
		~Delete(void) {};
		friend class Singleton<Delete>;
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
	public:
		bool fullName() { return true; };
		std::string getName() { return "Delete"; };
	};
	
	class Quit : public PlayingAction, public Singleton<Quit> {
	private:
		Quit(void) {};
		~Quit(void) {};
		friend class Singleton<Quit>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		bool fullName() { return true; };
		std::string getName() { return "Quit"; };
	};

	class Who : public PlayingAction, public Singleton<Who> {
	private:
		Who(void) {};
		~Who(void) {};
		friend class Singleton<Who>;
	public:
		void Run(UBSocket* sock, const std::string& argument, mud::PCharacter* ch);
		std::string getName() { return "Who"; };
	};
};
