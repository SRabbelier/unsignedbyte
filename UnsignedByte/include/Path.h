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

#include <vector>
#include "Coordinate.h"

class Path
{
public:
	/**
	 * \brief Constructor
	 * \param from Starting point
	 * \param to Destination
	 */
	Path(const Coordinate& from, const Coordinate& to);
	
	/**
	 * \brief Destructor
	 */
	~Path() {};

	/**
	 * \brief Getter
	 * \return Returns our start point
	 */
	const Coordinate& getFrom() const;
	
	/**
	 * \brief Getter
	 * \return Returns our destination
	 */
	const Coordinate& getTo() const;
	
	/**
	 * \brief Setter
	 * \param from Sets our start point
	 */
	void setFrom(const Coordinate& from);
	
	/**
	 * \brief Setter
	 * \param to Sets our destination
	 */
	void setTo(const Coordinate& to);
	
	/**
	 * \brief Gets the length of the largest component since all other components can be combined into the largest 
	 * \return The largest component
	 */
	long length() const;				//returns distance between coords
	
	/**
	 * \brief The direction one should travel in from 'from' to reach 'to'
	 * \return Unit coord for approx direction
	 */
	const Coordinate& direction() const;
	
	/**
	 * \brief Retreives the exact path between From to To.
	 * \return Set of exact directions
	 */
	std::vector<Coordinate> route() const;

private:
	Coordinate m_from;
	Coordinate m_to;
	
	long m_xcomponent;
	long m_ycomponent;
	long m_zcomponent;
	
	/**
	 * \brief Resets internal coordinates
	 */
	void reset();
};
