#include "my_string.h"
#include "generic_vector.h"
#include "multi.h"

typedef struct node Node;
struct node {
	MY_STRING hKey;
	GENERIC_VECTOR hVector;
	Node* pLeft;
	Node* pRight;
	int height;
};

Status avl_insert(Node** ppRoot, MY_STRING hKey, MY_STRING hWord);

Status avl_new_node(Node** ppNode, MY_STRING hKey, MY_STRING hWord);

void avl_print_inorder(Node* pRoot);

void avl_update_height(Node* pNode);

int avl_height(Node* pNode);

int avl_balance_factor(Node* pNode);

Node* avl_left_rotate(Node* pNode);

Node* avl_right_rotate(Node* pNode);

void avl_destroy(Node** ppNode);

Node* get_largest_node(Node* pRoot);

void get_largest_recursive(Node* pNode, int* max, Node** ppMaxNode);
