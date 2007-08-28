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

#include "singleton.h"
#include "Global.h"

typedef std::vector<std::string> Strings;

class String : public Singleton<String>
{
private:
	String(void) {};
	~String(void) {};

	friend class Singleton<String>;

public:
	Strings lines(const std::string& input, const char* separator);
	std::string unlines(const Strings& input, const char* filler, int newlineat = 1);
	
	size_t maxlength(const Strings& content);
	std::string box(const Strings& content, const std::string& header = Global::Get()->EmptyString);
	
	std::string toupper(const std::string& convertToUpper);
	std::string tolower(const std::string& convertToLower);
};
