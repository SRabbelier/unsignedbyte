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

class UBSocket;
class Cache;

namespace mud
{
	class Account : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */
		long getID() const { return m_account->getaccountid() ; }
		const std::string& getName() const { return m_account->getname(); }
		const std::string& getPassword() const { return m_account->getpassword(); }

		/**
		 * \brief Setters
		 */
		void setName(const std::string& name) { m_account->setname(name); };
		void setPassword(const std::string& password) { m_account->setpassword(password); };

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		Table* getTable() const;
		
		/**
		 * \brief Static operations
		 */
		static std::vector<std::string> List();
		static void Close(Account* account);
		static bool IllegalName(const std::string& name);
		
		/**
		 * \brief Database operations
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		db::Accounts* m_account;

		/**
		 * \brief Ctors
		 */
		Account(db::Accounts* account);	
		Account(const Account& rhs);
		Account operator=(const Account& rhs);
		~Account(void);
		
		friend class Cache; // for constructor
	};
}