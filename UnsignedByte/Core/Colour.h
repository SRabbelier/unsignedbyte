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
	class ColourManager;
	class Colour : public Savable
	{
	public:
		const std::string& getName() const;
		std::string getColourString();
		const std::string& getCode() const;

		void setName(const std::string& name);
		void setColourString(const std::string& colourstring);
		void setCode(const std::string& code);

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
		SavableManagerPtr m_colour;

		/**
		 * \brief Ctors
		 */ 
		Colour(SavableManagerPtr object);
		Colour(const Colour& rhs);
		Colour operator=(const Colour& rhs);
		~Colour(void);
		
		friend class ColourManager;
		friend SmartPtrDelete(mud::Colour);
	};
}
