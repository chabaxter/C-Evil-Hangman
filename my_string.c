#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

typedef struct my_string My_string;

struct my_string {
	int size;
	int capacity;
	char* data;
};

MY_STRING my_string_init_default(void) {
	My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
	if (pMy_string != NULL) {
		pMy_string->capacity = 7;
		pMy_string->size = 0;
		pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
		if (pMy_string->data == NULL) {
			free(pMy_string); pMy_string = NULL;
			return NULL;
		}
	}
	return (MY_STRING)pMy_string;
}

void my_string_destroy(ITEM* phItem) {
	My_string* pMy_string = (My_string*)*phItem;
	if (pMy_string != NULL && pMy_string->data != NULL) {
		free(pMy_string->data);
		free(pMy_string);
	}
	*phItem = NULL;
}

MY_STRING my_string_init_c_string(const char* c_string) {
	My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
	int i = 0;
	char c;

	if (pMy_string != NULL) {
		c = c_string[i];
		for (i = 1; c != '\0'; i++) {
			c = c_string[i];
		}
		pMy_string->data = (char*)malloc(sizeof(char) * i);
		if (pMy_string->data == NULL) {
			free(pMy_string); pMy_string = NULL;
			return NULL;
		}
		pMy_string->capacity = i;
		pMy_string->size = i - 1;
		for (i = 0; i < pMy_string->capacity; i++) {
			pMy_string->data[i] = c_string[i];
		}
	}

	return (MY_STRING)pMy_string;
}

int my_string_get_capacity(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;

	int i = 0;

	int max = pLeft_string->size > pRight_string->size ? pLeft_string->size : pRight_string->size;

	while (i < max)
	{
		if (i > pRight_string->size) 
			return 1;

		if (i > pLeft_string->size) 
			return -1;

		if (pLeft_string->data[i] < pRight_string->data[i]) 
			return -1;

		else if (pLeft_string->data[i] > pRight_string->data[i]) 
			return 1;

		i++;
	}

	return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
	My_string* pMy_string = (My_string*)hMy_string;

	int noc;
	char c;

	if (pMy_string == NULL)
		return FAILURE;

	pMy_string->size = 0;

	fscanf(fp, " ");
	noc = fscanf(fp, "%c", &c);

	if (noc == EOF) return FAILURE;

	while (noc == 1 && c != ' ' && c != '\n') {
		my_string_push_back(hMy_string, c);
		noc = fscanf(fp, "%c", &c);
	}

	if (noc != 1 && noc != EOF)
		return FAILURE;

	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
	My_string* pMy_string = (My_string*)hMy_string;
	int i = 0;
	if (fp != NULL) {
		while (i < pMy_string->size) {
			fprintf(fp, "%c", pMy_string->data[i]);
			i++;
		}
		return SUCCESS;
	}
	return FAILURE;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
	My_string* pMy_string = (My_string*)hMy_string;
	int i;


	if (pMy_string->size >= pMy_string->capacity) {
		pMy_string->capacity += 7;
		char* temp = (char*)malloc(sizeof(char) * pMy_string->capacity);
		if (temp == NULL) {
			pMy_string->capacity -= 7;
			return FAILURE;
		}
		for (i = 0; i < pMy_string->size; i++) {
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
	}

	pMy_string->data[pMy_string->size] = item;
	pMy_string->size++;
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;

	if (pMy_string->size == 0) {
		return FAILURE;
	}

	pMy_string->size--;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index) {
	My_string* pMy_string = (My_string*)hMy_string;
	if (index < pMy_string->size && index >= 0)
		return &(pMy_string->data[index]);
	return NULL;
}

char* my_string_c_str(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	int i;
	char* temp;

	if (pMy_string->size == pMy_string->capacity) {
		pMy_string->capacity += 1;
		temp = (char*)malloc(sizeof(char) * pMy_string->capacity);
		if (temp == NULL) {
			return NULL;
		}
		for (i = 0; i < pMy_string->size; i++) {
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
	}
	pMy_string->data[pMy_string->size] = '\0';

	return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
	My_string* pResult = (My_string*)hResult;
	My_string* pAppend = (My_string*)hAppend;
	int a = 0, r = 0, i;
	char* temp;

	if (pResult->size + pAppend->size >= pResult->capacity) {
		temp = (char*)malloc(sizeof(char) * (pResult->capacity + (pAppend->size * 3)));
		if (temp == NULL) {
			return FAILURE;
		}
		for (i = 0; i < pResult->capacity; i++) {
			temp[i] = pResult->data[i];
		}
		free(pResult->data);
		pResult->data = temp;
		pResult->capacity = (pResult->capacity + (pAppend->size * 3));
	}

	r = pResult->size;
	while (a < (pAppend->size + 1)) {
		pResult->data[r] = pAppend->data[a];

		a++;
		r++;
	}
	pResult->size += pAppend->size;

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->size <= 0;
}

Status my_string_assignment(ITEM* phItemLeft, ITEM hItemRight) {
	My_string* pLeft = (My_string*)*phItemLeft;
	My_string* pRight = (My_string*)hItemRight;
	int i;

	if (pLeft == NULL) pLeft = (My_string*)my_string_init_default();

	if (pLeft == NULL) return FAILURE;

	if (pRight == NULL) return FAILURE;

	if (pLeft->size < pRight->size) //make sure we have room
	{
		free(pLeft->data);
		pLeft->capacity = pRight->size;
		pLeft->data = (char*)malloc(sizeof(char) * pLeft->capacity);
	}

	pLeft->size = pRight->size;  //adjust size

	for (i = 0; i < pLeft->size; i++) //copy data
		pLeft->data[i] = pRight->data[i];

	*phItemLeft = pLeft;

	return SUCCESS;
}