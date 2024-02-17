/*
 * Filename: RBTree.cpp
 * Contains: Implementation of Red-Black Trees 
 */

#include <iostream>

#include "RBTree.h"
#include "pretty_print.h"

using namespace std;

/*******************************
 * BEGIN PUBLIC RBTREE SECTION *
 *******************************/

/*
 * The RBTree constructors use intializer lists. They are complete and you
 *  should not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
RBTree::RBTree() : root(new BSTNode()) {}

RBTree::RBTree(const RBTree &source)
    : root(new BSTNode(*source.root)) {}

RBTree::~RBTree()
{
    delete this->root;
}

/*
 * Parameters: the source tree that needs to be copied
 * Returns: a pointer to the tree
 * Purpose:  Assignment overload. Assigns rhs to this by deep copy.
 */
RBTree &RBTree::operator=(const RBTree &source)
{

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

int RBTree::minimum_value() const
{
    return this->root->minimum_value()->data;
}

int RBTree::maximum_value() const
{
    return this->root->maximum_value()->data;
}

unsigned int RBTree::count_of(int value) const
{
    return this->root->search(value)->count;
}

void RBTree::insert(int value)
{
    this->root = this->root->rb_insert(value);
    this->root->color = BSTNode::Color::BLACK;
}

void RBTree::remove(int value)
{
    this->root = this->root->rb_remove(value);
    this->root->color = BSTNode::Color::BLACK;
}

int RBTree::tree_height() const
{
    return this->root->node_height();
}

int RBTree::node_count() const
{
    return this->root->node_count();
}

int RBTree::count_total() const
{
    return this->root->count_total();
}

void RBTree::print_tree() const
{
    print_pretty(*this->root, 1, 0, std::cout);
}
