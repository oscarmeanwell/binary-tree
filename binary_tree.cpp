#include "binary_tree.h"
#include <sstream>

using namespace std;
string strtmp = "";

//Find the smallest node in the tree
node* getSmallestNode(node* tree){
  while(tree->left != NULL) tree = tree->left;
  return tree;
}

//Find if an integer is in the tree
bool treeSearch(node *tree, int value)
{
	if (tree == NULL)
		return false;
	
	else if (tree->data == value)
		return true;
	
	else if (value < tree->data)
		return treeSearch(tree->left, value);
	else
		return treeSearch(tree->right, value);
}

//Remove an item from the tree if it exists in the tree
struct node* recremove(node *&tree, int value)
{
	//If no tree or if the value isnt in the tree, break.
	if (tree == NULL || !treeSearch(tree, value))
		return tree;
	
	//Traverse the tree until node is found
	else if (value < tree->data) 
		tree->left = recremove(tree->left, value);
	else if (value > tree->data)
		tree->right = recremove(tree->right, value);
	else
	{
		//Node has no Children
		if (tree->left == NULL && tree->right == NULL)
		{
			delete tree;
			tree = NULL;
		}
		//Node has one child
		else if (tree->left == NULL)
		{
			struct node *temp = tree;
			tree = tree->right;
			delete temp;
		}
		else if (tree->right == NULL)
		{
			struct node *temp = tree;
			tree = tree->left;
			delete temp;
		}
		else{
			 struct node *temp = getSmallestNode(tree->right);
			 tree->data = temp->data;
			 tree->right = recremove(tree->right, temp->data);
		}
	}
	return tree;
}


//Traverse the tree in order
string recinorder(node *tree)
{
	if (tree != NULL)
	{
		recinorder(tree->left);
		strtmp += to_string(tree->data) + " ";
		recinorder(tree->right);
	}
	
	return strtmp;
}

//Traverse the tree in post order
string recpostorder(node *tree)
{
	if (tree != NULL)
	{
		recpostorder(tree->left);
		recpostorder(tree->right);	
		strtmp += to_string(tree->data) + " ";
	}
	
	return strtmp;
}


//Traverse the tree in order
string recpreorder(node *tree)
{
	if (tree != NULL)
	{
	    strtmp += to_string(tree->data) + " ";
		recpreorder(tree->left);
		recpreorder(tree->right);
	}
	
	return strtmp;
}

//Insert an item into the tree
void treeInsert(node **tree, int item)
{
	//if item already exists in tree dont add
	if (!treeSearch(*tree, item))
	{
		if (*tree == NULL)
		{
			(*tree) = new node;
			(*tree)->data = item;	
			return;
		}
		else if (item < (*tree)->data)
			treeInsert((&(*tree)->left), item);
		else
			treeInsert((&(*tree)->right), item);
	}
}

//Create an empty binary tree
binary_tree::binary_tree()
{
	node *tree = new node;
}

//Insert an item into the tree
binary_tree::binary_tree(int value)
{
	treeInsert(&tree, value);
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values)
{
	for (int i = 0; i < values.size(); i++)
		treeInsert(&tree, values[i]);
}

// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs)
{
	strtmp = "";
	stringstream ss(recinorder(rhs.tree));
	int temp;
	while (ss >> temp)
		treeInsert(&tree, temp);
	
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree()
{
    delete tree;
}


// Adds a value to the tree
void binary_tree::insert(int value)
{
	treeInsert(&tree, value);
}

// Removes a value from the tree
void binary_tree::remove(int value)
{
	recremove(tree, value);
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const
{
    return treeSearch(tree, value);
}

// Prints the tree to standard out in numerical order
std::string binary_tree::inorder() const
{
	strtmp = "";
	string x = recinorder(tree);
    return (x.substr(0, (x.size()-1)));

}

// Prints the tree in pre-order
std::string binary_tree::preorder() const
{
	strtmp = "";
	string z = recpreorder(tree);
    return (z.substr(0, (z.size()-1)));
}

// Prints the tree in post-order
std::string binary_tree::postorder() const
{
	strtmp = "";
	string x = recpostorder(tree);
	
    return (x.substr(0, (x.size()-1)));
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other)
{	
	return binary_tree(other);
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
	strtmp = "";
	string x = recinorder(tree);
	strtmp = "";
	string y = recinorder(other.tree);
	if (x == y)
		return true;
	else
		return false;
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
	strtmp = "";
	string x = recinorder(tree);
	strtmp = "";
	string y = recinorder(other.tree);
	if (x != y)
		return true;
	else
		return false;
    return true;
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value)
{
	treeInsert(&tree, value);
    return binary_tree();
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value)
{
	recremove(tree, value);
    return binary_tree();
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value)
{
	int temp;
	while (in >> temp)
		treeInsert(&value.tree, temp);
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value)
{
	strtmp = "";
	string x = recinorder(value.tree);
	return (out << x.substr(0, (x.size()-1)));
}
