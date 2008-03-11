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

#include <string>
#include <vector>

#include "smart_ptr.h"
#include "chunkimporter.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "StringUtilities.h"
#include "DatabaseMgr.h"

class Base
{
	public:
		Base()
		{
			printf("Base constructor...\n");
		}
		
		~Base()
		{
			printf("Base destructor...\n");
		}
};

class Derived : public Base
{
	public:
		Derived()
		{
			printf("Derived constructor...\n");
		}
		
		~Derived()
		{
			printf("Derived destructor...\n");
		}
};

class Simple
{
	public:
		Simple()
		{
			printf("Simple constructor...\n");
		}
	
		~Simple()
		{
			printf("Simple destructor...\n");
		}
};

void TestSimple()
{
	SmartPtr<Simple> simplePtr(new Simple());
	simplePtr.print();
}

void TestBase()
{
	SmartPtr<Base> basePtr(new Base());
	basePtr.print();
}

void TestDerived()
{
	SmartPtr<Derived> derivedPtr(new Derived());
	derivedPtr.print();
}

void TestBaseDerived()
{
	printf("creating derivedPtr...\n");
	SmartPtr<Derived> derivedPtr(new Derived());
	derivedPtr.print();
	printf("\n");
	
	printf("creating basePtr...\n");
	SmartPtr<Base> basePtr = derivedPtr;
	derivedPtr.print();
	basePtr.print();
	printf("\n");
	
	printf("creating anotherDerivePtr...\n");
	SmartPtr<Derived> anotherDerivePtr = derivedPtr;
	derivedPtr.print();
	basePtr.print();
	anotherDerivePtr.print();
}

SmartPtr<Simple> TestPointerPass_a()
{
	printf("[functionenter:TestPointerPass_a]\n");
	printf("Creating simplePtr_a...\n");
	SmartPtr<Simple> simplePtr_a(new Simple());
	simplePtr_a.print();
	printf("\n");
	
	printf("Creating anotherSimplePtr_a...\n");
	SmartPtr<Simple> anotherSimplePtr_a = simplePtr_a;
	anotherSimplePtr_a.print();
	printf("\n");
	
	printf("Returning anotherSimplePtr_a...\n");
	printf("[functionleave:TestPointerPass_a(%p)]\n", &anotherSimplePtr_a);
	return anotherSimplePtr_a;
}

void TestPointerPass()
{
	printf("Creating simplePtr...\n");
	SmartPtr<Simple> simplePtr(new Simple());
	simplePtr.print();
	printf("\n");
	
	printf("Creating anotherSimplePtr...\n");
	SmartPtr<Simple> anotherSimplePtr = TestPointerPass_a();
	anotherSimplePtr.print();
	printf("\n");
	
	printf("Assigning simplePtr = anotherSimplePtr...\n");
	simplePtr = anotherSimplePtr;
	simplePtr.print();
	printf("\n");
}

class TestNullPtrClass
{
	public:
		TestNullPtrClass() : m_nullPtr()
		{
			
		}
		
		SmartPtr<Simple> getPtr() { return m_nullPtr; }
		void setPtr(SmartPtr<Simple> that) { m_nullPtr = that; }
		
	private:
		SmartPtr<Simple> m_nullPtr;
};

void TestNullPtr()
{
	printf("Creating nullPtr...\n");
	TestNullPtrClass* testClass = new TestNullPtrClass();
	SmartPtr<Simple> nullPtr = testClass->getPtr();
	
	SmartPtr<Simple> newPtr(new Simple());
	testClass->setPtr(newPtr);
	
	SmartPtr<Simple> retreivedPtr = testClass->getPtr();
	delete testClass;
	printf("Done.\n");
}

void TestChunkImporter()
{
	value_type key = mud::ChunkManager::Get()->Add();
	mud::ChunkPtr chunk = mud::ChunkManager::Get()->GetByKey(key);
	
	chunk->setDescription("Some chunk thingy.");
	chunk->setTags("Chunk Thingy");
	chunk->Save();
	
	printf("Creating importer...\n");
	std::string input;
	input.append("Algemene beschrijving.\n");
	input.append("*Eerste detail.\n");
	input.append("\tMet wat extra beschrijving.\n");
	input.append("\tDrie regels in totaal.\n");
	input.append("*Tweede detail.\n");
	input.append("*Derde detail.\n");
	input.append("**Met een subdetail\n");
	input.append("\tMet wat extra text in subdetail\n");
	input.append("**Nog een subdetail\n");
	input.append("*Vierde detail\n");
	input.append("**Subdetail\n");
	input.append("***Subsub detail\n");
	input.append("***Subsub detail twee\n");
	input.append("****Subsubsub detail\n");
	input.append("**Subdetail\n");
	ChunkImporterPtr importer(new ChunkImporter(input));
	printf(importer->getResult().c_str());
	printf("\n");
	
	printf("Applying chunk now...\n");
	importer->Apply(chunk);
	printf("\n");
}

void TestStringUtilities()
{
	std::string input;
	input.append("Dit is de eerste regel.\n");
	input.append("Dit is de tweede regel.\n");
	input.append("Derde regel.\n");
	input.append("Regel vier.\n");
	input.append("Laatste regel.\n");
	
	Strings results = String::Get()->lines(input,"\n");
	for(Strings::iterator it = results.begin(); it != results.end(); it++)
	{
		printf(it->c_str());
		printf("|\n");
	}
	printf("\n\n");
	
	Strings inputs;
	inputs.push_back("Dit is de eerste regel.");
	inputs.push_back("Dit is de tweede regel.");
	inputs.push_back("Derde regel.");
	inputs.push_back("Regel vier.");
	inputs.push_back("Laatste regel.");
	
	printf("\n=========\n");
	printf(String::Get()->unlines(inputs, "+", 0).c_str());
	printf("\n=========\n");
	printf(String::Get()->unlines(inputs, "~", 1).c_str());
	printf("\n=========\n");
	printf(String::Get()->unlines(inputs, "#", 2).c_str());
	printf("\n=========\n");
	printf(String::Get()->unlines(inputs, "@", 3).c_str());
	printf("\n=========\n");
	printf(String::Get()->unlines(inputs, "=", 4).c_str());
	printf("\n=========\n");
	printf(String::Get()->unlines(inputs, "&", 5).c_str());
	printf("\n=========\n");
	printf(String::Get()->unlines(inputs, "&", 6).c_str());
	printf("\n=========\n");
	printf("\n\n");
	
	Strings inputs_two;
	inputs_two.push_back("Dit is de eerste regel.\nMet wat extra's.");
	inputs_two.push_back("Dit is de tweede regel.");
	inputs_two.push_back("Derde regel.\nMet iets erachter.\nTwee ietsen zelfs");
	inputs_two.push_back("Regel vier.\nZit.\nVol.\nMet.\nExtra.\nRegels.\nZes in totaal.");
	inputs_two.push_back("Lege regels!\n\n\n\n\n\n\n\n");
	inputs_two.push_back("Laatste regel.");
	
	Strings results_two = String::Get()->unlines(inputs_two);
	
	printf("\n=========\n");
	for(Strings::iterator it = results_two.begin(); it != results_two.end(); it++)
	{
		printf(it->c_str());
		printf("|\n");
	}
	printf("\n=========\n");
	printf("\n\n");
	
	printf("\n=========\n");
	printf(String::Get()->box(inputs_two).c_str());
	printf("\n=========\n");
	
	printf("\n");
}

int main()
{ 
	/*
	printf("Opening database...\n");
	std::string dbname = "TestCase";
	dbname.append(".db");
	DatabaseMgr::Initialize(dbname);
	printf("Done.\n");
	*/
	
	/*
	printf("[starttest:Simple]\n");
	TestSimple();
	printf("[endtest:Simple]\n");
	printf("\n");
	
	printf("[starttest:Base]\n");
	TestBase();
	printf("[endtest:Simple]\n");
	printf("\n");
	
	printf("[starttest:Derived]\n");
	TestDerived();
	printf("[endtest:Simple]\n");
	printf("\n");
	
	printf("[starttest:BaseDerived]\n");
	TestBaseDerived();
	printf("[endtest:BaseDerived]\n");
	printf("\n");
	
	printf("[starttest:PointerPass]\n");
	TestPointerPass();
	printf("[endtest:PointerPass]\n");
	printf("\n");
	*/
	
	printf("[starttest:NullPointer]\n");
	TestNullPtr();
	printf("[endtest:NullPointer]\n");
	printf("\n");

	/*
	printf("[starttest:ChunkImporter]\n");
	TestChunkImporter();
	printf("[endtest:ChunkImporter]\n");
	printf("\n");

	printf("[starttest:StringUtilities]\n");
	TestStringUtilities();
	printf("[endtest:StringUtilities]\n");
	printf("\n");
	*/
	
	return 0;
}
