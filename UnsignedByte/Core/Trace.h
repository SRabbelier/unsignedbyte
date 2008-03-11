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

#include "SavableHeaders.h"

namespace mud
{
	class TraceManager;
	
	class Trace : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */
		const std::string& getDiff() const;
		const std::string& getDescription() const;
		time_t getTime() const;
		value_type getAccount() const;

		/**
		 * \brief Setters
		 */
		void setDiff(const std::string& diff);
		void setDescription(const std::string& description);
		void setTime(time_t time);
		void setAccount(value_type account);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TableImplPtr getTable() const;
		
		/**
		 * \brief Database operations
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		friend class mud::TraceManager; // For constructor
		friend SmartPtrDelete(mud::Trace);
		
		SavableManagerPtr m_trace;

		/**
		 * \brief Constructor
		 * \param trace The DB object
		 * \return 
		 */
		Trace(SavableManagerPtr trace);
		
		Trace(const Trace& rhs);
		Trace operator=(const Trace& rhs);
			
		/**
		 * \brief Default destructor
		 */
		~Trace(void);
	};
}
