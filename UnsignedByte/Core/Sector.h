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
#include "smart_ptr.h"
#include "Savable.h"
#include "db.h"

namespace mud
{
	class SectorManager;
	class Sector;
	typedef SmartPtr<Sector> SectorPtr;

	class Sector : public Savable
	{
	public:
		/** 
		 * \brief Getters
		 */ 
		const std::string& getName() const { return m_sector->getname(); }
		const std::string& getSymbol() const { return m_sector->getsymbol(); }
		long getMoveCost() const { return m_sector->getmovecost(); }
		bool isWater() const { return m_sector->getwater(); }
		
		/**
		 * \brief Setters
		 */ 
		void setName(const std::string& name) { m_sector->setname(name); }
		void setSymbol(const std::string& symbol) { m_sector->setsymbol(symbol); }
		void setMoveCost(long movecost) { m_sector->setmovecost(movecost); }
		void setWater(bool water) { m_sector->setwater(water); }

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
		db::Sectors* m_sector;

		/**
		 * \brief Ctors
		 */ 
		Sector(db::Sectors* Sector);
		Sector(const Sector& rhs);
		Sector operator=(const Sector& rhs);
		~Sector(void);
		
		friend class SectorManager;
		friend void boost::checked_delete<mud::Sector>(mud::Sector* x);
	};
}
