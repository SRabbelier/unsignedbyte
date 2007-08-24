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

#include "Coordinate.h"

Coordinate Coordinate::NORTH	(0, 1, 0);
Coordinate Coordinate::NUP		(0, 1, 1);
Coordinate Coordinate::NDOWN	(0, 1, -1);

Coordinate Coordinate::SOUTH	(0, -1, 0);
Coordinate Coordinate::SUP		(0, -1, 1);
Coordinate Coordinate::SDOWN	(0, -1, -1);

Coordinate Coordinate::EAST		(1, 0, 0);
Coordinate Coordinate::EUP		(1, 0, 1);
Coordinate Coordinate::EDOWN	(1, 0, -1);

Coordinate Coordinate::WEST		(-1, 0, 0);
Coordinate Coordinate::WUP		(-1, 0, 1);
Coordinate Coordinate::WDOWN	(-1, 0, -1);

Coordinate Coordinate::NW		(-1, 1, 0);
Coordinate Coordinate::NWUP		(-1, 1, 1);
Coordinate Coordinate::NWDOWN	(-1, 1, -1);

Coordinate Coordinate::NE		(1, 1, 0);
Coordinate Coordinate::NEUP		(1, 1, 1);
Coordinate Coordinate::NEDOWN	(1, 1, -1);

Coordinate Coordinate::SW		(-1, -1, 0);
Coordinate Coordinate::SWUP		(-1, -1, 1);
Coordinate Coordinate::SWDOWN	(-1, -1, -1);

Coordinate Coordinate::SE		(1, -1, 0);
Coordinate Coordinate::SEUP		(1, -1, 1);
Coordinate Coordinate::SEDOWN	(1, -1, -1);

Coordinate Coordinate::UP		(0, 0, 1);
Coordinate Coordinate::DOWN		(0, 0, -1);

Coordinate::Coordinate(long X, long Y, long Z) : 
m_xcoordinate(X), 
m_ycoordinate(Y), 
m_zcoordinate(Z)
{
	  
}

Coordinate::~Coordinate()
{
	
}

Coordinate Coordinate::operator+ (const Coordinate & rhs) const
{
	return Coordinate(	getXCoordinate()+rhs.getXCoordinate(), 
						getYCoordinate()+rhs.getYCoordinate(), 
						getZCoordinate()+rhs.getZCoordinate()	);
}

Coordinate Coordinate::operator- (const Coordinate & rhs) const
{
	return Coordinate(	getXCoordinate()-rhs.getXCoordinate(), 
						getYCoordinate()-rhs.getYCoordinate(), 
						getZCoordinate()-rhs.getZCoordinate()	);
}

long Coordinate::getXCoordinate() const
{
	return m_xcoordinate;
}
	
long Coordinate::getYCoordinate() const
{
	return m_ycoordinate;
}
	
long Coordinate::getZCoordinate() const
{
	return m_zcoordinate;
}
