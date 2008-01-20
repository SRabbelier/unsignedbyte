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

#include <string>
#include <vector>
#include <stdarg.h>

#include "SQLSocket.h"
#include "Global.h"
#include "DatabaseMgr.h"

#include "Query.h"

SQLSocket::SQLSocket(ISocketHandler& h) :
TcpSocket(h)
{
	SetLineProtocol();
}

SQLSocket::~SQLSocket(void)
{
	
}

void SQLSocket::OnAccept()
{
	std::string addr = GetRemoteAddress();
	if(addr.compare("127.0.0.1") && addr.compare("localhost"))
	{
		Global::Get()->logf("Unauthorized SQL request from '%s'!\n", addr.c_str());
		SetCloseAndDelete();
		return;
	}
}

void SQLSocket::OnLine(const std::string &line)
{
	Global::Get()->logf("SQL request: '%s'\n", line.c_str());
	Query q(DatabaseMgr::Get()->DBref());
	q.get_result(line);
	
	std::vector< std::vector<std::string> > result;
	while(q.fetch_row())
	{
		std::vector<std::string> row;
		std::string column = q.getstr();
		while(column.size())
		{
			row.push_back(column);
			column = q.getstr();
		}
		result.push_back(row);
	}
	q.free_result();
	if(result.size() == 0)
	{
		Send("No result.\n");
		return;
	}
	
	std::string res;
	for(std::vector< std::vector<std::string> >::iterator its = result.begin(); its != result.end(); its++)
	{
		std::vector<std::string> row = *its;
		if(row.size() == 0)
			continue;
		
		if(row.size() == 1)
		{
			res.append(row[0]);
			res.append("\n");
			continue;
		}
		
		std::string rowres;
		for(std::vector<std::string>::iterator it = row.begin(); it != row.end(); it++)
		{
			if(it != row.begin())
				rowres.append(" | ");
			rowres.append(*it);
		}
		
		res.append(rowres);
		res.append("\n");
	}
	
	Send(res);
	return;
}

void SQLSocket::Send(const std::string& msg)
{
	SendBuf(msg.c_str(), msg.size());
	return;
}
