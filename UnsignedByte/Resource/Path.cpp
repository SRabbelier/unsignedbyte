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
 
#include "Path.h"
#include "Coordinate.h"

Path::Path(const Coordinate& from, const Coordinate& to ) :
m_from(from),
m_to(to)
{	
	reset();
}

void Path::reset()
{
	//assign the component values in the transform
	m_xcomponent = m_to.getXCoordinate() - m_from.getXCoordinate();
	m_ycomponent = m_to.getYCoordinate() - m_from.getYCoordinate();
	m_zcomponent = m_to.getZCoordinate() - m_from.getZCoordinate();
}

void Path::setFrom(const Coordinate& from)
{
	m_from = from;
	reset();
}

void Path::setTo(const Coordinate& to)
{
	m_to = to;
	reset();
}

const Coordinate& Path::getFrom() const
{
	return m_from;
}

const Coordinate& Path::getTo() const
{
	return m_to;
}

long Path::length() const
{
	long x_length = abs(m_xcomponent);
	long y_length = abs(m_ycomponent);
	long z_length = abs(m_zcomponent);

	if (x_length >= y_length && x_length >= z_length)
		return x_length;
	else if (y_length >= z_length)		
		return y_length;
	else
		return z_length;
}

const Coordinate& Path::direction() const
{	
	long ratio = 10;
	long threshold = 20;
	
	long x = m_xcomponent;
	long y = m_ycomponent;
	long z = m_zcomponent;

	long x_length = abs(x);
	long y_length = abs(y);
	long z_length = abs(z);


//*********  x is largest component **********//

	if (x_length >= y_length && x_length >= z_length)
	{
		if (x>0)								//x is +ve (east)
		{
			if (y>0 && (x_length*ratio)/y_length<=threshold)	//y is +ve and a decent ratio of x
			{
				if (z==0)						//z will be 0 in most situations
					return Coordinate::NE;
				else if (z>0 && (x_length*ratio)/z_length<=threshold)	//z has to be a decent ratio too
					return Coordinate::NEUP;
				else if (z<0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::NEDOWN;
				else									
					return Coordinate::NE;					//in case z isn't 0, but irrelevant
			}
			else if (y<0 && (x_length*ratio)/y_length<=threshold)	//y is -ve and a decent ratio of x
			{
				if (z==0)
					return Coordinate::SE;
				else if (z>0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::SEUP;
				else if (z<0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::SEDOWN;
				else
					return Coordinate::SE;
			}
			else								//catch the irrelevant and 0 cases of y
			{
				if (z==0)
					return Coordinate::EAST;
				else if (z>0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::EUP;
				else if (z<0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::EDOWN;
				else
					return Coordinate::EAST;
			}

		}
		else if (x<0)							//x is -ve (west)
		{
			if (y>0 && (x_length*ratio)/y_length<=threshold)	//same stuff as x +ve
			{
				if (z==0)
					return Coordinate::NW;					//west this time
				else if (z>0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::NWUP;
				else if (z<0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::NWDOWN;
				else									
					return Coordinate::NW;
			}
			else if (y<0 && (x_length*ratio)/y_length<=threshold)
			{
				if (z==0)
					return Coordinate::SW;
				else if (z>0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::SWUP;
				else if (z<0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::SWDOWN;
				else
					return Coordinate::SW;
			}
			else
			{
				if (z==0)
					return Coordinate::WEST;
				else if (z>0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::WUP;
				else if (z<0 && (x_length*ratio)/z_length<=threshold)
					return Coordinate::WDOWN;
				else
					return Coordinate::WEST;
			}
		}
	}

//*********  y is largest component **********//

	else if (y_length >= z_length)				//x has been checked already
	{
		if (y>0)								//y is +ve (north)
		{
			if (x>0 && (y_length*ratio)/x_length<=threshold)	//x is +ve (east)
			{
				if (z==0)						//the rest is very similar to before
					return Coordinate::NE;
				else if (z>0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::NEUP;
				else if (z<0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::NEDOWN;
				else									
					return Coordinate::NE;					//in case z isn't 0, but irrelevant
			}
			else if (x<0 && (y_length*ratio)/x_length<=threshold)	//x is -ve (west)
			{
				if (z==0)
					return Coordinate::NW;
				else if (z>0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::NWUP;
				else if (z<0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::NWDOWN;
				else
					return Coordinate::NW;
			}
			else								//x is irrelevant or 0
			{
				if (z==0)
					return Coordinate::NORTH;
				else if (z>0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::NUP;
				else if (z<0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::NDOWN;
				else
					return Coordinate::NORTH;
			}

		}
		else if (y<0)							//y is -ve (south)
		{
			if (x>0 && (y_length*ratio)/x_length<=threshold)	//x is +ve (east)
			{
				if (z==0)
					return Coordinate::SE;
				else if (z>0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::SEUP;
				else if (z<0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::SEDOWN;
				else									
					return Coordinate::SE;
			}
			else if (x<0 && (y_length*ratio)/x_length<=threshold)	//x is -ve (west)
			{
				if (z==0)
					return Coordinate::SW;
				else if (z>0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::SWUP;
				else if (z<0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::SWDOWN;
				else
					return Coordinate::SW;
			}
			else								//if x is irrelevant
			{
				if (z==0)
					return Coordinate::SOUTH;
				else if (z>0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::SUP;
				else if (z<0 && (y_length*ratio)/z_length<=threshold)
					return Coordinate::SDOWN;
				else
					return Coordinate::SOUTH;
			}
		}
	}

//*********  z is largest component **********//

	else										//z has to be largest
	{
		if (z>0)								//z is +ve (up)
		{
			if (x>0 && (z_length*ratio)/x_length<=threshold)	//using a bigger ratio to narrow
			{									//the 'cone' of pure UP
				if (y>0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::NEUP;
				else if (y<0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::SEUP;
				else
					return Coordinate::EUP;					//in case y is irrelevant
			}
			else if (x<0 && (z_length*ratio)/x_length<=threshold)	//x is -ve (west)
			{
				if (y>0 && (z_length*ratio)/y_length<=threshold)	//y is +ve (north)
					return Coordinate::NWUP;
				else if (y<0 && (z_length*ratio)/y_length<=threshold)	//y is -ve (south)
					return Coordinate::SWUP;
				else
					return Coordinate::WUP;
			}
			else								//x is irrelevant or 0
			{
				if (y>0 && (z_length*ratio)/y_length<=threshold)	//if y is +ve and decent ratio
					return Coordinate::NUP;
				else if (y<0 && (z_length*ratio)/y_length<=threshold)	//y is -ve
					return Coordinate::SUP;
				else
					return Coordinate::UP;					//y AND x are irrelevant or 0
			}

		}
		else if (z<0)							//z is -ve (down)
		{
			if (x>0 && (z_length*ratio)/x_length<=threshold)	//x is +ve (east)
			{
				if (y>0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::NEDOWN;
				else if (y<0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::SEDOWN;
				else									
					return Coordinate::EDOWN;
			}
			else if (x<0 && (z_length*ratio)/x_length<=threshold)	//x is -ve (west)
			{
				if (y>0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::NWDOWN;
				else if (y<0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::SWDOWN;
				else
					return Coordinate::WDOWN;
			}
			else								//if x is irrelevant
			{
				if (y>0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::NDOWN;
				else if (y<0 && (z_length*ratio)/y_length<=threshold)
					return Coordinate::SDOWN;
				else
					return Coordinate::DOWN;				//x AND y are irrelevant or 0
			}
		}
	}
}

std::vector<Coordinate> Path::route() const
{
	std::vector<Coordinate> route;
	long distance = length();
	Path thePath(m_from, m_to);

	for(long i = 0; i < distance; i++)
	{
		route.push_back(thePath.getTo());		//push destination to route
		thePath.setTo(thePath.getTo() - thePath.direction());	//increment destination closer
	}

	return route;
}
