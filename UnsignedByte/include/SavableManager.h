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

#include "Types.h"

class SavableManager
{
	public:
		// Factories
		static SavableManagerPtr getnew(TableImplPtr table);
		static SavableManagerPtr bykeys(TableImplPtr table, value_type keys);
		static SavableManagerPtr bykeys(TableImplPtr table, Keys keys);
		static SavableManagerPtr byvalue(ValuePtr value);
		static Keys lookupvalue(ValuePtr value);

		// Database interaction
		void erase();
		void save();
		bool exists();

		// Bindable interface
		void bindKeys(sqlite3_stmt* stmt, int startpos = 1) const;
		void bindFields(sqlite3_stmt* stmt, int startpos = 1) const;
		void bindUpdate(sqlite3_stmt* stmt) const;
		void bindLookup(sqlite3_stmt* stmt) const;
		
		void parseInsert(sqlite3* db);
		void parseSelect(sqlite3_stmt* stmt);
		void parseLookup(sqlite3_stmt* stmt);

		// Getters
		TablePtr getTable() const;
		const Keys& getkeys() const;
		ValuePtr getfield(FieldImplPtr field) const;
		
		// Setters
		void setkeys(Keys keys);
		void setvalue(ValuePtr value);

	private:
		SavableManager(TableImplPtr table);
		~SavableManager();
		
		friend SmartPtrDelete(SavableManager);
		
		TableImplPtr m_table;		
		std::string m_lookupvalue;
		
		Keys m_keys;
		Fields m_fields;
		
		// State flags
		bool m_newentry;
		bool m_dirty;
};
