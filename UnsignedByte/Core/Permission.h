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
	class Permission : public Savable
	{
	public:
		static bool defaultGrant;
		static bool defaultLog;
		
		/**
		 * \brief Getters
		 */ 
		long getAccount() const { return m_permission->getfkAccounts(); }
		long getGrantGroup() const { return m_permission->getfkGrantGroups(); }
		
		bool hasGrant() const;
		bool hasLog() const;
		
		void setGrant(bool grant);
		void setLog(bool log);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		Table* getTable() const { return GetTable(); }
		
		/**
		 * \brief Static utilities
		 */
		static Table* GetTable();
		static std::vector<std::string> List();
		static void Close(Permission* permission);
		static bool isGrant(long grant);
		static bool isLog(long grant);
		
		/**
		 * \brief Database utilities
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		db::Permissions* m_permission;

		Permission(db::Permissions* Permission);
		Permission(const Permission& rhs) {};
		Permission operator=(const Permission& rhs) { return *this; };
		~Permission(void);
		
		friend class Cache;
		
		enum GRANTS
		{
			GRANT_NOTSET, // grant for this grantgroup is not set
			GRANT_ENABLE, // explicitly enable the grantgroup
			GRANT_DISABLE, // explicitly disable the grantgroup
			GRANT_ENABLEANDLOG, // enable and log the command
			GRANT_DISABLEANDLOG, // enable and log the attemp
		};
	};
}
