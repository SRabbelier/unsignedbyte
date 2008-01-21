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

#include "SavableHeaders.h"

#include <stack>


namespace mud
{
	class Chunk;
	typedef SmartPtr<mud::Chunk> ChunkPtr;
	
	class Detail;
	typedef SmartPtr<mud::Detail> DetailPtr;
}

class ChunkImporter;
typedef SmartPtr<ChunkImporter> ChunkImporterPtr;
	
class ChunkImporter 
{
	class MyDetail;
	typedef SmartPtr<MyDetail> MyDetailPtr;
	typedef std::vector<MyDetailPtr> MyDetailVector; // not called 'Details' to prevent confusion with db::Details
	private:
		class MyDetail
		{
			public:
				MyDetail() { }
				~MyDetail() { }
				
				void append(const std::string& line) { m_description.push_back(line); }
				void addDetail(MyDetailPtr detail) { m_details.push_back(detail); }
				
				const std::vector<std::string>& getDescription() { return m_description; }
				const MyDetailVector& getDetails() { return m_details; }
				
				std::string toString();
				void apply(mud::DetailPtr detail);
				
			private:
				std::vector<std::string> m_description;
				MyDetailVector m_details;
		};
		
	public:
		ChunkImporter(const std::string& input);
		
		~ChunkImporter();
		
		void Apply(mud::ChunkPtr chunk);
		const std::string& getResult();

	private:
		ChunkImporter(const ChunkImporter& rhs);
		ChunkImporter& operator=(const ChunkImporter& rhs);
		
		void Parse();
		
		// mud::ChunkPtr m_chunk;
		std::string m_input;
		
		std::vector<std::string> m_description;
		
		MyDetailPtr m_result;
		std::string m_resultstring;
};
