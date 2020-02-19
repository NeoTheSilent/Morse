#include "Letters.h"

// Binary Search Tree Nodes
struct node
{
	// Our main information will be from the Letter class
	Letters key;
	struct node *left, *right;
};
struct node *newNode(Letters item)
{
	// Inserting an element into a binary search tree
	struct node *temp = new node;
	temp->key = item;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
struct node* insert(struct node* node, Letters key, int deep)
{
	// If the referenced node doesn't exist, create it with the key.
	if (node == NULL) {
		return newNode(key);
	}
	// If the new letter has a [.] in the next spot, we insert it to the left
	if (key.getMorse()[deep] == '.')
		node->left = insert(node->left, key, deep + 1);
	// Otherwise, if the new letter has a [_] in the next spot, we insert it to the right
	else if (key.getMorse()[deep] == '_')
		node->right = insert(node->right, key, deep + 1);

	// Then, we return the (pointer) node unchanged
	return node;
}
void inorder(struct node *root)
{
	if (root != NULL)
	{
		// We go in the In Order way, so Left, Root, Right. Every time we get the Root's info, 
		// we make sure to share all of the info regarding the Letter and the Morse Letter associated with it
		inorder(root->left);
		cout << "Letter: " << root->key.getCharacter() << endl << "Morse: " << root->key.getMorse() << endl << endl;
		inorder(root->right);
	}
}

struct node* letter_to_morse(struct node* root, char letter)
{
	// If the root exists
	if (root != NULL)
	{
		// We check to see if the character associated with the root is the letter we're searching for
		if (root->key.getCharacter() == letter) {
			// If it is, we return the Morse Letter and output.
			cout << root->key.getMorse();
			return root;
		}
		// Otherwise, we keep searching
		else {
			letter_to_morse(root->left, letter);
			letter_to_morse(root->right, letter);
		}
	}
}

struct node* morse_to_letter(struct node* root, string word)
{
	// If the root exists
	if (root != NULL)
	{
		// We check to see if the morse letter is the same as the morse word we're inputting
		if (root->key.getMorse() == word) {
			// If it is, we return the associated character
			cout << root->key.getCharacter();
			return root;
		}
		else {
			// Otherwise, we keep searching
			morse_to_letter(root->left, word);
			morse_to_letter(root->right, word);
		}
	}
}