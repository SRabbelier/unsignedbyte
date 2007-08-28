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
#include <stdexcept>

#include "PCharacter.h"
#include "UBSocket.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "ub.h"
#include "Account.h"
#include "EditorAccount.h"

PCharacter::PCharacter(UBSocket* sock, db::Characters* character) :
Character(character),
m_sock(sock)
{

}

PCharacter::~PCharacter(void)
{
	//m_sock is deleted by handler
}

void PCharacter::Quit()
{
	m_sock->SetEditor(new EditorAccount(m_sock));
	return;	
}

void PCharacter::Save()
{
	OnSend("Saving...\n");
	Character::Save();
	OnSend("Saved!\n");

	return;
}

void PCharacter::OnSend(const std::string &msg)
{
	/*
	for(UBSockets::iterator it = m_snooping.begin(); it != m_snooping.end(); it++)
	{
		(*it)->Sendf("##%s## %s", getName().c_str(), msg.c_str());
	}
	*/
	
	m_sock->Send(msg);
	return;
}

bool PCharacter::isAccount(Account* account)
{
	return true;
	// TODO
}

void PCharacter::Close(PCharacter* Ch)
{
	if(Ch == NULL)
		throw std::invalid_argument("PCharacter::Close(), Ch == NULL!");
	
	Cache::Get()->ClosePCharacter(Ch->m_character->characterid);
	delete Ch;
}
