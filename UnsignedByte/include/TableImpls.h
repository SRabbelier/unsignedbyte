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

#include "Types.h"

namespace db
{
	class TableImpls : public Singleton<TableImpls>
	{
	public:
		static TableImpls* Get();
		static void Free();

		TableImplPtr ACCOUNTS;
		TableImplPtr AREAS;
		TableImplPtr BRANCHES;
		TableImplPtr CHARACTERACCOUNT;
		TableImplPtr CHARACTERBRANCH;
		TableImplPtr CHARACTERCLUSTER;
		TableImplPtr CHARACTERS;
		TableImplPtr CHARACTERSKILL;
		TableImplPtr CHARACTERSTAT;
		TableImplPtr CHARACTERTREE;
		TableImplPtr CLUSTERS;
		TableImplPtr CHUNKS;
		TableImplPtr COLOURS;
		TableImplPtr COMMANDS;
		TableImplPtr DETAILS;
		TableImplPtr DETAILROOM;
		TableImplPtr DETAILCHUNK;
		TableImplPtr DETAILCHARACTER;
		TableImplPtr DETAILDETAIL;
		TableImplPtr EXITROOM;
		TableImplPtr EXITS;
		TableImplPtr GRANTGROUPS;
		TableImplPtr PERMISSIONS;
		TableImplPtr RACES;
		TableImplPtr ROOMS;
		TableImplPtr SECTORS;
		TableImplPtr SKILLS;
		TableImplPtr STATS;
		TableImplPtr TREES;
		TableImplPtr VERSION;

		TableImplVector::const_iterator begin() const { return m_tables.begin(); }
		TableImplVector::const_iterator end() const { return m_tables.end(); }

	private:
		TableImpls();
		~TableImpls() { }
		TableImpls(const TableImpls& rhs);
		TableImpls operator=(const TableImpls& rhs);
		friend class Singleton<TableImpls>;

		TableImplVector m_tables;
		static TableImpls* ms_instance;
	};
} // end of namespace

