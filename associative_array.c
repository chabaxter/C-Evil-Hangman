#include <stdio.h>
#include <stdlib.h>
#include "associative_array.h"
#include "multi.h"
#include "my_string.h"
#include "generic_vector.h"


Status avl_insert(Node** ppNode, MY_STRING hKey, MY_STRING hWord) {
	int balanceFactor;
	int comparison;

	if (*ppNode == NULL) {	//	Check if this node exists yet
		return avl_new_node(ppNode, hKey, hWord);

	}

	comparison = my_string_compare(hKey, (*ppNode)->hKey);

	if (comparison < 0) {	//	Check if the new values key is smaller
		if (!avl_insert(&((*ppNode)->pLeft), hKey, hWord)) return FAILURE;
	}
	else if (comparison > 0) {	//	Check if the new values key is larger
		if (!avl_insert(&((*ppNode)->pRight), hKey, hWord)) return FAILURE;
	}
	else {
		generic_vector_push_back((*ppNode)->hVector, hWord);
		return SUCCESS;	//	If the keys are equal, do not do anything
	}

	avl_update_height(*ppNode);

	balanceFactor = avl_balance_factor(*ppNode);

	if (balanceFactor > 1) {
		if (avl_balance_factor((*ppNode)->pLeft) > 0) {	//	Left Heavy
			(*ppNode) = avl_right_rotate(*ppNode);
		}
		else if (avl_balance_factor((*ppNode)->pLeft) < 0) {	//	Left-Right
			(*ppNode)->pLeft = avl_left_rotate((*ppNode)->pLeft);
			(*ppNode) = avl_right_rotate(*ppNode);
		}
	}
	else if (balanceFactor < -1) {
		if (avl_balance_factor((*ppNode)->pRight) > 0) {	//	Right-Left
			(*ppNode)->pRight = avl_right_rotate((*ppNode)->pRight);
			(*ppNode) = avl_left_rotate(*ppNode);
		}
		else if (avl_balance_factor((*ppNode)->pRight) < 0) {	//	Right Heavy
			(*ppNode) = avl_left_rotate(*ppNode);
		}
	}
	return SUCCESS;
}

Status avl_new_node(Node** ppNode, MY_STRING hKey, MY_STRING hWord) {
	*ppNode = (Node*)malloc(sizeof(Node));
	if (*ppNode == NULL) return FAILURE;

	(*ppNode)->hKey = my_string_init_default();
	my_string_assignment(&((*ppNode)->hKey), hKey);

	(*ppNode)->hVector = generic_vector_init_default(my_string_assignment, my_string_destroy);
	generic_vector_push_back((*ppNode)->hVector, hWord);

	(*ppNode)->pLeft = NULL;
	(*ppNode)->pRight = NULL;
	(*ppNode)->height = 1;

	return SUCCESS;
}

void avl_print_inorder(Node* pRoot) {
	if (pRoot != NULL) {
		avl_print_inorder(pRoot->pLeft);
		my_string_insertion(pRoot->hKey, stdout); printf(" :%d\n", generic_vector_get_size(pRoot->hVector));
		avl_print_inorder(pRoot->pRight);
	}
}

void avl_update_height(Node* pNode) {
	pNode->height = (avl_height(pNode->pLeft) > avl_height(pNode->pRight)) ? avl_height(pNode->pLeft) : avl_height(pNode->pRight);
	pNode->height++;
}

int avl_height(Node* pNode) {
	if (pNode == NULL)
		return 0;
	else
		return pNode->height;
}

int avl_balance_factor(Node* pNode) {
	if (pNode == NULL) return 0;
	return avl_height(pNode->pLeft) - avl_height(pNode->pRight);
}

Node* avl_left_rotate(Node* pNode) {
	Node* pY = pNode->pRight;
	Node* pY_leaf;

	pY_leaf = (NULL == pY->pLeft) ? NULL : pY->pLeft;

	pY->pLeft = pNode;
	pNode->pRight = pY_leaf;

	avl_update_height(pNode);
	avl_update_height(pY);

	return pY;
}

Node* avl_right_rotate(Node* pNode) {
	Node* pX = pNode->pLeft;
	Node* pX_leaf;

	pX_leaf = (NULL == pX->pRight) ? NULL : pX->pRight;

	pX->pRight = pNode;
	pNode->pLeft = pX_leaf;

	avl_update_height(pNode);
	avl_update_height(pX);

	return pX;
}

void avl_destroy(Node** ppNode) {
	while (*ppNode != NULL) {
		avl_destroy(&(*ppNode)->pLeft);
		avl_destroy(&(*ppNode)->pRight);
		my_string_destroy(&(*ppNode)->hKey);
		generic_vector_destroy(&((*ppNode)->hVector));
		free(*ppNode); *ppNode = NULL;
	}
}

Node* get_largest_node(Node* pRoot) {
	int maxSize = 0;

	Node* pMaxNode = NULL;

	if (pRoot == NULL) return NULL;
	get_largest_recursive(pRoot, &maxSize, &pMaxNode);
	return pMaxNode;
}

void get_largest_recursive(Node* pNode, int* max, Node** ppMaxNode) {
	if (pNode != NULL) {
		int size = generic_vector_get_size(pNode->hVector);
		if (*max < size) {
			*max = size;
			*ppMaxNode = pNode;
		}
		get_largest_recursive(pNode->pLeft, max, ppMaxNode);
		get_largest_recursive(pNode->pRight, max, ppMaxNode);
	}
}
