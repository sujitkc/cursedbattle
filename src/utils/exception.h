/***************************************************************************
 *   Copyright (C) 2006 by Sujit Kumar Chakrabarti                         *
 *   sujitkc@gmail.com                                 			   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using namespace std;
class Exception
{
private:
	string m_Source;
	string m_Message;
public:
	Exception (const string aSource, const string aMessage) : m_Source (aSource), m_Message (aMessage){}
	string getSource (){	return m_Source;	}
	string getMessage (){	return m_Message;	}
};

#endif //EXCEPTION_H
