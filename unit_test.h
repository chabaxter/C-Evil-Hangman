#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_cbaxter_init_default_capacity_returns_7(char* buffer, int length);

Status test_cbaxter_destroy_handle_is_NULL(char* buffer, int length);

Status test_cbaxter_init_c_string_returns_nonNULL(char* buffer, int length);
Status test_cbaxter_init_c_string_size_returns_4(char* buffer, int length);
Status test_cbaxter_init_c_string_capacity_returns_5(char*buffer, int length);

Status test_cbaxter_compare_shorter_returns_negative(char* buffer, int length);
Status test_cbaxter_compare_longer_returns_positive(char* buffer, int length);
Status test_cbaxter_compare_same_returns_0(char* buffer, int length);
Status test_cbaxter_compare_lex_smaller_returns_negative(char* buffer, int length);
Status test_cbaxter_compare_lex_larger_returns_positive(char* buffer, int length);

Status test_cbaxter_push_capacity_returns_7(char* buffer, int length);
Status test_cbaxter_push_size_returns_5(char* buffer, int length);
Status test_cbaxter_push_pushes_e(char* buffer, int length);
Status test_cbaxter_push_resized_capacity_returns_14(char* buffer, int length);
Status test_cbaxter_push_resized_size_returns_8(char* buffer, int length);

Status test_cbaxter_pop_size_returns_3(char* buffer, int length);
Status test_cbaxter_pop_returns_FAILURE_when_size_0(char* buffer, int length);

Status test_cbaxter_at_returns_adress_of_e(char* buffer, int length);

Status test_cbaxter_c_str_appends_NULL(char* buffer, int length);
Status test_cbaxter_c_str_increases_capacity_if_full(char* buffer, int length);

Status test_cbaxter_concat_size_returns_15(char* buffer, int length);

Status test_cbaxter_item_assignment_makes_deep_copy(char* buffer, int length);
Status test_cbaxter_item_assignment_copies_string(char* buffer, int length);

#endif
