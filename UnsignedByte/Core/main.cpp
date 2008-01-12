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

#ifdef _WIN32
#include <winsock2.h>
#endif
#include "DatabaseMgr.h"
#include "Query.h"
#include "UBHandler.h"
#include "ListenSocket.h"
#include "UBSocket.h"
#include "SQLSocket.h"
#include "Global.h"
#include "Account.h" // needed because we include UBSocket.h
#include "SavableHeaders.h"
#include <iostream>

void exitfunc()
{
	printf("exiting...\n");
	std::cin.get();
	return;
}

void add(SocketHandler* h,int port)
{
	ListenSocket<UBSocket> *l = new ListenSocket<UBSocket>(*h);
	printf("Attempting bind on port %d... ", port);
	if (l -> Bind(port))
	{
		printf("Not successful\n");
		delete l;
		return;
	}
	printf("OK\n");
	l -> SetDeleteByHandler();
	h->Add(l);
}

void addSQL(SocketHandler* h, int port)
{
	ListenSocket<SQLSocket> *l = new ListenSocket<SQLSocket>(*h);
	printf("Attempting SQL bind on port %d... ", port);
	if (l -> Bind(port))
	{
		printf("Not successful\n");
		delete l;
		return;
	}
	printf("OK\n");
	l -> SetDeleteByHandler();
	h->Add(l);
}

bool m_quit = false;

int main(int argc, char** argv)
{
	printf("Opening database...\n");
	std::string dbname = game::vname;
	dbname.append(".db");
	DatabaseMgr::Initialize(dbname);
	printf("Done.\n");
	
	db::TableImpls::Get();

	add(UBHandler::Get(), 4000);
	add(UBHandler::Get(), 4040);
	addSQL(UBHandler::Get(), 9090);

	printf("Running!\n");

	while (!m_quit)
	{
		UBHandler::Get()->Select(0, 200000);
		UBHandler::Get()->SwitchEditors();
	}

	UBHandler::Get()->Shutdown();
	UBHandler::Get()->Select();
	UBHandler::Free(); 
	
	SqliteMgr::Free();
	DatabaseMgr::Free();

	printf("End of program.\n");
	exitfunc();
	return 0;
}
