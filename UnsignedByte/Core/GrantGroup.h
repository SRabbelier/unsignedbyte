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
#include "Savable.h"
#include "db.h"

namespace mud
{
	class GrantGroup : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */ 
		const std::string& getName() const { return m_grantgroup->getname(); }
		long getImplication() const { return m_grantgroup->getimplies(); }
		
		bool getDefaultGrant();
		bool getDefaultLog();

		/**
		 * \brief Setters
		 */ 
		void setName(const std::string& name) { m_grantgroup->setname(name); }
		void setImplication(long implication) { m_grantgroup->setimplies(implication); }
		
		void setDefaultGrant(bool defaultgrant);
		void setDefaultLog(bool defaultlog);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TablePtr getTable() const { return GetTable(); }
		
		/**
		 * \brief Static utilities
		 */
		static TablePtr GetTable();
		static std::vector<std::string> List();
		static void Close(GrantGroup* grantgroup);
		
		/**
		 * \brief Database utilities
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		db::GrantGroups* m_grantgroup;

		/**
		 * \brief Ctors
		 */ 
		GrantGroup(db::GrantGroups* GrantGroup);
		GrantGroup(const GrantGroup& rhs) {};
		GrantGroup operator=(const GrantGroup& rhs) { return *this;};
		~GrantGroup(void);
		
		friend class Cache;
	};
}
