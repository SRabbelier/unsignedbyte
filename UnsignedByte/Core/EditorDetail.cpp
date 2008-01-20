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

#include "SavableHeaders.h"

#include "EditorDetail.h"
#include "EditorString.h"
#include "EditorBool.h"

#include "UBSocket.h"
#include "StringUtilities.h"

#include "Account.h"
#include "Detail.h"

EditorDetail::DetailCommand EditorDetail::m_listCommands("?", &EditorDetail::listCommands);
EditorDetail::DetailCommand EditorDetail::m_editKey("Key", &EditorDetail::editKey);
EditorDetail::DetailCommand EditorDetail::m_editDescription("Description", &EditorDetail::editDescription);
EditorDetail::DetailCommand EditorDetail::m_showDetail("Show", &EditorDetail::showDetail);
EditorDetail::DetailCommand EditorDetail::m_saveDetail("Save", &EditorDetail::saveDetail);

EditorDetail::EditorDetail(UBSocket* sock, mud::DetailPtr detail) :
Editor(sock),
m_detail(detail),
m_target(M_NONE)
{
	
}

EditorDetail::~EditorDetail(void)
{

}

void EditorDetail::OnFocus()
{		
	switch(m_target)
	{
		case M_NONE:
			return;
			
		case M_DESCRIPTION:
			m_detail->setDescription(m_value);
			break;
	}
	
	m_target = M_NONE;
}

std::string EditorDetail::lookup(const std::string& action)
{		
	DetailCommand* act = DetailInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorDetail::dispatch(const std::string& action, const std::string& argument)
{
	DetailCommand* act = DetailInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		Global::Get()->bugf("EditorDetail::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());

	return;
}

EditorDetail::DetailInterpreter::DetailInterpreter(void)
{
	addWord("?", &m_listCommands);
	addWord("name", &m_editKey);
	addWord("show", &m_showDetail);
	addWord("save", &m_saveDetail);
}

EditorDetail::DetailInterpreter::~DetailInterpreter(void)
{

}

void EditorDetail::listCommands(const std::string& argument)
{
	std::string name = this->name();
	name.append("Editing");
	m_sock->Send(String::Get()->box(DetailInterpreter::Get()->getWords(), name));
	m_sock->Send("\n");
	return;
}

void EditorDetail::editKey(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Detail key can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Detail key changed from '%s' to '%s'.\n", m_detail->getKey().c_str(), argument.c_str());
	m_detail->setKey(argument);
	return;
}

void EditorDetail::editDescription(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("No argument, dropping you into the string editor!\n");
		m_sock->SetEditor(new EditorString(m_sock, m_value));
		m_target = M_DESCRIPTION;
		return;
	}

	m_sock->Sendf("Detail description changed from '%s' to '%s'.\n", m_detail->getDescription().c_str(), argument.c_str());
	m_detail->setDescription(argument);
	return;
}

void EditorDetail::showDetail(const std::string& argument)
{
	std::vector<std::string> result;
	std::string key = "Key: '";
	key.append(m_detail->getKey());
	key.append("'.");
	result.push_back(key);
	
	std::string description = "Description: '";
	description.append(m_detail->getDescription());
	description.append("'.");
	result.push_back(description);
	
	m_sock->Send(String::Get()->box(result, "Detail"));
}

void EditorDetail::saveDetail(const std::string& argument)
{
	m_sock->Sendf("Saving detail '%s'.\n", m_detail->getKey().c_str());
	m_detail->Save();
	m_sock->Send("Saved.\n");
	return;
}
