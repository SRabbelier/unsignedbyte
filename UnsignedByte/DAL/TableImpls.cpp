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

/* NOTE: This file was generated automatically. Do not edit. */

#include "TableImpl.h"
#include "TableImpls.h"
#include "Tables.h"
#include "FieldImpl.h"
#include "KeyDef.h"
#include "db.h"

using namespace db;

TableImpls* TableImpls::ms_instance = 0;

TableImpls* TableImpls::Get()
{
	if(ms_instance == 0)
	{
		ms_instance = new TableImpls();

		// Init the Fields
		db::AccountsFields::Get();
		db::AreasFields::Get();
		db::BranchesFields::Get();
		db::CharacterAccountFields::Get();
		db::CharacterBranchFields::Get();
		db::CharacterClusterFields::Get();
		db::CharactersFields::Get();
		db::CharacterSkillFields::Get();
		db::CharacterStatFields::Get();
		db::CharacterTreeFields::Get();
		db::ClustersFields::Get();
		db::ChunksFields::Get();
		db::ColoursFields::Get();
		db::CommandsFields::Get();
		db::DetailsFields::Get();
		db::DetailRoomFields::Get();
		db::DetailChunkFields::Get();
		db::DetailCharacterFields::Get();
		db::DetailDetailFields::Get();
		db::ExitRoomFields::Get();
		db::ExitsFields::Get();
		db::GrantGroupsFields::Get();
		db::PermissionsFields::Get();
		db::RacesFields::Get();
		db::RoomsFields::Get();
		db::SectorsFields::Get();
		db::SkillsFields::Get();
		db::StatsFields::Get();
		db::TreesFields::Get();
		db::VersionFields::Get();
	}
	return ms_instance;
}

void TableImpls::Free()
{
	if(ms_instance != 0)
		delete ms_instance;
}

TableImpls::TableImpls() :
ACCOUNTS(new TableImpl(Tables::Get()->ACCOUNTS)),
AREAS(new TableImpl(Tables::Get()->AREAS)),
BRANCHES(new TableImpl(Tables::Get()->BRANCHES)),
CHARACTERACCOUNT(new TableImpl(Tables::Get()->CHARACTERACCOUNT)),
CHARACTERBRANCH(new TableImpl(Tables::Get()->CHARACTERBRANCH)),
CHARACTERCLUSTER(new TableImpl(Tables::Get()->CHARACTERCLUSTER)),
CHARACTERS(new TableImpl(Tables::Get()->CHARACTERS)),
CHARACTERSKILL(new TableImpl(Tables::Get()->CHARACTERSKILL)),
CHARACTERSTAT(new TableImpl(Tables::Get()->CHARACTERSTAT)),
CHARACTERTREE(new TableImpl(Tables::Get()->CHARACTERTREE)),
CLUSTERS(new TableImpl(Tables::Get()->CLUSTERS)),
CHUNKS(new TableImpl(Tables::Get()->CHUNKS)),
COLOURS(new TableImpl(Tables::Get()->COLOURS)),
COMMANDS(new TableImpl(Tables::Get()->COMMANDS)),
DETAILS(new TableImpl(Tables::Get()->DETAILS)),
DETAILROOM(new TableImpl(Tables::Get()->DETAILROOM)),
DETAILCHUNK(new TableImpl(Tables::Get()->DETAILCHUNK)),
DETAILCHARACTER(new TableImpl(Tables::Get()->DETAILCHARACTER)),
DETAILDETAIL(new TableImpl(Tables::Get()->DETAILDETAIL)),
EXITROOM(new TableImpl(Tables::Get()->EXITROOM)),
EXITS(new TableImpl(Tables::Get()->EXITS)),
GRANTGROUPS(new TableImpl(Tables::Get()->GRANTGROUPS)),
PERMISSIONS(new TableImpl(Tables::Get()->PERMISSIONS)),
RACES(new TableImpl(Tables::Get()->RACES)),
ROOMS(new TableImpl(Tables::Get()->ROOMS)),
SECTORS(new TableImpl(Tables::Get()->SECTORS)),
SKILLS(new TableImpl(Tables::Get()->SKILLS)),
STATS(new TableImpl(Tables::Get()->STATS)),
TREES(new TableImpl(Tables::Get()->TREES)),
VERSION(new TableImpl(Tables::Get()->VERSION))
{
	m_tables.push_back(ACCOUNTS);
	m_tables.push_back(AREAS);
	m_tables.push_back(BRANCHES);
	m_tables.push_back(CHARACTERACCOUNT);
	m_tables.push_back(CHARACTERBRANCH);
	m_tables.push_back(CHARACTERCLUSTER);
	m_tables.push_back(CHARACTERS);
	m_tables.push_back(CHARACTERSKILL);
	m_tables.push_back(CHARACTERSTAT);
	m_tables.push_back(CHARACTERTREE);
	m_tables.push_back(CLUSTERS);
	m_tables.push_back(CHUNKS);
	m_tables.push_back(COLOURS);
	m_tables.push_back(COMMANDS);
	m_tables.push_back(DETAILS);
	m_tables.push_back(DETAILROOM);
	m_tables.push_back(DETAILCHUNK);
	m_tables.push_back(DETAILCHARACTER);
	m_tables.push_back(DETAILDETAIL);
	m_tables.push_back(EXITROOM);
	m_tables.push_back(EXITS);
	m_tables.push_back(GRANTGROUPS);
	m_tables.push_back(PERMISSIONS);
	m_tables.push_back(RACES);
	m_tables.push_back(ROOMS);
	m_tables.push_back(SECTORS);
	m_tables.push_back(SKILLS);
	m_tables.push_back(STATS);
	m_tables.push_back(TREES);
	m_tables.push_back(VERSION);
}

