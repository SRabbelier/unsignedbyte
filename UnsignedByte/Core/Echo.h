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
	class EchoManager;
	
	class Echo : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */
		const std::string& getMessage() const;
		value_type getAudibility() const;
		value_type getVisibility() const;

		/**
		 * \brief Setters
		 */
		void setMessage(const std::string& message);
		void setAudibility(value_type audibility);
		void setVisibility(value_type visibility);

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
		friend class mud::EchoManager; // For constructor
		friend SmartPtrDelete(mud::Echo);
		
		SavableManagerPtr m_echo;

		/**
		 * \brief Constructor
		 * \param echo The DB object
		 * \return 
		 */
		Echo(SavableManagerPtr echo);
		
		Echo(const Echo& rhs);
		Echo operator=(const Echo& rhs);
			
		/**
		 * \brief Default destructor
		 */
		~Echo(void);
	};
}
