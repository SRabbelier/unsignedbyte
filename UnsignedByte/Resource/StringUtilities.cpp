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

#include <algorithm>
#include <cctype>

#include "StringUtilities.h"
#include "Parse.h"
#include "Global.h"

Strings String::lines(const std::string& input, const char* separator)
{
	Strings result;
	Parse p(input, separator, 1);

	while(true)
	{
		std::string line = p.getword();
		if(line.size())
			result.push_back(line);
		else
			break;
	}

	return result;
}

std::string String::unlines(const Strings& input, const char* filler, int extra)
{
	std::string result;
	int i = 0;
	for(Strings::const_iterator it = input.begin(); it != input.end(); it++)
	{
		i++;
		if(i != 0 && extra && i%extra == 0)
			result += "\n";

		result += (*it);
		result += filler;
	}

	return result;
}

size_t String::maxlength(const Strings& input)
{
	size_t champ = 0;
	for(Strings::const_iterator it = input.begin(); it != input.end(); it++)
	{
		size_t current = it->size();
		if(current > champ)
			champ = current;
	}
	return champ;
}

std::string String::box(const Strings& content, const std::string& header)
{
	bool useheader = (header != Global::Get()->EmptyString);

	size_t length = maxlength(content);
	if(useheader && header.size() > length)
		length = header.size();
	
	length += 4;

	std::string result;	
	std::string linefill;
	std::string spacefill;
	std::string fill;

	linefill.assign(length, '_');
	spacefill.assign(length, ' ');
	fill.assign( (length-header.size())/2 + 2,' ');

	std::string title;
	if(useheader)
		title = (Global::Get()->sprintf("%s%s%s\n", fill.c_str(), header.c_str(), fill.c_str()));

	std::string toplet(Global::Get()->sprintf("__%s__\n", linefill.c_str()));
	std::string top(Global::Get()->sprintf("|\\%s/|\n", linefill.c_str()));
	std::string body(Global::Get()->sprintf("||%s||\n", spacefill.c_str()));
	std::string footlet(Global::Get()->sprintf("||%s||\n", linefill.c_str()));
	std::string footer(Global::Get()->sprintf("|/%s\\|\n", linefill.c_str()));

	if(useheader)
		result.append(title);
	result.append(toplet);
	result.append(top);
	result.append(body);
	for(Strings::const_iterator it = content.begin(); it != content.end(); it++)
	{		
		result.append(Global::Get()->sprintf("||  %s%.*s||\n",it->c_str(), length - it->size() - 2, spacefill.c_str()));
	}
	result.append(footlet);
	result.append(footer);

	return result;
}

std::string String::toupper(const std::string& input)
{
	std::string convertToUpper = input;
	std::transform(convertToUpper.begin(), convertToUpper.end(), convertToUpper.begin(), (int(*)(int)) std::toupper);
	return convertToUpper ;
}

std::string String::tolower(const std::string& input)
{
	std::string convertToUpper = input;
	std::transform(convertToUpper.begin(), convertToUpper.end(), convertToUpper.begin(), (int(*)(int)) std::tolower);
	return convertToUpper ;
}
