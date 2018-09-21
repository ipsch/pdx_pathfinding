#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_
//============================================================================
// Projekt     : oDataStructs
// Name        : rb_node.hpp
// Author      : ipsch (Ingmar Palle Schnell)
// contact     : i.p.schnell(at)gmail.com
// ceated      : 2018-07-27
// Version     : 1.1 (2018-07-30)
// Copyright   : CC:by-nc-sa
// Description : data structure "red-black tree"
//               (an implementation of self balancing 2-3-Trees)
// Reference   : Rudolf Bayer (1972). "Symmetric binary B-Trees:
//               Data structure and maintenance algorithms".
//               Acta Informatica. 1 (4): 290–306. doi:10.1007/BF00289509.
//============================================================================


// RB-Tree Conditions
// 	1.) Alle externen Blatt-Knoten (d. s. die #NIL-Knoten) sind schwarz.
// 	2.) Ist ein Knoten rot, so sind beide Kinder schwarz.
// 	3.) Jeder Pfad von einem gegebenen Knoten zu seinen Blattknoten enthält die gleiche Anzahl schwarzer Knoten.




#include <iostream>
#include "rb_node.hpp"



template <class ... Args> class RedBlackTree;


template <typename KeyType, typename ... Args>
class RedBlackTree<KeyType, Args...>
{
public :
	typedef RedBlackNode<KeyType, Args...> NodeType;
	RedBlackTree() : root_(0L) { }
	~RedBlackTree() {Clear(root_);};
	NodeType *find(const KeyType &key) const;
	NodeType *find(const KeyType &key, NodeType *N) const;
	void Insert(const KeyType &key, Args ... args);
	void Remove(NodeType *N);
	void Traverse() const;
	void Clear() {Clear(root_); root_=0L;}

//protected :
	NodeType *root_;         // base of tree
	const bool black_=true;  //
	const bool red_=false;

	// accessing Node properties and Node relations
	bool GetColor(NodeType *N) const {return (N==0L) ? black_ : N->color_;}
	NodeType *GetRoot(void) const {return root_;}
	NodeType *GetGrandparent(NodeType *N) const;
	NodeType *GetSibling(NodeType * N) const;
	NodeType *GetUncle(NodeType *N) const;
	bool IsLeftInnerGrandChild(NodeType *N, NodeType *G) const;
	bool IsRightInnerGrandChild(NodeType *N, NodeType *G) const;

	// Tree traversal and data visualization
	// NLR=Pre-order, LNR=In-order, LRN=Post-order
	template <typename Func>
	void TraverseNLR(Func func,NodeType *node);
	template <typename Func>
	void TraverseLNR(Func func,NodeType *node);
	template <typename Func>
	void TraverseLRN(Func func,NodeType *node);

	// Tree operation/manipulation
	void RotateLeft(NodeType *N);
	void RotateRight(NodeType *N);
	void BinaryInsert(NodeType *mountpoint, NodeType *newNode);
	void FixInsertion(NodeType *N);
	void FixRemoval(NodeType *N);
	void Clear(NodeType *N);
};






// accessing Node properties and Node relations ###############################
template <class KeyType, class ... Args>
RedBlackNode<KeyType, Args...> *RedBlackTree<KeyType, Args...>::GetGrandparent(RedBlackNode<KeyType, Args...> *N) const
// returns Grandparent of Node N (parent of parent)
// Note: N might be root
{
	return (N->parent_!=0L) ? N->parent_->parent_ : 0L;
}


template <class KeyType, class ... Args>
RedBlackNode<KeyType,Args...> *RedBlackTree<KeyType,Args...>::GetSibling(NodeType *N) const
// returns the sibling of Node N
// Note: N might be root & sibling might not exist (returning 0L aka NIL)
{
	NodeType *P = N->parent_;
	if (N->parent_ == 0L)
		return 0L; // No parent means no sibling
	return (N == P->left_child_) ? P->right_child_ : P->left_child_;
}


template <class KeyType, class ... Args>
RedBlackNode<KeyType,Args...> *RedBlackTree<KeyType,Args...>::GetUncle(NodeType *N) const
{
	NodeType *G = GetGrandparent(N);
	if (N->parent_ == G->left_child_)
		return G->right_child_;
	else
		return G->left_child_;
}


template <class KeyType, class ... Args>
bool RedBlackTree<KeyType,Args...>::IsRightInnerGrandChild(NodeType *N, NodeType *G) const
{
	if(G->right_child_==0L)
		return false;
	if(N == G->right_child_->left_child_)
		return true;
	return false;
}


template <class KeyType, class ... Args>
bool RedBlackTree<KeyType,Args...>::IsLeftInnerGrandChild(NodeType *N,NodeType *G) const
{
	if(G->left_child_==0L)
		return false;
	if(N == G->left_child_->right_child_)
		return true;
	return false;
}



// Tree traversal and data visualization ######################################
template <class KeyType, class ... Args>
RedBlackNode<KeyType,Args...> *RedBlackTree<KeyType,Args...>::find(const KeyType &key) const
{
	return RedBlackTree<KeyType,Args...>::find(key,root_);
}


template <class KeyType, class ... Args>
RedBlackNode<KeyType,Args...> *RedBlackTree<KeyType,Args...>::find(const KeyType &key, NodeType *N) const
{
	if (N==0L) return 0L;
	if (key == N->key_)
		return N;
	else if (key < N->key_)
		return RedBlackTree<KeyType,Args...>::find(key,N->left_child_);
	else if (key > N->key_)
		return RedBlackTree<KeyType,Args...>::find(key,N->right_child_);
	return 0L;
}


template <class KeyType, class ... Args>
void printNodeDetails(RedBlackNode<KeyType,Args...> *N)
{
	std::cout << "Node->data_:" << N->data_ << "\t";
	std::cout << "@ " << N << "\n";
	std::cout << "Node->left_child_:" << N->left_child_ << "\n";
	std::cout << "Node->right_child_:" << N->right_child_ << "\n";
	std::cout << "Node->parent_:" << N->parent_ << "\n";
	std::cout << "Node->color_:" << N->color_ << "\n\n";
}


template <class NodeType>
void printNodeDID(NodeType *N)
{
	static int number_of_NIL_nodes = 0;

	if(N->left_child_!=0L)
	{
		std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
	    //std::cout << " [label=\""<< N->data_ << "\"] ";
	    std::cout << "\" -> \"";
	    std::cout << N->left_child_ << "(" << N->left_child_->key_ << "/" << N->left_child_->color_ << ")\";";
	    std::cout << std::endl;
	}
	else
	{
		std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
		std::cout << "\" -> \"0L (" << number_of_NIL_nodes << ")\"" << std::endl;
		++number_of_NIL_nodes ;
	}

	if(N->right_child_!=0L)
	{
		std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
		std::cout << "\" -> \"" ;
		std::cout <<  N->right_child_ << "(" << N->right_child_->key_ << "/" << N->right_child_->color_ << ")\";";
		std::cout << std::endl;
	}
	else
	{
		std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
	    std::cout << "\" -> \"0L (" << number_of_NIL_nodes << ")\"" << std::endl;
		++number_of_NIL_nodes;
	}


	if(N->parent_!=0L)
	{
		std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
		std::cout << "\" -> \"";
		std::cout <<  N->parent_ << "(" << N->parent_->key_ << "/" << N->parent_->color_ << ")\";";
		std::cout << std::endl;
	}
	else
	{
		std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
		std::cout << "\" -> \"0L\"";
		std::cout << std::endl;
	}

	return;
}



template <class KeyType, class ... Args>
template <typename Func>
void RedBlackTree<KeyType,Args...>::TraverseNLR(Func func, NodeType *node)
/**
 * \brief Traverses the Tree in pre-order (NLR = Node, Left, Right) and applies func to all nodes visited
 *
 * \details Making func a template makes TraverseLRN() flexible and usefull in many ways;
 * for example can it be used as a callback function to output the contend of the trees nodes
 * But since usage isn't too straight forward we give an example on how to use it:
 *
 * \example
 * \code
 * class BigObject ...;                     // A class with extensive use of memory (lets say a big array)
 * RedBlackTree<int, *BigObject> list;      // A list in form of a RedBlackTree
 * for(i=0; i<100; ++i)                     // Filling the tree with pointers to BigObjects
 * 		list.Insert(i, new BigObject(..));
 * ..
 *                                   // Do stuff with the list
 * // Print all keys and some_member_ of BigObject
 * list.TraverseNLR(
 *			[](RedBlackTree<int, *BigObject>::NodeType *bar)
 *				{std::cout << bar->key_ << "\t" << bar_->data_->some_member_ << std::endl;});
 *
 * // Clean up list
 * list.TraverseNLR(
 *			[](RedBlackTree<int, *BigObject>::NodeType *bar)
 *				{delete bar->data_; bar->data_=NULL;});
 * return;
 * \endcode
 *
 * \param[in] *Node Pointer a node where to start traversing (default = this->root_ (The trees root))
 * \param[in] func a function pointer or a closure (lambda-function) that will be applied to all nodes
 * visited
 */
{
	if (node==0L)
		return;
	func(node);
	if (node->left_child_!=0L)
		TraverseLRN(func,node->left_child_);
	if (node->right_child_!=0L)
		TraverseLRN(func,node->right_child_);
	return;
}


template <class KeyType, class ... Args>
template <typename Func>
void RedBlackTree<KeyType,Args...>::TraverseLNR(Func func, NodeType *node)
/**
 * \brief Traverses the Tree in in-order (LNR = Left, Node, Right) and applies func to all nodes visited
 *
 * \param[in] *Node Pointer a node where to start traversing (default = this->root_ (The trees root))
 * \param[in] func a function pointer or a closure (lambda-function) that will be applied to all nodes
 * visited
 *
 * \sa Please see documentation of TraverseNLR(..) for details
 */
{
	if (node==0L)
		return;
	if (node->left_child_!=0L)
		TraverseLRN(func,node->left_child_);
	func(node);
	if (node->right_child_!=0L)
		TraverseLRN(func,node->right_child_);
	return;
}


template <class KeyType, class ... Args>
template <typename Func>
void RedBlackTree<KeyType,Args...>::TraverseLRN(Func func, NodeType *node)
/**
 * \brief Traverses the Tree in post-order (LRN = Left, Right, Node) and applies func to all nodes visited
 *
 * \param[in] *Node Pointer a node where to start traversing (default = this->root_ (The trees root))
 * \param[in] func a function pointer or a closure (lambda-function) that will be applied to all nodes
 * visited
 *
 * \sa Please see documentation of TraverseNLR(..) for details
 */
{
	if (node==0L)
		return;
	if (node->left_child_!=0L)
		TraverseLRN(func,node->left_child_);
	func(node);
	if (node->right_child_!=0L)
		TraverseLRN(func,node->right_child_);
	return;
}


// Tree operation/manipulation ################################################
template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::RotateLeft(NodeType *N)
// Rotates a Node N according to the diagram below
// Nodes possess pointers to left and right child AND to parent
// => there are six connections to be changed (3Nodes*2connections)
//            P                                 P
//           /                                 /
//          N         rotateLeft(N)           R
//         / \            ====>              / \
//        A   R                             N   B
//           / \                           / \
//          M   B                         A   M
{
	NodeType *R = N->right_child_;
	if(R==0L)
		return;
	// reconnect P
	R->parent_=N->parent_;
	if(N->parent_!=0L)
		if (N->parent_->right_child_==N)
			N->parent_->right_child_=R;
		else
			N->parent_->left_child_=R;
	// reconnect M
	N->right_child_=R->left_child_;
	if(R->left_child_!=0L)
		R->left_child_->parent_=N;
	// reconnect N and L
	N->parent_=R;
	R->left_child_=N;
	return;
}


template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::RotateRight(NodeType *N)
// Rotates a Node N according to the diagram below
// Nodes possess pointers to left and right child AND to parent
// => there are six connections to be changed (3Nodes*2connections)
//            P                                 P
//           /                                 /
//          N         rotateRight(N)          L
//         / \            ====>              / \
//        L   B                             A   N
//       / \                                   / \
//      A   M                                 M   B
{
	NodeType *L = N->left_child_;
	if(L==0L)
		return;
	// reconnect P
	L->parent_=N->parent_;
	if(N->parent_!=0L)
		if (N->parent_->left_child_==N)
			N->parent_->left_child_=L;
		else
			N->parent_->right_child_=L;
	// reconnect M
	N->left_child_=L->right_child_;
	if(L->right_child_!=0L)
		L->right_child_->parent_=N;
	// reconnect N and L
	N->parent_=L;
	L->right_child_=N;
	return;
}


template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::Insert(const KeyType &key, Args ... args)
// This insert function serves as interface / is public
// It manages features specific for RB-Trees;
// It utilizes a recursive insert function that is private and
// related to the underlying data structure of a BSTree
{
	NodeType *newNode = new NodeType(key, args ...);

	// insert newNode as if we just had a
	// binary-search-Tree, restore Conditions
	// specific for red-black-trees afterwards
	RedBlackTree<KeyType,Args...>::BinaryInsert(root_, newNode);
	RedBlackTree<KeyType,Args...>::FixInsertion(newNode);

	// since FixTree can change the root
	root_ = newNode;
	while(root_->parent_!=0L)
		root_=root_->parent_;
}


template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::BinaryInsert(NodeType *mountpoint,
		NodeType *newNode)
{
	// newNode to Left Sub-branch
	if(mountpoint!=0L && newNode->key_<mountpoint->key_)
	{
		if(mountpoint->left_child_!=0L)
		{
			BinaryInsert(mountpoint->left_child_, newNode);
			return;
		}
		else
			mountpoint->left_child_=newNode;
	}
	// newNode to Right Sub-branch
	else if (mountpoint!=0L) // && (newNode->data_>=mountpoint->data_)
	{
		if(mountpoint->right_child_!=0L)
		{
			BinaryInsert(mountpoint->right_child_, newNode);
			return;
		}
		else
			mountpoint->right_child_=newNode;
	}

	newNode->parent_=mountpoint;
	newNode->left_child_=0L;
	newNode->right_child_=0L;
	newNode->color_=red_;

	return;
}


template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::FixInsertion(NodeType *N)
{
	if(N->parent_==0L)
	{
		// N has no parent => N is root => set color to BLACK
		N->color_=true;
	}
	else if(N->parent_->color_==true)
	{
		return; // N has a BLACK parent => N is RED => insertion is no Problem
	}
	else if( (GetUncle(N)!=0L?GetUncle(N)->color_:true)==false) // N has RED parent AND RED uncle
	{                                // =>
		N->parent_->color_ = black_;
		GetUncle(N)->color_ = black_;
		GetGrandparent(N)->color_ = red_;
		FixInsertion(GetGrandparent(N));
	}
	else
	{
		NodeType *p = N->parent_;
		NodeType *g = GetGrandparent(N);

		if (IsLeftInnerGrandChild(N,g))
		{
			RotateLeft(p);
			N = N->left_child_;
		}
		else if (IsRightInnerGrandChild(N,g))
		{
			RedBlackTree<KeyType,Args...>::RotateRight(p);
			N = N->right_child_;
		}

		p = N->parent_;
		g = GetGrandparent(N);

		if (N == p->left_child_)
			RedBlackTree<KeyType,Args...>::RotateRight(g);
		else
			RedBlackTree<KeyType,Args...>::RotateLeft(g);
		p->color_ = true;
		g->color_ = false;
	}
	return;
}


template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::Remove(NodeType *N)
// remove let you pick an arbitrary node N within the rb-tree and delete it.
// remove works in three steps.
// step 1: find node D in Ns left (or right) subtree with next smaller (or greater) key (favor left/right subtree depending on subtrees depth).
//         Move contend of Node D to N (key and data. RB-tree properties as color/children etc. stay UNCHANGED).
//         (Note: D will have at most one child by property of a binary tree (node is "most left" or "most right" Node in the subtree)
// step 2: if D has a child connect Ds child to Ds parent by replacing D. D is now unconnected => delete D (after step 3).
//         (binary tree properties are preserved to this point rb-tree properties might be lost by disconnecting D.
// step 3: repair rb-tree properties starting at Ds child.
//         There are a view cases where rb-tree properties can be restored by repainting Nodes in Ds childs proximity.
//         The more complex cases (where Nodes have to be moved) are handled by the FixRemoval function.
// NOTE  : Steps 2 and 3 can be switched without changing the result (FixRemoval moves D and Ds subtree (aka D and its child) like
//         a single unit. By applying step 2 first We don't have to implement lots of special rules to handle Ds childs NIL nodes.
{
	NodeType *left = N->left_child_;
	NodeType *right = N->right_child_;
	NodeType *D = N;

	// step 1: find node D
	// Note: The "most RIGHT" node from LEFT sub tree has the next
	//       SMALLER key to N (and vice versa for the right sub tree)
	while(left!=0L || right!=0L )
	{
		if(left!=0L)
		{
			D = left;
			left = left->right_child_;
		}
		if(right!=0L)
		{
			D = right;
			right = right->left_child_;
		}
	} // END WHILE

	CopyContent(*N,*D);

	//step 2:
	// D has been marked for deletion (reminder: D has at most one non-leaf child)
	// Connect Ds Child C to Ds Parent by replacing D
	//if(D==root_) // D->parent_==0L (Note: if D==root_ => D has only NIL children
	//{
	//	root_=0L;
	//	delete D;
	//	return;
	//}

	//     (A)            (B)            (C)
	//             P/?            P/B            P/?
 	//            /              /              /
	//         D/B            D/R            D/B
	//        /   \          /   \          /   \
	//     NIL     NIL    NIL     NIL    NIL     C/R
	//                                          /   \
	//                                       NIL     NIL
	//
	//

	NodeType *C = (D->right_child_==0L) ? D->left_child_ : D->right_child_;

	// case (A)
	if( (D->color_==black_) && (C==0L) )
		FixRemoval(D);

	// all cases (implicitly (B) )
	if(D->parent_!=0L)
	{
	    if (D == D->parent_->left_child_)
	        D->parent_->left_child_ = C;
	    else
	        D->parent_->right_child_ = C;
	}
	else
		root_ = C;

	// case (C)
	if(C!=0L)
	{
		C->parent_=D->parent_;
		C->color_ = black_;
	}

	delete D;
}


template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::FixRemoval(NodeType *N)
{
	//case 1:
	if (N->parent_ == 0L)
	{
		std::cout << "FixRemove (case 1)\n";
		root_=N;
		return;
	}


	//delete_case2(n);
	//return;
	NodeType *S = GetSibling(N);
	if (S->color_ == red_)
	{
		std::cout << "FixRemove (case 2)\n";
		N->parent_->color_ = red_;
		S->color_ = black_;
		if (N == N->parent_->left_child_)
			RotateLeft(N->parent_);
		else
			RotateRight(N->parent_);
	}

	//delete_case3(n);
	S = GetSibling(N);
	if ((N->parent_->color_ == black_) &&
			(S->color_ == black_) &&
			(GetColor(S->left_child_) == black_) &&
			(GetColor(S->right_child_) == black_))
	{
		std::cout << "FixRemove (case 3)\n";
		S->color_ = red_;
		FixRemoval(N->parent_);
		return;
	}


	//delete_case4(n);
	S = GetSibling(N);
	if ((N->parent_->color_ == red_) &&
			(S->color_ == black_) &&
			(GetColor(S->left_child_) == black_) &&
			(GetColor(S->right_child_) == black_))
	{
		std::cout << "FixRemove (case 4)\n";
		S->color_ = red_;
		N->parent_->color_ = black_;
		return;
	}


	//delete_case5(n);
	S = GetSibling(N);
	if  (S->color_ == black_)
	{
		std::cout << "FixRemove (case 5)\n";
		// this if statement is trivial,
		// due to case 2 (even though case 2 changed the sibling to a sibling's child,
		// the sibling's child can't be red_, since no red_ parent_ can have a red_ child).
		//
		// the following statements just force the red_ to be on the left_child_ of the left_child_ of the parent_,
		// or right_child_ of the right_child_, so case six will rotate correctly.
		if ((N == N->parent_->left_child_) &&
				(GetColor(S->right_child_) == black_) &&
				(GetColor(S->left_child_) == red_))
		{ /* this last test is trivial too due to cases 2-4. */
			S->color_ = red_;
			S->left_child_->color_ = black_;
			RotateRight(S);
		}
		else if ((N == N->parent_->right_child_) &&
				(GetColor(S->left_child_) == black_) &&
				(GetColor(S->right_child_) == red_))
		{/* this last test is trivial too due to cases 2-4. */
			S->color_ = red_;
			S->right_child_->color_ = black_;
			RotateLeft(S);
		}
	}


	//delete_case6(n);
	S = GetSibling(N);
	std::cout << "FixRemove (case 6)\n";
	S->color_ = N->parent_->color_;
	N->parent_->color_ = black_;

	if (N == N->parent_->left_child_)
	{
		S->right_child_->color_ = black_;
		RotateLeft(N->parent_);
	}
	else
	{
		S->left_child_->color_ = black_;
		RotateRight(N->parent_);
	}

}


template <class KeyType, class ... Args>
void RedBlackTree<KeyType,Args...>::Clear(NodeType *N)
{
	if(N==0L)
		return;
	Clear(N->left_child_);
	Clear(N->right_child_);
	delete N;
	return;
}


#endif
