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
	class Sector;
	typedef SmartPtr<mud::Sector> SectorPtr;
	
	class SectorManager;

	class Sector : public Savable
	{
	public:
		/** 
		 * \brief Getters
		 */ 
		const std::string& getName() const;
		const std::string& getSymbol() const;
		long getMoveCost() const;
		bool isWater() const;
		
		/**
		 * \brief Setters
		 */ 
		void setName(const std::string& name);
		void setSymbol(const std::string& symbol);
		void setMoveCost(long movecost);
		void setWater(bool water);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TableImplPtr getTable() const;
		
		/**
		 * \brief Database utilities
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		SavableManagerPtr m_sector;

		/**
		 * \brief Ctors
		 */ 
		Sector(SavableManagerPtr Sector);
		Sector(const Sector& rhs);
		Sector operator=(const Sector& rhs);
		~Sector(void);
		
		friend class SectorManager;
		friend SmartPtrDelete(mud::Sector);
	};
}
