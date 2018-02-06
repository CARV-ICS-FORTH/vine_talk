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


#ifndef VDF_COLLECTOR_HEADER
	#define VDF_COLLECTOR_HEADER
	#include "conf.h"
	#ifdef VINE_TELEMETRY
		#include <Poco/Net/TCPServerConnection.h>
		#include <Poco/Net/StreamSocket.h>
		#include "Poco/Net/TCPServer.h"
		#include <unordered_map>
		#include <mutex>
		#include <ostream>
		#include "Sample.h"
		#include "JobTrace.h"

		class Collector : public Poco::Net::TCPServer, public Poco::Net::TCPServerConnectionFactory
		{
			public:
				class CollectorConnection : public Poco::Net::TCPServerConnection
				{
					virtual void run();
					public:
						CollectorConnection(const Poco::Net::StreamSocket& s,Collector & collector);
					private:
						Collector & collector;
				};
			private:
	
				uint64_t start_time;
				std::mutex map_lock;
				std::unordered_map<void*,JobTrace*> jobs;
			public:
				Collector(uint16_t port);
				void rawDump(std::ostream & os);
				static void generateTaskExecutionGraph(std::ostream & os,const std::vector<JobTrace*> & jobs);
				void taskExecutionGraph(std::ostream & os);
				virtual Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& sock);
		};
	#else
		#include <stdint.h>
		#include <ostream>
		class Collector
		{
			public:
				Collector(uint16_t port){}
				void rawDump(std::ostream & os){os << "Telemetry is disabled!";}
				void start(){}
				void stop(){}
		};
	#endif
#endif
