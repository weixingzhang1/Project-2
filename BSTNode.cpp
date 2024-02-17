#include "BSTNode.h"

#include <cassert>
#include <algorithm>
#include <string>
using namespace std;

/**
 * A pseudo-assert macro that immediately returns from the enclosing function
 *  if e is false.
 */
#define ABORT_UNLESS(e) \
    if (!(e))           \
    {                   \
        return;         \
    }

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to decorate
 * Returns: the decorator to print with this node using its to_string function.
 *      The decorator is either nothing, '*', 'r', or 'R' (computed as node is
 *      BLACK with count <=1, BLACK with count >1, RED with count =1, or RED
 *      with count >1).
 */
std::string decorator_string(const BSTNode *node)
{
    std::string dec = "";
    if (node && node->node_height() >= 0)
    {
        if (node->color == BSTNode::Color::RED)
        {
            if (node->count > 1)
            {
                dec = "R";
            }
            else
            {
                dec = "r";
            }
        }
        else
        {
            if (node->count > 1)
            {
                dec = "*";
            }
        }
    }
    return dec;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to get the value label for
 * Returns: node's data as a string, or empty_string if node is an empty tree.
 */
std::string value_string(const BSTNode *node)
{
    std::string value = "";
    if (node && node->node_height() >= 0)
    {
        value = std::to_string(node->data);
    }
    return value;
}

/**
 * This function is implemented for you, for your conveninence.
 *
 * Input: Node a
 *        Node b
 * Returns: N/A
 * Does: Swaps the colors of Nodes a and b.
 * Assumes: a and b are both non-null
 */
void swap_colors(BSTNode *a, BSTNode *b)
{
    BSTNode::Color t = a->color;
    a->color = b->color;
    b->color = t;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * It is implemented in two different ways (one of them commented out):
 *    - The commented-out version makes explicit that LEFT is the opposite of
 *      RIGHT, and that ROOT has no opposite
 *    - The uncommented version uses the fact that enum values in C++ are given
 *      integer values in increasing order starting at 0 and can be implicitly
 *      converted into an int. Since the Direction enum is defined in order
 *      LEFT, ROOT, RIGHT, the values are LEFT=0, ROOT=1, RIGHT=2.
 * Both exhibit constant time and space complexity so are asymptotically
 *  equivalent.
 *
 * Input: Direction dir
 * Returns: the opposite of dir, or ROOT if dir is ROOT.
 */
BSTNode::Direction opposite_direction(BSTNode::Direction dir)
{
    // BSTNode::Direction opp = dir;
    // if (dir == BSTNode::Direction::LEFT)
    // {
    //     opp = BSTNode::Direction::RIGHT;
    // }
    // else if (dir == BSTNode::Direction::RIGHT)
    // {
    //     opp = BSTNode::Direction::LEFT;
    // }
    // return opp;
    return BSTNode::Direction(BSTNode::Direction::RIGHT - dir);
}

/*
 * These BSTNode constructors use intializer lists. They are complete and you
 *  may not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
BSTNode::BSTNode() : count(0), height(-1), color(BLACK),
                     left(nullptr), right(nullptr), parent(nullptr) {}
BSTNode::BSTNode(int data)
    : data(data), count(1), height(0), color(BLACK),
      left(new BSTNode()), right(new BSTNode()), parent(nullptr) {}

/*
 * Parameters: other, node
 * Returns: the root of a tree that is a copy of the tree rooted at other
 * Purpose: creates a new node with the same properties as other by performing
     *      a pre-order deep copy of the tree rooted at other. The root of the
     *      new tree has parent nullptr (it is considered the ultimate root of
     *      its tree).
 */
BSTNode::BSTNode(const BSTNode &other)
{
    color = other.color; 
    data = other.data; 
    count = other.count; 
    parent = nullptr; 
    height = other.height;
    

    //copy left subtree
    if(!other.left->is_empty())
    {
        this->left = new BSTNode(*other.left);
        this->left->parent = this;
    }
    else {
        this->left = new BSTNode(); 
        left->parent = this;
    }
    //copy right subtree
    if(!other.right->is_empty()){
        this->right = new BSTNode(*other.right);
        this->right->parent = this; 
    }
    else 
    {
        this->right = new BSTNode();
        this->right->parent = this;
    }
}

/*
 * Parameters: node this - the node to free
 * Returns: N/A
 * Purpose: Performs a post-order delete to free all memory owned by this.
 */
BSTNode::~BSTNode()
{
    delete this->left;
    delete this->right;
}

std::string BSTNode::to_string() const
{
    return value_string(this) + decorator_string(this);
}

/*
 * Parameters: Node this - the root of the tree
 * Returns: a pointer to the node with the minimum value in the tree rooted
    *      at this
 * Purpose: finds the minimum value of the tree
 */
const BSTNode *BSTNode::minimum_value() const
{
    if (this->is_empty())
    {
        return this; 
    }
    //left traversal- search through the left side of the bst to find the minimum value
    const BSTNode* current = this; 
    while (!current->left->is_empty())
    {
        current = current->left;
    }
    return current;
}

/*
 * Parameters: node this - the root of the tree
 * Returns: a pointer to the node with the maximum value in the tree rooted
     *      at this.
 * Purpose: finds the maximum value of the tree
 */
const BSTNode *BSTNode::maximum_value() const
{
    //to find the maximum value, need to look through the right side of the bst to find the largest value 
    const BSTNode* current = this; 
    while (!current->right->is_empty())
    {
        current = current->right;
    }
    return current;
}

/*
 * Parameters: Node this - the root of the tree
 int value - the value for which to search in the tree
 * Returns: a pointer to the node with value in the tree rooted at this
 * Purpose: performs a search in the tree rooted at this and returns the
     *      node with that value in the tree, or an empty tree if the value
     *      does not appear in the tree rooted at this.
 */
const BSTNode *BSTNode::search(int value) const
{
    if (this->is_empty())
    {
        return this;
    }
    if (value < this->data)
    {
        return this->left->search(value);
    }
    else if (value > this->data)
    {
        return this->right->search(value);
    }
    else 
    {
        return this;
    }

}

/*
 * Parameters: Node this - the root of the tree
     *        int value - the value to insert
 * Returns: a pointer to the root of the tree into which value has just
     *      been inserted, with parent `nullptr`
 * Purpose: inserts (a single occurrence of) value into the tree rooted at
     *      this. Uses the "naive BST" insertion algorithm.
 */
BSTNode *BSTNode::insert(int value)
{
    //if newNode is null, then create a newNode and return newNode 
    //else if the value < data insert the left subtree; left->insert(value), left->parent = this
    //if the value > data insert right subtree
    //if value is equal to the current node's data do nothing
    
    if (this->is_empty())
    {
        this->data = value; 
        this->count = 1; 
        this->height = 0; 
        this->parent = parent; 
        this->left = new BSTNode();
        this->right = new BSTNode();
        return this;
    }
    else if (value < this->data)
    {
        this->left = this->left->insert(value);
        this->make_locally_consistent();
       
    }
    else if (value > this->data)
    {
        this->right = this->right->insert(value);
        this->make_locally_consistent();
        
    }
    else if (value == this->data)
    {
        this->count ++; 
        
    }
    this->make_locally_consistent(); //update the height
    return this;
   
    
}


/*
 * Parameters: Node this - the root of the tree
     *        int value - the value to insert
 * Returns: a pointer to the root of the tree into which value has just
     *      been inserted, with parent `nullptr`. The returned tree is an AVL
     *      Tree.
 * Purpose: inserts (a single occurrence of) value into the tree rooted at
     *      this. Uses the AVL Tree insertion algorithm.
 */
BSTNode *BSTNode::avl_insert(int value)
{
    /********************************
     ***** BST Insertion Begins *****
     ********************************/
    // BSTNode* root = this;
    if (this->is_empty())
    {
        this->data = value; 
        this->count = 1; 
        this->height = 0; 
        this->parent = parent; 
        this->left = new BSTNode();
        this->right = new BSTNode();
        return this;
    }
    else if (value < this->data)
    {
        this->left = this->left->avl_insert(value); //recursively call insert
        this->make_locally_consistent(); //update height
        
    }
    else if (value > this->data)
    {
        this->right = this->right->avl_insert(value); //recursively call insert
        this->make_locally_consistent(); //update height
         
    }
    else if (value == this->data)
    {
        this->count ++; 
    }
    
    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/
    BSTNode *root = this;
    root->make_locally_consistent(); //update height
    root = root->avl_balance(); //rotations
    root->make_locally_consistent(); //update height
    return root;

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/
   
}



/*
 * Parameters: Node this - the root of the tree
     *        int value - the value to insert
 * Returns: a pointer to the root of the tree into which value has just
     *      been inserted, with parent `nullptr`. The returned tree is a
     *      Red-Black Tree.
 * Purpose: inserts (a single occurrence of) value into the tree rooted at
     *      this. Uses the Red-Black Tree insertion algorithm.
 */
BSTNode *BSTNode::rb_insert(int value)
{
    /********************************
     ***** BST Insertion Begins *****
     ********************************/
    if (this->is_empty())
    {
        this->data = value; 
        this->count = 1; 
        this->height = 0; 
        this->parent = parent; 
        this->color = RED;
        this->left = new BSTNode();
        this->right = new BSTNode();
        return this;
    }
    else if (value < this->data)
    {
        this->left = this->left->rb_insert(value);
        this->make_locally_consistent();
    }
    else if (value > this->data)
    {
        this->right = this->right->rb_insert(value);
        this->make_locally_consistent();
       
    }
    else if (value == this->data)
    {
        this->count ++; 
        
    }
    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     ***** RB Maintenance Begins ****
     ********************************/
    
    BSTNode *root = this;
    root->make_locally_consistent(); //update height
    root = root->rb_eliminate_red_red_violation(); 
    root->make_locally_consistent(); //update height
    return root;
   
    /********************************
     ****** RB Maintenance Ends *****
     ********************************/
    return this;
}

/*
 * Parameters: Node this - the root of the tree
     *        int value - the value to remove
 * Returns: a pointer to the root of the tree from which value has just
     *      been removed, whose parent pointer is `nullptr`. This method may
     *      return an empty tree.
 * Purpose:removes (a single occurrence of) value from the tree rooted at
     *      this. Uses the "naive BST" removal algorithm.
 */
BSTNode *BSTNode::remove(int value)
{
   
    BSTNode * root = this; 
    if (this->is_empty())
    {
        return this;
    }
    
    if (value < root->data)
    {
        root->left = root->left->remove(value);
        root->make_locally_consistent();
        return root;
    }

    else if (value > root->data)
    {
        root->right = root->right->remove(value);
        root->make_locally_consistent();
        return root;
    }
    
    else {

        if(root->count > 1)
        {
            root->count--;
        }
        else if (this->left->is_empty() && this->right->is_empty()) //if leaf
        {
            root->make_locally_consistent();
            delete this;
            root = new BSTNode();
        }
        else if(this->left->is_empty() && !this->right->is_empty()) //left is empty
        {
            root = this->right;
            this->right = nullptr;
            delete this;
        }
        else if (this->right->is_empty() && !this->left->is_empty()) //right is empty
        {
            root = this->left; 
            this->left = nullptr;
            delete this;
        }
        //both children exist
        else 
        {
            BSTNode* min_value = (BSTNode*)root->right->minimum_value();
            root->data = min_value->data; 
            root->count = min_value->count; 
            min_value->count = 1;
            root->right= root->right->remove(min_value->data);
        }
    }
    root->make_locally_consistent();
    return root;
}

/*
 * Parameters: Node this - the root of the tree
     *        int value - the value to remove
 * Returns:  a pointer to the root of the tree from which value has just
     *      been removed, whose parent pointer is `nullptr`. This method may
     *      return an empty tree. The returned tree is an AVL Tree.
 * Purpose:removes (a single occurrence of) value from the tree rooted at
     *      this. Uses the AVL Tree removal algorithm.
 */
BSTNode *BSTNode::avl_remove(int value)
{


    /********************************
     ****** BST Removal Begins ******
     ********************************/

    BSTNode * root = this; 
    if (this->is_empty())
    {
        return this;
    }
    
    if (value < root->data)
    {
        root->left = root->left->avl_remove(value);
        root->make_locally_consistent();
        
    }

    else if (value > root->data)
    {
        root->right = root->right->avl_remove(value);
        root->make_locally_consistent();
    }
    
    else {

        if(root->count > 1)
        {
            root->count--;
        }
        else if (this->left->is_empty() && this->right->is_empty()) //if leaf
        {
            root->make_locally_consistent();
            delete this;
            root = new BSTNode();
        }
        else if(this->left->is_empty() && !this->right->is_empty()) //left is empty
        {
            root = this->right;
            this->right = nullptr;
            delete this;
        }
        else if (this->right->is_empty() && !this->left->is_empty()) //right is empty
        {
            root = this->left; 
            this->left = nullptr;
            delete this;
        }
        //both children exist
        else 
        {
            BSTNode* min_value = (BSTNode*)root->right->minimum_value();
            root->data = min_value->data; 
            root->count = min_value->count; 
            min_value->count = 1;
            root->right= root->right->remove(min_value->data);
        }
    }
    

    /********************************
     ******* BST Removal Ends *******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/
    root->make_locally_consistent(); //update heigth
    root = root->avl_balance(); //rotation
    root->make_locally_consistent(); //update height
    return root;

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/

    
}


BSTNode *BSTNode::rb_remove(int value)
{
    // This is implemented for you.
    BHVNeighborhood nb(this, ROOT);
    BSTNode *root = this->rb_remove_helper(value, nb);
    nb.fix_blackheight_imbalance();
    return root;
}

/*
 * Parameters: Node this - the root of the tree
 * Returns:  the height of the tree rooted at this (an empty tree has height
     *      -1).
 * Purpose: returns the height
 */
int BSTNode::node_height() const
{   
    if(this->is_empty())
    {
        return -1; 
    }
    else
    {
        return height;
    }

}

/*
 * Parameters: Node this - the root of the tree
 * Returns:  the number of non-empty nodes in the tree rooted at this
 * Purpose: returns the number of nodes
 */
unsigned int BSTNode::node_count() const
{
    unsigned int l_node = 0; 
    unsigned int r_node = 0;
    if(this->is_empty())
    {
        return 0; 
    }
    else 
    {
        l_node = this->left->node_count();
        r_node = this->right->node_count();
        return r_node + 1 + l_node; 
    }
}

/*
 * Parameters: Node this - the root of the tree
 * Returns:  the total of all counts in the tree rooted at this
 * Purpose: returns the number of total counts
 */
unsigned int BSTNode::count_total() const
{
    unsigned int l_node = 0; 
    unsigned int r_node = 0;
    
    if(this->is_empty())
    {
        return 0; 
    }
    else 
    {
        l_node = this->left->count_total();
        r_node = this->right->count_total();
        return r_node + count + l_node; 
    }

}

/*
 * Parameters: Node this - the node whose parent we are searching for
     *        Node root - the root of the tree in which to search
 * Returns:  a pointer to the parent of this in the tree rooted at root, or
     *      nullptr if this is the root of the tree
 * Purpose: Searches the tree rooted at root for this, then returns that
     *      node's parent.
 */
const BSTNode *BSTNode::parent_in(BSTNode *root) const
{   
    return root->parent;
}

bool BSTNode::is_empty() const
{
    bool empty_by_count = this->count == 0;
    bool empty_by_height = this->height == -1;
    bool empty_by_children = !this->left && !this->right;

    // Assert some invariants about binary search trees
    assert(!this->left == !this->right);
    assert(empty_by_count == empty_by_height);
    assert(empty_by_height == empty_by_children);

    // Return any of the equivalent checks
    return empty_by_count;
}

BSTNode *BSTNode::child(Direction dir) const
{
    BSTNode *child = nullptr;
    if (dir == LEFT)
    {
        child = this->left;
    }
    else if (dir == RIGHT)
    {
        child = this->right;
    }
    return child;
}

void BSTNode::set_child(Direction dir, BSTNode *child)
{
    if (dir != ROOT)
    {
        if (dir == LEFT)
        {
            this->left = child;
        }
        else if (dir == RIGHT)
        {
            this->right = child;
        }
        child->parent = this;
    }
    else
    {
        assert(false);
    }
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

BSTNode::RRVNeighborhood::RRVNeighborhood(BSTNode *root)
    : g{root}, p{nullptr}, x{nullptr}, y{nullptr}, shape{SHAPE_NONE}
{
    // Stop if g is RED or too short
    ABORT_UNLESS((this->g->color == BLACK) &&
                 (this->g->node_height() > 1));

    if (this->g->left->color == BLACK)
    {
        // If there is a red-red violation, it's to the right
        this->y = this->g->left;
        this->p = this->g->right;

        // Stop if g has two BLACK children
        ABORT_UNLESS(this->p->color == RED);

        if (this->p->left->color == RED)
        {
            this->shape = RL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(this->p->right->color == RED);

            this->shape = RR;
            this->x = this->p->right;
        }
    }
    else if (this->g->right->color == BLACK)
    {
        // If there is a red-red violation, it's to the left
        this->y = this->g->right;
        this->p = this->g->left;

        if (this->p->left->color == RED)
        {
            this->shape = Shape::LL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(p->right->color == RED);

            this->shape = LR;
            this->x = this->p->right;
        }
    }
    else
    {
        // Both children of g are RED. Find the red-red violation
        BSTNode *lc = this->g->left;
        BSTNode *llc = lc->left;
        BSTNode *lrc = lc->right;
        BSTNode *rc = this->g->right;
        BSTNode *rlc = rc->left;
        BSTNode *rrc = rc->right;

        if (llc && llc->color == RED)
        {
            this->shape = LL;
            this->p = lc;
            this->x = llc;
            this->y = rc;
        }

        if (lrc && lrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = LR;
            this->p = lc;
            this->x = lrc;
            this->y = rc;
        }

        if (rlc && rlc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == Shape::SHAPE_NONE);

            this->shape = Shape::RL;
            this->p = rc;
            this->x = rlc;
            this->y = lc;
        }

        if (rrc && rrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = RR;
            this->p = rc;
            this->x = rrc;
            this->y = lc;
        }

        // Stop if there is no red-red violation
        ABORT_UNLESS(this->shape != SHAPE_NONE);
    }
}

BSTNode::BHVNeighborhood::BHVNeighborhood(BSTNode *n, Direction dir)
    : n{n}, p{nullptr}, s{nullptr}, c{nullptr}, d{nullptr},
      del_case{CASE_NONE}, dir{dir}
{
    ABORT_UNLESS(this->n && !this->n->is_empty() &&
                 this->n->color == BLACK);

    this->p = this->n->parent;

    if (!this->p)
    {
        this->del_case = CASE_1;
        assert(dir == ROOT);
        this->dir = ROOT;
    }
    else
    {
        assert(!this->p->is_empty());
        assert(this->dir != ROOT);

        this->s = this->p->child(opposite_direction(dir));
        this->c = this->s->child(dir);
        this->d = this->s->child(opposite_direction(dir));

        if (this->p->color == BLACK &&
            this->s->color == BLACK &&
            this->c && this->c->color == BLACK &&
            this->d && this->d->color == BLACK)
        {
            this->del_case = CASE_2;
        }
        else if (this->p->color == BLACK &&
                 this->s->color == RED)
        {
            assert(this->c && this->c->color == BLACK &&
                   this->d && this->d->color == BLACK);

            this->del_case = CASE_3;
        }
        else if (this->p->color == RED &&
                 this->s->color == BLACK &&
                 this->c->color == BLACK &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_4;
        }
        else if (this->s->color == BLACK &&
                 this->c->color == RED &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_5;
        }
        else if (this->s->color == BLACK &&
                 this->d->color == RED)
        {
            this->del_case = CASE_6;
        }
        else
        {
            this->del_case = CASE_NONE;
        }
    }
}

void BSTNode::BHVNeighborhood::fix_blackheight_imbalance()
{
    /*
     * This is implemented for you. Study it carefully so you understand what
     *  is going on when a node is deleted from a Red-Black Tree.
     */
    BSTNode::BHVNeighborhood nb = *this;
    while (nb.p)
    {
        BSTNode::Direction pdir = ROOT;
        if (nb.p->parent)
        {
            if (nb.p == nb.p->parent->left)
            {
                pdir = LEFT;
            }
            else if (nb.p == nb.p->parent->right)
            {
                pdir = RIGHT;
            }
            else
            {
                // Should never happen: nb.p is non-null.
                assert(false);
            }
        }
        BSTNode *grandparent = nb.p->parent;

        switch (nb.del_case)
        {
        case CASE_2:
            nb.s->color = RED;
            nb.n = nb.p;
            nb = BSTNode::BHVNeighborhood(nb.n->parent, nb.dir);
            break;
        case CASE_3:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case >= CASE_4);
            break;
        case CASE_4:
            swap_colors(nb.p, nb.s);
            return;
        case CASE_5:
            nb.p->set_child(opposite_direction(nb.dir),
                            nb.s->dir_rotate(opposite_direction(nb.dir)));
            swap_colors(nb.c, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case == CASE_6);
            break;
        case CASE_6:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb.d->color = BLACK;
            return;
        default:
            // CASE_NONE or CASE_1 (should never happen; nb.p is non-null)
            assert(false);
            break;
        }
    }
}

BSTNode *BSTNode::rb_remove_helper(int value, BHVNeighborhood &nb)
{
    // This is implemented for you
    BSTNode *root = this;
    if (root->height >= 0)
    {
        if (value < root->data)
        {
            nb.dir = LEFT;
            root->left = root->left->rb_remove_helper(value, nb);
        }
        else if (value > root->data)
        {
            nb.dir = RIGHT;
            root->right = root->right->rb_remove_helper(value, nb);
        }
        else
        {
            // We found the value. Remove it.
            if (root->count > 1)
            {
                root->count--;
            }
            else
            {
                if (root->left->is_empty() &&
                    root->right->is_empty())
                {
                    // root has no children. We may have to do extra work.

                    // Get its neighborhood
                    nb = BHVNeighborhood(this, nb.dir);

                    // Delete it
                    delete this;
                    root = new BSTNode();
                }
                else if (!root->left->is_empty() &&
                         root->right->is_empty())
                {
                    // this has one (left) child. Promote this's child
                    this->left->color = root->color;
                    root = this->left;
                    this->left = nullptr;
                    delete this;
                }
                else if (root->left->is_empty() &&
                         !root->right->is_empty())
                {
                    // this has one (right) child. Promote this's child
                    this->right->color = root->color;
                    root = this->right;
                    this->right = nullptr;
                    delete this;
                }
                else
                {
                    /*
                     * this has two children.
                     *
                     * Find the successor to use as a replacement, then remove it
                     * entirely from this's right subtree. This requires setting
                     * the replacement's count to 1 so that the node is entirely
                     * removed rather than simply having its count decremented.
                     * Removal is the only place a const-to-non-const cast should
                     * appear in your solution.
                     *
                     * TODO: (optional) Rewrite this section of code to eliminate
                     *  the const-to-non-const cast.
                     */

                    BSTNode *replacement = (BSTNode *)root->right->minimum_value();
                    root->data = replacement->data;
                    root->count = replacement->count;
                    replacement->count = 1;
                    nb.dir = RIGHT;
                    root->right = root->right->rb_remove_helper(replacement->data, nb);
                }
            }
        }
    }

    root->make_locally_consistent();

    return root;
}

BSTNode *BSTNode::dir_rotate(Direction dir)
{
    // This is implemented for you.
    BSTNode *root = this;
    if (dir == LEFT)
    {
        root = root->left_rotate();
    }
    else if (dir == RIGHT)
    {
        root = root->right_rotate();
    }
    return root;
}

/*
 * Parameters: Node this - the root of the tree.
 * Returns:  pointer to the root of rotated tree, whose parent pointer is
     *      the parent of this.
 * Purpose:  right rotate tree rooted at this
 */
BSTNode *BSTNode::right_rotate()
{
    BSTNode *newroot = left;
    left = newroot->right; 
    
    // Update parents
    if (parent != nullptr)
    {
        (parent->left == this) ? (parent->left = newroot) : (parent->right = newroot);
    }
   
    newroot->right = this; 
    newroot->parent = parent; 
    parent = newroot; 
    
    // Update heights
    this->make_locally_consistent();
    newroot->make_locally_consistent();
    return newroot;
}

/*
 * Parameters: Node this - the root of the tree.
 * Returns:  pointer to the root of rotated tree, whose parent pointer is
     *      the parent of this.
 * Purpose:  left rotate tree rooted at this
 */
BSTNode *BSTNode::left_rotate()
{
    BSTNode *newroot = right;
    right = newroot->left; 

    // // Update parents
    if (parent != nullptr)
    {
        (parent->left == this) ? (parent->left = newroot) : (parent->right = newroot);
    }
    
    newroot->left = this; 
    newroot->parent = parent; 
    parent = newroot; 
    
    // Update heights
    this->make_locally_consistent();
    newroot->make_locally_consistent();
    return newroot;
}

/*
 * Parameters: Node this - the root of a Red-Black tree.
 * Returns:  A pointer to the root of the balanced tree
 * Purpose:  lEliminates the red-red violation (if there is one) in the
     *      neighborhood of this, meaning this and its children and one of its
     *      grandchildren (the grandchild that is the cause of a red-red
     *      violation, if there is one). The black-height of the returned tree
     *      is the same as the black-height of this and the returned node is
     *      the root of a Red-Black tree, with the possible exception that it
     *      is RED. If there is no violation, return this unchanged.
 */
BSTNode *BSTNode::avl_balance()
{
    int balance = height_diff();

    if(balance > 1)//if the tree is rigth heavy
    {
        int l_balance = this->right->right->height - this->right->left->height;
        
        if (l_balance > 0)//RR
        {
            this->make_locally_consistent();
            return left_rotate();
        }
        else //RL
        {
            this->right = this->right->right_rotate();
            return left_rotate();
        }
    }
    else if (balance < -1) //left heavy 
    {
        int r_balance = this->left->right->height - this->left->left->height;
        
        if(r_balance <= 0 ) //LL
        {
            this->make_locally_consistent();
            return right_rotate();
        }
        else //LR
        {
            this->left = this->left->left_rotate();
            return right_rotate();
        }
    }
    return this;
}

/*
 * Parameters: Node this - the root of the tree.
 * Returns:  integer value signifying the height difference.
 * Purpose:  calculates the difference in the height of the left and right
     *      subtree of this, computed as (this.right.height - this.left.height)
 */
BSTNode *BSTNode::rb_eliminate_red_red_violation()
{
    /*
     * Get this's neighborhood (children + grandchildren), which might have
     *  shape NONE if this is BLACK or this.height <= 1 or there is no red-red
     *  violation in the neighborhood of this.
     */
    RRVNeighborhood nb(this);

    if (nb.shape != SHAPE_NONE)
    {
        if(nb.y->color == BLACK)
        {
            if(nb.shape == LL)
            {
                nb.g->right_rotate();
                nb.g->color = RED; 
                nb.p->color = BLACK; 
            }   
            else if(nb.shape == RR)
            {
                nb.g->left_rotate(); 
                nb.g->color = RED; 
                nb.p->color = BLACK; 
            } 
            else if(nb.shape == LR)
            {
                nb.p = nb.p->left_rotate();
                nb.g->right_rotate();
                swap_colors(nb.p, nb.g);
                // nb.g->color = RED; 
                // nb.x->color = BLACK;
            } 
            else if(nb.shape == RL)
            {

                nb.p = nb.p->right_rotate();
                nb.g->left_rotate();
                swap_colors(nb.g,nb.p);
                // nb.g->color = RED; 
                // nb.x->color = BLACK; 
            } 
            this->make_locally_consistent();
            return nb.p;
        }
        else if (nb.y->color == RED)
        {
            nb.g->color = RED; 
            nb.y->color = BLACK; 
            nb.p->color = BLACK; 
            return this;
        }
        
    }
    return this;
}

int BSTNode::height_diff() const
{
    /*
     * This is implemented for you. Note the use of the node_height() function
     *  rather than the height property. Why do you think is it written in this
     *  way?
     */
    int diff = 0;
    if (!this->is_empty())
    {
        diff = this->right->node_height() - this->left->node_height();
    }

    return diff;
}

/*
 * Parameters:  Node this - the root of the tree to make consistent
 * Returns: N/A
 * Purpose:  Updates the tree rooted at this to be locally consistent, in the
     *      following way:
     *        - this.height = 1 + MAX(this.left.height, this.right.height)
     *        - this.left.parent = this
     *        - this.right.parent = this
     *  If this is empty, this.height is set to -1 and nothing is done to its
     *      children.
 */
void BSTNode::make_locally_consistent()
{
    if(!this->is_empty())
    {
        this->height = 1+ std::max(this->left->height, this->right->height);
        this->left->parent = this; 
        this->right->parent = this; 
    }
}
