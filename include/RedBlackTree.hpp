/** \file
 * 		RedBlackTree.hpp
 *
 *  \brief
 *  	Provides a "red-black tree" data structure
 *
 *  \detail
 *  	Contains
 *  	- Class RedBlackTree (a self balancing binary tree structure)
 *  	- Class RedBlackNode (a node type designed to be used in RedBlackTree)
 *  	Both classes are part of namespace o_data_structures
 *  	(a collection of different data structures)
 *
 *  \version
 *  	2018-10-11 ipsch: 1.0.0 - final
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */

#pragma once
#ifndef RED_BLACK_TREE_HPP_
#define RED_BLACK_TREE_HPP_

#include <iostream>

namespace o_data_structures
{
	const bool RED = false;   //< Node color
	const bool BLACK = true;  //< Node color


	//! \brief Prototype for variadic template class RedBlackNode
	template <class ... Args> struct RedBlackNode;


	//! \brief Specialization of class RedBlackNode with only one field (key_)
	template <class KeyType>
	class RedBlackNode<KeyType>
	{
	public :
		typedef RedBlackNode<KeyType> NodeType;
		RedBlackNode(KeyType key);
		NodeType operator=(const NodeType &rhs);
		NodeType copy_internals(const NodeType &rhs);

		NodeType *left_;    //< pointer to left child
		NodeType *right_;   //< pointer to right child
		NodeType *parent_;  //< pointer to parent node
		KeyType key_;       //< this nodes search key
		bool color_;        //< this nodes color

	}; // END CLASS RedBlackNode<KeyType>


	//! \brief Specialization of class RedBlackNode with two fields (key_, data_)
	template <class KeyType, class DataType>
	class RedBlackNode<KeyType, DataType>
	{
	public :
		typedef RedBlackNode<KeyType,DataType> NodeType;
		RedBlackNode(const KeyType &key, const DataType &data);
		NodeType operator=(const NodeType &rhs);
		NodeType copy_internals(const NodeType &rhs);

		NodeType *left_;    //< pointer to left child
		NodeType *right_;   //< pointer to right child
		NodeType *parent_;  //< pointer to parent node
		KeyType key_;       //< this nodes search key
		DataType data_;     //< field for some data with this node/key
		bool color_;        //< this nodes color

	}; // END CLASS RedBlackNode<KeyType, DataType>


	//! \brief Constructor
	template <class KeyType>
	RedBlackNode<KeyType>::RedBlackNode(KeyType key) :
				left_(0L), right_(0L), parent_(0L), key_(key), color_(false)
	{
		// Nothing to do here
	};


	//! \brief Constructor
	template <class KeyType, class DataType>
	RedBlackNode<KeyType,DataType>::RedBlackNode(const KeyType &key, const DataType &data) :
			left_(0L), right_(0L), parent_(0L), key_(key), data_(data), color_(RED)
	{
		// Nothing to do here
	};


	/** \brief Copies only "internal" field key
	 *  \details copy copy_internals(..) is needed for node
	 *  removal in class RedBlackTree. It copies only internal fields
	 *  leaving pointer to parent and child nodes untouched.
	 *  \param[in] rhs The node to copy from
	 *  \return A partial copy of rhs
	 */
	template <class KeyType>
	RedBlackNode<KeyType>  RedBlackNode<KeyType>::copy_internals(const RedBlackNode<KeyType> &rhs)
	{
		this->color_ = rhs.color_;
		this->key_ = rhs.key_;
		return *this;
	}


	/** \brief Copies only "internal" fields key and data
	 *  \details copy copy_internals(..) is needed for node
	 *  removal in class RedBlackTree. It copies only internal fields
	 *  leaving pointer to parent and child nodes untouched.
	 *  \param[in] rhs The node to copy from
	 *  \return A partial copy of rhs
	 */
	template <class KeyType, class DataType>
	RedBlackNode<KeyType,DataType> RedBlackNode<KeyType,DataType>::copy_internals(const RedBlackNode<KeyType,DataType> &rhs)
	{
		this->color_ = rhs.color_;
		this->data_ = rhs.data_;
		this->key_ = rhs.key_;
		return *this;
	}


	/** \brief operator=
	 *  \details copy all data fields of RedBlackNode
	 *  copies pointer values, doesn't copy pointer content
	 *  \param[in] rhs The node to copy from
	 *  \return a copy of rhs
	 */
	template <class KeyType>
	RedBlackNode<KeyType> RedBlackNode<KeyType>::operator=(const RedBlackNode<KeyType> &rhs)
	{
		this->right_ = rhs.right_;
		this->left_ = rhs.left_;
		this->parent_ = rhs.parent_;
		this->color_ = rhs.color_;
		this->key_ = rhs.key_;
		return *this;
	}


	/** \brief operator=
	 *  \details copy all data fields of RedBlackNode
	 *  copies pointer values, doesn't copy pointer content
	 *  \param[in] rhs The node to copy from
	 *  \return a copy of rhs
	 */
	template <class KeyType, class DataType>
	RedBlackNode<KeyType,DataType> RedBlackNode<KeyType,DataType>::operator=(const RedBlackNode<KeyType,DataType> &rhs)
	{
		this->right_ = rhs.right_;
		this->left_ = rhs.left_;
		this->parent_ = rhs.parent_;
		this->color_ = rhs.color_;
		this->data_ = rhs.data_;
		this->key_ = rhs.key_;
		return *this;
	}


	/** \brief function to print information about a node to std::cout;
	 *  \detail designed to work with class RedBlackNode<..>
	 */
	template <typename NodeType>
	void printNodeDetails(NodeType *n)
	{
		std::cout << "Node->data_:" << n->data_ << "\t";
		std::cout << "@ " << n << "\n";
		std::cout << "Node->left_:" << n->left_ << "\n";
		std::cout << "Node->right_:" << n->right_ << "\n";
		std::cout << "Node->parent_:" << n->parent_ << "\n";
		std::cout << "Node->color_:" << n->color_ << "\n\n";
	}


	/** \brief function to print information about a node to std::cout;
	 *  \detail designed to work with class RedBlackNode<..>
	 *  output can be used to represent the graphs structure using the online
	 *  plugin "Dagre Interactive Demo" at
	 *  http://www.samsarin.com/project/dagre-d3/latest/demo/interactive-demo.html
	 */
	template <class NodeType>
	void printNodeDID(NodeType *N)
	{
		static int number_of_NIL_nodes = 0;

		if (N->left_ != 0L)
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

		if (N->right_ != 0L)
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


		if (N->parent_ != 0L)
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


	/** \brief Specialization of class RedBlackTree with two fields (key_, data_)
	 *
	 *
	 *  \detail Class RedBlackTree is an implementation of a self balancing binary tree
	 *  that is equivalent to a 2-3-4-Tree (aka B-Tree of order 4).
	 *  It is a structure to store data that obeys an order relation.
	 *  Self balancing implies that the tree depth is approximately equal
	 *  for all path from its root to its leave nodes.
	 *  Search speed benefits from the equal depth and is of the order
	 *  of log(n) where n denoted the total number of elements.
	 *
	 *  The trees Node feature following properties
	 *  \section node_properties Node properties
	 *  	- key value
	 *      - data value
	 *      - pointer to related nodes left child, right child and parent
	 *      - color: A node is either black or red
	 *
	 *  Following properties (RB-Tree conditions) must be fulfilled
	 *  for Red-Black-Tree to be valid:
	 *  \section RB_conditions Red-Black-Tree Conditions
	 *  	- (1) All external leaf nodes (nodes without children)
	 *  	  aka NIL-node (not in list) are black
	 *  	- (2) both childs of a red node are black
	 *  	- (3) Every path from an arbitrary node down to its leaf nodes contains
	 *  	  the same number of black nodes (called black-depth)
	 *
	 *  \section RBTree_references References
	 *  	Rudolf Bayer (1972). "Symmetric binary B-Trees:
	 *	    Data structure and maintenance algorithms".
	 *	    Acta Informatica. 1 (4): 290–306. doi:10.1007/BF00289509.
	 *
	 *
	 *  \sa class RedBlackNode
	 */
	template <class KeyType, class DataType>
	class RedBlackTree//<KeyType,DataType>
	{
	public :
		typedef RedBlackNode<KeyType, DataType> NodeType;
		RedBlackTree() : root_(0L) { }
		~RedBlackTree() {clear(root_);};

		NodeType *root_;  //< base of tree

		// Adding / removing nodes
		void insert(const KeyType &key, const DataType &data);
		void remove(NodeType *N);
		void clear(NodeType *n);
		void clear() {clear(root_); root_=0L;}

		// Searching the tree
		NodeType *find(const KeyType &key, NodeType *N) const;
		NodeType *find(const KeyType &key) const;

		// Tree traversal (NLR=Pre-order, LNR=In-order, LRN=Post-order)
		template <typename Func>
		void traverse_NLR(Func func, NodeType *node);
		template <typename Func>
		void traverse_LNR(Func func, NodeType *node);
		template <typename Func>
		void traverse_LRN(Func func, NodeType *node);

	protected :
		NodeType *get_grandparent(NodeType *n) const;
		NodeType *get_sibling(NodeType *n) const;
		NodeType *get_uncle(NodeType *n) const;
		bool is_LeftInnerGrandChild(NodeType *n, NodeType *g) const;
		bool is_RightInnerGrandChild(NodeType *n, NodeType *g) const;
		inline bool get_color(NodeType *n) const {return (n == 0L) ? BLACK : n->color_;}

		void rotate_left(NodeType *n);
		void rotate_right(NodeType *n);

		void insert_binary(NodeType *n, NodeType *m);
		void fix_insertion(NodeType *n);
		void fix_removal(NodeType *n);
	};


	/** \param[in] n The node whose parent we seek to find
	 *  \return Pointer to 'n's parent if it exists; null pointer otherwise (<=> n is root_)
	 */
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::get_grandparent(NodeType *n) const
	{
		return (n->parent_ != 0L) ? n->parent_->parent_ : 0L;
	}


	/** \param[in] n The node whose sibling we seek to find
	 *  \return Pointer to 'n's sibling if it exists; null pointer otherwise (<= n is root_ or sibling doesn't exist)
	 */
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::get_sibling(NodeType *n) const
	{
		NodeType* p = n->parent_;
		if (n->parent_ == 0L)
			return 0L;
		return (n == p->left_) ? p->right_ : p->left_;
	}


	/** \param[in] n The node whose uncle we seek to find
	 *  \return Pointer to 'n's uncle if it exists; null pointer otherwise
	 *  (Grandparent might not exist; if grandparent exists, uncle should exist
	 *  because of RB-Tree condition (II)).
	 */
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::get_uncle(NodeType *n) const
	{
		NodeType* g = get_grandparent(n);
		return (n->parent_ == g->left_) ? g->right_ : g->left_;
	}


	/** \brief Checks if n is the right inner grand child of g. (see diagram below)
	 *  \param[in] n node we like to check
	 *  \param[in] g 'n's grandparent
	 *  \return true if n is 'g's right inner grand child; false otherwise
	 *  \detail \code
	 *         g
	 *        / \
	 *           p
	 *          /
	 *         n
	 *  \endcode
	 *  \note since fix_insertion(..) (only caller of is_RightInnerGrandChild(..) ) derives g,
	 *  we provide it as argument (for performance reason) instead of re-deriving it locally
	 */
	template <class KeyType, class DataType>
	bool RedBlackTree<KeyType,DataType>::is_RightInnerGrandChild(NodeType *n, NodeType *g) const
	{
		if (g->right_== 0L)
			return false;
		return (n == g->right_->left_ ) ? true : false;
	}


	/** \brief Checks if n is the left inner grand child of g. (see diagram below)
	 *  \param[in] n node we like to check
	 *  \param[in] g 'n's grandparent
	 *  \return true if n is 'g's right inner grand child; false otherwise
	 *  \detail \code
	 *         g
	 *        / \
	 *       p
	 *        \
	 *         n
	 *  \endcode
	 *  \note since fix_insertion(..) (only caller of is_LeftInnerGrandChild(..) ) derives g,
	 *  we provide it as argument (for performance reason) instead of re-deriving it locally
	 */
	template <class KeyType, class DataType>
	bool RedBlackTree<KeyType,DataType>::is_LeftInnerGrandChild(NodeType *n, NodeType *g) const
	{
		if (g->left_ == 0L)
			return false;
		return (n == g->left_->right_) ? true : false;
	}


	/** \brief Searches Red-Black-Tree for key beginning at node n
	 *  \param[in] key The key to search for
	 *  \param[in] n The node to start the search at (tree traversal is NLR=node,left,right)
	 *  \return Pointer to node with its key value being equal to search key; null pointer no node is found.
	 */
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::find(const KeyType &key, NodeType *n) const
	{
		if (n == 0L) return 0L;
		if (key == n->key_)
			return n;
		else if (key < n->key_)
			return RedBlackTree<KeyType,DataType>::find(key, n->left_);
		else if (key > n->key_)
			return RedBlackTree<KeyType,DataType>::find(key, n->right_);
		return 0L;
	}


	/** \brief Searches Red-Black-Tree for key beginning at root_
	 *  \detail delegates search to find(const KeyType &key, NodeType *n) with n=root_
	 *  \param[in] key The key to search for
	 *  \return Pointer to node with its key value being equal to search key; null pointer no node is found.
	 */
	template <class KeyType, class DataType>
	typename RedBlackTree<KeyType,DataType>::NodeType *RedBlackTree<KeyType,DataType>::find(const KeyType &key) const
	{
		return RedBlackTree<KeyType,DataType>::find(key,root_);
	}


	/** \brief Traverses the Tree in pre-order (NLR = Node, Left, Right) and applies func to all nodes visited
	 *  \param[in] *Node Pointer a node where to start traversing
	 *  \param[in] func a function pointer or a closure (lambda-function) that will be applied to all nodes visited
	 *  \example
	 */
	template <class KeyType, class DataType>
	template <typename Func>
	void RedBlackTree<KeyType,DataType>::traverse_NLR(Func func, NodeType *node)
	{
		if (node == 0L)
			return;
		func(node);
		if (node->left_ != 0L)
			traverse_NLR(func,node->left_);
		if (node->right_ != 0L)
			traverse_NLR(func,node->right_);
		return;
	}


	/** \brief Traverses the Tree in in-order (LNR = Left, Node, Right) and applies func to all nodes visited
	 *  \param[in] *Node Pointer a node where to start traversing
	 *  \param[in] func a function pointer or a closure (lambda-function) that will be applied to all nodes visited
	 *  \sa See documentation of traverse_NLR(..) for an example on how to use tree traversal
	 */
	template <class KeyType, class DataType>
	template <typename Func>
	void RedBlackTree<KeyType,DataType>::traverse_LNR(Func func, NodeType *node)
	{
		if (node == 0L)
			return;
		if (node->left_ != 0L)
			traverse_LNR(func,node->left_);
		func(node);
		if (node->right_ != 0L)
			traverse_LNR(func,node->right_);
		return;
	}


	/** \brief Traverses the Tree in post-order (LRN = Left, Right, Node) and applies func to all nodes visited
	 *  \param[in] *Node Pointer a node where to start traversing
	 *  \param[in] func a function pointer or a closure (lambda-function) that will be applied to all nodes visited
	 *  \sa See documentation of traverse_NLR(..) for an example on how to use tree traversal
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


	/** \brief Rotates the graph left
	 *  \detail Rotation around node N according to the diagram below
	 *  Note: Nodes possess pointers to left and right child AND to parent
	 *  => there are six connections to be changed (3Nodes*2connections)
	 *  \code
	 *            P                                 P
	 *           /                                 /
	 *          N         rotate_left(N)           R
	 *         / \            ====>              / \
	 *        A   R                             N   B
	 *           / \                           / \
	 *          M   B                         A   M
	 *  \endcode
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::rotate_left(NodeType *N)
	{
		NodeType *R = N->right_;
		if (R == 0L)
			return;
		// reconnect P
		R->parent_=N->parent_;
		if (N->parent_ != 0L)
		{
			if (N->parent_->right_==N)
				N->parent_->right_=R;
			else
				N->parent_->left_=R;
		}
		// reconnect M
		N->right_=R->left_;
		if (R->left_ != 0L)
			R->left_->parent_=N;
		// reconnect N and L
		N->parent_=R;
		R->left_=N;
		return;
	}


	/** \brief Rotates the graph right
	 *  \detail Rotation around node N according to the diagram below
	 *  Note: Nodes possess pointers to left and right child AND to parent
	 *  => there are six connections to be changed (3Nodes*2connections)
	 *  \code
	 *            P                                 P
	 *           /                                 /
	 *          N         rotate_right(N)         L
	 *         / \            ====>              / \
	 *        L   B                             A   N
	 *       / \                                   / \
	 *      A   M                                 M   B
	 *  \endcode
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::rotate_right(NodeType *N)
	{
		NodeType *L = N->left_;
		if (L == 0L)
			return;
		// reconnect P
		L->parent_ = N->parent_;
		if(N->parent_ != 0L)
		{
			if (N->parent_->left_ == N)
				N->parent_->left_ = L;
			else
				N->parent_->right_ = L;
		}
		// reconnect M
		N->left_ = L->right_;
		if (L->right_ != 0L)
			L->right_->parent_ = N;
		// reconnect n and L
		N->parent_ = L;
		L->right_ = N;
		return;
	}


	/** \brief interface to insert a node into the Red-Black-Tree
	 *
	 *  \detail Allocates memory for the newly added node and
	 *  delegates the process of insertion into two stages.
	 *  First append the node onto the tree taking order conditions into account.
	 *  Second is to restore Red-Black-Tree conditions that might
	 *  have been violated through the first stage
	 *
	 *  \param[in] The key value of the newly added node
	 *  \param[in] the data value of the newly added node
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::insert(const KeyType &key, const DataType &data)
	{
		NodeType *node = new NodeType(key, data);
		insert_binary(node, root_);
		fix_insertion(node);
		return;
	}


	/** \brief Appends a node onto the existing Red-Black-Tree (inserting 1st stage of 2)
	 *
	 *  \detail When inserting a node into the tree it's first placed
	 *  taking only order conditions of an ordered binary tree into account:
	 *  For every Node in the tree its node value is greater than its left
	 *  childs value and smaller or equal than its right childs value.
	 *  note: after appending a node Red-Black-Tree conditions are most likely violated
	 *  and need to be restored by calling fix_insertion(..)
	 *
	 *  \param[in] n The node we want to insert
	 *  \param[in] m (Mounting node) The node where we try to append the newly added node onto
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::insert_binary(NodeType *n, NodeType *m)
	{
		if (m == 0L)
		{
			root_ = n;
			n->parent_ = 0L;
		}
		else if (n->key_ < m->key_)
		{
			if (m->left_ == 0L)
			{
				m->left_ = n;
				n->parent_ = m;
			}
			else
			{
				insert_binary(n, m->left_);
			}
		}
		else // if (n->key_ >= m->key_)
		{
			if (m->right_ == 0L)
			{
				m->right_ = n;
				n->parent_ = m;
			}
			else
			{
				insert_binary(n, m->right_);
			}
		}
		return;
	}


	/** \brief Restores Red-Black-Tree conditions (inserting 2nd stage of 2)
	 *
	 *  \detail fix_insertion(..) should be called after insert_binary(..)
	 *  has inserted a node into the tree.
	 *  insert_binary(..) takes order conditions into
	 *  account but might violate Red-Black-Tree conditions.
	 *  fix_insertion(..) restores RB-conditions and preserves order conditions.
	 *
	 *  \param[in] n Pointer to the node which was inserted last
	 *
	 *  \sa see source code for further documentation
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::fix_insertion(NodeType *n)
	{
		// n is RED & has no parent
		// => N must become root
		if(n->parent_ == 0L)
		{
			n->color_ = true;
			root_ = n;
			return;
		}

		// n is RED & has a BLACK parent
		// => RB-condition is fulfilled
		// => insertion doesn't need to be fixed
		if(n->parent_->color_ == BLACK)
		{
			return;
		}

		// n is RED, has a RED parent & has a RED uncle
		// => RB-condition is violated (n red, parent red) but:
		// => grandparent is BLACK (red parent & red uncle)
		// => recolor parent, uncle & grandparent + move problem a level upwards
		if( (get_uncle(n) != 0L ? get_uncle(n)->color_ : BLACK) == RED)
		{
			n->parent_->color_ = BLACK;
			get_uncle(n)->color_ = BLACK;
			get_grandparent(n)->color_ = RED;
			fix_insertion(get_grandparent(n));
			return;
		}

		// all remaining cases: 4 possible combinations
		//   (a)           (b)        (c)         (d)
		//		    G           G           G           G
		//         / \         / \         / \         / \
		//        P   U       P   U       U   P       U   P
		//       /             \             /             \
		//      N               N           N               N
		// n is RED, has RED parent and BLACK uncle and BLACK Grandparent (since parent is RED)
		// => if dealing with (b) or (c): translate (b) to (a) and (c) to (d)
		//    note: order relation must be preserved (n's position mustn't be swapped, instead
		//    graph is rotated around p and nodes "renamed" accordingly)
		// => rotate graph around g (pulling p upwards) and recolor p,g to "balance" subtree

		NodeType *p = n->parent_;
		NodeType *g = get_grandparent(n);


		if(g==0L)
			return;


		if (is_LeftInnerGrandChild(n,g))
		{
			rotate_left(p);
			n = n->left_;
			p = n->parent_;
		}
		else if (is_RightInnerGrandChild(n,g))
		{
			rotate_right(p);
			n = n->right_;
			p = n->parent_;
		}


		if (n == p->left_)
			rotate_right(g);
		else
			rotate_left(g);

		p->color_ = BLACK;
		g->color_ = RED;

		if(root_==g)
			root_ = p;

		return;
	}


	/** \brief removes a node from the Red-Black-Tree
	 *
	 *  \detail
	 * remove let you pick an arbitrary node N within the rb-tree and delete it.
	 * remove works in three steps.
	 * step 1: find node D in Ns left (or right) subtree with next smaller (or greater) key (favor left/right subtree depending on subtrees depth).
	 *         Move contend of Node D to N (key and data. RB-tree properties as color/children etc. stay UNCHANGED).
	 *         (Note: D will have at most one child by property of a binary tree (node is "most left" or "most right" Node in the subtree)
	 * step 2: if D has a child connect Ds child to Ds parent by replacing D. D is now unconnected => delete D (after step 3).
	 *         (binary tree properties are preserved to this point rb-tree properties might be lost by disconnecting D.
	 * step 3: repair rb-tree properties starting at Ds child.
	 *         There are a view cases where rb-tree properties can be restored by repainting Nodes in Ds childs proximity.
	 *         The more complex cases (where Nodes have to be moved) are handled by the fix_removal function.
	 * NOTE  : Steps 2 and 3 can be switched without changing the result (fix_removal moves D and Ds subtree (aka D and its child) like
	 *         a single unit. By applying step 2 first We don't have to implement lots of special rules to handle Ds childs NIL nodes.
	 *
	 *  \param[in] N Pointer to the node to be removed
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::remove(NodeType *N)
	{
		NodeType *left = N->left_;
		NodeType *right = N->right_;
		NodeType *D = N;

		// step 1: find node D
		// Note: The "most RIGHT" node from LEFT sub tree has the next
		//       SMALLER key to N (and vice versa for the right sub tree)
		while ((left != 0L) || (right != 0L))
		{
			if (left != 0L)
			{
				D = left;
				left = left->right_;
			}
			if (right != 0L)
			{
				D = right;
				right = right->left_;
			}
		} // END WHILE

		(*N) = copy_internals(*D);

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
		if( ( D->color_ == BLACK ) && ( C == 0L ) )
			fix_removal(D);

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
			C->color_ = BLACK;
		}

		delete D;
	}


	/** \brief restores RB-conditions after remove(..)
	 *
	 *  \details fix_removal is used if the RB-conditions
	 *  after a call to remove(..) couldn't be restored by recoloring single nodes.
	 *  \param[in] node Pointer to node where removal faild to fix RB-conditions
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::fix_removal(NodeType *N)
	{
		// case 1: N has become the new root_
		if (N->parent_ == 0L)
		{
			root_=N;
			return;
		}

		// case 2:
		NodeType *S = get_sibling(N);
		if (S->color_ == RED)
		{
			N->parent_->color_ = RED;
			S->color_ = BLACK;
			if (N == N->parent_->left_)
				rotate_left(N->parent_);
			else
				rotate_right(N->parent_);
		}

		// case 3:
		S = get_sibling(N);
		if ((N->parent_->color_ == BLACK) &&
				(S->color_ == BLACK) &&
				(get_color(S->left_) == BLACK) &&
				(get_color(S->right_) == BLACK))
		{
			S->color_ = RED;
			fix_removal(N->parent_);
			return;
		}


		// case 4:
		S = get_sibling(N);
		if ((N->parent_->color_ == RED) &&
				(S->color_ == BLACK) &&
				(get_color(S->left_) == BLACK) &&
				(get_color(S->right_) == BLACK))
		{
			S->color_ = RED;
			N->parent_->color_ = BLACK;
			return;
		}


		// case 5:
		S = get_sibling(N);
		if  (S->color_ == BLACK)
		{
			// this if statement is trivial,
			// due to case 2 (even though case 2 changed the sibling to a sibling's child,
			// the sibling's child can't be RED, since no RED parent_ can have a RED child).
			//
			// the following statements just force the RED to be on the left_ of the left_ of the parent_,
			// or right_ of the right_, so case six will rotate correctly.
			if ((N == N->parent_->left_) &&
					(get_color(S->right_) == BLACK) &&
					(get_color(S->left_) == RED))
			{ /* this last test is trivial too due to cases 2-4. */
				S->color_ = RED;
				S->left_->color_ = BLACK;
				rotate_right(S);
			}
			else if ((N == N->parent_->right_) &&
					(get_color(S->left_) == BLACK) &&
					(get_color(S->right_) == RED))
			{/* this last test is trivial too due to cases 2-4. */
				S->color_ = RED;
				S->right_->color_ = BLACK;
				rotate_left(S);
			}
		}


		// case 6:
		S = get_sibling(N);
		S->color_ = N->parent_->color_;
		N->parent_->color_ = BLACK;

		if (N == N->parent_->left_)
		{
			S->right_->color_ = BLACK;
			rotate_left(N->parent_);
		}
		else
		{
			S->left_->color_ = BLACK;
			rotate_right(N->parent_);
		}

	}


	/** \brief Frees memory allocated for tree nodes
	 *
	 *  \detail Traverses sub-tree starting at node n in post-order (LRN)
	 *  \param[in] n Pointer to node
	 */
	template <class KeyType, class DataType>
	void RedBlackTree<KeyType,DataType>::clear(NodeType *n)
	{
		if ( n == 0L )
			return;
		clear(n->left_);
		clear(n->right_);
		delete n;
		n = 0L;
		return;
	}


} // END OF NAMESPACE o_data_structures

#endif // END OF RED_BLACK_TREE_HPP_
