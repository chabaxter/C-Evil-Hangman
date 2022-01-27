#include <stdio.h>
#include <string.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
	Status (*tests[])(char*, int) =
	{
		test_init_default_returns_nonNULL,
		test_get_size_on_init_default_returns_0,
		test_cbaxter_init_default_capacity_returns_7,

		test_cbaxter_destroy_handle_is_NULL,

		test_cbaxter_init_c_string_returns_nonNULL,
		test_cbaxter_init_c_string_size_returns_4,
		test_cbaxter_init_c_string_capacity_returns_5,

		test_cbaxter_compare_shorter_returns_negative,
		test_cbaxter_compare_longer_returns_positive,
		test_cbaxter_compare_same_returns_0,
		test_cbaxter_compare_lex_smaller_returns_negative,
		test_cbaxter_compare_lex_larger_returns_positive,
		
		test_cbaxter_push_capacity_returns_7,
		test_cbaxter_push_size_returns_5,
		test_cbaxter_push_pushes_e,
		test_cbaxter_push_resized_capacity_returns_14,
		test_cbaxter_push_resized_size_returns_8,

		test_cbaxter_pop_size_returns_3,
		test_cbaxter_pop_returns_FAILURE_when_size_0,

		test_cbaxter_at_returns_adress_of_e,

		test_cbaxter_c_str_appends_NULL,
		test_cbaxter_c_str_increases_capacity_if_full,

		test_cbaxter_concat_size_returns_15,

		test_cbaxter_item_assignment_makes_deep_copy,
		test_cbaxter_item_assignment_copies_string
	};

	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;
	
	for(i = 0; i < number_of_functions; i++)
	{
		if(tests[i](buffer, 500) == FAILURE)
		{
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else
		{
			printf("PASS: Test %d passed\n", i);
			printf("\t%s\n", buffer);
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count, number_of_functions);
	return 0;
}

