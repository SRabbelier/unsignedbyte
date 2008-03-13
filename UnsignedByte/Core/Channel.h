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
	class ChannelManager;
	
	class Channel : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */
		const std::string& getName() const;
		const std::string& getDescription() const;

		/**
		 * \brief Setters
		 */
		void setName(const std::string& name);
		void setDescription(const std::string& description);

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
		friend class mud::ChannelManager; // For constructor
		friend SmartPtrDelete(mud::Channel);
		
		SavableManagerPtr m_channel;

		/**
		 * \brief Constructor
		 * \param channel The DB object
		 * \return 
		 */
		Channel(SavableManagerPtr channel);
		
		Channel(const Channel& rhs);
		Channel operator=(const Channel& rhs);
			
		/**
		 * \brief Default destructor
		 */
		~Channel(void);
	};
}
