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


#ifndef VDF_PALLETE_HEADER
#define VDF_PALLETE_HEADER
#include <map>
#include <set>
#include <vector>
#include <string>

class Pallete
{
	public:
		Pallete();
		/**
		 * \param id Color id to be returned
		 * \param opacity Opacity of color(0 transparent 15 opaque)
		 * \return String of the form #RGBA
		 */
		static std::string get(size_t id,int opacity);
		/**
		 * \param id Color id to be returned
		 * \param opacity Opacity of color(0 transparent)
		 * \return String of the form #RGBA
		 */
		static std::string get(std::string name,int opacity);
	private:
		static void init();
		static std::vector<std::string> colors;
		static std::set<size_t> unused_colors;
		static std::map<std::string,size_t> named_colors;
};
#endif
