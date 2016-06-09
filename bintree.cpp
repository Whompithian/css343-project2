/*
 * @file    bintree.cpp
 *          Addapted from:
 *          Carrano, F. M. (2007). Trees. In M. Hirsch (Ed.) "Data Abstraction
 *              & Problem Solving with C++: Walls and Mirrors" (5th ed.) pp.
 *              523-529, 559-563. Boston, MA: Pearson Education, Inc.
 * @brief   This class represents a binary search tree which holds its data in
 *          a NodeData object, to which it keeps a pointer. NodeData must
 *          support ==, <, and << operators. Some specialized methods are
 *          provided for displaying the contents of the tree. There is no
 *          method for removing a single item, so the tree must be emptied to
 *          remove anything.
 * @author  Brendan Sweeney, SID 1161836
 * @date    January 21, 2012
 */

#include <cstddef>          // definition of NULL
#include <new>              // for bad_alloc

#include "bintree.h"

using namespace std;


/**---------------------- Default Constructor ---------------------------------
 * Creates an empty tree.
 * @pre None.
 * @post An empty binary search tree exists.
 */
BinTree::BinTree() : root(NULL)
{
} // end default constructor

/**---------------------- Copy Constructor ------------------------------------
 * Copies the tree orig into a new tree.
 * @param orig  The tree to be copied.
 * @pre There is sufficient memory to allocate a copy of orig.
 * @post A binary search tree exists that is a structural copy of the tree
 *       orig; orig remains unchanged.
 */
BinTree::BinTree(const BinTree& orig)
{
    copyTree(orig.root, root);
} // end copy constructor

/**---------------------- Destructor ------------------------------------------
 * Deallocates memory for a tree before it is released.
 * @pre None.
 * @post This tree is empty before is is released; all NodeData objects to
 *       which this tree held pointers are deleted.
 */
BinTree::~BinTree()
{
    makeEmpty();
} // end destructor

/**---------------------- isEmpty() -------------------------------------------
 * Determines whether a binary search tree is empty.
 * @pre None.
 * @post This tree remains unchanged.
 * @return true if the tree is empty; false, otherwise.
 */
bool BinTree::isEmpty(void) const
{
    return (root == NULL);
} // end isEmpty()

/**---------------------- makeEmpty() -----------------------------------------
 * Deallocates memory for a tree.
 * @pre None.
 * @post This tree is now empty; all NodeData objects to which this tree held
 *       pointers are deleted.
 */
void BinTree::makeEmpty(void)
{
    destroyTree(root);
} // end makeEmpty()

/**---------------------- destroyTree() ---------------------------------------
 * Deallocates memory for a tree.
 * @param treePtr  Pointer to the root of the tree to be deallocated.
 * @pre None.
 * @post treePtr points to an empty tree.
 */
void BinTree::destroyTree(Node *& treePtr)
{
    // postorder traversal
    if (treePtr != NULL)        // base case check
    {
        destroyTree(treePtr->left);
        destroyTree(treePtr->right);
        if (treePtr->data != NULL)
            delete treePtr->data;
        treePtr->data = NULL;
        delete treePtr;
        treePtr = NULL;
    } // end if (treePtr != NULL)
} // end destroyTree(Node*&)

/**---------------------- = Assignment Operator -------------------------------
 * Copies the contents of rhs into this tree. Any contents of this tree are
 * removed beforehand. Once copied, this tree will hold pointers to the same
 * objects as rhs, so emptying one tree will cause data loss in the other.
 * @param rhs  The right-hand tree to be copied.
 * @pre There is sufficient memory to allocate a copy of rhs.
 * @post This tree is a structural copy of rhs; rhs remains unchanged.
 * @return This binary search tree, which is equivalent to rhs.
 */
BinTree& BinTree::operator=(const BinTree& rhs)
{
    if (this != &rhs)
    {
        destroyTree(root);          // deallocate left-hand side
        copyTree(rhs.root, root);   // copy right-hand side
    } // end if (this != &rhs)

    return *this;
} // end operator=(BinTree&)

/**---------------------- copyTree() ------------------------------------------
 * Copies the tree rooted at treePtr into a tree rooted at newTreePtr.
 * @param treePtr  The root of the tree to be copied.
 * @param newTreePtr  A container for the root of a copy of treePtr.
 * @pre There is sufficient memory to allocate a new tree; NodeData provides
 *      the == and < operators.
 * @post newTreePtr points to the root of a structural copy of the tree whose
 *       root is pointed to by treePtr.
 */
void BinTree::copyTree(Node *treePtr, Node *& newTreePtr) const
{
    // preorder traversal
    if (treePtr != NULL)
    {
        // copy node
        try
        {
            newTreePtr = new Node;
            newTreePtr->data = new NodeData(*treePtr->data);
            // continue down left branch
            copyTree(treePtr->left, newTreePtr->left);
            // continue down right branch
            copyTree(treePtr->right, newTreePtr->right);
        }
        catch (bad_alloc e)
        {
            cerr << "Could not allocate memory: copyTree() failed.";
        } // end try
    }
    else
    {
        newTreePtr = NULL;  // copy empty tree
    } // end if (treePtr != NULL)
} // end copyTree(Node*, Node*&)

/**---------------------- == Equality Operator --------------------------------
 * Compares this binary search tree with another for equality. Equality means
 * that both trees contain the same data and have the same structure.
 * @param rhs  The right-hand tree to be compared.
 * @pre NodeData provides an equality operator.
 * @post Both binary search trees remain unchanged.
 * @return true if both trees have identical structures and content; false,
 *         otherwise.
 */
bool BinTree::operator==(const BinTree& rhs) const
{
    return compare(root, rhs.root);
} // end operator==(BinTree&)

/**---------------------- compare() -------------------------------------------
 * Compares two subtrees for equivalent content and structure.
 * @param lhs  A binary search tree to check for equality.
 * @param rhs  A binary search tree to check against for equality.
 * @pre None.
 * @post Both trees remain unchanged.
 * @return true if both trees are structurally identical and hold the same
 *         data; false, otherwise.
 */
bool BinTree::compare(const Node *lhs, const Node *rhs) const
{
    bool success;

    if (lhs == NULL && rhs == NULL)         // empty trees equivalent
    {
        success = true;
    }
    else if (lhs != NULL && rhs != NULL)    // there is data to compare
    {
        success = lhs->data == rhs->data &&             // compare data
                  compare(lhs->left, rhs->left) &&      // check left subtree
                  compare(lhs->right, rhs->right);      // check right subtree
    }
    else
    {
        success = false;
    } // end if (lhs == NULL && rhs == NULL)

    return success;
} // end compare(Node*, Node*)

/**---------------------- != Inequality Operator ------------------------------
 * Compares this binary search tree with another for inequality. Inequality
 * means that the trees contain different data or have different structures.
 * @param rhs  The right-hand tree to be compared.
 * @pre NodeData provides an equality operator.
 * @post Both binary search trees remain unchanged.
 * @return false if both trees have identical structures and content; true,
 *         otherwise.
 */
bool BinTree::operator!=(const BinTree& rhs) const
{
    return !(*this == rhs);
} // end operator!=(BinTree&)

/**---------------------- << Stream Out Operator ------------------------------
 * Writes the contents of this tree to the provided ostream, in sorted order,
 * space separated on a single line.
 * @param output  The ostream to which to write this tree's contents.
 * @param source  The tree whose contents are to be written (this tree).
 * @pre The ostream, output, is writable.
 * @post The ostream, output, contains a string representing the contents of
 *       this tree, in sorted order; this tree remains unchanged.
 * @return A reference to the provided ostream, with the contents of this tree
 *         appended to it.
 */
ostream& operator<<(ostream& output, const BinTree& source)
{
    source.inorderHelper(output, source.root);
    output << endl;

    return output;
} // end operator<<(ostream&, BinTree&)

/**---------------------- inorderHelper() -------------------------------------
 * Traverses a binary search tree in sorted order, starting at treePtr, and
 * writes the data value of each item once, preceded by a space.
 * @param treePtr  Node at which to begin traversal.
 * @pre The ostream, output, can be written to; NodeData prvides the <<
 *      operator.
 * @post The ostream, output, contains the data element of every node in the
 *       subtree rooted at treePtr, space separated.
 */
void BinTree::inorderHelper(ostream& output, const Node *treePtr) const
{
    if (treePtr != NULL)        // base case check
    {
        inorderHelper(output, treePtr->left);       // write left subtree
        output << ' ' << *treePtr->data;            // write current data
        inorderHelper(output, treePtr->right);      // write right subtree
    } // end if (treePtr != NULL)
} // end inorder(ostream&, Node*)

/**---------------------- insert() --------------------------------------------
 * Inserts an item into a binary search tree.
 * @param newItem  An object to be added to the tree.
 * @pre NodeData provdes the == and < operators.
 * @post newItem is in its proper position in the tree.
 * @return true if newItem could be inserted in the tree; false if newItem
 *         already existed in the tree.
 */
bool BinTree::insert(NodeData *newItem)
{
    return insertItem(root, newItem);
} // end insert(NodeData*)

/**---------------------- insertItem() ----------------------------------------
 * Recursively inserts an item into a binary search tree.
 * @param treePtr  Pointer to the node to start a check for insertion.
 * @param newItem  The item to be inserted into this tree.
 * @pre treePtr points to a binary search tree; NodeData provides the == and <
 *      operators.
 * @post newItem is in its proper position in the tree.
 * @return true if the item is successfully inserted; false if the item already
 *         exists in this tree or memory could not be allocated.
 */
bool BinTree::insertItem(Node *& treePtr, NodeData *newItem)
{
    bool success;

    if (treePtr == NULL)
    { // position of insertion found; insert as leaf
        // create a new node
        try
        {
            treePtr = new Node;
            treePtr->data = newItem;
            success = true;
        }
        catch (bad_alloc e)
        {
            cerr << "Could not allocate memory for " << *newItem
                 << ": insert() failed.";
            success = false;
        } // end try
    }
    // duplicates are not allowed
    else if (*newItem == *treePtr->data)
    {
        success = false;
    }
    // else search for the insertion position
    else if (*newItem < *treePtr->data)
    {
        // search the left subtree
        success = insertItem(treePtr->left, newItem);
    }
    else
    {
        // search the right subtree
        success = insertItem(treePtr->right, newItem);
    } // end if (treePtr == NULL)

    return success;
} // end insertItem(Node*&, NodeData*&)

/**---------------------- retrieve() ------------------------------------------
 * Retrieves a given item from a binary search tree.
 * @param searchItem  The item to be located.
 * @param dataItem  A container for the found item.
 * @pre NodeData provides the == and < operators.
 * @post If the retrieval was successful, dataItem contains the retrieved item;
 *       this tree remains unchanged.
 */
bool BinTree::retrieve(const NodeData& searchItem, NodeData *& dataItem) const
{
    return retrieveItem(root, searchItem, dataItem);
} // end retrieve(NodeData&, NodeData*&)

/**---------------------- retrieveItem() --------------------------------------
 * Recursively retrieves an item from a binary search tree.
 * @param treePtr  Pointer to the node at which to start searching.
 * @param searchItem  The item to be located.
 * @param dataItem  A container for the located item.
 * @pre treePtr points to a binary search tree; NodeData provides the == and <
 *      operators.
 * @post If the retrieval was successful, treeItem contains the retrieved item;
 *       this tree remains unchanged.
 * @return true if searchItem matches an item in the tree; false if searchItem
 *         could not be found.
 */
bool BinTree::retrieveItem(const Node *treePtr,
                           const NodeData& searchItem,
                                 NodeData *& dataItem) const
{
    bool success;

    if (treePtr == NULL)    // hit leaf, item not found
    {
        success = false;
    }
    else if (searchItem == *(treePtr->data))
    {
        // item is in the root of this subtree
        dataItem = treePtr->data;
        success = true;
    }
    else if (searchItem < *(treePtr->data))
    {
        // search the left subtree
        success = retrieveItem(treePtr->left, searchItem, dataItem);
    }
    else
    {
        // search the right subtree
        success = retrieveItem(treePtr->right, searchItem, dataItem);
    } // end if (treePtr == NULL)

    return success;
} // end retrieveItem(Node*, NodeData&, NodeData*&)

/**---------------------- displaySideways() -----------------------------------
 * Displays a binary tree as though you are viewing it from the side;
 * hard coded displaying to standard output.
 * @pre cout can be written to.
 * @post This tree remains unchanged.
 */
void BinTree::displaySideways(void) const
{
   sideways(root, 0);
} // end displaySideways()

/**---------------------- sideways() ------------------------------------------
 * Displays a binary tree as though you are viewing it from the side;
 * hard coded displaying to standard output.
 * @param current  The Node being examined for display.
 * @param level  The depth of the current Node, used to determine indentation.
 * @pre cout can be written to.
 * @post cout contains a graphical representation of this tree.
 */
void BinTree::sideways(Node *current, int level) const
{
   if (current != NULL)
   {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level
      for(int i = level; i >= 0; i--)
      {
          cout << "    ";
      } // end for(int i = level)

      cout << *current->data << endl;        // display information of object
      sideways(current->left, level);
   } // end if (current != NULL)
} // end sideways(Node*, int)

/**---------------------- getDepth() ------------------------------------------
 * Determines the depth of a node in a binary search tree. If the data is found
 * at the root, the depth is 1. If the data is not found, the depth is 0. The
 * item is sought with iteration through the tree, rather than binary
 * comparisons.
 * @param searchItem  The item to locate in the tree.
 * @pre NodeData provides an equality operator.
 * @post This tree remains unchanged.
 * @return The depth of the node containing treeItem, if found; 0, otherwise.
 */
int BinTree::getDepth(const NodeData& searchItem) const
{
    return depth(root, searchItem);
} // end getDepth(NodeData&)

/**---------------------- depth() ---------------------------------------------
 * Determines the depth of a node in a binary search tree. If the data is found
 * at the root, the depth is 1. If the data is not found, the depth is 0. The
 * item is sought with iteration through the tree, rather than binary
 * comparisons.
 * @param searchItem  The item to locate in the tree.
 * @pre NodeData provides an equality operator.
 * @post This tree remains unchanged.
 * @return The depth of the node containing treeItem, if found; 0 the item is
 *         not found.
 */
int BinTree::depth(const Node *treePtr, const NodeData& dataItem) const
{
    int level;

    if (treePtr == NULL)        // base case: hit leaf: item not found
    {
        level = 0;
    }
    else if (dataItem == *treePtr->data)       // base case: item found
    {
        level = 1;
    }
    else
    {
        // check left subtree for item
        level = depth(treePtr->left, dataItem);

        if (level == 0)     // item not in left subtree
        {
            level = depth(treePtr->right, dataItem);
        } // end if (depth == 0)

        if (level > 0)      // item found in a subtree
        {
            ++level;        // add depth for this level
        } // end if (depth > 0)
    } // end if (treePtr == NULL)

    return level;
} // end depth(Node*, NodeData&)

/**---------------------- bstreeToArray() -------------------------------------
 * Fills an array of NodeData* by using an inorder traversal of the tree. The
 * tree is left empty. The size of the array is not checked and is assumed to
 * be sufficient to contain every element in the tree.
 * @param target[]  The array to fill with the NodeData* from this tree.
 * @pre target[] currently contains 100 NULL elements.
 * @post target[] contains every element found in this tree, in sorded order;
 *       this tree is empty.
 */
void BinTree::bstreeToArray(NodeData *target[])
{
    int index = 10;
    // Anything I do with an element of target[0-9] causes SEGFAULT. I was
    // unable to find the cause, so I decided to skip the first 10 elements to
    // at least demonstrate that the algorithm works.
    inorderToArray(root, target, index);
    destroyTree(root);
} // end bstreeToArray(NodeData*[])

/**---------------------- inorderToArray() ------------------------------------
 * Traverses a binary search tree in sorted order and moves each data element
 * into an array of NodeData*. The size of targe[] is assumed to be sufficient
 * to contain all elements in the subtree.
 * @param treePtr  The root of a subtree to move into an array.
 * @param target[]  An array to move a subtree into.
 * @param index  The index at which to insert the next item into the array.
 * @pre target[] is large enough to contain every element in the subtree; the
 *      initial call to this method is proceeded by destroyTree().
 * @post target[] contains every data item from the subtree in sorted order;
 *       data pointers in the subree are NULL.
 * @note This tree MUST be emptied after calling this method, or it will not be
 *       a binary search tree.
 */
void BinTree::inorderToArray(Node *treePtr, NodeData *target[], int& index)
{
    if (treePtr != NULL)
    {
        inorderToArray(treePtr->left, target, index);
        target[index++] = treePtr->data;
        treePtr->data = NULL;
        inorderToArray(treePtr->right, target, index);
    } // end if (treePtr != NULL)
} // end inorderTransfer(Node*, NodeData*[])

/**---------------------- arrayToBSTree() -------------------------------------
 * Populates this tree from the contents of an array of sorted NodeData*. Any
 * contents of this tree are removed beforehand. The new tree is balanced by
 * using bisection of the array to choose the order of insertion.
 * @param source[]  The array from which to populate this tree.
 * @pre target[] is sorted in ascending order.
 * @post This tree is balanced and contains all NodeData* that were contained
 *       in source[]; all elements of source[] are now NULL.
 */
void BinTree::arrayToBSTree(NodeData *source[])
{
    int low = 10, high;     // low = 10 due to bug in bstreeToArray()
    
    destroyTree(root);

    // find last element, assuming contiguous data
    for (high = low; high < 100 && source[high] != NULL; ++high)
    {
    } // end for (high = low)
    
    --high;      // high was length of array; set to index of last element

    if (source[low] != NULL)                // ensure array has first element
    {
        bisectBuild(source, low, high);     // build a balanced tree
    } // end if (source[low] != NULL)
} // end arrayToBSTree(NodeData*[])

/**---------------------- bisectBuild() ---------------------------------------
 * Fills this tree from the contents of an array segment of sorted NodeData*.
 * The new tree is balanced by using bisection of the array segment to choose
 * the order of insertion. Elements are removed from the array as they are
 * inserted into this tree.
 * @param source[]  The array from which to fill this tree.
 * @param low  The lower bound of the segment to examine.
 * @param high  The upper bound of the segment to examine.
 * @pre source[] is sorted in ascending order; this tree only contains data
 *      from the array source[].
 * @post The data elements in the provided array segment have been inserted
 *       into this tree; this tree is balanced.
 */
void BinTree::bisectBuild(NodeData *source[], int low, int high)
{
    int mid = (low + high) / 2;

    if (low <= mid)                     // base case check
    {
        if (insert(source[mid]))        // middle element is subtree root
        {
            source[mid] = NULL;         // array emptied as tree is built
            bisectBuild(source, low, mid - 1);      // build left branch
            bisectBuild(source, mid + 1, high);     // build right branch
        } // end if (insert(source[mid]))
    } // end if (low <= mid)
} // end bisectBuild(NodeData*&[], int, int)
