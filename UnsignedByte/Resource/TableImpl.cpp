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

#include "TableImpl.h"
#include "ListActor.h"
#include "SqliteMgr.h"
#include "FieldImpl.h"
#include "FieldDef.h"
#include "KeyDef.h"

TableImpl::TableImpl(TableDefPtr table) :
Table(table->tableName()),
m_table(table),
m_lastchange(time(NULL)),
m_listcache(0)
{

}

const std::vector<std::string>& TableImpl::tableList()
{
	if(m_listcache > m_lastchange || !m_list.size())
	{
		ListActor act;
		SqliteMgr::Get()->doForEach(this, act);
		m_list = act.getList();
		m_listcache = time(NULL);
	}

	return m_list;
}

void TableImpl::addKey(KeyDefPtr key) 
{
	Assert(key); 
	
	m_keys.push_back(key); 
}

void TableImpl::addField(FieldImplPtr field) 
{ 
	Assert(field); 
	
	m_implfields.push_back(field); 
}

void TableImpl::modify()
{
	m_lastchange = time(NULL);
}

bool TableImpl::hasfield(FieldImplPtr field) const
{
	for(FieldImplVector::const_iterator it = m_implfields.begin(); it != m_implfields.end(); it++)
	{
		if((*it) == field)
			return true;
	}
	
	return false;
}
