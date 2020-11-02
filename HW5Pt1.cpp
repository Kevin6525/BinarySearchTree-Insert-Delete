#include <iostream>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <array>

using namespace std;
//Create BST Struct
struct BST
{
	char data;
	BST *left, *right;
};
//For creating a new BST struct
struct BST *newBST(char value)
{
	struct BST *temp = (struct BST *)malloc(sizeof(struct BST));
	temp->data = value;
	temp->left = NULL;
	temp->right = NULL;
}
//Insert function
BST* insert(BST* root, char value)
{
	//If inserting into empy BST node, create a new BST node with value
	if(root == NULL)
	{
		return newBST(value);
	}
	//If the char value is less than what the root value is, put it on the left side of the BST using recursion
	if(value < root->data)
	{
		root->left = insert(root->left, value);
	}
	//If the char value is greater than the root value, put it on the right side of the BST using recursion
	else
	{
		root->right = insert(root->right, value);
	}
	//Return the BST after insertion
	return root;
}
//Delete function
BST* deleteNode(BST* root, char value)
{
	//If deleting from empty, just return the BST
	if(root == NULL)
	{
		return root;
	}
	//If the value we're deleting is less than the root node value, we continue searching for the value to delete by using recursion down the left side of BST
	//Note: Left side has lower values than root node, right side has greater values
	if(value < root->data)
	{
		root->left = deleteNode(root->left, value);
	}
	//If the value we're trying to delete is greater than the root node value, we continue searching for the value by using recursion down the right side of the BST
	else if(value > root->data)
	{
		root->right = deleteNode(root->right, value);
	}
	//This is the case when we find the value we are trying to delete
	else
	{
		//If the left child is empty, then the right child takes the place of the deleted node
		if(root->left == NULL)
		{
			struct BST *temp = root->right;
			delete(root);
			return temp;
		}
		//If the right child is empty, then the left child takes the place of the deleted node
		else if(root->right == NULL)
		{
			struct BST *temp = root->left;
			delete(root);
			return temp;
		}
		//This is the case when the node has two children
		//We look for the smallest value in the right subtree to replace the node. 
		//The smallest in the right subtree is also the value that is next in line if we arrange the values in increasing order
		struct BST *temp = root->right;
		//This while loop finds the left most value in the right subtree, which is the smallest value in that subtree
		while(temp!= NULL && temp->left != NULL)
		{
			temp = temp->left;
		}
		root->data = temp->data;
		root->right = deleteNode(root->right, temp->data);
	}
	//Return the BST
	return root;
}
//Provided by textbook
void print(const BST* node, int depth) { //Print function used in textbook
	cout << setw(4 * depth) << "";
	if (node == NULL)
		cout << "[EMPTY]" << endl;
	else if (node->right == NULL && node->left == NULL) {
		cout << node->data;
		cout << " [LEAF]" << endl;
	}
	else {
		cout <<  node->data;
		cout << endl;
		print(node->right, depth + 1);
		print(node->left, depth + 1);
	}
}
int main()
{
	//We use arrays to simplify the process in main function
	struct BST *root = NULL;
	char array[] = {'S', 'F', 'E', 'V', 'D', 'U', 'J', 'P', 'O', 'T'};
	for(int i = 0; i < sizeof(array); i ++)
	{
		root = insert(root, array[i]);
		cout<<"Inserting: "<<array[i]<<endl;
		print(root, 0);
	}
	cout<<"Made it out insert"<<endl;
	for(int i = 0; i < sizeof(array); i ++)
	{
		root = deleteNode(root, array[i]);
		cout<<"Deleting: "<<array[i]<<endl;
		print(root, 0);
	}
}
