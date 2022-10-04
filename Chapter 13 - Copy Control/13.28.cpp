// Exercise 13.28:
/*
 Given the following classes, implement a default constructor and the necessary copy-control members.
 
 >> This is a bit of a rubbish question...and requires an understanding of binary trees to get the most out of the exercise.
 */

//"A binary tree is made of nodes, where each node contains a "left" reference, a "right" reference, and a data element.
// The topmost node in the tree is called the root.
// Every node (excluding a root) in a tree is connected by a directed edge from exactly one other node.
// This node is called a parent."


#include <string>

class TreeNode {
public:
    // constructors
    TreeNode() : value(), count(0), left(nullptr), right(nullptr) { }
    TreeNode(const std::string &v, int c) : value(v), count(c), left(nullptr), right(nullptr) { }
    
    TreeNode(const TreeNode&);
    
    TreeNode& operator=(const TreeNode&);
    
    ~TreeNode();
private:
    std::string value;
    // surprised an int is used instead of a std::size_t* to keep count
    int count;
    TreeNode *left;
    TreeNode*right;
};

// destructor
// we must delete links to left and right children before deleting the node
TreeNode::~TreeNode()
{
    delete left;
    delete right;
}

// copy constructor
// if we delete unique children then we must create them
TreeNode::TreeNode(const TreeNode &o)
{
    value = o.value;
    count = o.count;
    
    left = new TreeNode(*o.left);
    right = new TreeNode(*o.right);
}

// copy assignment operator
TreeNode& TreeNode::operator=(const TreeNode &rhs)
{
    // following good practice
    // (1) copy rhs into local tmp
    // (2) destory existing members from lhs
    // (3) copt data from tmp into lhs
    auto ltmp = new TreeNode(*rhs.left);
    delete left;
    left = ltmp;
    // delete ltmp;
    // ltmp = nullptr;
    
    auto rtmp = new TreeNode(*rhs.right);
    delete right;
    right = rtmp;
    // delete rtmp;
    // rtmp = nullptr;
    
    value = rhs.value;
    count = rhs.count;
    
    return *this;
}

class BinStrTree {
public:
    // constructors
    BinStrTree() : root(new TreeNode()) { }
    BinStrTree(const BinStrTree&);
    BinStrTree& operator=(const BinStrTree&);
    ~BinStrTree();
private:
    // only given one member...
    TreeNode *root;
};

// destructor
BinStrTree::~BinStrTree() { delete root; }

// copy constructor
BinStrTree::BinStrTree(const BinStrTree &o) { root = new TreeNode(*o.root); }

// copy-assignment operator
BinStrTree& BinStrTree::operator=(const BinStrTree &rhs)
{
    auto tmp = new TreeNode(*rhs.root);
    delete root;
    root = tmp;
    return *this;
}

int main()
{
    TreeNode n1;
    
    BinStrTree bst1;
    
    return 0;
}
