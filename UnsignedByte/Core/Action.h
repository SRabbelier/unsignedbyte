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

class UBSocket;

template <class T>
class Action
{
    public:
        virtual void Run(T * act, const std::string& argument) = 0;
		virtual std::string getName() = 0;
		virtual bool fullName(); // only add the full name

    protected:
        Action();
		Action(const Action& rhs);
        virtual ~Action();
};

typedef Action<UBSocket> UBAction;

template <class T> bool Action<T>::fullName()
{ 
	return false; 
};

template <class T> Action<T>::Action()
{
}

template <class T> Action<T>::Action(const Action<T>& rhs)
{
}

template <class T> Action<T>::~Action()
{
}

template <class T, class E>
class EditorAction
{
    public:
        virtual void Run(T*, const std::string& argument, E*) = 0;
		virtual std::string getName() = 0;		
		virtual bool fullName(); // only add the full name

    protected:
        EditorAction();
		EditorAction(const EditorAction& rhs);
        virtual ~EditorAction();
};

template <class T, class B> bool EditorAction<T, B>::fullName()
{ 
	return false; 
};

template <class T, class B> EditorAction<T, B>::EditorAction()
{
}

template <class T, class B> EditorAction<T, B>::EditorAction(const EditorAction<T, B>& rhs)
{
}

template <class T, class B> EditorAction<T, B>::~EditorAction()
{
}

