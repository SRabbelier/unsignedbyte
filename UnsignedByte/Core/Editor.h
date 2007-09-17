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
#include "Global.h"
#include "UBSocket.h"

class Editor
{
public:
	Editor(UBSocket* sock);
	virtual ~Editor(void);

	virtual void OnLine(const std::string& line);
	virtual std::string name() = 0;
	virtual std::string prompt() { return Global::Get()->EmptyString; };
	
	virtual std::string lookup(const std::string& action) { return Global::Get()->EmptyString; };
	virtual void dispatch(const std::string& action, const std::string& argument) { return; };
	
	void Send(const std::string& msg);
	void Sendf(const char* format, ...);
	void Disconnect();

protected:
	UBSocket* m_sock;
	
private:
	Editor(const Editor& rhs) : m_sock(rhs.m_sock) {};
};
