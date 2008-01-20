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
#pragma once

#include <map>

#include "singleton.h"
#include "smart_ptr.h"

class SavableManager;
typedef SmartPtr<SavableManager> SavableManagerPtr;

class Table;
typedef SmartPtr<Table> TablePtr;

typedef std::map<TablePtr, SavableManagerPtr> SavableManagerMap;

class SavablesManager : public Singleton<SavablesManager>
{
public:
	void getManager(TablePtr table) { return m_savablemanagers[table]; }
	
private:
	friend class Singleton<SavablesManager>;
	SavablesManager();
	~SavablesManager();

	SavableManagerMap m_savablemanagers;
};
	
