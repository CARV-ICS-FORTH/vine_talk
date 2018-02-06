/*
 * Copyright 2018 Foundation for Research and Technology - Hellas
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0 [1] [1]
 *
 * Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *  implied.
 * See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * Links:
 *  ------
 * [1] http://www.apache.org/licenses/LICENSE-2.0 [1]
*/


#include "Sample.h"

bool Sample :: recv(Poco::Net::StreamSocket & sock)
{
	return sock.receiveBytes(&stats,sizeof(stats)) > 0;
}

void Sample :: setID(int id)
{
	this->id = id;
}
int Sample :: getID()
{
	return id;
}
void * Sample :: getVAccel()
{
	return stats.vaccel;
}
void * Sample :: getPAccel()
{
	return stats.paccel;
}
std::string Sample :: getPAccelDesc()
{
	if(!stats.paccel)
		return "Unknown";
	return ((vine_object_s*)stats.paccel)->name;
}

uint64_t Sample :: getStart() const
{
	return stats.start;
}

uint64_t Sample :: getEnd() const
{
	return getStart()+getDuration();
}

uint64_t Sample :: getDuration() const
{
	return stats.part[BREAKDOWN_PARTS];
}

uint64_t Sample :: operator[](int part) const
{
	return stats.part[part];
}

bool Sample :: byStartTime(const Sample & a,const Sample & b)
{
	return a.getStart()< b.getStart();
}

bool Sample :: byEndTime(const Sample & a,const Sample & b)
{
	return a.getEnd() < b.getEnd();
}

bool Sample :: byDuration(const Sample & a,const Sample & b)
{
	return a.getDuration() < b.getDuration();
}

