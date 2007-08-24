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
#include "Permission.h"

namespace db { class Commands; };

class Command : public Savable
{
public:
	static bool defaultHighForce;
	static bool defaultForce;
	static bool defaultLowForce;

	/**
	 * \brief Getters
	 */ 
	std::string& getName() const { return m_command->name; };
	long getGrantGroup() const { return m_command->grantgroup; };
	bool canHighForce() const { return m_command->highforce; };
	bool canForce() const { return m_command->force; };
	bool canLowForce() const { return m_command->lowforce; };
	
	bool getGrant(UBSocket* sock);
	bool getDefaultGrant();
	
	bool getLog(UBSocket* sock);
	bool getDefaultLog();
	
	/**
	 * \brief Setters
	 */ 
	void setName(const std::string& name) { m_command->name = name; };
	void setGrantGroup(long grantgroup) { m_command->grantgroup = grantgroup; };
	void setHighForce(bool highforce) { m_command->highforce = highforce; };
	void setForce(bool force) { m_command->force = force; };
	void setLowForce(bool lowforce) { m_command->lowforce = lowforce; };

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
	
	/**
	 * \brief Database utilities
	 */
	void Delete();
	void Save();
	bool Exists();

private:
	db::Commands* m_command;

	Command(db::Commands* Command);
	Command(const Command& rhs) {};
	Command operator=(const Command& rhs) { return *this; };
	~Command(void);
	friend class Cache;
};
