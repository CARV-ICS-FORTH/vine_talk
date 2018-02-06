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


#ifndef VDF_MISC_HEADER
	#define VDF_MISC_HEADER
	#include <sstream>
	#include <string>

	static const char * bytes_to_orders[] = {"b ","Kb","Mb","Gb","Tb","Pb",0};
	static const char * ns_to_secs[] = {"ns","us","ms","s","KiloSec","MegaSec",0};



	std::string autoRange(size_t value,const char * units[],int order,int precission = 1000);

	std::string tag_gen(std::string tag,std::string inner_html = "",std::string attrs = "");

	#define _S(VAL) std::to_string(VAL)
	#define _TR(...) tag_gen("tr",__VA_ARGS__)
	#define _TD(...) tag_gen("td",__VA_ARGS__)
	#define _TH(...) tag_gen("th",__VA_ARGS__)
	#define _RECT(FILL,X,Y,W,H,ATTR)									\
							tag_gen("rect","",((FILL!="")?("fill=#"+std::string(FILL)):(std::string()))+		\
							" x="+_S(X)+						\
							" y="+_S(Y)+						\
							" width="+_S(W)+					\
							" height="+_S(H)+					\
							ATTR)
	#define _TEXT(...) tag_gen("text",__VA_ARGS__)

#endif
