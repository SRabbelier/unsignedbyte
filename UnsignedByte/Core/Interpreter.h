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

#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> Strings;
typedef Strings::iterator StringsI;

template <class T>
class Interpreter
{
public:
	Interpreter();
	~Interpreter();

	void addWord(const std::string& name, T* cmd);
	T* translate(const std::string& name);
	
	Strings getWords();

protected:
	std::map<std::string, T*> m_fullwords; // available commands
	std::map<std::string, T*> m_words; // table for command lookup
	
private:
	Interpreter(const Interpreter& rhs) {};
	Interpreter operator=(const Interpreter& rhs) { return *this; };
};

template <class T>
Interpreter<T>::Interpreter()
{

}

template <class T>
Interpreter<T>::~Interpreter()
{
	m_words.clear();
	m_fullwords.clear();
}

template <class T> 
void Interpreter<T>::addWord(const std::string& name, T* word)
{
	m_fullwords[name] = word;

	if(word->fullName())
		return;

    for(size_t i = 1; i <= name.length(); i++)
    {
        if(m_words.find(name.substr(0, i)) == m_words.end())
        {
            m_words[name.substr(0,i)] = word;
        }
    }

	return;
}

template <class T> 
T* Interpreter<T>::translate(const std::string& name)
{
	typename std::map<std::string, T*>::iterator word = m_fullwords.find(name);
	if(word == m_fullwords.end())
	{
		word = m_words.find(name);
		if(word == m_words.end())
			return NULL;
	}

	return word->second;
}

template <class T> 
Strings Interpreter<T>::getWords()
{
	Strings words;

	for(typename std::map<std::string, T*>::iterator it = m_fullwords.begin(); it != m_fullwords.end(); it++)
	{
		words.push_back(it->first);
	}

	return words;
}
