/*
 * @file    bintree.h
 *          Addapted from:
 *          Carrano, F. M. (2007). Trees. In M. Hirsch (Ed.) "Data Abstraction
 *              & Problem Solving with C++: Walls and Mirrors" (5th ed.) pp.
 *              556-559. Boston, MA: Pearson Education, Inc.
 * @brief   This class represents a binary search tree which holds its data in
 *          a NodeData object, to which it holds a pointer. NodeData must
 *          support ==, <, and << operators. Some specialized methods are
 *          provided for displaying the contents of the tree. There is no
 *          method for removing a single item, so the tree must be emptied to
 *          remove anything.
 * @author  Brendan Sweeney, SID 1161836
 * @date    January 20, 2012
 */

#ifndef _BINTREE_H
#define	_BINTREE_H

#include "nodedata.h"


typedef void (*FunctionType)(NodeData& anItem);

class BinTree
{
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
   friend ostream& operator<<(ostream& output, const BinTree& source);

public:

/**---------------------- Default Constructor ---------------------------------
 * Creates an empty tree.
 * @pre None.
 * @post An empty binary search tree exists.
 */
    BinTree();

/**---------------------- Copy Constructor ------------------------------------
 * Copies the tree orig into a new tree.
 * @param orig  The tree to be copied.
 * @pre There is sufficient memory to allocate a copy of orig.
 * @post A binary search tree exists that is a structural copy of the tree
 *       orig; orig remains unchanged.
 */
    BinTree(const BinTree& orig);

/**---------------------- Destructor ------------------------------------------
 * Deallocates memory for a tree before it is released.
 * @pre None.
 * @post This tree is empty before is is released; all NodeData objects to
 *       which this tree held pointers are deleted.
 */
    virtual ~BinTree();

/**---------------------- isEmpty() -------------------------------------------
 * Determines whether a binary search tree is empty.
 * @pre None.
 * @post This tree remains unchanged.
 * @return true if the tree is empty; false, otherwise.
 */
    virtual bool isEmpty(void) const;

/**---------------------- makeEmpty() -----------------------------------------
 * Deallocates memory for a tree.
 * @pre None.
 * @post This tree is now empty; all NodeData objects to which this tree held
 *       pointers are deleted.
 */
    virtual void makeEmpty(void);

/**---------------------- = Assignment Operator -------------------------------
 * Copies the contents of rhs into this tree. Any contents of this tree are
 * removed beforehand. Once copied, this tree will hold pointers to the same
 * objects as rhs, so emptying one tree will cause data loss in the other.
 * @param rhs  The right-hand tree to be copied.
 * @pre There is sufficient memory to allocate a copy of rhs.
 * @post This tree is a structural copy of rhs; rhs remains unchanged.
 * @return This binary search tree, which is equivalent to rhs.
 */
    virtual BinTree& operator=(const BinTree& rhs);

/**---------------------- == Equality Operator --------------------------------
 * Compares this binary search tree with another for equality. Equality means
 * that both trees contain the same data and have the same structure.
 * @param rhs  The right-hand tree to be compared.
 * @pre NodeData provides an equality operator.
 * @post Both binary search trees remain unchanged.
 * @return true if both trees have identical structures and content; false,
 *         otherwise.
 */
    virtual bool operator==(const BinTree& rhs) const;

/**---------------------- != Inequality Operator ------------------------------
 * Compares this binary search tree with another for inequality. Inequality
 * means that the trees contain different data or have different structures.
 * @param rhs  The right-hand tree to be compared.
 * @pre NodeData provides an equality operator.
 * @post Both binary search trees remain unchanged.
 * @return false if both trees have identical structures and content; true,
 *         otherwise.
 */
    virtual bool operator!=(const BinTree& rhs) const;

/**---------------------- insert() --------------------------------------------
 * Inserts an item into a binary search tree.
 * @param newItem  An object to be added to the tree.
 * @pre NodeData provdes the == and < operators.
 * @post newItem is in its proper position in the tree.
 * @return true if newItem could be inserted in the tree; false if newItem
 *         already existed in the tree.
 */
    virtual bool insert(NodeData *newItem);

/**---------------------- retrieve() ------------------------------------------
 * Retrieves a given item from a binary search tree.
 * @param searchItem  The item to be located.
 * @param dataItem  A container for the found item.
 * @pre NodeData provides the == and < operators.
 * @post If the retrieval was successful, dataItem contains the retrieved item;
 *       this tree remains unchanged.
 */
    virtual bool retrieve(const NodeData& searchItem,
                                NodeData *& dataItem) const;

/**---------------------- displaySideways() -----------------------------------
 * Displays a binary tree as though you are viewing it from the side;
 * hard coded displaying to standard output.
 * @pre cout can be written to.
 * @post This tree remains unchanged.
 */
    virtual void displaySideways(void) const;

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
    virtual int getDepth(const NodeData& searchItem) const;

/**---------------------- bstreeToArray() -------------------------------------
 * Fills an array of NodeData* by using an inorder traversal of the tree. The
 * tree is left empty. The size of the array is not checked and is assumed to
 * be sufficient to contain every element in the tree.
 * @param target[]  The array to fill with the NodeData* from this tree.
 * @pre target[] currently contains 100 NULL elements.
 * @post target[] contains every element found in this tree, in sorded order;
 *       this tree is empty.
 */
    virtual void bstreeToArray(NodeData* target[]);

/**---------------------- arrayToBSTree() -------------------------------------
 * Populates this tree from the contents of an array of sorted NodeData*. Any
 * contents of this tree are removed beforehand. The new tree is balanced by
 * using bisection of the array to choose the order of insertion.
 * @param source[]  The array from which to populate this tree.
 * @pre target[] is sorted in ascending order.
 * @post This tree is balanced and contains all NodeData* that were contained
 *       in source[]; all elements of source[] are now NULL.
 */
    virtual void arrayToBSTree(NodeData* source[]);
    
private:

    struct Node
    {
        NodeData *data;     // Pointer to data object
        Node     *left;     // Pointer to left child
        Node     *right;    // Pointer to right child
    }; // end Node

    Node *root;             // Pointer to root of tree

/**---------------------- inorderHelper() -------------------------------------
 * Traverses a binary search tree in sorted order, starting at treePtr, and
 * writes the data value of each item once, preceded by a space.
 * @param treePtr  Node at which to begin traversal.
 * @pre The ostream, output, can be written to; NodeData prvides the <<
 *      operator.
 * @post The ostream, output, contains the data element of every node in the
 *       subtree rooted at treePtr, space separated.
 */
    void inorderHelper(ostream& output, const Node *treePtr) const;

/**---------------------- sideways() ------------------------------------------
 * Displays a binary tree as though you are viewing it from the side;
 * hard coded displaying to standard output.
 * @param current  The Node being examined for display.
 * @param level  The depth of the current Node, used to determine indentation.
 * @pre cout can be written to.
 * @post cout contains a graphical representation of this tree.
 */
    void sideways(Node *current, int level) const;

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
    bool insertItem(Node *& treePtr, NodeData *newItem);

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
    bool retrieveItem(const Node *treePtr,
                      const NodeData& treeItem,
                            NodeData *& dataItem) const;

/**---------------------- copyTree() ------------------------------------------
 * Copies the tree rooted at treePtr into a tree rooted at newTreePtr.
 * @param treePtr  The root of the tree to be copied.
 * @param newTreePtr  A container for the root of a copy of treePtr.
 * @pre There is sufficient memory to allocate a new tree; NodeData provides
 *      the == and < operators.
 * @post newTreePtr points to the root of a structural copy of the tree whose
 *       root is pointed to by treePtr.
 */
    void copyTree(Node *treePtr, Node *& newTreePtr) const;

/**---------------------- destroyTree() ---------------------------------------
 * Deallocates memory for a tree.
 * @param treePtr  Pointer to the root of the tree to be deallocated.
 * @pre None.
 * @post treePtr points to an empty tree.
 */
    void destroyTree(Node *& treePtr);

/**---------------------- compare() -------------------------------------------
 * Compares two subtrees for equivalent content and structure.
 * @param lhs  A binary search tree to check for equality.
 * @param rhs  A binary search tree to check against for equality.
 * @pre None.
 * @post Both trees remain unchanged.
 * @return true if both trees are structurally identical and hold the same
 *         data; false, otherwise.
 */
    bool compare(const Node *lhs, const Node *rhs) const;

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
    int depth(const Node *treePtr, const NodeData& dataItem) const;

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
    void inorderToArray(Node *treePtr, NodeData *target[], int& index);

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
    void bisectBuild(NodeData *source[], int low, int high);

}; // end BinTree


#endif	/* _BINTREE_H */
