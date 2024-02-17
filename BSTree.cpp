/*
 * Filename: BSTree.cpp
 * Contains: Implementation of Naive Binary Search Trees 
 */

#include <iostream>

#include "BSTree.h"
#include "pretty_print.h"

using namespace std;

/*******************************
 * BEGIN PUBLIC BSTREE SECTION *
 *******************************/

/*
 * The BSTree constructors use intializer lists. They are complete and you
 *  should not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
BSTree::BSTree() : root(new BSTNode()) {}

BSTree::BSTree(const BSTree &source)
    : root(new BSTNode(*source.root)) {}

BSTree::~BSTree()
{
    delete this->root;
}

/*
 * Parameters: the source tree that needs to be copied
 * Returns: a pointer to the tree
 * Purpose:  Assignment overload. Assigns rhs to this by deep copy.
 */
BSTree &BSTree::operator=(const BSTree &source)
{
    // Check for self-assignment
    if (this != &source)
    {
        delete this->root; // Delete existing tree, if it exists
        
        if (source.root) // Copy root from source.root, if it exists
        {
            this->root = new BSTNode(*source.root);
        }
        else
        {
            this->root = nullptr;
        }
    }    
    // Don't forget to return *this
    return *this;
}

int BSTree::minimum_value() const
{
    return this->root->minimum_value()->data;
}

int BSTree::maximum_value() const
{
    return this->root->maximum_value()->data;
}

unsigned int BSTree::count_of(int value) const
{
    return this->root->search(value)->count;
}

void BSTree::insert(int value)
{
    this->root = this->root->insert(value);
}

void BSTree::remove(int value)
{
    this->root = this->root->remove(value);
}

int BSTree::tree_height() const
{
    return this->root->node_height();
}

int BSTree::node_count() const
{
    return this->root->node_count();
}

int BSTree::count_total() const
{
    return this->root->count_total();
}

void BSTree::print_tree() const
{
    print_pretty(*this->root, 1, 0, std::cout);
}
