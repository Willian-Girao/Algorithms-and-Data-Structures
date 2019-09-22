#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SPACECOUNT 6

typedef struct nodes {
	int data;
	struct nodes *left;
	struct nodes *right;
	int h;
	int q;
} node;

node* newNode(int data) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->h = 1;
	newNode->q = 0;

	return newNode;
}

/* Max between two values */
int max(int a, int b) {
	return (a > b)? a : b;
}

/* Returns the height of a node */
int height(node* root) {
	if (root == NULL) {
		return 0;
	}
	return root->h;
}

/* Checks wether some rotation needs to be done */
int checkUnbalanced(node* root) {
	if (root == NULL) {
		return 0;
	}
	return (height(root->right) - height(root->left));
}

/* 
Perform a simple left rotation when:
	- Balance factor (q) is bigger than 1
	- Root of right sub-tree has q >= 0
*/
node* leftRotation(node* root) {
	node *A = root->right->left; /* Save left sub-tree of new root */
	node *O = root; /* Save old root */
	node *N = root->right; /* Right child of old root is the new root */
	N->left = O; /* Old root becomes the new root's left child */
	O->right = A; /* Old root's right child receives lef child of it's previous right node */

	/* Resets altered nodes heights */
	N->h = 0;
	O->h = 0;

	/* Update altered nodes heights */
	N->h = 1 + max(height(N->left), height(N->right));
	O->h = 1 + max(height(O->left), height(O->right));

	/* Update alted nodes balance factors */
	N->q = checkUnbalanced(N);
	O->q = checkUnbalanced(O);

	return N;
}

/* 
Perform a simple right rotation when:
	- Balance factor (q) is smaller than -1
	- Root of left sub-tree has q <= 0
*/
node* rightRotation(node* root) {
	node *A = root->left->right; /* Save right sub-tree of new root */
	node *O = root; /* Save old root */
	node *N = root->left; /* Left child of old root is the new root */
	N->right = O; /* Old root becomes the new root's right child */
	O->left = A; /* Old root's left child receives right child of it's previous left node */

	/* Resets altered nodes heights */
	N->h = 0;
	O->h = 0;

	/* Update altered nodes heights */
	N->h = 1 + max(height(N->left), height(N->right));
	O->h = 1 + max(height(O->left), height(O->right));

	/* Update alted nodes balance factors */
	N->q = checkUnbalanced(N);
	O->q = checkUnbalanced(O);

	return N;
}

/*
Perform double left rotation when:
	- Balance factor (above 1) of root is positive
	- Balance factor of root's right child is negative
*/
node* doubleLeftRotation(node* root) {
	/* right rotation on the root's right sub-tree */
	node *rightRot = rightRotation(root->right);
	root->right = rightRot;

	/* left rotation on the whole tree */
	return leftRotation(root);
}

/*
Perform double right rotation when:
	- Balance factor (above 1) of root is negative
	- Balance factor of root's left child is positive
*/
node* doubleRightRotation(node* root) {
	/* left rotation on the root's left sub-tree */
	node *leftRot = leftRotation(root->left);
	root->left = leftRot;

	/* right rotation on the whole */
	return rightRotation(root);
}

/* Insert function to add node to the tree */
node* insert(int data, node* root) {

	/* base case for when we find a null node */
	if (root == NULL) {
		return newNode(data);
	}

	/* decide where to go in the tree */
	if (data < root->data) {
		root->left = insert(data, root->left);
	} else {
		root->right = insert(data, root->right);
	}

	/* update's current node's (recursive call) height */
	root->h = 1 + max(height(root->left), height(root->right));
	root->q = checkUnbalanced(root);

	/* perform rotations (if needed) */
	if (root->q > 1) {
		if (root->right->q >= 0) {
			return leftRotation(root);
		}
		if (root->right->q < 0) {
			return doubleLeftRotation(root);
		}
	}
	if (root->q < -1) {
		if (root->left->q <= 0) {
			return rightRotation(root);
		}
		if (root->left->q > 0) {
			return doubleRightRotation(root);
		}
	}
	
	/* return root */
	return root;
}

node* deletingRootAux(node* root, node* father) {
	if (root == NULL) {
		return father;
	}

	deletingRootAux(root->left, root);
}

node* getBiggestOfTheSmallest(node* root, node* father) {
	if (root == NULL) {
		return father;
	}

	getBiggestOfTheSmallest(root->right, root);
}

/* Delete if a node is in the tree */
node* delete(int x, node* root) {
	if (root == NULL) { /* Check for empty tree/inexisting value case */
		printf("Status: inexisting data to be removed.\n");
		return NULL;
	}

	if (root->data == x) { /* Data to be removed is the root of the original tree */
		if (root->left != NULL && root->right != NULL) { /* Root has two children */
			node *newRoot = getBiggestOfTheSmallest(root->left, root); /* Gets the "biggest of the smallest" */
			root->data = newRoot->data; /* Make it the new root */
			root->left = delete(newRoot->data, root->left); /* Update left subtree */

			printf("Status: data successfully removed.\n");

		} else { /* Root has one or zero child */
			node *aux = root->left ? root->left : root->right;
			if (aux == NULL) {
				root = NULL; /* No value to be replaced */
			} else {
				root = aux; /* Existing child replaces current root */
			}
		}
	} else if (x < root->data) { /* Value to be remove ain't the original tree's root */
		root->left = delete(x, root->left);
	} else {
		root->right = delete(x, root->right);
	}

	if (root == NULL) { /* Catching the case of non-existing children */
		return NULL;
	}

	/* update's current node's (recursive call) height */
	root->h = 1 + max(height(root->left), height(root->right));
	root->q = checkUnbalanced(root);

	/* perform rotations (if needed) */
	if (root->q > 1) {
		if (root->right->q >= 0) {
			return leftRotation(root);
		}
		if (root->right->q < 0) {
			return doubleLeftRotation(root);
		}
	}
	if (root->q < -1) {
		if (root->left->q <= 0) {
			return rightRotation(root);
		}
		if (root->left->q > 0) {
			return doubleRightRotation(root);
		}
	}

	return root;
}

/* Find if a node is in the tree */
node* search(int x, node* root) {
	if (root == NULL) {
		return NULL;
	}

	node *aux = NULL;

	if (root->data == x) {
		return root;
	} else if (x < root->data) {
		aux = search(x, root->left);
	} else if (x > root->data) {
		aux = search(x, root->right);
	} else {
		return NULL;
	}

	return aux;
}

/* Prints the entire tree in a horizontal manner */
void prettyPrint(node* root, int space) {
	space += SPACECOUNT;
	/* Checks if tree is empty */
	if (root == NULL) {
		for (int i = SPACECOUNT; i < space; ++i)	{
			printf(" ");
		}
		printf("null\n");
		return;
	}

	/* Processing right hand children */
	prettyPrint(root->right, space);

	/* Print current node */
	for (int i = SPACECOUNT; i < space; ++i)	{
		printf(" ");
	}
	printf("%d-{ \n", root->data);

	/* Processing left hand children */
	prettyPrint(root->left, space);
}

/* Prints the entire tree in a horizontal manner */
int prettyPrint2(node* root, int space, int line, int j) {
	/* Checks if tree is empty */
	if (root == NULL) {
		return line;
	}

	space += SPACECOUNT;
	j += 2;

	/* Processing right hand children */
	printf("\n");
	printf("\n");
	line += 2;
	prettyPrint2(root->right, (space+(6*root->h))-j, line, j);
	printf("\033[2A"); // Move up X lines;
	printf("\033[2D"); // Move left X column;

	/* Print current node */
	for (int i = SPACECOUNT; i < space; ++i)	{
		printf(" ");
	}
	printf("%d", root->data);

	/* Processing left hand children */
	printf("\n");
	printf("\n");
	line += 2;
	prettyPrint2(root->left, (space-(12*root->h))+j, line, j);
	printf("\033[2A"); // Move up X lines;
	printf("\033[2D"); // Move left X column;

	return line;
}

void menu(node* root) {
	int action = -1;
	int x = -1;
	node *find = NULL;
	while (action != 0) {
		printf("[ 1 ] Print tree.			[ 2 ] Delete data.\n");
		printf("[ 3 ] Query data.			[ 4 ] Insert data.\n");
		printf("[ 5 ] Exit.\n");
		printf("\n");
		printf("Select action: ");
		scanf("%d", &action);

		switch (action) {
			case 1:
		      prettyPrint(root, 5);
		      break;
		    case 2:
		      printf("Key to be deleted: ");
			  scanf("%d", &x);
		      delete(x, root);
		      break;
		    case 3:
		      printf("Key to be find: ");
			  scanf("%d", &x);
		      find = search(x, root);
			  if (find != NULL) {
			  	printf("\n");
				printf("Data found.\n");
				printf("Key: %d\n", find->data);
				printf("Height: %d\n", find->h);
				printf("\n");
			  } else {
				printf("\n");
				printf("Data NOT found\n");
				printf("\n");
			  }
		      break;
		    case 4:
		      printf("Key to be inserted: ");
			  scanf("%d", &x);
			  root = insert(x, root);
		      break;
		    case 5:
		      action = 0;
		      break;
		    default :
		      printf("Invalid invalid input.\n");
		}
		printf("\n\n");
	}

}


int main () {

	node *root = newNode(10);
	root = insert(13, root);
	root = insert(8, root);
	root = insert(15, root);
	root = insert(9, root);
	root = insert(14, root);
	root = insert(20, root);
	root = insert(12, root);
	root = insert(24, root);
	root = insert(7, root);
	root = insert(6, root);
	root = insert(5, root);

	menu(root);

	return 0;
}
