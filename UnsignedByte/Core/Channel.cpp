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

#include "Channel.h"
#include "Global.h"
#include "db.h"

using mud::Channel;

Channel::Channel(SavableManagerPtr channel) :
m_channel(channel)
{
	Assert(channel);
}

Channel::~Channel(void)
{

}

const std::string& Channel::getName() const
{
	return m_channel->getfield(db::ChannelsFields::Get()->NAME)->getStringValue();
}

const std::string& Channel::getDescription() const
{
	return m_channel->getfield(db::ChannelsFields::Get()->DESCRIPTION)->getStringValue();
}

bool mud::Channel::needLogin() const
{
	return m_channel->getfield(db::ChannelsFields::Get()->NEEDLOGIN)->getBoolValue();
}

void Channel::setName(const std::string& name)
{
	ValuePtr value(new Value(db::ChannelsFields::Get()->NAME, name));
	m_channel->setvalue(value);
}

void Channel::setDescription(const std::string& description)
{
	ValuePtr value(new Value(db::ChannelsFields::Get()->DESCRIPTION, description));
	m_channel->setvalue(value);
}

void mud::Channel::setNeedLogin(bool needLogin)
{
	ValuePtr value(new Value(db::ChannelsFields::Get()->NEEDLOGIN, needLogin));
	m_channel->setvalue(value);
}

void Channel::Delete()
{
	m_channel->erase();
}

void Channel::Save()
{
	m_channel->save();
}

bool Channel::Exists()
{
	return m_channel->exists();
}

std::vector<std::string> Channel::Show()
{
	std::vector<std::string> result;
	
	result.push_back(Global::Get()->sprintf("Name: '%s'.", getName().c_str()));
	result.push_back(Global::Get()->sprintf("Description: '%s'.", getDescription().c_str()));

	return result;
}

std::string Channel::ShowShort()
{
	return Global::Get()->sprintf("%s: %s\n", 
			getName().c_str(),
			getDescription().c_str());
}

TableImplPtr Channel::getTable() const
{
	return m_channel->getTable();
}
