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


#include <iostream>
#include <vine_pipe.h>
#include <map>

struct Metrics
{
	int type;
	size_t leaks;
	size_t size;
};

int main(int argc, char * argv[])
{
	std::map<std::string,Metrics> leaks;

	auto vpipe = vine_talk_init();

	int type;
	utils_list_s *list;
	utils_list_node_s *itr;
	vine_object_s *obj;

	for(type = 0 ; type < VINE_TYPE_COUNT ; type++)
	{
		list = vine_object_list_lock(&(vpipe->objs),(vine_object_type_e)type);

		utils_list_for_each(*list,itr)
		{
			obj = (vine_object_s*)itr->owner;
			auto & stats = leaks[obj->name];
			stats.leaks++;
		}

		vine_object_list_unlock(&(vpipe->objs),(vine_object_type_e)type);
	}

	for(auto leak : leaks)
	{
		std::cerr.width(12);
		std::cerr << leak.second.leaks << " leaks of " << leak.first << std::endl;
	}

	vine_talk_exit();
	return 0;
}
