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
#include <vector>
#include <stack>

#include "smart_ptr.h"

namespace mud
{
	//class Chunk;
	//typedef SmartPtr<Chunk> ChunkPtr;
}

class ChunkImporter;
typedef SmartPtr<ChunkImporter> ChunkImporterPtr;
	
class ChunkImporter 
{
	private:
		class Detail
		{
			public:
				typedef std::vector<ChunkImporter::Detail*> Details;
				
				Detail() { }
				~Detail() { }
				
				void append(const std::string& line) { m_description.push_back(line); }
				void addDetail(Detail* detail) { m_details.push_back(detail); }
				
				std::string toString();
				
			private:
				std::vector<std::string> m_description;
				Details m_details;
		};
		
	public:
		ChunkImporter(
		//mud::ChunkPtr chunk, 
		const std::string& input);
		
		~ChunkImporter();
		
		void Apply();
		const std::string& getResult();

	private:
		ChunkImporter(const ChunkImporter& rhs);
		ChunkImporter& operator=(const ChunkImporter& rhs);
		
		void Parse();
		
		// mud::ChunkPtr m_chunk;
		std::string m_input;
		
		std::vector<std::string> m_description;
		
		ChunkImporter::Detail* m_result;
		std::string m_resultstring;
};
