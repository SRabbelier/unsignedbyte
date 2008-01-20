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

#include "EditorString.h"
#include "StringUtilities.h"
#include "UBSocket.h"
#include "Account.h"

EditorString::EditorString(UBSocket* sock, std::string& target) :
Editor(sock),
m_state(M_FIRST),
m_target(target)
{
	OnLine(Global::Get()->EmptyString);
}

EditorString::~EditorString()
{
	std::string result = String::Get()->unlines(m_strings, " ");
	m_target = result;
}

EditorString::E_STATE EditorString::ParseMode(char mode, bool silent)
{
	E_STATE choice = M_FIRST;
	
	switch(mode)
	{
		default:
			if(!silent)
				m_sock->Sendf("Unknown mode '%c'.\n", mode);
			break;
		
		case 'a': // append
			m_sock->Send("Switching to 'append' mode.\n");
			choice = M_APPEND;
			break;	
			
		case 'd': // done
			m_sock->Send("Allright, done!\n");
			choice = M_WAITING_FOR_INPUT;
			break;
			
		case 'r': // replace
			m_sock->Send("Switching to 'replacement' mode.\n");
			choice = M_REPLACE;
			break;
		
		case 's': // show
		case 'v': // view
			m_sock->Send("Switching to 'viewing' mode.\n");
			choice = M_VIEW;
			break;
	}
	
	return choice;
}

void EditorString::ParseDot(const std::string& line)
{
	std::string command = line;
	command.erase(0, 1);
	
	E_STATE changedstate = ParseMode(command[0]);
	if(changedstate != M_FIRST)
	{
		m_state = changedstate;
		return;
	}
	
	if(!command.compare("c"))
	{
		m_sock->Send("Text cleared.\n");
		m_strings.clear();
		return;
	}
	
	if(!command.compare("q"))
	{
		m_sock->Send("Quitting now.\n");
		m_state = M_DONE;
		return;
	}
	
	if(!command.compare("h"))
	{
		m_sock->Send("Some descriptive help text goes here.\n");
		return;
	}
	
	m_sock->Sendf("Unknown dot command '%s'.\n", command.c_str());
	return;
}

void EditorString::OnLine(const std::string& line)
{	
	if(!line.compare("~"))
	{
		m_sock->Send("Allright, done!\n");
		m_state = M_DONE;
	}
	
	if(line[0] == '.')
	{
		ParseDot(line);
		return;
	}

	switch(m_state)
	{
	default:
	{
		Global::Get()->bug("EditorString::OnLine(), default m_state!\n");
		m_sock->Send("BUG! Disconnecting you now...\n");
		m_sock->SetCloseAndDelete();
		return;
	} /* default */

	case M_FIRST:
	{
		m_state = M_WAITING_FOR_INPUT;
		m_sock->Send("Welcome to the string editor.\n");
		// fallthrough
	} /* case M_FIRST: */

	case M_WAITING_FOR_INPUT:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Please choose an editing mode.\n");
			m_sock->Send("If you need help please type '.h'.\n");
			return;
		}
		
		char mode;
		
		if(line[0] == '.')
			mode = line[1];
		else
			mode = line[0];
		
		E_STATE choice = ParseMode(mode);
		
		if(choice == M_FIRST)
			m_state = M_WAITING_FOR_INPUT;
		else
			m_state = choice;
		
		OnLine(Global::Get()->EmptyString);
		return;
	} /* case M_WAITING_FOR_INPUT: */

	case M_APPEND:
	{
		if(line.size() == 0)
		{
			m_sock->Sendf("If you want to append a newline type '.n' on an empty line.\n");
			return;
		}

		m_strings.push_back(line);
		return;
	} /* case M_APPEND: */
	
	case M_REPLACE:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Not yet implemented - Alturin 30-12-2007.\n");
			return;
		}
		
		return;
	}
	case M_VIEW:
	{
		if(line.size() != 0)
		{
			m_sock->Send("At the moment all you can do here is hit enter to show the entire string.\n");
			return;
		}
		
		m_sock->Send(String::Get()->unlines(m_strings, " "));
		return;
	}


	case M_DONE:
	{
		m_sock->PopEditor();
		return;
	} /* case M_DONE: */
	
	} /* switch(state) */

}
