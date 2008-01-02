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

#include <string>
#include <vector>

#include "smart_ptr.h"
#include "chunkimporter.h"

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

void TestChunkImporter()
{
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
	input.append("**Subdetail\n");
	ChunkImporterPtr importer(new ChunkImporter(input));
	printf(importer->getResult().c_str());
	printf("\n");
}

int main()
{ 
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
	
	printf("[starttest:ChunkImporter]\n");
	TestChunkImporter();
	printf("[endtest:ChunkImporter]\n");
	printf("\n");
	
	return 0;
}
