#include <stdio.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	
	if(hString == NULL)
	{
		strncpy(buffer, "test_init_default_returns_nonNULL\n""my_string_init_default returns NULL", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_size(hString) != 0)
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n""Did not receive 0 from get_size after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_init_default_capacity_returns_7(char* buffer, int length){
	const int expected = 7;
	int capacity;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();
	capacity = my_string_get_capacity(hString);
	
	if(capacity != expected){
		status = FAILURE;
		printf("Expected a capacity of %d, but got %d\n", expected, capacity);
		strncpy(buffer, "test_cbaxter_init_default_capcity_returns_7\n""Did not receive 7 from get_capacity after init_default\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_init_default_capcity_returns_7\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_destroy_handle_is_NULL(char* buffer, int length){
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	my_string_destroy(&hString);

	if (hString != NULL){
		status = FAILURE;
		strncpy(buffer, "test_cbaxter_destroy_handle_is_NULL\n""destroy did not make the handle NULL\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_destroy_handle_is_NULL\n", length);
	}
	return status;
}

Status test_cbaxter_init_c_string_returns_nonNULL(char* buffer, int length){
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("four");
	
	if(hString == NULL){
		status = FAILURE;
		strncpy(buffer, "test_init_c_string_returns_nonNULL\n""my_string_init_c_string returns NULL", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_init_c_string_returns_nonNULL\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_init_c_string_size_returns_4(char* buffer, int length){
	const int expected = 4;
	int size;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("four");
	size = my_string_get_size(hString);
	
	if(size != expected){
		status = FAILURE;
		printf("Expected a size of %d, but got %d\n", expected, size);
		strncpy(buffer, "test_cbaxter_init_c_string_size_returns_4\n""Did not receive 4 from get_size after init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_init_c_string_size_returns_4\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_init_c_string_capacity_returns_5(char* buffer, int length){
	const int expected = 5;
	int capacity;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("four");
	capacity = my_string_get_capacity(hString);
	
	if(capacity != expected){
		status = FAILURE;
		printf("Expected a capacity of %d, but got %d\n", expected, capacity);
		strncpy(buffer, "test_cbaxter_init_c_string_capacity_returns_5\n""Did not receive 5 from get_capacity after init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_init_c_string_capacity_returns_5\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_compare_shorter_returns_negative(char* buffer, int length){
	int comparison;
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_string("A");
	hString2 = my_string_init_c_string("AB");

	comparison = my_string_compare(hString1, hString2);

	if (comparison >= 0){
		status = FAILURE;
		printf("Expected a negative comparison, got %d instead", comparison);
		strncpy(buffer, "test_cbaxter_compare_shorter_returns_negative\n""Did not receive a nagative value from compare after shorter string entered first\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_compare_shorter_returns_negative\n", length);
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_cbaxter_compare_longer_returns_positive(char* buffer, int length){
	int comparison;
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_string("AB");
	hString2 = my_string_init_c_string("A");

	comparison = my_string_compare(hString1, hString2);

	if (comparison <= 0){
		status = FAILURE;
		printf("Expected a positive comparison, got %d instead", comparison);
		strncpy(buffer, "test_cbaxter_compare_longer_returns_positive\n""Did not receive a positive value from compare after longer string entered first\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_compare_longer_returns_positive\n", length);
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_cbaxter_compare_same_returns_0(char* buffer, int length){
	int comparison;
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_string("AB");
	hString2 = my_string_init_c_string("AB");

	comparison = my_string_compare(hString1, hString2);

	if (comparison != 0){
		status = FAILURE;
		printf("Expected comparison to return 0, got %d instead", comparison);
		strncpy(buffer, "test_cbaxter_compare_same_returns_0\n""Did not receive 0 from compare after the same string entered twice\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_compare_same_returns_0\n", length);
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_cbaxter_compare_lex_smaller_returns_negative(char* buffer, int length){
	int comparison;
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_string("A");
	hString2 = my_string_init_c_string("B");

	comparison = my_string_compare(hString1, hString2);

	if (comparison >= 0){
		status = FAILURE;
		printf("Expected a negative comparison, got %d instead", comparison);
		strncpy(buffer, "test_cbaxter_compare_lex_smaller_returns_negative\n""Did not receive a nagative value from compare after lexigraphically smaller string entered first\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_compare_lex_smaller_returns_negative\n", length);
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_cbaxter_compare_lex_larger_returns_positive(char* buffer, int length){
	int comparison;
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_string("B");
	hString2 = my_string_init_c_string("A");

	comparison = my_string_compare(hString1, hString2);

	if (comparison <= 0){
		status = FAILURE;
		printf("Expected a positive comparison, got %d instead", comparison);
		strncpy(buffer, "test_cbaxter_compare_lex_larger_returns_positive\n""Did not receive a positive value from compare after lexigraphically larger string entered first\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_compare_lex_larger_returns_positive\n", length);
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_cbaxter_push_capacity_returns_7(char* buffer, int length){
	const int expected = 7;
	int capacity;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("123456");
	my_string_push_back(hString, '7');

	capacity = my_string_get_capacity(hString);
	
	if(capacity != expected){
		status = FAILURE;
		printf("Expected a capacity of %d, but got %d\n", expected, capacity);
		strncpy(buffer, "test_cbaxter_push_capacity_returns_7\n""Did not receive 7 from get_capacity after push\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_push_capacity_returns_7\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_push_size_returns_5(char* buffer, int length){
	const int expected = 5;
	int size;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("four");
	my_string_push_back(hString, 's');

	size = my_string_get_size(hString);
	
	if(size != expected){
		status = FAILURE;
		printf("Expected a size of %d, but got %d\n", expected, size);
		strncpy(buffer, "test_cbaxter_push_size_returns_5\n""Did not receive 5 from get_size after push\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_push_size_returns_5\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_push_pushes_e(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	char c;

	hString = my_string_init_c_string("abcd");
	my_string_push_back(hString, 'e');
	c = *my_string_at(hString, 4);

	if (c != 'e') {
		status = FAILURE;
		printf("Expected the character 'e', got '%c' instead\n", c);
		strncpy(buffer, "test_cbaxter_push_pushes_e\n""Did not receive 'e' from string_at after push\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_push_pushes_e\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_push_resized_capacity_returns_14(char* buffer, int length){
	const int expected = 14;
	int capacity;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("sevena");
	my_string_push_back(hString, 'b');
	my_string_push_back(hString, 'c');

	capacity = my_string_get_capacity(hString);
	
	if(capacity != expected){
		status = FAILURE;
		printf("Expected a capacity of %d, but got %d\n", expected, capacity);
		strncpy(buffer, "test_cbaxter_push_resized_capacity_returns_14\n""Did not receive 14 from get_capacity after push resize\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_push_resized_capacity_returns_14\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_push_resized_size_returns_8(char* buffer, int length){
	const int expected = 8;
	int size;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("sevenab");
	my_string_push_back(hString, 'c');

	size = my_string_get_size(hString);
	
	if(size != expected){
		status = FAILURE;
		printf("Expected a size of %d, but got %d\n", expected, size);
		strncpy(buffer, "test_cbaxter_push_resized_size_returns_8\n""Did not receive 8 from get_size after push resize\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_push_resized_size_returns_8\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_pop_size_returns_3(char* buffer, int length){
	const int expected = 3;
	int size;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("four");
	my_string_pop_back(hString);

	size = my_string_get_size(hString);
	
	if(size != expected){
		status = FAILURE;
		printf("Expected a size of %d, but got %d\n", expected, size);
		strncpy(buffer, "test_cbaxter_pop_size_returns_3\n""Did not receive 3 from get_size after pop\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_pop_size_returns_3\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_pop_returns_FAILURE_when_size_0(char* buffer, int length){
	MY_STRING hString = NULL;
	Status status;
	
	hString = my_string_init_default();
		
	if(my_string_pop_back(hString)){
		status = FAILURE;
		printf("Pop back did not return FAILURE\n");
		strncpy(buffer, "test_cbaxter_pop_returns_FAILURE_when_size_0\n""pop_back did not return FAILURE when string object of size 0 entered\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_pop_returns_FAILURE_when_size_0\n",  length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_at_returns_adress_of_e(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	char c;

	hString = my_string_init_c_string("abcde");
	c = *my_string_at(hString, 4);

	if (c != 'e') {
		status = FAILURE;
		printf("Expected the character 'e', got '%c' instead\n", c);
		strncpy(buffer, "test_cbaxter_at_returns_adress_of_e\n""Did not receive 'e' from string_at\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_at_returns_adress_of_e\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_c_str_appends_NULL(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	char c;

	hString = my_string_init_default();
	my_string_push_back(hString, 'a');
	c = my_string_c_str(hString)[1];

	if (c != '\0') {
		status = FAILURE;
		printf("Expected the character NULL, got '%c' instead\n", c);
		strncpy(buffer, "test_cbaxter_c_str_appends_NULL\n""Did not receive NULL from string_at\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_c_str_appends_NULL\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_c_str_increases_capacity_if_full(char* buffer, int length) {
	const int expected = 7;
	int capacity;
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("hello");
	my_string_push_back(hString, 'a');
	my_string_c_str(hString);
	capacity = my_string_get_capacity(hString);

	if (capacity != expected) {
		status = FAILURE;
		printf("Expected capacity of %d, got %d instead\n", expected, capacity);
		strncpy(buffer, "test_cbaxter_c_str_increases_capacity_if_full\n""Did not get a capacity of 7 after converting to c string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_c_str_increases_capacity_if_full\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_cbaxter_concat_size_returns_15(char* buffer, int length)
{
        const int expected = 15;
    	int size;
        MY_STRING hString1 = NULL;
        MY_STRING hString2 = NULL;
        Status status;

        hString1 = my_string_init_c_string("abcdefghij");
        hString2 = my_string_init_c_string("klmno");

        my_string_concat(hString1, hString2);
        size = my_string_get_size(hString1);

        if (size != expected)
        {
            status = FAILURE;
            printf("Expected %d, recieved %d", expected, size);
            strncpy(buffer, "test_cbaxter_concat_size_return_15\n""expected get_size to return 15 after concat\n", length);
        }
        else
        {
            status = SUCCESS;
            strncpy(buffer, "test_cbaxter_concat_size_return_15\n", length);
        }
    
        my_string_destroy(&hString1);
        my_string_destroy(&hString2);
        return status;
}

Status test_cbaxter_item_assignment_makes_deep_copy(char* buffer, int length){
	MY_STRING hStrings[2] = { NULL };
	Status status;

	hStrings[0] = my_string_init_c_string("Test");
	my_string_assignment(hStrings + 1, hStrings[0]);

	if (hStrings == hStrings + 1){
		status = FAILURE;
		strncpy(buffer, "test_cbaxter_item_assignment_makes_deep_copy\n""The copied handle is storing the same adress as the original\n", length);	
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_cbaxter_item_assignment_makes_deep_copy\n", length);
	}
	my_string_destroy(hStrings);
	my_string_destroy(hStrings + 1);
	return status;
}

Status test_cbaxter_item_assignment_copies_string(char* buffer, int length) {
	MY_STRING hStrings[2] = { NULL };
	Status status = SUCCESS;
	int i;

	hStrings[0] = my_string_init_c_string("Test");

	my_string_assignment(hStrings + 1, hStrings[0]);

	for (i = 0; i < 4 && status; i++) {
		if (*my_string_at(hStrings[0], i) == *my_string_at(hStrings[1], i)) {
			status = SUCCESS;
		}
		else {
			status = FAILURE;
		}
	}

	my_string_destroy(hStrings);
	my_string_destroy(hStrings + 1);
	return status;
}
