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

#include "Types.h"

class Tables : public Singleton<Tables>
{
public:
	TableDefPtr ACCOUNTS;
	TableDefPtr AREAS;
	TableDefPtr BRANCHES;
	TableDefPtr CHANNELS;
	TableDefPtr CHARACTERACCOUNT;
	TableDefPtr CHARACTERBRANCH;
	TableDefPtr CHARACTERCLUSTER;
	TableDefPtr CHARACTERSKILL;
	TableDefPtr CHARACTERSTAT;
	TableDefPtr CHARACTERTREE;
	TableDefPtr CHUNKS;
	TableDefPtr CLUSTERS;
	TableDefPtr COLOURS;
	TableDefPtr COMMANDS;
	TableDefPtr DETAILS;
	TableDefPtr DETAILROOM;
	TableDefPtr DETAILCHUNK;
	TableDefPtr DETAILCHARACTER;
	TableDefPtr DETAILDETAIL;
	TableDefPtr ECHOS;
	TableDefPtr ENTITIES;
	TableDefPtr EXITROOM;
	TableDefPtr EXITS;
	TableDefPtr GRANTGROUPS;
	TableDefPtr PERMISSIONS;
	TableDefPtr RACES;
	TableDefPtr ROOMS;
	TableDefPtr SECTORS;
	TableDefPtr SKILLS;
	TableDefPtr STATS;
	TableDefPtr TRACES;
	TableDefPtr TRACECHUNK;
	TableDefPtr TRACEDETAIL;
	TableDefPtr TRACEENTITY;
	TableDefPtr TRACEROOM;
	TableDefPtr TREES;
	TableDefPtr VERSION;
	
	TableDefVector::const_iterator begin() const { return m_tables.begin(); }
	TableDefVector::const_iterator end() const { return m_tables.end(); }
	
private:
	friend class Singleton<Tables>;
	Tables();
	~Tables();
	
	TableDefVector m_tables;
};
