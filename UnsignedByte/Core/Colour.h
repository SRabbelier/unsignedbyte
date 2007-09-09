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
	class Colour : public Savable
	{
	public:
		const std::string& getName() const { return m_colour->getname(); }
		std::string getColourString();
		const std::string& getCode() const { return m_colour->getcode(); }

		void setName(const std::string& name) { m_colour->setname(name); }
		void setColourString(const std::string& colourstring) { m_colour->setcolourstring(colourstring); }
		void setCode(const std::string& code) { m_colour->setcode(code); };

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		Table* getTable() const;
		
		/**
		 * \brief Static utilities
		 */
		static std::vector<std::string> List();
		static void Close(Colour* colour);
		
		/**
		 * \brief Database utilities
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		db::Colours* m_colour;

		/**
		 * \brief Ctors
		 */ 
		Colour(db::Colours* object);
		Colour(const Colour& rhs) {};
		Colour operator=(const Colour& rhs) { return *this;};
		~Colour(void);
		
		friend class Cache;
	};
}
