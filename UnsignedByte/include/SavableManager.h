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

#include "Types.h"

typedef std::map<Keys*, SavableManagerPtr> ByKeyCache;
typedef std::map<Value*, SavableManagerPtr> ByValueCache;

class SavableManager
{
	public:
		// Factories
		static SavableManagerPtr getnew(TableImplPtr table);
		static SavableManagerPtr bykeys(KeyPtr keys);
		static SavableManagerPtr bykeys(KeysPtr keys);
		static SavableManagerPtr byvalue(ValuePtr value);
		static KeysPtr lookupvalue(ValuePtr value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3* db, sqlite3_stmt* stmt, int startpos = 1) const;
		void bindFields(sqlite3* db, sqlite3_stmt* stmt, int startpos = 1) const;
		void bindUpdate(sqlite3* db, sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3* db, sqlite3_stmt* stmt) const;
		
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);

		// Getters
		TableImplPtr getTable() const;
		KeysPtr getkeys() const;
		
		ValuePtr getfield(FieldImplPtr field) const;
		KeyPtr getkey(KeyDefPtr keydef) const;
		
		std::string getDiff() const;
		
		// Setters
		void setkeys(KeysPtr keys);
		void setvalue(ValuePtr value);

	private:
		SavableManager(TableImplPtr table);
		~SavableManager();
		
		friend SmartPtrDelete(SavableManager);
		
		static ByKeyCache ms_byKeyCache;
		static ByValueCache ms_byValueCache;
		
		TableImplPtr m_table;		
		ValuePtr m_lookupvalue;
		
		KeysPtr m_keys;
		Fields m_fields;
		
		// State flags
		bool m_newentry;
		bool m_dirty;
};
