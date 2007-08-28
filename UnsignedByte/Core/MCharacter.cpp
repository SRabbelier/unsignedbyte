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

#include "MCharacter.h"
#include "UBSocket.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "ub.h"
#include "Account.h"
#include "EditorAccount.h"

MCharacter::MCharacter(db::Characters* character) :
Character(character)
{

}

MCharacter::~MCharacter(void)
{
	//m_sock is deleted by handler
}

void MCharacter::Quit()
{
	Save();
	return;	
}

void MCharacter::Save()
{
	Send("Saving...\n");
	Character::Save();
	Send("Saved!\n");

	return;
}

void MCharacter::Send(const std::string &msg)
{
	return;
}

std::vector<std::string> MCharacter::Show()
{
	std::vector<std::string> result;
	
	return result;
}

std::string MCharacter::ShowShort()
{
	std::string result;
	
	return result;
}

std::vector<std::string> MCharacter::List()
{
	std::vector<std::string> result;
	Longs ids = DatabaseMgr::Get()->GetSavableIDS(Tables::Get()->CHARACTERS);
	for(Longs::iterator it = ids.begin(); it != ids.end(); it++)
	{
		long id = (*it);
		if(!Cache::Get()->IsMobile(id))
			continue;
			
		MCharacter* mcharacter = Cache::Get()->GetMCharacter(id);
		std::string line;
		line.append(Global::Get()->sprintf("%d> ", id));
		line.append(mcharacter->ShowShort());
		result.push_back(line);
	}
	return result;
}
