/**
 * \file BinaryHeap.hpp
 *
 * \brief Contains class BinaryHeap that provides a binary minimum heap data structure
 *
 * \details For details on the implementation of class BinarayHeap please see
 *          its documentation in BinaryHeap.hpp (this file) alongside with its definition.
 *          Here is just a short list of features of this class.
 *          - BinaryHeap is a template class. It should work with every other class that
 *            provides algebraic relations < , > , ==, >= and <=.
 *
 * \sa
 * - Class BinaryHeap is documented in BinaryHeap.hpp (this file) along with its declaration
 * - Class BinaryHeaps methods are documented in BinaryHeap.tpp along with their definitions
 *
 * \section section_BinaryHeap_history Development History
 * \version 2018-09-07: 1.0.0 (ipsch)
 *
 * \author ipsch (Ingmar Palle Schnell)
 *
 * contact: i.p.schnell(at)gmail.com
 *
 */
#pragma once

#include <cmath>                       // needed for std::floor(..)
#include <stdexcept>                   // exception handling



namespace o_data_structures
{

	template <class ... Args> class BinaryHeap;

	/**
	 * \class BinaryHeap
	 * \brief BinaryHeap is an implementation of a complete binary minimum search tree
	 *
	 * \details
	 * It stores data elements (called items or nodes) of the type (KeyType)
	 * in a dynamic array (BinaryHeap::A_).
	 * (Note: we use item and node synonymously: Item shall stress the point
	 * of storing data while node stresses the point how items relate to each other)
	 * There are in total n_items_ stored and max_items_ denoting the number
	 * of storable items (the current size of A_).
	 *
	 * Using index arithmetics every item can be associated with a left and a right child node
	 * ( GetLeftsIndex() and GetRightsIndex(..) ) and vice versa ( GetParentsIndex(..) ).
	 * Through this hierarchical structure the items in A_ are associated with
	 * different levels (rank_ = 0, 1, 2, ..).
	 *
	 * The following table gives an overview how many nodes exist on each level and
	 * how many nodes exist in total. As can be seen from the table there will always
	 * be one single node at the end of A_ that isn't actually used to store data.
	 * We uses this additional note for swap operations
	 *
	 *	rank 	|	Nodes in level 	|	Nodes in Tree	|	 Swap Nodes		|	arraySize
	 *----------|-------------------|-------------------|-------------------|--------------
	 *	rank_	|					|	 (max_items_)	|	A_[ASize_-1]	|	(ASize_)
	 *    n     |        2^n		|	  2^(n+1)-1 	|		  1			|	2^(n+1)
	 *    0		|		 1			|	 	  1			|		  1			|		2
	 *	  1		|		 2			|		  3			|		  1			|		3
	 *	  2		|		 3			|		  7			|		  1			|	    8
	 *	  3		|		 4			|		  15		|		  1			|		16
	 *	  4		|		 5			|		  31		|		  1			|		32
	 *
	 * For each node N within the tree the minimum Heap condition is fulfilled; meaning:
	 *   N =< N_LeftChild && N_i =< N_RightChild
	 *
	 * This implies that the data is partially sorted with the smallest element being always at the top.
	 * The user/caller doesn't need to manage data to keep the heap structure;
	 * Instead the methods int insert(KeyType newkey), KeyType remove(const unsigned int &i),
	 * int increase_key(int i, KeyType newkey), int decrease_key(int i, KeyType newkey)
	 * int change_key(int i, KeyType newkey), void build()
	 * manage data manipulation on their own.
	 *
	 * This class was written with the intention to give some flexibility regarding the stored items.
	 * Any class that provides the algebraic relations < , > , ==, >= and <= can be used with this class.
	 * The main intention was to use a class with at least two fields - one being a key value for sorting
	 * and the other being a pointer to an bigger data structure stored outside of the tree structure.
	 *
	 * The methods find(..) to search for a certain item/key within the tree do unsorted list search.
	 *
	 * following table gives (theoretical) time complexity of algorithms on a binary heap
	 *
	 * Algorithm|  Average	|    Worst case
	 * ---------|-----------|-----------------
	 * Space	|	O(n)	|	O(n)
	 * Search	|	O(n)	|	O(n)
	 * insert	|	O(1)	|	O(log n)
	 * Delete	|	O(log n)|	O(log n)
	 * Peek		|	O(1)	|	O(1)
	 *
	 *
	 */
	template <typename KeyType>
	class BinaryHeap<KeyType>
	{
	public :
		BinaryHeap(const unsigned int &nDegree=0);
		~BinaryHeap();

		int insert(const KeyType &newkey);
		KeyType remove(const unsigned int &i);

		int increase_key(int i, KeyType new_key);
		int decrease_key(int i, KeyType new_key);
		int change_key(int i, const KeyType &new_key);
		void build();

		bool is_empty(void) const {return n_items_==0;}

		// various find functions
		template<typename Func>
		bool find(Func IsEqual) const;
		template<typename Func>
		bool find(unsigned int &iter, Func IsEqual) const;
		template<typename Func>
		bool find(const KeyType key,
				Func IsEqual = [] (const KeyType &N, const KeyType &key) {return N==key;}) const;
		template<typename Func>
		bool find(const KeyType key, unsigned int &iter,
				Func IsEqual = [] (const KeyType &N, const KeyType &key) {return N==key;}) const;

		// ToDo : 2019-09-11 ipsch: BinaryHeap member should be private
		// but there are a few accesses that rely on public rights
		KeyType *A_;                         ///< Array where heap elements get stored in (literally "The Tree")
		unsigned int max_items_;           ///< Current size of the heap (maximum number of storable elements)
		unsigned int rank_;                ///< Current number of layers/levels associated with max_items_
		unsigned int n_items_;             ///< Number of data nodes currently stored in BinarayHeap::A_

	private :


		unsigned int GetLeftsIndex(const int &i) const {return 2*i+1;}
		/**<
		 * \brief Index arithmetics to get the index of Node-is left child within BinaryHeap::A_
		 * \param[in] i Index of node-i
		 * \return The Index of node-is left child
		 */
		unsigned int GetRightsIndex(const int &i) const {return 2*i+2;}
		/**<
		 * \brief Index arithmetics to get the index of Node-is right child within BinaryHeap::A_
		 * \param[in] i Index of node-i
		 * \return The Index of node-is right child
		 */
		unsigned int GetParentsIndex(const int &i) const  {return std::floor((i-1)/2);}
		/**<
		 * \brief Index arithmetics to get the index of Node-is parent within BinaryHeap::A_
		 * \param[in] i Index of node-i
		 * \return The Index of node-is parent
		 */

		// helper functions
		bool IsMinHeap(const unsigned int &i);
		void Swap(const unsigned int &a, const unsigned int &b);
		int Resize(const unsigned int &new_max_items);
		int SiftDown(int i); // aka heapify
		int SiftUp(unsigned int i);

	};


	template <typename KeyType, typename DataType>
	class BinaryHeap<KeyType,DataType> : BinaryHeap<KeyType>
	{



	};




	////////////////////////////////////////////////////////////
	/// MEMBER FUNCTION IMPLEMENTATION /////////////////////////
	////////////////////////////////////////////////////////////

	template <typename KeyType>
	BinaryHeap<KeyType>::BinaryHeap(const unsigned int &nDegree) : rank_(nDegree), n_items_(0)
	/**
	 * \brief Constructor
	 * \param[in] nDegree number of layers pre-constructed at initialization
	 * \details since the allocation of memory for heap size is usually dynamically
	 * it can be desirable to define a lower bound on levels which are always
	 * available without dynamic allocation. This can be achieved by using nDegree (default = 0).
	 */
	{
		max_items_ = (unsigned int) (pow(2.,rank_+1)-1);;
		A_ = new KeyType[(unsigned int) pow(2.,rank_+1)];
	}


	template <typename KeyType>
	BinaryHeap<KeyType>::~BinaryHeap()
	/**
	 * \brief Destructor
	 */
	{
		delete[] A_;
	}




	template <typename KeyType>
	int BinaryHeap<KeyType>::insert(const KeyType &item)
	/**
	 *  \brief Adds an item to the heap
	 *  \details insert() automatically handles reallocation of the heaps memory if
	 *  necessary and restores minimum heap condition
	 *
	 *  \param[in] item The item to be added to the heap
	 *  \return Error-code: Return 0 on success and -1 otherwise
	 */
	{
		if (!IsMinHeap(0))
		{
			throw std::runtime_error("insert: Heap Condition not met\n");
			return -1;
		}
		// insert Item after the last one in array- A_
		// sift Item up until equilibrium is reached
		Resize(n_items_+1);
		A_[n_items_] = item;
		SiftUp(n_items_);
		++n_items_;
	  return 0;
	}


	template <typename KeyType>
	KeyType BinaryHeap<KeyType>::remove(const unsigned int &i)
	/**
	 *  \brief removes an item from the heap
	 *  \details remove() automatically handles reallocation of the heaps memory if
	 *  necessary and restores minimum heap condition
	 *
	 *  \param[in] item Index of the item to be removed from the heap
	 *  \return Copy of removed item
	 */
	{
		if (!IsMinHeap(0))
		{
			throw std::runtime_error("remove: Heap Condition not met\n");
		}

		if (i>=n_items_)
		{
			throw std::runtime_error("remove: index i out of bound\n");
		}

		KeyType removedItem = A_[i];
		int lastIdx = n_items_-1;
		Swap(i,lastIdx);
		--n_items_;
		Resize(lastIdx);
		//  Im Fall i == lastIdx wurde die Heap-Eigenschaft durch das Entfernen
		// des Elements beibehalten, und i befindet sich nun ''out of bounds'',
		// weil das Array verkleinert wurde. Ein Aufruf von heapify oder
		// decrease würde zum Absturz führen.
		if ( i != lastIdx )
		{
			if ( i == 0 || A_[i] > A_[GetParentsIndex(i)] )
			{
				SiftDown(i);
			}
			else
			{
				SiftUp(i); // decrease macht nichts, wenn H.key(i) == H.key(parent(i))
			}
		}
		return removedItem;
	}


	template <typename KeyType>
	int BinaryHeap<KeyType>::increase_key(int i, KeyType new_key)
	/**
	 * \brief decreases the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for KeyType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	{
		if (!IsMinHeap(0))
		{
			throw std::runtime_error("change_key: Heap Condition not met\n");
			return -1;
		}

		if (new_key > A_[i])
		{
			A_[i] = new_key;
			SiftDown(i);
		}
		return 0;
	}


	template <typename KeyType>
	int BinaryHeap<KeyType>::decrease_key(int i, KeyType new_key)
	/**
	 * \brief decreases the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for KeyType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	{
		if (!IsMinHeap(0))
		{
			throw std::runtime_error("change_key: Heap Condition not met\n");
			return -1;
		}


		else if (new_key < A_[i])
		{
			A_[i] = new_key;
			SiftUp(i);
		}
		return 0;
	}



	template <typename KeyType>
	int BinaryHeap<KeyType>::change_key(int i, const KeyType &newKey)
	/**
	 * \brief changes the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for KeyType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	{
		if (!IsMinHeap(0))
		{
			throw std::runtime_error("change_key: Heap Condition not met\n");
			return -1;
		}

		if (newKey > A_[i])
		{
			A_[i] = newKey;
			SiftDown(i);
		}
		else if (newKey < A_[i])
		{
			A_[i] = newKey;
			SiftUp(i);
		}
		return 0;
	}




	template <typename KeyType>
	void BinaryHeap<KeyType>::build()
	/**
	 * \brief restores heap conditions for all elements buttom up
	 * \details Applies SiftDown for all elements in BinaryHeap::A_
	 *          beginning with the last element
	 *
	 */
	{
		if (n_items_==1)
			return;
		for (int i = n_items_/2-1; i>=0; --i)
			SiftDown(i);
	}




	template<typename KeyType>
	template<typename Func>
	bool BinaryHeap<KeyType>::find(const KeyType item, Func IsEqual) const
	/**
	 * \brief Searches the heap for an item (use this if item is a literal or float and its position in heap isn't of interest)
	 *
	 * \details
	 * This search function is intended to be used if KeyType is either
	 * a literals or float. In This case the vale of item is identical to its key.
	 * IsEqual is by default:
	 *
	 * Func = [] (const KeyType &N, const KeyType &key) {return N==key;}
	 *
	 * And shouldn't be overridden.
	 *
	 * \param[in] item The item to search for
	 * \param[in] Func Function-pointer or lambda-function to compare item to items in BinaryHeap::A_

	 * \return Returns true if item was found in heap; returns false otherwise
	 *
	 * \sa
	 * - if the position of item within BinaryHeap is needed to read, remove or modify item the
	 *   method bool BinaryHeap<KeyType>::find(const KeyType key, unsigned int &iter, Func IsEqual) const
	 *   should be used.
	 * - if item is a class or object with more than one field and operator== isn't defined for this
	 *   class or the search should be applied to an other field than operator== is designed for
	 *   the one of the following two methods should be used
	 *   - bool BinaryHeap<KeyType>::find(Func IsEqual) const
	 *   - bool BinaryHeap<KeyType>::find(unsigned int &iter, Func IsEqual) const
	 */
	{
		for(unsigned int i=0; i<n_items_; ++i)
			if(IsEqual(A_[i],item))
				return true;
		return false;
	}


	template<typename KeyType>
	template<typename Func>
	bool BinaryHeap<KeyType>::find(const KeyType item, unsigned int &iter, Func IsEqual) const
	/**
	 * \brief Searches the heap for an item (use this if item is a literal or float and its position in heap is of interest)
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
	 *   method bool BinaryHeap<KeyType>::find(const KeyType item, Func IsEqual) const
	 *   should be used.
	 * - if item is a class or object with more than one field and operator== isn't defined for this
	 *   class or the search should be applied to an other field than operator== is designed for
	 *   the one of the following two methods should be used
	 *   - bool BinaryHeap<KeyType>::find(Func IsEqual) const
	 *   - bool BinaryHeap<KeyType>::find(unsigned int &iter, Func IsEqual) const
	 */
	{
		for(unsigned int i=0; i<n_items_; ++i)
			if(IsEqual(A_[i]),item)
			{
				iter = i;
				return true;
			}
		return false;
	}


	template<typename KeyType>
	template<typename Func>
	bool BinaryHeap<KeyType>::find(Func IsEqual) const
	/**
	 * \brief Searches the heap for an item (use this if item has multiple fields but no operator== or operator== isn't designed for the field you want to search for; and items position on the heap isn't of interest)
	 *
	 * \details
	 * This search function is intended to be used if KeyType is
	 * an object with multiple field but no operator== is defined or operator==
	 * doesn't compare fields you actually want to compare
	 *
	 * This function is basically the same as
	 * bool BinaryHeap<KeyType>::find(const KeyType item, Func IsEqual) const
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
	 *   - bool BinaryHeap<KeyType>::find(const KeyType item, unsigned int &iter, Func IsEqual) const
	 *   - bool BinaryHeap<KeyType>::find(const KeyType item, Func IsEqual) const
	 *   if item is literal or float
	 *
	 * - If items position on the heap is of interest, but apart from that prerequisite are the same use:
	 * bool BinaryHeap<KeyType>::find(unsigned int &iter, Func IsEqual) const
	 */
	{
		for(unsigned int i=0; i<n_items_; ++i)
			if(IsEqual(A_[i]))
				return true;
		return false;
	}


	template<typename KeyType>
	template<typename Func>
	bool BinaryHeap<KeyType>::find(unsigned int &iter, Func IsEqual) const
	/**
	 * \brief Searches the heap for an item (use this if item has multiple fields but no operator== or operator== isn't designed for the field you want to search for; and items position on the heap is of interest)
	 *
	 * \details
	 * This search function is intended to be used if KeyType is
	 * an object with multiple field but no operator== is defined or operator==
	 * doesn't compare fields you actually want to compare
	 *
	 * This function is basically the same as
	 * bool BinaryHeap<KeyType>::find(const KeyType item, unsigned int &iter, Func IsEqual) const
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
	 *
	 * \param[in] item The item to search for
	 * \param[out] iter the index of item on the heap is written iter on return
	 * \param[in] Func Function-pointer or lambda-function to compare item to items in BinaryHeap::A_

	 * \return Returns true if item was found in heap; returns false otherwise
	 *
	 * \sa
	 * - Alternatice seach functions if item is literal or float
	 *   - bool BinaryHeap<KeyType>::find(const KeyType item, unsigned int &iter, Func IsEqual) const
	 *   - bool BinaryHeap<KeyType>::find(const KeyType item, Func IsEqual) const
	 *
	 * - if item is a class or object with more than one field and operator== isn't defined for this
	 *   class or the search should be applied to an other field than operator== is designed for
	 *   the one of the following two methods should be used
	 *   - bool BinaryHeap<KeyType>::find(Func IsEqual) const
	 *   - bool BinaryHeap<KeyType>::find(unsigned int &iter, Func IsEqual) const
	 */
	{
		for(unsigned int i=0; i<n_items_; ++i)
			if(IsEqual(A_[i]))
			{
				iter = i;
				return true;
			}
		return false;
	}




	template <typename KeyType>
	bool BinaryHeap<KeyType>::IsMinHeap(const unsigned int &i)
	/**
	 * \details Checks if the sub-branch beginning at node i is a MinHeap.
	 * Meaning: For every node in the sub-tree its key must be
	 * smaller than the the key of both its children
	 * (Note: Nodes without children return true)
	 *
	 * \param[in] i Index of the Node which will be root of the subtree to be examined
	 * \return Returns true if the subtree beginning at node i fulfills the MinHeap condition (false otherwise)
	 *
	 */
	{
		if(GetLeftsIndex(i)>=n_items_) // no left child => no children at all => we are done
			return true;
		bool L = (A_[i]<=A_[GetLeftsIndex(i)]);
		if(GetRightsIndex(i)>=n_items_) // no right child => no next layer => result depends on left child only
			return L;
		if( (!L) || (A_[i]>A_[GetRightsIndex(i)]) ) // return early if heap condition is violated
			return false;
		return IsMinHeap(GetLeftsIndex(i)) &&
				IsMinHeap(GetRightsIndex(i)); // check next layer
	}


	template <typename KeyType>
	void BinaryHeap<KeyType>::Swap (const unsigned int &a, const unsigned int &b)
	/**
	 * \brief swaps two elements a and b with each other
	 * \details swap utilizes the very last element in BinaryHeap::A_ for temporary storage
	 *          (this element is never used to represent a regular node within the tree)
	 * \param[in] a First element to swap
	 * \param[in] b Second element to swap
	 */
	{
		A_[max_items_] = A_[a];
		A_[a] = A_[b];
		A_[b] = A_[max_items_];
	}


	template <typename KeyType>
	int BinaryHeap<KeyType>::Resize(const unsigned int &new_max_items)
	/**
	 * \brief reallocates memory for the heap (array BinaryHeap::A_) depending
	 * on size new_maxItems
	 *
	 * \details resize(..) is able to increase or reduce allocated memory.
	 *
	 * \param[i] new_max_items Number (aka Index) of items
	 * \return error-code 0 if reallocation was successful; -1 otherwise
	 */
	{
		// increase allocated memory
		if ( new_max_items > max_items_ )
		{
			++rank_;
			max_items_ = (unsigned int) pow(2.,rank_+1)-1;
			KeyType *tmp = new KeyType[(unsigned int) pow(2.,rank_+1)];
			for(unsigned int j=0; j<n_items_; ++j)
			{
				tmp[j] = A_[j];
			}
			delete[] A_;
			A_=tmp;
			return 0;
		}

		// do not decrease if already under certain threshold
		// (try avoid reallocating too often)
		if ( new_max_items <=2 )
			return 0;

		// decrease allocated memory if at least two levels are empty
		if ( new_max_items <= (unsigned int) pow(2.,rank_-1)-1 )
		{
			--rank_;
			max_items_ = (unsigned int) pow(2.,rank_+1)-1;
			KeyType *tmp = new KeyType[(unsigned int) pow(2.,rank_+1)];
			for(unsigned int j=0; j<n_items_; ++j)
				tmp[j] = A_[j];
			delete[] A_;
			A_=tmp;
			return 0;
		}

		return -1;
	}


	template <typename KeyType>
	int BinaryHeap<KeyType>::SiftDown(int index)
	/**
	 * \brief (aka heapify) Moves a node at index downwards within the tree by swapping with its child nodes until equilibrium is reached
	 * \details Right child has priority if left and right are equal
	 * \param[in] index Index of the node to be relocated
	 * \return Error-code: 0 on success; -1 otherwise (note used at he moment)
	 */
	{
		// ToDo : 2018-09-11 ipsch: Assert in class BinaryHeap
		if( !(IsMinHeap(GetLeftsIndex(index)) &&
				IsMinHeap(GetRightsIndex(index))) )
		{
			throw std::runtime_error("SiftDown: Heap condition not met\n");
			return -1;
		}

		int min = index;
		if (GetLeftsIndex(index) < n_items_ && A_[GetLeftsIndex(index)] < A_[min])
			min = GetLeftsIndex(index);
		if (GetRightsIndex(index) < n_items_ && A_[GetRightsIndex(index)] < A_[min])
			min = GetRightsIndex(index);
		if (min != index)
		{
			Swap(index, min);
			SiftDown(min);
		}
		return 0;
	}


	template <typename KeyType>
	int BinaryHeap<KeyType>::SiftUp(unsigned int index)
	/**
	 * \brief Moves a node at index up within the tree by swapping with its parent node until equilibrium is reached
	 *
	 * \param[in] index Index of the node to be relocated
	 * \return Error-code: 0 on success; -1 otherwise (note used at he moment)
	 */
	{
		// ToDo : 2018-09-11 ipsch: Assert in class BinaryHeap
		//if(!isMinHeap(left(0)))
		//{
		//	std::cout << "SiftUp: Heap condition not met\n";
		//	return -1;
		//}

		while ( (index > 0) && (A_[index] < A_[GetParentsIndex(index)]) )
		{
			Swap(index, GetParentsIndex(index));
			index = GetParentsIndex(index);
		}
		return 0;
	}


} // END OF NAMESPACE o_data_structures
