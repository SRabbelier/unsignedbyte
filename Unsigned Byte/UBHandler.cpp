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

#include "ListenSocket.h"
#include "UBHandler.h"
#include "UBSocket.h"
#include "SQLSocket.h"
#include "PCharacter.h"
#include "Global.h"

UBHandler* UBHandler::ms_instance = 0;

UBHandler* UBHandler::Get()
{
	if(!ms_instance)
		ms_instance = new UBHandler();
	return ms_instance;

}

void UBHandler::Free()
{
	if( ms_instance )
	{
		delete ms_instance;
		ms_instance = 0;
	}
}

void UBHandler::SwitchEditors()
{
	for(socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++)
	{
		Socket* socky = it->second;

		if(dynamic_cast<ListenSocket<UBSocket>*>(socky))
			continue;
			
		if(dynamic_cast<ListenSocket<SQLSocket>*>(socky))
			continue;
			
		if(dynamic_cast<SQLSocket*>(socky))
			continue;

		UBSocket* sock = dynamic_cast<UBSocket*>(socky);
		if(sock)
		{
			sock->SwitchEditors();	
		}
		else
		{
			Global::Get()->bugf("Socket %d could not be casted to an UBSocket!\n", socky->GetSocket());
			socky->Send("For some reason your connection could not be resolved to an UBSocket, could not switch editors!\n");
			socky->Send("Closing your connection now!\n");
			socky->SetCloseAndDelete();
		}
	}
}

void UBHandler::Shutdown()
{
	for(socket_m::iterator it = m_add.begin(); it != m_add.end(); it++)
		Shutdown(it->second);

	for(socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++)
		Shutdown(it->second);

	for(std::list<Socket*>::iterator it = m_delete.begin(); it != m_delete.end(); it++)
		Shutdown(*it);
}

void UBHandler::Shutdown(Socket* sock)
{
	// If it's a listning socket, they're not our buisness
	if(dynamic_cast<ListenSocket<UBSocket>*>(sock))
		return;

	sock->Send("\n");
	sock->Send("The mud is being shut down!");
	sock->SetCloseAndDelete();
}

socket_m& UBHandler::Sockets()
{
	return m_sockets;
}
