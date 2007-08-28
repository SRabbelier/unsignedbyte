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

#include <SocketHandler.h>

class Socket;
typedef std::map<SOCKET,Socket *> socket_m;

// Manual Singleton since SocketHandler already declares Get
class UBHandler : public SocketHandler
{
	static UBHandler* ms_instance;
public:
	static UBHandler* Get();
	static void Free();

private:
	UBHandler(void) {};
	UBHandler(const UBHandler& rhs) {};
	UBHandler operator=(const UBHandler& rhs) { return *this;};
	~UBHandler(void) {};

public:
	void SwitchEditors();

	void Shutdown();
	void Shutdown(Socket* sock);
	socket_m& Sockets();
};
