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
#pragma once

#include "SavableHeaders.h"

#include <stack>

#include <TcpSocket.h>
#include <ISocketHandler.h>

namespace mud { 
	class Account; 
	typedef SmartPtr<mud::Account> AccountPtr;
	
	class Channel;
	typedef SmartPtr<mud::Channel> ChannelPtr;
};

class Editor;

class UBSocket : public TcpSocket
{
public:
	/**
	 * \brief Ctors
	 */ 
	UBSocket(ISocketHandler&);
	~UBSocket(void);

	/**
	 * \brief Socket input
	 */ 
	void OnLine(const std::string& line);
	void OnAccept();
	
	/**
	 * \brief Socket output
	 */ 
	void Send(const std::string& msg);
	void Sendf(const char* format, ...);

	/**
	 * \brief Prompt utilities
	 */ 
	void SetPrompt(const std::string& prompt = "");
	void SendPrompt();

	/**
	 * \brief Getters
	 */ 
	mud::Account* GetAccount() const;
	UBSocket* GetForcer() const;
	bool hasAccount() const;
	bool isHighForced() const { return m_highforced; }
	bool isForced() const { return m_forced; }
	bool isLowForced() const { return m_lowforced; }
	
	bool canReceiveChannel(mud::ChannelPtr channel);
	
	/**
	 * \brief Setters
	 */ 
	void SetAccount(mud::AccountPtr account) { m_account = account; }
	void SetEditor(Editor* cmd, bool popLast = false);
	void PopEditor();
	void SetForcer(UBSocket* forcer, bool weakForce = true, bool forced = false, bool highforced = false);
	void EndForce();

	/**
	 * \brief Utilities
	 */ 
	void SwitchEditors();
	
	/**
	 * \brief Static utilities
	 */ 
	static UBSocket* Cast(Socket* sock, bool Error = true);

private:
	/**
	 * \brief Ctors
	 */ 
	UBSocket(const UBSocket& rhs);
	UBSocket operator=(const UBSocket& rhs);

	/**
	 * \brief Variables
	 */ 
	std::string m_prompt;	// Current prompt
	mud::AccountPtr m_account; 	// Current account
	bool m_popeditor;		// Delete the top editor?
	bool m_popLast;			// Delete top editor when adding new one?
	std::stack<Editor*> m_editors; // stack of editors
	Editor* m_nexteditor; 	// Next Editor
	UBSocket* m_forcer; 	// Current forcer
	bool m_lowforced; 		// Low forced?
	bool m_forced;			// Forced?
	bool m_highforced;		// High forced?
	bool m_hascolor;		// Have colour codes?
	char m_colorcode;		// Current colourcode
};
