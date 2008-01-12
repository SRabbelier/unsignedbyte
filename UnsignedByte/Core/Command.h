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

#include "SavableHeaders.h"

#include "Permission.h"

namespace mud
{
	class CommandManager;
	class Command;
	typedef SmartPtr<Command> CommandPtr;
	class Command : public Savable
	{
	public:
		static bool defaultHighForce;
		static bool defaultForce;
		static bool defaultLowForce;

		/**
		 * \brief Getters
		 */ 
		const std::string& getName() const;
		long getGrantGroup() const;
		bool canHighForce() const;
		bool canForce() const;
		bool canLowForce() const;
		
		bool getGrant(UBSocket* sock);
		bool getDefaultGrant();
		
		bool getLog(UBSocket* sock);
		bool getDefaultLog();
		
		/**
		 * \brief Setters
		 */ 
		void setName(const std::string& name);
		void setGrantGroup(long grantgroup);
		void setHighForce(bool highforce);
		void setForce(bool force);
		void setLowForce(bool lowforce);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TablePtr getTable() const;
			
		/**
		 * \brief Database utilities
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		SavableManagerPtr m_command;

		Command(SavableManagerPtr Command);
		Command(const Command& rhs);
		Command operator=(const Command& rhs);
		~Command(void);
		friend class CommandManager;
		friend SmartPtrDelete(mud::Command);
	};
}
