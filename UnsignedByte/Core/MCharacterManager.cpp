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

#include "MCharacterManager.h"
#include "MCharacter.h"
#include "MCharacter.h"
#include "TableImpls.h"
#include "db.h"

using mud::MCharacterManager;
using mud::MCharacter;
using mud::MCharacterPtr;

mud::MCharacterPtr MCharacterManager::GetByKey(value_type id)
{
	KeyPtr key(new Key(db::CharactersFields::Get()->CHARACTERID, id));
	SavableManagerPtr manager = SavableManager::bykeys(key);
	MCharacterPtr p(new MCharacter(manager));
	return p;
}

mud::MCharacterPtr MCharacterManager::GetByName(cstring value)
{
	ValuePtr val(new Value(db::CharactersFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	MCharacterPtr p(new MCharacter(manager));
	return p;
}
