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

#include <string>
#include <map>
#include <stdarg.h>
#include <stdexcept>

#include "Editor.h"
#include "Parse.h"
#include "Permission.h"
#include "Cache.h"
#include "Command.h"
#include "UBSocket.h"
#include "Account.h"

using mud::Permission;
using mud::Command;

Editor::Editor(UBSocket* sock) : 
m_sock(sock) 
{
	if(sock == NULL)
		throw std::invalid_argument("Editor::Editor(), m_sock == NULL!");
}

Editor::~Editor()
{
	
}

void Editor::Send(const std::string& msg) 
{ 
	m_sock->Send(msg); 
}

void Editor::Sendf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	Send(Global::Get()->sprint(args, format));
	va_end(args);
}

void Editor::Disconnect()
{
	m_sock->SetCloseAndDelete();
}

void Editor::OnLine(const std::string& line)
{
	if(line.size() == 0)
	{
		m_sock->SendPrompt();
		return;
	}

	Parse p(line);
	std::string action = p.getword();
	std::string argument = p.getrest();

	std::string actionname = lookup(action);
		
	if(actionname.size() == 0)
	{
		// TODO: Log failure?
		Sendf("Unknown action '%s', type action for a list of available actions.\n", action.c_str());
		m_sock->SendPrompt();
		return;
	}

	std::string commandname = name();
	commandname.append("::");
	commandname.append(actionname);

	bool hasGrant = Permission::defaultGrant;
	bool hasLog = Permission::defaultLog;
	
	bool canLowForce = Command::defaultLowForce;
	bool canForce = Command::defaultForce;
	bool canHighForce = Command::defaultHighForce;
	
	bool isLowForced = m_sock->isLowForced();
	bool isNormalForced = m_sock->isForced();
	bool isHighForced = m_sock->isHighForced();
	bool isForced = isLowForced || isNormalForced || isHighForced;

	long id = mud::Cache::Get()->lookupCommandByName(actionname);
	if(id)
	{
		Command* cmd = mud::Cache::Get()->GetCommandByKey(id);
		hasGrant = cmd->getGrant(m_sock);
		hasLog = cmd->getLog(m_sock);
		if(isForced)
		{
			canHighForce = cmd->canHighForce();
			canForce = cmd->canForce();
			canLowForce = cmd->canLowForce();
		}
	}
	
	if(isForced)
	{
		if(isLowForced && !canLowForce)
		{
			m_sock->GetForcer()->Sendf("You can't make them to '%s'!\n", action.c_str());
			return;
		}
		
		if(isForced && !canForce)
		{
			m_sock->GetForcer()->Sendf("You can't force them to '%s'!\n", action.c_str());
			return;
		}
		
		if(isHighForced && !canHighForce)
		{
			m_sock->GetForcer()->Sendf("There is no way you can make them '%s'!\n", action.c_str());
			return;
		}
	}
	
	if(hasGrant)
	{
		if(hasLog || isForced)
		{
			if(isForced)
			{
				// TODO log
			}
			else
			{
				// TODO log
			}
		}
		
		dispatch(action, argument);
	}
	else
	{
		if(hasLog || isForced)
		{
			if(isForced)
			{
				// TODO log
			}
			else
			{
				// TODO log
			}				
		}
		
		Sendf("Sorry, you do not have permission to '%s'.\n", actionname.c_str());
	}
	
	m_sock->SendPrompt();
	return;
}
