/***************************************************************************
 *   Copyright (C) 2007 by Daniel Brody                                    *
 *   erasnode@gmail.com                                                    *
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

class Coordinate
{
public:
	static Coordinate NORTH;
	static Coordinate NUP;
	static Coordinate NDOWN;

	static Coordinate SOUTH;
	static Coordinate SUP;
	static Coordinate SDOWN;

	static Coordinate EAST;
	static Coordinate EUP;
	static Coordinate EDOWN;

	static Coordinate WEST;
	static Coordinate WUP;
	static Coordinate WDOWN;

	static Coordinate NW;
	static Coordinate NWUP;
	static Coordinate NWDOWN;

	static Coordinate NE;
	static Coordinate NEUP;
	static Coordinate NEDOWN;

	static Coordinate SW;
	static Coordinate SWUP;
	static Coordinate SWDOWN;

	static Coordinate SE;
	static Coordinate SEUP;
	static Coordinate SEDOWN;

	static Coordinate UP;
	static Coordinate DOWN;

	/**
	 * \brief Specialized constructor
	 * \param X initial X coordinate
	 * \param Y initial Y coordinate
	 * \param Z initial Z coordinate
	 */
	Coordinate(long X, long Y, long Z);
	
	/**
	 * \brief Copy Constructor
	 * \param rhs Copy from
	 */
	Coordinate(const Coordinate& rhs);
	
	/**
	 * \brief Default constructor
	 */
	~Coordinate();
	
	/**
	 * \brief Overloaded addition operator
	 * \param rhs Coordinate to be added
	 * \return this+rhs
	 */
	Coordinate operator+ (const Coordinate & rhs) const;


	/**
	 * \brief Overloaded substraction operator
	 * \param rhs Coordinate to be substracted
	 * \return this-rhs
	 */
	Coordinate operator- (const Coordinate & rhs) const;

	/**
	 * \brief Getter
	 * \return X coordinate
	 */
	long getXCoordinate() const;
	
	/**
	 * \brief Getter
	 * \return Y Coordinate
	 */
	long getYCoordinate() const;
	
	/**
	 * \brief Getter
	 * \return Z coordinate
	 */
	long getZCoordinate() const;
	   
private:
	/**
	 * \brief Hide default constructor
	 */
	Coordinate() {};

	long m_xcoordinate;
	long m_ycoordinate;
	long m_zcoordinate;
};
