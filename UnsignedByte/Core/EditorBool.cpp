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

#include "EditorBool.h"
#include "StringUtilities.h"
#include "UBSocket.h"
#include "Account.h"

EditorBool::EditorBool(UBSocket* sock, bool& target) :
Editor(sock),
m_state(M_FIRST),
m_target(target)
{
	OnLine(Global::Get()->EmptyString);
}

EditorBool::~EditorBool()
{
	m_target = m_result;
}

void EditorBool::OnLine(const std::string& line)
{	
	switch(m_state)
	{
	default:
	{
		Global::Get()->bug("EditorBool::OnLine(), default m_state!\n");
		m_sock->Send("BUG! Disconnecting you now...\n");
		m_sock->SetCloseAndDelete();
		return;
	} /* default */

	case M_FIRST:
	{
		m_state = M_WAITNG_FOR_CHOICE;
		// fallthrough
	} /* case M_FIRST: */
	
	case M_WAITNG_FOR_CHOICE:
	{
		if(line.size() == 0)
		{
			m_sock->Send("Please choose 'yes' or 'no'.\n");
			return;
		}
		
		if(!line.compare("yes") || !line.compare("y"))
		{
			m_result = true;
			m_state = M_DONE;
		}
		
		if(!line.compare("no") || !line.compare("n"))
		{
			m_result = false;
			m_state = M_DONE;
		}
		
		if(m_state != M_DONE)	
		{
			OnLine(Global::Get()->EmptyString);
			return;
		}
		
		// fallthrough
	}
	
	case M_DONE:
	{
		m_sock->PopEditor();
		return;
	}
	} // switch(m_state)
}
