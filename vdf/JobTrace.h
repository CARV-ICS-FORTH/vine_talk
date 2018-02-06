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


#ifndef VDF_JOBTRACE_HEADER
	#define VDF_JOBTRACE_HEADER
	#include <string>
	#include <vector>
	#include <string>
	#include <mutex>
	#include <ostream>
	#include "Sample.h"

	class JobTrace
	{
		public:
			JobTrace();
			uint64_t getStart() const;
			uint64_t getEnd() const;
			uint64_t getDuration() const;
			void histogram(std::ostream & os,float ratio);
			void addSample(const Sample & sample);
			size_t getSize();
			const std::vector<Sample> & getSamples() const;
			static bool byStartTime(const std::pair<void* const, JobTrace*> & a,const std::pair<void* const, JobTrace*> & b);
			static bool byStartTimeP(const JobTrace* a,const JobTrace* b);
			std::string getName();
		private:
			std::string name;
			std::vector<Sample> samples;
			uint64_t start;
			uint64_t end;
			std::mutex lock;
	};

#endif
