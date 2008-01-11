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

#include "chunkimporter.h"
#include "Chunk.h"

#include "StringUtilities.h"

std::string ChunkImporter::Detail::toString()
{
	std::string result;
	result.append("[\n");
	result.append(String::Get()->unlines(m_description , "\n", 0));
	for(DetailVector::iterator it = m_details.begin(); it != m_details.end(); it++)
	{
		result.append((*it)->toString());
	}
	result.append("]\n");
	return result;
}

void ChunkImporter::Detail::apply(SavableManagerPtr detail)
{	
	DetailVector details = getDetails();
	for(DetailVector::iterator it = details.begin(); it != details.end(); it++)
	{
		DetailPtr onedetail = *it;
		
		SavableManagerPtr newmanager = SavableManager::getnew(db::TableImpls::Get()->DETAILS);
		ValuePtr value(new Value(db::DetailsFields::Get()->DESCRIPTION, String::Get()->unlines(onedetail->getDescription() , " ", 0)));
		newmanager->setvalue(value);
		newmanager->save();
				
		/**
		 * Connect the detail to the chunk
		 */ 
		Keys keys;
		KeyPtr key;
		key = new Key(db::DetailDetailFields::Get()->FKDETAILSPRIMARY, newmanager->getkey(db::DetailsFields::Get()->DETAILID)->getValue());
		keys[db::DetailDetailFields::Get()->FKDETAILSPRIMARY.get()] = key;
		key = new Key(db::DetailDetailFields::Get()->FKDETAILSSECONDARY, detail->getkey(db::DetailsFields::Get()->DETAILID)->getValue());
		keys[db::DetailDetailFields::Get()->FKDETAILSSECONDARY.get()] = key;
		
		SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->DETAILDETAIL, keys);
		manager->save();
		
		onedetail->apply(detail);
	}
}

ChunkImporter::ChunkImporter(
const std::string& input) :
m_input(input)
{
	Parse();
}

ChunkImporter::~ChunkImporter()
{
	
}

/**

The format is as follows:
[format description]

Chunk Description
This may span several lines
* Detail of Chunk
**	Detail of Detail of Chunk
	Continuation of detail
	Further continued
**	Another Detail of Detail of Chunk 
***	Detail of above detail
** 	Yet Another Detail of Detail of Chunk
* Detail of the chunk
* Some more detail of the chunk

[/format description]
[formal format description]

TEXT: {^*\n\t}


import:		description
		|	details
		|	description '\n' details

description: 	description '\n' TEXT
			|	TEXT
			
details:	detail
		|	details '\n' detail
		
detail:		'*' TEXT
		|	'*' TEXT '\n' lines
		|	subdetail
		
lines:		lines tabs TEXT '\n'
		|	tabs TEXT '\n'
		
tabs:	tabs	'\t'
	|	'\t'
		
subdetail:	'*' detail	

[/formal format description]
[call graph]
bovenaan [current = topDetail, details.top() = NULL]
* klein [ current = newDetail, details.top() = topDetail] // details.push(current), current = new Detail()
** heel erg [ current = notherNewDetail, details.top() = newDetail] // details.push(current), current = new Detail()
* blauw [ current = newDetail, details.top() = topDetail] // details.top()->addDetail(current), current = details.pop(), detail.top()->addDetail(current), current = new Detail()
	en groen [ current = newDetail, details.top() = topDetail] // current.append(line)
* dinges [ current = YoNewDetail, details.top() = topDetail] // details.top()->addDetail(current), current = new Detail()
[/call graph]
*/
void ChunkImporter::Parse()
{	
	bool inDescr = true;
	size_t i = 0;
	int lastDepth = 0;
	
	std::stack<DetailPtr> details;
	SmartPtr<Detail> current(new ChunkImporter::Detail());
	
	Strings lines = String::Get()->lines(m_input, "\n");
	
	for(Strings::iterator it = lines.begin(); it != lines.end(); it++)
	{
		std::string line = *it;
		int depth = 0;
		
		if(!line.size())
			continue;
		
		/**
		 * If we're still in the description of the chunk, just append.
		 */ 
		if(inDescr)
		{
			/**
			 * This is the first detail, so stop appending
			 */ 
			if(line[0] == '*')
			{
				inDescr = false;
			}
			else
			{
				current->append(line);
				continue;
			}
		}
	
		/**
		 * Find out how deep the rabbit hole goes
		 */ 
		for(i = 0; i < line.size(); i++)
		{
			if(line[i] != '*')
			{
				depth = i;
				break;
			}
		}
		
		/**
		 * Apparently not that deep, just append this line to the current detail
		 */ 
		if(depth == 0)
		{
			/**
			 * Find out how deep the tabbification is
			 */ 
			int tabDepth = 0;
			for(i = 0; i < line.size(); i++)
			{
				if(line[i] != '\t')
				{
					tabDepth = i;
					break;
				}
			}
			
			/**
			 * The format dictates that there is at least one tab before each continuation
			 */ 
			if(!tabDepth)
			{
				Global::Get()->bugf("Malformed import line.\n");
				m_result = NULL;
				return;
			}
			
			/** 
			 * Erase the tabs and append it to the current detail
			 */ 
			line.erase(0, tabDepth);
			current->append(line);
			continue;
		} // if(depth == 0)
		
		line.erase(0, depth);
		
		if(depth < lastDepth)
		{
			details.top()->addDetail(current);
			current = details.top();
			details.pop();
		}
		
		if(depth > lastDepth)
		{			
			details.push(current);
			current.reset(new Detail());
		}

		/**
		 * This needs to be done not only when depth==lastDepth, but also when we just went down a detail level
		 */
		if(lastDepth >= depth && details.size())
		{
			details.top()->addDetail(current);
			current.reset(new Detail());
		}
		
		current->append(line);
		lastDepth = depth;
	}
	
	while(details.size() > 0)
	{
		details.top()->addDetail(current);
		current = details.top();
		details.pop();
	}
	
	m_result = current;
	m_resultstring = current->toString();
}

void ChunkImporter::Apply(mud::ChunkPtr chunk)
{
	/**
	 * Set description to that of the top node
	 */ 
	chunk->setDescription(String::Get()->unlines(m_result->getDescription() , " ", 0));
	
	/**
	 * Add all the details as details of the chunk
	 */ 
	DetailVector details = m_result->getDetails();
	for(DetailVector::iterator it = details.begin(); it != details.end(); it++)
	{
		SmartPtr<Detail> onedetail = *it;
		
		SavableManagerPtr detailmanager = SavableManager::getnew(db::TableImpls::Get()->DETAILS);
		ValuePtr value(new Value(db::DetailsFields::Get()->DESCRIPTION, String::Get()->unlines(onedetail->getDescription() , " ", 0)));
		detailmanager->setvalue(value);
		detailmanager->save();
		
		/**
		 * Connect the new detail to the chunk
		 */ 
		Keys keys;
		KeyPtr key;
		key = new Key(db::DetailsFields::Get()->DETAILID, chunk->getID());
		keys[db::DetailsFields::Get()->DETAILID.get()] = key;
		key = new Key(db::ChunksFields::Get()->CHUNKID, detailmanager->getkey(db::DetailsFields::Get()->DETAILID)->getValue());
		keys[db::ChunksFields::Get()->CHUNKID.get()] = key;
		
		SavableManagerPtr manager = SavableManager::bykeys(db::TableImpls::Get()->DETAILCHUNK, keys);
		manager->save();
		
		onedetail->apply(detailmanager);
	}
}

const std::string& ChunkImporter::getResult()
{
	return m_resultstring;
}
