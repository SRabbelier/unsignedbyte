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

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <set>

#include <sqlite3.h>

#include "smart_ptr.h"
#include "singleton.h"

typedef unsigned long value_type;
typedef std::set<value_type> value_types;
typedef const std::string& cstring;

typedef std::vector<std::string> Strings;

class UBSocket;

class Actor;
typedef SmartPtr<Actor> ActorPtr;

class Table;
typedef SmartPtr<Table> TablePtr;
typedef std::vector<TablePtr> TableVector;
typedef std::map<std::string, TablePtr> TableMap;

class TableDef;
typedef SmartPtr<TableDef> TableDefPtr;
typedef std::vector<TableDefPtr> TableDefVector;

class TableImpl;
typedef SmartPtr<TableImpl> TableImplPtr;
typedef std::vector<TableImplPtr> TableImplVector;

class KeyDef;
typedef SmartPtr<KeyDef> KeyDefPtr;
typedef std::vector<KeyDefPtr> KeyDefs;

class Key;
typedef SmartPtr<Key> KeyPtr;

class Keys;
typedef std::map<KeyDef*, KeyPtr> KeyMap;
typedef SmartPtr<Keys> KeysPtr;

class Value;
typedef SmartPtr<Value> ValuePtr;

class FieldDef;
typedef SmartPtr<FieldDef> FieldDefPtr;
typedef std::vector<FieldDefPtr> FieldDefVector;

class FieldImpl;
typedef SmartPtr<FieldImpl> FieldImplPtr;
typedef std::vector<FieldImplPtr> FieldImplVector;
typedef std::map<FieldImpl*, ValuePtr> Fields;

class Field;
typedef SmartPtr<Field> FieldPtr;
// typedef std::map<FieldPtr, ValuePtr> Fields;
typedef std::vector<FieldPtr> FieldVector;

class SavableManager;
typedef SmartPtr<SavableManager> SavableManagerPtr;
