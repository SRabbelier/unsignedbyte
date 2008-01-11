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

namespace mud
{
	class RaceManager;
	class Race : public Savable
	{
	public:
		const std::string& getName() const;
		void setName(const std::string& name);

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
		SavableManagerPtr m_race;

		/**
		 * \brief Ctors
		 */ 
		Race(SavableManagerPtr race);
		Race(const Race& rhs);
		Race operator=(const Race& rhs);
		~Race(void);
		
		friend class RaceManager;
		friend SmartPtrDelete(mud::Race);
	};
}
