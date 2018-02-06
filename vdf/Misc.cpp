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


#include "Misc.h"

std::string autoRange(size_t value,const char * units[],int order,int precission)
{
	int c = 0;
	float ret = value;
	std::ostringstream oss;
	while(ret >= order && units[c])
	{
		ret /= (float)order;
		c++;
	}
	oss << ((int)(ret*precission))/((float)precission) << " " << units[c];
	return oss.str();
}

std::string tag_gen(std::string tag,std::string inner_html,std::string attrs)
{
	std::ostringstream oss;

	oss << "<" << tag << " " << attrs << ">" << inner_html << "</" << tag << ">";

	return oss.str();
}
