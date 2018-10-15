/** \file
 * 		BinaryHeap.hpp
 *
 *  \brief
 *  	Provides a binary minimum heap data structure (class BinaryHeap)
 *
 *  \details
 *  	For details on the implementation of class BinarayHeap please see
 *  	its documentation in BinaryHeap.hpp (this file) alongside with its definition.
 *      Here is just a short list of features of this class.
 *      - BinaryHeap is a template class. It should work with every other class that
 *        provides algebraic relations < , > , ==, >= and <=.
 *
 * \version
 * 		2018-10-11: 1.1.0 (ipsch) modified to work with Paradox Problem A
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */

#ifndef BINARYHEAP_HPP_
#define BINARYHEAP_HPP_

//#define BINARYHEAP_CAUTIOUS    // unset if STL isn't available

#if defined (BINARYHEAP_CAUTIOUS)
#include <stdexcept>           // exception handling
#endif

#include <iostream>
#include <cmath>               // std::floor(..)
#include "oMath.hpp"           // templates for min / max
#include "BinaryHeapNode.hpp"  // NodeType used in class BinaryHeap

namespace o_data_structures
{

	////////////////////////////////////////////////////////////
	/// HELPFER FUNCTIONS //////////////////////////////////////
	////////////////////////////////////////////////////////////

	/** \brief Index arithmetics to get the index of Node-is left child within BinaryHeap::A_
	 *  \param[in] i Index of node-i
	 *  \return The Index of node-is left child
	 */
	inline unsigned int left(const unsigned int &i)
	{
		return 2*i+1;
	}

	/** \brief Index arithmetics to get the index of Node-is right child within BinaryHeap::A_
	 *  \param[in] i Index of node-i
	 *  \return The index of node-is right child
	 */
	inline unsigned int right(const unsigned int &i)
	{
		return 2*i+2;
	}

	/** \brief Index arithmetics to get the index of Node-is parent within BinaryHeap::A_
	 *  \param[in] i Index of node-i
	 *  \return The index of node-is parent
	 */
	inline unsigned int parent(const unsigned int &i)
	{
		return std::floor((i-1)/2);
	}



	////////////////////////////////////////////////////////////
	/// CLASS DECLARATION //////////////////////////////////////
	////////////////////////////////////////////////////////////


	/** \brief BinaryHeap is an implementation of a complete binary minimum search tree
	 *
	 *  \details It stores data elements (called items or nodes) of the type (KeyType)
	 *  in a dynamic array (BinaryHeap::A_).
	 *  (Note: we use item and node synonymously: Item shall stress the point
	 *  of storing data while node stresses the point how items relate to each other).
	 *  There are in total n_items_ stored and max_items_ denoting the number
	 *  of storable items (the current size of A_).
	 *
	 *  Using index arithmetics every item can be associated with a left and a right child node
	 *  ( left() and right(..) ) and vice versa ( parent(..) ).
	 *  Through this hierarchical structure the items in A_ are associated with
	 *  different levels (rank_ = 0, 1, 2, ..).
	 *
	 *  The following table gives an overview how many nodes exist on each level and
	 *  how many nodes exist in total. As can be seen from the table there will always
	 *  be one single node at the end of A_ that isn't actually used to store data.
	 *  We uses this additional note for swap operations
	 *
	 *
	 * 	rank 	|	Nodes in level 	|	Nodes in Tree	|	 swap Nodes		|	arraySize
	 * ---------|-------------------|-------------------|-------------------|--------------
	 * 	rank_	|					|	 (max_items_)	|	A_[ASize_-1]	|	(ASize_)
	 *    n     |        2^n		|	  2^(n+1)-1 	|		  1			|	2^(n+1)
	 *    0		|		 1			|	 	  1			|		  1			|		2
	 * 	  1		|		 2			|		  3			|		  1			|		3
	 * 	  2		|		 3			|		  7			|		  1			|	    8
	 * 	  3		|		 4			|		  15		|		  1			|		16
	 * 	  4		|		 5			|		  31		|		  1			|		32
	 *
	 *
	 *  For each node N within the tree the minimum Heap condition
	 *  ((N =< N_left) && (N =< N_right))
	 *  is fulfilled; Where N_left and N_right denote Ns left- and right child accordingly
	 *
	 *  This implicates that the data is partially sorted with the smallest element being
	 *  always on top of the heap (stored at A_[0]).
	 *  The user/caller doesn't need to manage data to keep the heap structure;
	 *  Instead the methods int insert(KeyType newkey), KeyType remove(const unsigned int &i),
	 *  int increase_key(int i, KeyType newkey), int decrease_key(int i, KeyType newkey)
	 *  int change_key(int i, KeyType newkey), void build()
	 *  manage data manipulation on their own.
	 *
	 *  BinaryHeap was intended to be used in combination with class BinaryHeapNode.
	 *  This class was written with the intention to give some flexibility regarding the stored items.
	 *  Any class that provides the ordered relation for < , > , >=, <= and == can be used with this class.
	 *
	 *
	 *  The methods find(..) to search for a certain item/key within the tree do unsorted list search.
	 *
	 *  following table gives (theoretical) time complexity of algorithms on a binary heap
	 *
	 *  Algorithm|  Average	|    Worst case
	 *  ---------|----------|-----------------
	 *  Space	 |	O(n)	|	O(n)
	 *  Search	 |	O(n)	|	O(n)
	 *  insert	 |	O(1)	|	O(log n)
	 *  Delete	 |	O(log n)|	O(log n)
	 *  Peek     |	O(1)	|	O(1)
	 *
	 */

	template <typename KeyType, typename DataType>
	class BinaryHeap
	{
	public :
		typedef BinaryHeapNode<KeyType,DataType> NodeType;
		//BinaryHeap(const unsigned int &nDegree=0);
		BinaryHeap();
		BinaryHeap(const unsigned int &nDegree);
		~BinaryHeap();

		void insert(const KeyType &newkey, const DataType &data);
		void remove(const unsigned int &i);
		DataType pop(const unsigned int &i);

		void increase_key(const unsigned int &i, KeyType new_key);
		void decrease_key(const unsigned int &i, KeyType new_key);
		void change_key(const unsigned int &i, const KeyType &new_key);
		void build();


		bool is_empty(void) const {return n_items_==0;}

		// Func IsEqual = [] (const KeyType &N, const KeyType &key) {return N==key;}

		// various find functions
		template<typename Func>
		bool find_(unsigned int &iter, Func IsEqual) const;
		bool find(unsigned int &iter, const KeyType &key) const;
		bool find(const KeyType &key) const;


		NodeType *A_;             //< Array where heap elements get stored in (literally "The Tree")
		unsigned int max_items_;  //< Current size of the heap (maximum number of storable elements)
		unsigned int rank_;       //< Current number of layers/levels associated with max_items_
		unsigned int n_items_;    //< Number of data nodes currently stored in BinarayHeap::A_
		unsigned int min_items_;  //< Minimum number of items that should be storable in A_;

	protected :
		// helper functions
		bool is_minHeap(const unsigned int &i=0);
		void swap(const unsigned int &a, const unsigned int &b);
		void resize(const unsigned int &new_max_items);
		void sift_down(int i); // aka heapify
		void sift_up(unsigned int i);
	}; // END OF CLASS BinaryHeap<KeyType,DataType>




	////////////////////////////////////////////////////////////
	/// METHOD DEFINITIONS//////////// /////////////////////////
	////////////////////////////////////////////////////////////


	template <typename KeyType, typename DataType>
	BinaryHeap<KeyType,DataType>::BinaryHeap() : rank_(0), n_items_(0), min_items_(2)
	{
		unsigned int tmp = o_math::oPow2(rank_+1);
		max_items_ = tmp - 1;
		A_ = new NodeType[tmp];
	}


	/** \brief Constructor
	 *  \details since the allocation of memory for heap size is usually dynamically
	 *  it can be desirable to define a lower bound on levels which are always
	 *  available without dynamic allocation. This can be achieved by using nDegree (default = 0).
	 * 	\param[in] nDegree number of layers pre-constructed at initialization
	 */
	template <typename KeyType, typename DataType>
	BinaryHeap<KeyType,DataType>::BinaryHeap(const unsigned int &nDegree) : rank_(nDegree), n_items_(0)
	{
		unsigned int tmp = o_math::oPow2(rank_+1);
		max_items_ = min_items_ = tmp - 1;
		A_ = new NodeType[tmp];
	}


	//! \brief Destructor
	template <typename KeyType, typename DataType>
	BinaryHeap<KeyType,DataType>::~BinaryHeap()
	{
		delete[] A_;
	}



	/** \brief Adds an item to the heap
	 *
	 *  \detail Is responsible for creation of the node to add.
	 *  Delegates the process of insertion at the right
	 *  place within the heap to its base classes insert method.
	 *
	 *  \param[in] newkey Search key of the new node
	 *  \param[in] data Data field of the new node
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::insert(const KeyType &newkey, const DataType &data)
	{
		NodeType item(newkey, data);
		resize(n_items_+1);
		A_[n_items_] = item;
		sift_up(n_items_);
		++n_items_;
	}


	/** \brief removes an item from the heap
	 *  \details remove() automatically handles reallocation of the heaps memory if
	 *  necessary and restores minimum heap condition
	 *
	 *  \param[in] item Index of the item to be removed from the heap
	 *  \return Copy of removed item
	 */
	template <typename KeyType, typename DataType>
	DataType BinaryHeap<KeyType,DataType>::pop(const unsigned int &i)
	{
       #if defined(BINARYHEAP_CAUTIOUS)
		if (i>=n_items_)
			throw std::runtime_error("pop: index i out of bound\n");
       #endif
		DataType removedItem = A_[i].data_;
		remove(i);
		return removedItem;
	}


	/** \brief removes an item from the heap
	 *  \details remove() automatically handles reallocation of the heaps memory if
	 *  necessary and restores minimum heap condition
	 *
	 *  \param[in] item Index of the item to be removed from the heap
	 *  \return Copy of removed item
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::remove(const unsigned int &i)
	{
       #if defined(BINARYHEAP_CAUTIOUS)
		if (i>=n_items_)
			throw std::runtime_error("remove: index i out of bound\n");
       #endif

		DataType removedItem = A_[i].data_;
		unsigned int lastIdx = n_items_-1;
		swap(i,lastIdx);
		--n_items_;
		resize(lastIdx);

		// Assume the case of deleting the item at position i = lastIdx :
		// => i would be out of bound after a call to resize(..)
		// => calling sift_up(..) or sift_down(..) would crash the program.
		if ( i != lastIdx )
		{
			if ( i == 0 || A_[i] > A_[parent(i)] )
				sift_down(i);
			else
				sift_up(i); // do nothing if H.key(i) == H.key(parent(i)) only one element in the heap
		}
		return;
	}





	/** \brief Increases the key of the node at index i to newKey
	 *
	 *  \detail
	 * Note: If using some class for KeyType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::increase_key(const unsigned int &i, KeyType new_key)
	{
       #if defined(BINARYHEAP_CAUTIOUS)
		if (!is_minHeap())
			throw std::runtime_error("increase_key: Heap Condition not met\n");
		if (i>=n_items_)
			throw std::runtime_error("pop: index i out of bound\n");
		if (new_key <= A_[i])
			throw runtime_error("increase_key: new_key too small\n");
       #endif
		this->A_[i].key_ = new_key;
		this->sift_down(i);
		return;
	}








	/** \brief decreases the key of the node at index i to newKey
	 *
	 *  \details
	 *  Note: If using some class for KeyType Change key will use operator= offer
	 *  the class to overwirte item at index with newKey
	 *
	 *  \param[in] i Index of the item that will be change
	 *  \param[in] newKey The new key or item to replace item at i
	 *  \return Error-code 0 on success; -1 otherwise
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType, DataType>::decrease_key(const unsigned int &i, KeyType new_key)
	{
       #if defined(BINARYHEAP_CAUTIOUS)
		if (!is_minHeap())
			throw std::runtime_error("decrease_key: Heap Condition not met\n");
		if (i>=n_items_)
			throw std::runtime_error("decrease_key: index i out of bound\n");
		if (new_key >= A_[i])
			throw runtime_error("decrease_key: new_key too big\n");
       #endif
		this->A_[i].key_ = new_key;
		this->sift_up(i);
		return;
	}

	/** \brief Changes the key of an item
	 *
	 *  \details
	 *  - change_key(..) is also responsible for
	 *    repositioning the item within the heap
	 *
	 *  \param[in] i Index/position of the item
	 *  \param[in] newKey New value key
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::change_key(const unsigned int &i, const KeyType &newKey)
	{
       #if defined(BINARYHEAP_CAUTIOUS)
		if ( !is_minHeap() )
			throw std::runtime_error("change_key: Heap Condition not met\n");
       #endif

		if (newKey > this->A_[i].key_)
		{
 			this->A_[i].key_ = newKey;
			this->sift_down(i);
		}
		else if (newKey < this->A_[i].key_)
		{
			this->A_[i].key_ = newKey;
			this->sift_up(i);
		}
		return;
	}


	/** \brief restores heap conditions for all elements buttom up
	 *  \details Applies SiftDown for all elements in BinaryHeap::A_
	 *  beginning with the last element
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::build()
	{
		if (n_items_==1)
			return;
		for (int i = n_items_/2-1; i>=0; --i)
			sift_down(i);
	}


	/** \brief Searches the heap for an item (use this if item is a literal or float and its position in heap isn't of interest)
	 *
	 *  \details
	 *  This search function is intended to be used if KeyType is either
	 *  a literals or float. In This case the vale of item is identical to its key.
	 *  IsEqual is by default:
	 *
	 *  Func = [] (const KeyType &N, const KeyType &key) {return N==key;}
	 *
	 *  And shouldn't be overridden.
	 *
	 *  \param[in] item The item to search for
	 *  \param[in] Func Function-pointer or lambda-function to compare item to items in BinaryHeap::A_
	 *  \return Returns true if item was found in heap; returns false otherwise
	 *
	 *  \sa
	 *  - if the position of item within BinaryHeap is needed to read, remove or modify item the
	 *    method bool BinaryHeap<KeyType,DataType>::find(const KeyType key, unsigned int &iter, Func IsEqual) const
	 *    should be used.
	 *  - if item is a class or object with more than one field and operator== isn't defined for this
	 *    class or the search should be applied to an other field than operator== is designed for
	 *    the one of the following two methods should be used
	 *    - bool BinaryHeap<KeyType,DataType>::find(Func IsEqual) const
	 *    - bool BinaryHeap<KeyType,DataType>::find(unsigned int &iter, Func IsEqual) const
	 */
	template<typename KeyType, typename DataType>
	template<typename Func>
	bool BinaryHeap<KeyType,DataType>::find_(unsigned int &iter, Func IsEqual) const
	{
		for(iter=0; iter<n_items_; ++iter)
			if(IsEqual(A_[iter]))
			{
				return true;
			}
		return false;
	}


	/** \brief Searches the heap for an item (use this if item is a literal or float and its position in heap is of interest)
	 *
	 * \details
	 * This search function is intended to be used if KeyType is either
	 * a literals or float and the position of item on the heap is of interest.
	 * In This case the vale of item is identical to its key.
	 * IsEqual is by default:
	 *
	 * Func = [] (const KeyType &N, const KeyType &key) {return N==key;}
	 *
	 * And shouldn't be overridden.
	 *
	 * \param[in] item The item to search for
	 * \param[out] iter the index of item on the heap is written iter on return
	 * \param[in] Func Function-pointer or lambda-function to compare item to items in BinaryHeap::A_
	 * \return Returns true if item was found in heap; returns false otherwise
	 *
	 * \sa
	 * - if the position of item on the heap isn't the
	 *   method bool BinaryHeap<KeyType,DataType>::find(const KeyType item, Func IsEqual) const
	 *   should be used.
	 * - if item is a class or object with more than one field and operator== isn't defined for this
	 *   class or the search should be applied to an other field than operator== is designed for
	 *   the one of the following two methods should be used
	 *   - bool BinaryHeap<KeyType,DataType>::find(Func IsEqual) const
	 *   - bool BinaryHeap<KeyType,DataType>::find(unsigned int &iter, Func IsEqual) const
	 */
	template<typename KeyType, typename DataType>
	bool BinaryHeap<KeyType,DataType>::find(unsigned int &iter, const KeyType &key) const
	{
		return find_(iter, [&key] (const KeyType &X) {return X==key;});
	}


	/** \brief Searches the heap for an item (use this if item has multiple fields but no operator== or operator== isn't designed for the field you want to search for; and items position on the heap isn't of interest)
	 *
	 * \details
	 * This search function is intended to be used if KeyType is
	 * an object with multiple field but no operator== is defined or operator==
	 * doesn't compare fields you actually want to compare
	 *
	 * This function is basically the same as
	 * bool BinaryHeap<KeyType,DataType>::find(const KeyType item, Func IsEqual) const
	 * but it gets rid of the item parameter, since it's assumed that
	 * a valid closure for comparison is supplied via Func.
	 * Func has no default value and must be supplied.
	 *
	 * An example how to use this function could look like this:
	 * \code{.cpp}
	 * 		struct foo
	 * 		{
	 * 			int x,y,z;
	 * 		};
	 *
	 * 		BinaryHeap<foo> bar;
	 * 		// ... inserting some items
	 * 		int search_value=100;
	 *  	bool search_success = bar.find([&search_value] (foo &item) {return item.y==search_value;});
	 * \endcode
	 *
	 * This example illustrates how fields that should be searched can easily be
	 * shwitch at the point of callin find(..)
	 * As result of this example, all elements of BinaryHeap::A_ would have their
	 * field y compared to search_value.
	 *
	 * \param[in] Func Function-pointer or lambda-function to compare item to items in BinaryHeap::A_
	 * \return Returns true if item was found in heap; returns false otherwise
	 *
	 * \sa
	 * - Use one of the alternative search functions
	 *   - bool BinaryHeap<KeyType,DataType>::find(const KeyType item, unsigned int &iter, Func IsEqual) const
	 *   - bool BinaryHeap<KeyType,DataType>::find(const KeyType item, Func IsEqual) const
	 *   if item is literal or float
	 *
	 * - If items position on the heap is of interest, but apart from that prerequisite are the same use:
	 * bool BinaryHeap<KeyType,DataType>::find(unsigned int &iter, Func IsEqual) const
	 */
	template<typename KeyType, typename DataType>
	bool BinaryHeap<KeyType,DataType>::find(const KeyType &key) const
	{
		unsigned int iter;
		return find_(iter, [&key] (const KeyType &X) {return X==key;});
	}



	/** \brief Checks if the sub-branch beginning at node i is a MinHeap
	 *  \details For every node in the sub-tree its key must be
	 *  smaller than the the key of both its children
	 *  (Note: Nodes without children return true)
	 *
	 *  \param[in] i Index of the Node which will be root of the subtree to be examined
	 *  \return Returns true if the subtree beginning at node i fulfills the MinHeap condition (false otherwise)
	 */
	template <typename KeyType, typename DataType>
	bool BinaryHeap<KeyType,DataType>::is_minHeap(const unsigned int &i)
	{
		if(left(i)>=n_items_) // no left child => no children at all => we are done
			return true;
		bool L = (A_[i]<=A_[left(i)]);
		if(right(i)>=n_items_) // no right child => no next layer => result depends on left child only
			return L;
		if( (!L) || (A_[i]>A_[right(i)]) ) // return early if heap condition is violated
			return false;
		return is_minHeap(left(i)) &&
				is_minHeap(right(i)); // check next layer
	}


	/** \brief swaps two elements a and b with each other
	 *  \details swap utilizes the very last element in BinaryHeap::A_ for temporary storage
	 *  (this element is never used to represent a regular node within the tree)
	 *  \param[in] a First element to swap
	 *  \param[in] b Second element to swap
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::swap (const unsigned int &a, const unsigned int &b)
	{
		A_[max_items_] = A_[a];
		A_[a] = A_[b];
		A_[b] = A_[max_items_];
	}


	/** \brief reallocates memory for the heap (array BinaryHeap::A_) depending
	 *  on size new_maxItems
	 *
	 *  \details resize(..) is able to increase or reduce allocated memory.
	 *
	 *  \param[i] new_max_items Number (aka Index) of items
	 *  \return error-code 0 if reallocation was successful; -1 otherwise
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::resize(const unsigned int &new_max_items)
	{
		// increase allocated memory
		if ( new_max_items > max_items_ )
		{
			++rank_;
			max_items_ = o_math::oPow2(rank_+1)-1;
			NodeType *tmp = new NodeType[o_math::oPow2(rank_+1)];
			for(unsigned int j=0; j<n_items_; ++j)
			{
				tmp[j] = A_[j];
			}
			delete[] A_;
			A_=tmp;
			return;
		}

		// do not decrease if already under certain threshold
		// (try avoid reallocating too often)
		if ( new_max_items <= min_items_ )
			return;

		// decrease allocated memory if at least two levels are empty
		if ( new_max_items <= o_math::oPow2(rank_-1)-1 )
		{
			--rank_;
			max_items_ = o_math::oPow2(rank_+1)-1;
			NodeType *tmp = new NodeType[o_math::oPow2(rank_+1)];
			for(unsigned int j=0; j<n_items_; ++j)
				tmp[j] = A_[j];
			delete[] A_;
			A_=tmp;
			return;
		}

		return;
	}


	/** \brief (aka heapify) Moves a node at index downwards within the tree by swapping with its child nodes until equilibrium is reached
	 *  \details Right child has priority if left and right are equal
	 *  \param[in] index Index of the node to be relocated
	 *  \return Error-code: 0 on success; -1 otherwise (note used at he moment)
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::sift_down(int i)
	{
		int min = i;
		if ( (left(i) < n_items_) && (A_[left(i)] < A_[min]) )
			min = left(i);
		if ( (right(i) < n_items_) && (A_[right(i)] < A_[min]) )
			min = right(i);
		if (min != i)
		{
			swap(i, min);
			sift_down(min);
		}
		return;
	}


	/** \brief Moves a node at index up within the tree by swapping with its parent node until equilibrium is reached
	 *
	 *  \param[in] index Index of the node to be relocated
	 */
	template <typename KeyType, typename DataType>
	void BinaryHeap<KeyType,DataType>::sift_up(unsigned int index)
	{
		while ( (index > 0) && (A_[index] < A_[parent(index)]) )
		{
			swap(index, parent(index));
			index = parent(index);
		}
		return;
	}


} // END OF NAMESPACE o_data_structures

#endif // END OF BINARYHEAP_HPP_
