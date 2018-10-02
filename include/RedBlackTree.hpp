/** \file
 * 		RedBlackTree.hpp
 *
 *  \brief
 *  	contains data structure "red-black tree"
 *      (an implementation of self balancing 2-3-Trees)
 *
 *  \version
 *  	2018-10-02 ipsch: 1.2 - reworked documentation
 *
 *  \authors
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */

	// Reference   : Rudolf Bayer (1972). "Symmetric binary B-Trees:
	//               Data structure and maintenance algorithms".
	//               Acta Informatica. 1 (4): 290–306. doi:10.1007/BF00289509.
	// RB-Tree Conditions
	// 	1.) Alle externen Blatt-Knoten (d. s. die #NIL-Knoten) sind schwarz.
	// 	2.) Ist ein Knoten rot, so sind beide Kinder schwarz.
	// 	3.) Jeder Pfad von einem gegebenen Knoten zu seinen Blattknoten enthält die gleiche Anzahl schwarzer Knoten.


#pragma once

#include "tuple.hpp"
#include <iostream> // ToDo: remove in shipping version

namespace o_data_structures
{

	/** \brief Prototype for variadic template class RedBlackNode
	 */
	template <class ... Args> struct RedBlackNode;


	/** \brief Specialization of class RedBlackNode with only one field (key_)
	 */
	template <class KeyType>
	class RedBlackNode<KeyType>
	{
	public :
		typedef RedBlackNode<KeyType> NodeType;
		NodeType *left_;
		NodeType *right_;
		NodeType *parent_;
		KeyType key_;
		bool color_;
		RedBlackNode(KeyType key) :
			left_(0L), right_(0L), parent_(0L), key_(key), color_(true)
		{
			// Nothing to do here
		};
	}; // END CLASS RedBlackNode<KeyType>


	/** \brief Specialization of class RedBlackNode with two fields (key_, data_)
	 */
	template <class KeyType, class DataType>
	class RedBlackNode<KeyType, DataType>
	{
	public :
		typedef RedBlackNode<KeyType,DataType> NodeType;
			NodeType *left_;
			NodeType *right_;
			NodeType *parent_;
			KeyType key_;
			DataType data_;
			bool color_;
			RedBlackNode(KeyType key, DataType data) :
				left_(0L), right_(0L), parent_(0L), key_(key), data_(data), color_(true)
			{
				// Nothing to do here
			};
	}; // END CLASS RedBlackNode<KeyType, DataType>



	/*

	 ToDo: implement operator=

	template <class KeyType>
	void CopyContent(RedBlackNode<KeyType> &target, RedBlackNode<KeyType> &source)
	{
		target.key_ = source.key_;
		return;
	}

	template <class KeyType, class DataType>
	void CopyContent(RedBlackNode<KeyType, Args...> &target, RedBlackNode<KeyType, Args...> &source)
	{
		target.key_ = source.key_;
		target.data_ = source.data_;
		return;
	}


	 */






	/** \brief Prototype for variadic template class RedBlackTree
	 */
	//template <class ... Args> class RedBlackTree;




	/** \brief Specialization of class RedBlackNode with only one field (key_)
	 */
	template <class KeyType, class DataType>
	class RedBlackTree//<KeyType,DataType>
	{
	public :
		typedef RedBlackNode<KeyType, DataType> NodeType;
		RedBlackTree() : root_(0L) { }
		~RedBlackTree() {clear(root_);};

		NodeType *root_;         // base of tree

		NodeType *find(const KeyType &key) const;
		NodeType *find(const KeyType &key, NodeType *N) const;
		void insert(const KeyType &key, const DataType &data);
		void remove(NodeType *N);
		//void traverse() const;
		void clear() {clear(root_); root_=0L;}
		void clear(NodeType *n);
	//protected :



		// accessing Node properties and Node relations

		NodeType *get_root(void) const {return root_;}


		// Tree traversal and data visualization
		// NLR=Pre-order, LNR=In-order, LRN=Post-order
		template <typename Func>
		void traverse_NLR(Func func, NodeType *node);
		template <typename Func>
		void traverse_LNR(Func func, NodeType *node);
		template <typename Func>
		void traverse_LRN(Func func, NodeType *node);

		// Tree operation/manipulation
		void rotate_left(NodeType *N);
		void rotate_right(NodeType *N);
		void BinaryInsert(NodeType *mountpoint, NodeType *newNode);
		void FixInsertion(NodeType *N);
		void FixRemoval(NodeType *N);

	protected :
		static const bool black_ = true;
		static const bool red_ = false;


		NodeType *get_grandparent(NodeType *n) const;
		NodeType *get_sibling(NodeType *n) const;
		NodeType *get_uncle(NodeType *n) const;
		bool is_LeftInnerGrandChild(NodeType *n, NodeType *g) const;
		bool is_RightInnerGrandChild(NodeType *n, NodeType *g) const;
		inline bool get_color(NodeType *n) const {return (n == 0L) ? black_ : n->color_;}

	};



	// accessing Node properties and Node relations ###############################
	// returns Grandparent of Node N (parent of parent)
	// Note: N might be root
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::get_grandparent(NodeType *n) const
	{
		return (n->parent_ != 0L) ? n->parent_->parent_ : 0L;
	}


	// returns the sibling of Node N
	// Note: N might be root & sibling might not exist (returning 0L aka NIL)
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::get_sibling(NodeType *n) const
	{
		NodeType* p = n->parent_;
		if (n->parent_ == 0L)
			return 0L;
		return (n == p->left_) ? p->right_ : p->left_;
	}


	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::get_uncle(NodeType *n) const
	{
		NodeType* g = get_grandparent(n);
		return ( n->parent_ == g->left_ ) ? g->right_ : g->left_;
	}


	template <class KeyType, class DataType>
	bool RedBlackTree<KeyType,DataType>::is_RightInnerGrandChild(NodeType *n, NodeType *g) const
	{
		if (g->right_== 0L)
			return false;
		return (n == g->right_->left_ ) ? true : false;
	}


	template <class KeyType, class DataType>
	bool RedBlackTree<KeyType,DataType>::is_LeftInnerGrandChild(NodeType *n, NodeType *g) const
	{
		if (g->left_ == 0L)
			return false;
		if (n == g->left_->right_)
			return true;
		return false;
	}




	// Tree traversal and data visualization ######################################
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::find(const KeyType &key) const
	{
		return RedBlackTree<KeyType,DataType>::find(key,root_);
	}


	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::find(const KeyType &key, NodeType *N) const
	{
		if (N==0L) return 0L;
		if (key == N->key_)
			return N;
		else if (key < N->key_)
			return RedBlackTree<KeyType,DataType>::find(key,N->left_);
		else if (key > N->key_)
			return RedBlackTree<KeyType,DataType>::find(key,N->right_);
		return 0L;
	}


	template <class KeyType, class DataType>
	void printNodeDetails(RedBlackNode<KeyType,DataType> *n)
	{
		std::cout << "Node->data_:" << n->data_ << "\t";
		std::cout << "@ " << n << "\n";
		std::cout << "Node->left_:" << n->left_ << "\n";
		std::cout << "Node->right_:" << n->right_ << "\n";
		std::cout << "Node->parent_:" << n->parent_ << "\n";
		std::cout << "Node->color_:" << n->color_ << "\n\n";
	}


	template <class NodeType>
	void printNodeDID(NodeType *N)
	{
		static int number_of_NIL_nodes = 0;

		if(N->left_!=0L)
		{
			std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
			//std::cout << " [label=\""<< N->data_ << "\"] ";
			std::cout << "\" -> \"";
			std::cout << N->left_ << "(" << N->left_->key_ << "/" << N->left_->color_ << ")\";";
			std::cout << std::endl;
		}
		else
		{
			std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
			std::cout << "\" -> \"0L (" << number_of_NIL_nodes << ")\"" << std::endl;
			++number_of_NIL_nodes ;
		}

		if(N->right_!=0L)
		{
			std::cout << "\""<< N << "(" << N->key_ << "/" << N->color_ << ")";
			std::cout << "\" -> \"" ;
			std::cout <<  N->right_ << "(" << N->right_->key_ << "/" << N->right_->color_ << ")\";";
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



	template <class KeyType, class DataType>
	template <typename Func>
	void RedBlackTree<KeyType,DataType>::traverse_NLR(Func func, NodeType *node)
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
		if (node->left_!=0L)
			traverse_LRN(func,node->left_);
		if (node->right_!=0L)
			traverse_LRN(func,node->right_);
		return;
	}


	template <class KeyType, class DataType>
	template <typename Func>
	void RedBlackTree<KeyType,DataType>::traverse_LNR(Func func, NodeType *node)
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
		if (node->left_!=0L)
			TraverseLRN(func,node->left_);
		func(node);
		if (node->right_!=0L)
			TraverseLRN(func,node->right_);
		return;
	}


	/**
	 * \brief Traverses the Tree in post-order (LRN = Left, Right, Node) and applies func to all nodes visited
	 *
	 * \param[in] *Node Pointer a node where to start traversing (default = this->root_ (The trees root))
	 * \param[in] func a function pointer or a closure (lambda-function) that will be applied to all nodes
	 * visited
	 *
	 * \sa Please see documentation of TraverseNLR(..) for details
	 */
	template <class KeyType, class DataType>
	template <typename Func>
	void RedBlackTree<KeyType,DataType>::traverse_LRN(Func func, NodeType *node)
	{
		if (node == 0L)
			return;
		if (node->left_ != 0L)
			traverse_LRN(func, node->left_);
		func(node);
		if (node->right_ != 0L)
			traverse_LRN(func, node->right_);
		return;
	}


	// Tree operation/manipulation ################################################
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::rotate_left(NodeType *N)
	// Rotates a Node N according to the diagram below
	// Nodes possess pointers to left and right child AND to parent
	// => there are six connections to be changed (3Nodes*2connections)
	//            P                                 P
	//           /                                 /
	//          N         rotate_left(N)           R
	//         / \            ====>              / \
	//        A   R                             N   B
	//           / \                           / \
	//          M   B                         A   M
	{
		NodeType *R = N->right_;
		if(R==0L)
			return;
		// reconnect P
		R->parent_=N->parent_;
		if(N->parent_!=0L)
			if (N->parent_->right_==N)
				N->parent_->right_=R;
			else
				N->parent_->left_=R;
		// reconnect M
		N->right_=R->left_;
		if(R->left_!=0L)
			R->left_->parent_=N;
		// reconnect N and L
		N->parent_=R;
		R->left_=N;
		return;
	}


	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::rotate_right(NodeType *N)
	// Rotates a Node N according to the diagram below
	// Nodes possess pointers to left and right child AND to parent
	// => there are six connections to be changed (3Nodes*2connections)
	//            P                                 P
	//           /                                 /
	//          N         rotate_right(N)          L
	//         / \            ====>              / \
	//        L   B                             A   N
	//       / \                                   / \
	//      A   M                                 M   B
	{
		NodeType *L = N->left_;
		if(L==0L)
			return;
		// reconnect P
		L->parent_=N->parent_;
		if(N->parent_!=0L)
			if (N->parent_->left_==N)
				N->parent_->left_=L;
			else
				N->parent_->right_=L;
		// reconnect M
		N->left_=L->right_;
		if(L->right_!=0L)
			L->right_->parent_=N;
		// reconnect N and L
		N->parent_=L;
		L->right_=N;
		return;
	}


	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::insert(const KeyType &key, const DataType &data)
	// This insert function serves as interface / is public
	// It manages features specific for RB-Trees;
	// It utilizes a recursive insert function that is private and
	// related to the underlying data structure of a BSTree
	{
		NodeType *newNode = new NodeType(key, data);

		// insert newNode as if we just had a
		// binary-search-Tree, restore Conditions
		// specific for red-black-trees afterwards
		RedBlackTree<KeyType,DataType>::BinaryInsert(root_, newNode);
		RedBlackTree<KeyType,DataType>::FixInsertion(newNode);

		// since FixTree can change the root
		root_ = newNode;
		while(root_->parent_!=0L)
			root_ = root_->parent_;
	}


	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::BinaryInsert(NodeType *mountpoint,
			NodeType *newNode)
	{
		// newNode to Left Sub-branch
		if(mountpoint!=0L && newNode->key_<mountpoint->key_)
		{
			if(mountpoint->left_!=0L)
			{
				BinaryInsert(mountpoint->left_, newNode);
				return;
			}
			else
				mountpoint->left_ = newNode;
		}
		// newNode to Right Sub-branch
		else if (mountpoint!=0L) // && (newNode->data_>=mountpoint->data_)
		{
			if(mountpoint->right_!=0L)
			{
				BinaryInsert(mountpoint->right_, newNode);
				return;
			}
			else
				mountpoint->right_=newNode;
		}

		newNode->parent_=mountpoint;
		newNode->left_=0L;
		newNode->right_=0L;
		newNode->color_=red_;

		return;
	}


	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::FixInsertion(NodeType *N)
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
		else if( (get_uncle(N)!=0L?get_uncle(N)->color_:true)==false) // N has RED parent AND RED uncle
		{                                // =>
			N->parent_->color_ = black_;
			get_uncle(N)->color_ = black_;
			get_grandparent(N)->color_ = red_;
			FixInsertion(get_grandparent(N));
		}
		else
		{
			NodeType *p = N->parent_;
			NodeType *g = get_grandparent(N);

			if (is_LeftInnerGrandChild(N,g))
			{
				rotate_left(p);
				N = N->left_;
			}
			else if (is_RightInnerGrandChild(N,g))
			{
				RedBlackTree<KeyType,DataType>::rotate_right(p);
				N = N->right_;
			}

			p = N->parent_;
			g = get_grandparent(N);

			if (N == p->left_)
				RedBlackTree<KeyType,DataType>::rotate_right(g);
			else
				RedBlackTree<KeyType,DataType>::rotate_left(g);
			p->color_ = true;
			g->color_ = false;
		}
		return;
	}




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

	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::remove(NodeType *N)
	{
		NodeType *left = N->left_;
		NodeType *right = N->right_;
		NodeType *D = N;

		// step 1: find node D
		// Note: The "most RIGHT" node from LEFT sub tree has the next
		//       SMALLER key to N (and vice versa for the right sub tree)
		while(left!=0L || right!=0L )
		{
			if(left!=0L)
			{
				D = left;
				left = left->right_;
			}
			if(right!=0L)
			{
				D = right;
				right = right->left_;
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

		NodeType *C = ( D->right_ == 0L ) ? D->left_ : D->right_;

		// case (A)
		if( ( D->color_ == black_ ) && ( C == 0L ) )
			FixRemoval(D);

		// all cases (implicitly (B) )
		if(D->parent_!=0L)
		{
			if (D == D->parent_->left_)
				D->parent_->left_ = C;
			else
				D->parent_->right_ = C;
		}
		else
			root_ = C;

		// case (C)
		if(C!=0L)
		{
			C->parent_ = D->parent_;
			C->color_ = black_;
		}

		delete D;
	}


	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::FixRemoval(NodeType *N)
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
			if (N == N->parent_->left_)
				rotate_left(N->parent_);
			else
				rotate_right(N->parent_);
		}

		//delete_case3(n);
		S = get_sibling(N);
		if ((N->parent_->color_ == black_) &&
				(S->color_ == black_) &&
				(GetColor(S->left_) == black_) &&
				(GetColor(S->right_) == black_))
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
				(GetColor(S->left_) == black_) &&
				(GetColor(S->right_) == black_))
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
			// the following statements just force the red_ to be on the left_ of the left_ of the parent_,
			// or right_ of the right_, so case six will rotate correctly.
			if ((N == N->parent_->left_) &&
					(GetColor(S->right_) == black_) &&
					(GetColor(S->left_) == red_))
			{ /* this last test is trivial too due to cases 2-4. */
				S->color_ = red_;
				S->left_->color_ = black_;
				rotate_right(S);
			}
			else if ((N == N->parent_->right_) &&
					(GetColor(S->left_) == black_) &&
					(GetColor(S->right_) == red_))
			{/* this last test is trivial too due to cases 2-4. */
				S->color_ = red_;
				S->right_->color_ = black_;
				rotate_left(S);
			}
		}


		//delete_case6(n);
		S = GetSibling(N);
		std::cout << "FixRemove (case 6)\n";
		S->color_ = N->parent_->color_;
		N->parent_->color_ = black_;

		if (N == N->parent_->left_)
		{
			S->right_->color_ = black_;
			rotate_left(N->parent_);
		}
		else
		{
			S->left_->color_ = black_;
			rotate_right(N->parent_);
		}

	}


	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::clear(NodeType *n)
	{
		if ( n == 0L )
			return;
		clear(n->left_);
		clear(n->right_);
		delete n;
		return;
	}


} // END OF NAMESPACE o_data_structures
