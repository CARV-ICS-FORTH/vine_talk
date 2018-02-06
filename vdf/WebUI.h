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


#ifndef VDF_WEB_UI_HEADER
	#define VDF_WEB_UI_HEADER
	#include <map>
	#include <Poco/Net/HTTPRequestHandler.h>
	#include <Poco/Net/HTTPServerRequest.h>
	#include <Poco/Net/HTTPResponse.h>
	#include <Poco/Net/HTTPServerResponse.h>
	#include "Collector.h"

	class WebUI : public Poco::Net::HTTPRequestHandler
	{
		virtual void handleRequest(Poco::Net::HTTPServerRequest & request,Poco::Net::HTTPServerResponse & response);
		public:
			WebUI(std::map<std::string,bool> & args,Collector * collector);
		private:
			Collector * collector;
			std::map<std::string,bool> args;
	};
#endif
