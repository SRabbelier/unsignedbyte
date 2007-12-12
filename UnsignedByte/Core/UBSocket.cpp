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

#include <assert.h>
#include <string>
#include <stdarg.h>
#include <stdexcept>

#include <Parse.h>

#include "UBSocket.h"
#include "PCharacter.h"

#include "DatabaseMgr.h"
#include "EditorAccountLogin.h"
#include "EditorOOC.h"
#include "Global.h"
#include "Account.h"
#include "Cache.h"
#include "Colour.h"

UBSocket::UBSocket(ISocketHandler& h) :
TcpSocket(h),
m_account(NULL),
m_editors(),
m_nexteditor(NULL),
m_lowforced(false),
m_forced(false),
m_highforced(false),
m_hascolor(true),
m_colorcode('`')
{
	SetLineProtocol();
}

UBSocket::~UBSocket(void)
{
	while(!m_editors.empty())
	{
		delete m_editors.top();
		m_editors.pop();
	}

	if(m_nexteditor != NULL)
	{
		delete m_nexteditor;
		m_nexteditor = NULL;
	}

	if(m_account)
	{
		mud::Account::Close(m_account);
		m_account = NULL;
	}
}

void UBSocket::OnAccept()
{
	Global::Get()->logf("Login from: %s\n", GetRemoteAddress().c_str());
	Sendf("Welcome to %s.\n", game::vname);
	Editor* p = new EditorAccountLogin(this);
	if(!m_editors.empty())
		throw std::logic_error("UBSocket::OnAccept(), m_editor != NULL!");

	m_editors.push(p);
}

void UBSocket::OnLine(const std::string &line)
{	
	bool popLast = false;
	
	SwitchEditors();

	if(m_editors.empty())
	{
		Global::Get()->bugf("UBSocket::OnLine(), m_editor == NULL!");
		Send("You don't have an editor mode set?\n");
		Send("Closing your connection now.\n");
		SetCloseAndDelete();
		return;
	}
	
	if(line.size() && line[0] == Global::Get()->OOCIdentifier)
	{
		m_editors.push(new EditorOOC(this));
		popLast = true;
	}
	
	m_editors.top()->OnLine(line);
	
	if(popLast)
		PopEditor();
		
	return;
}

mud::Account* UBSocket::GetAccount() const
{
	if(m_account == NULL)
		throw std::logic_error("UBSocket::GetAccount(), m_account == NULL!");
	
	return m_account;
}

UBSocket* UBSocket::GetForcer() const
{
	if(m_forcer == NULL)
		throw std::logic_error("UBSocket::GetForcer(), m_forcer == NULL!");
		
	return m_forcer;
}

bool UBSocket::hasAccount() const
{
	return m_account;
}

void UBSocket::SetPrompt(const std::string& prompt)
{
	m_prompt = prompt;
}

void UBSocket::SendPrompt()
{
	Send(m_prompt);
}

void UBSocket::SetEditor(Editor* edit, bool popLast)
{
	if(m_nexteditor)
	{
		Global::Get()->bug("UBSocket::SetEditor() was called while we are already waiting to switch to a next editor!\n");
		Send("Something went wrong, somehow you are switching to another editor while you were already doing just that!\n");
		Send("Closing your connection now.\n");
		SetCloseAndDelete();
		return;
	}

	SetPrompt();
	m_nexteditor = edit;
	m_popLast = popLast;
	return;
}

void UBSocket::SwitchEditors()
{		
	if(!m_popeditor && !m_nexteditor)
		return;
	
	if(m_popeditor && m_nexteditor)
	{
		Global::Get()->bug("UBSocket::SwitchEditors() was called, but we don't have both a new editor and we want to pop one?!");
		Send("Something went wrong, somehow you are switching to another editor but you're also deleting the top one?!\n");
		Send("Closing your connection now.\n");
		SetCloseAndDelete();
		return;
	}
	
	if(m_popeditor || m_popLast)
	{
		if(m_editors.empty()) // should be always
		{
			Global::Get()->bug("UBSocket::SwitchEditors() was called, but we don't have a current editor?!");
			Send("Something went wrong, somehow you are switching to another editor but you don't have one set?!\n");
			Send("Closing your connection now.\n");
			SetCloseAndDelete();
			return;
		}
		
		delete m_editors.top();
		m_editors.pop();
		m_popeditor = false;
		m_popLast = false;
		SetPrompt(m_editors.top()->prompt());
	}

	if(m_nexteditor)
	{
		m_editors.push(m_nexteditor);
		m_nexteditor = NULL;
		SetPrompt(m_editors.top()->prompt());
		SendPrompt();
	}
}

void UBSocket::PopEditor()
{
	if(m_popeditor)
	{
		Global::Get()->bug("UBSocket::PopEditor() was called, but the top editor is already being popped?!");
		Send("Something went wrong, somehow you are popping the top editor but it was already being popped?!\n");
		Send("Closing your connection now.\n");
		SetCloseAndDelete();
		return;
	}
	
	m_popeditor = true;
}

void UBSocket::Send(const std::string& msg)
{
	if(!m_hascolor || msg.find(m_colorcode) == std::string::npos)
	{
		SendBuf(msg.c_str(), msg.size());
		return;
	}

	std::string buf = msg;
	buf.append("`^");

	for(size_t i = buf.find(m_colorcode); i != std::string::npos; i = buf.find(m_colorcode))
	{
		if(i >= buf.size())
		{
			Global::Get()->bugf("Colour code %c was found as last character in output '%s'!\n", m_colorcode, msg.c_str());
			std::string err = Global::Get()->sprintf("Colour code %c was found as last character in output '%s'!\n", m_colorcode, msg.c_str());
			SendBuf(err.c_str(), err.size());
			return;
		}

		std::string code = buf.substr(i+1, 1);

		buf.erase(i+1, 1);
		buf.erase(i, 1);

		long id = db::Colours::lookupcode(code);
		if(!id)
		{
			Global::Get()->bugf("Unknown colour code %s!\n", code.c_str());
			continue;
		}

		mud::Colour* colour = mud::Cache::Get()->GetColourByKey(id);
		buf.insert(i, colour->getColourString());
	}
	
	SendBuf(buf.c_str(), buf.size());

}

void UBSocket::Sendf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	Send(Global::Get()->sprint(args, format));
	va_end(args);
}

UBSocket* UBSocket::Cast(Socket *sock, bool Error)
{
	UBSocket* sock2 = dynamic_cast<UBSocket*>(sock);
	if(!sock2)
	{
		if(Error)
		{
			Global::Get()->bugf("BUG: UBSocket::Cast(), Error = true, but sock could not be casted to an UBSocket!");
		}
		return NULL;
	}
	return sock2;
}
