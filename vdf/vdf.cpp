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


#include <vine_pipe.h>
#include <arch/alloc.h>
#include <core/vine_object.h>
#include <stdio.h>
#include "Poco/Net/HTTPServer.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/URI.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <unistd.h>
#include <map>
#include "Misc.h"
#include "WebUI.h"
#include "Collector.h"

using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;


vine_pipe_s *vpipe;

std::map<std::string,bool> args;

class WebUIFactory : public HTTPRequestHandlerFactory
{
public:
	WebUIFactory(Collector* collector)
	: collector(collector)
	{

	}
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& rq)
	{
		return new WebUI(args,collector);
	}
private:
	Collector * collector;
};

class Server : public ServerApplication
{
	void initialize(Application & self)
	{
		std::cerr << "VDF at port " << port << std::endl;
		collector = new Collector(port+1);
		webui = new HTTPServer(new WebUIFactory(collector),port,new HTTPServerParams());

	}

	int main(const std::vector < std::string > & args)
	{
		collector->start();

		vpipe = vine_talk_init();
		if(!vpipe)
		{
			fprintf(stderr,"Could not get vine_pipe instance!\n");
			return -1;
		}
		webui->start();


		waitForTerminationRequest();
		collector->stop();
		webui->stop();
	}

	HTTPServer *webui;
	Collector *collector;
	int port;

	public:
		Server(int port)
		:port(port)
		{}
};



int main(int argc,char * argv[])
{
	int port = 8888;

	for(int arg = 0 ; arg < argc ; arg++)
	{
		if(atoi(argv[arg]))
			port = atoi(argv[arg]);
		else
			args[argv[arg]] = true;
	}

	Server app(port);
	app.run(argc,argv);

	vine_talk_exit();
	return 0;
}
