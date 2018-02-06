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


#include "testing.h"
#include "utils/trace.h"
#define TEST_LENGTH 100000

void setup() {}
void teardown() {}

START_TEST(perf_test)
{
	utils_timer_s t;
	int c;
	trace_init();
	utils_timer_set(t,start);
	for(c = 0 ; c < TEST_LENGTH ; c++)
	{
		trace_vine_accel_acquire_phys(&c,"vine_accel_acquire_phys",t);
		utils_timer_set(t,stop);
	}
	trace_exit();
	utils_timer_set(t,stop);
	fprintf(stderr,"#%03d :: Tracing %d calls took : %ld ns\n",_i,TEST_LENGTH,utils_timer_get_duration_ns(t));
}
END_TEST


Suite* suite_init()
{
	Suite *s;
	TCase *tc_single;

	s         = suite_create("Tracer");
	tc_single = tcase_create("Single");
	tcase_add_unchecked_fixture(tc_single, setup, teardown);
	tcase_add_test(tc_single, perf_test);
	tcase_set_timeout(tc_single,60);
	suite_add_tcase(s, tc_single);
	return s;
}

int main(int argc, char *argv[])
{
	Suite   *s;
	SRunner *sr;
	int     failed;

	s  = suite_init();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (failed) ? EXIT_FAILURE : EXIT_SUCCESS;
}
