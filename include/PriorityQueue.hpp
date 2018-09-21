
#pragma once
#include <iostream>
//#include "PriorityQueue.hpp"


#include <iostream>
#include <cmath>                       // needed for std::floor(..)
#include <stdexcept>                   // exception handling
#include "oMath.hpp"

/*
namespace oMath
{

	unsigned int oPow2(unsigned int e)
	{
		unsigned int ret = 1;
		for(unsigned int i=0; i<e; ++i)
			ret <<= 1;
		return ret;
	}

	template <typename T>
	T max(const T &a, const T &b)
	{
		return a>b ? a : b;
	}

	template <typename T>
	T min(const T &a, const T &b)
	{
		return a<b ? a : b;
	}


} // END namespace
*/


namespace PriorityQueue
{
	template <typename KeyType, typename DataType>
	class HeapNode
	{
	public :
		explicit HeapNode() :
				key_(0), data_(0L) { }
//		explicit HeapNode(KeyType key, DataType data) :
//				key_(key), data_(data) { }               ///< Contructor
		explicit HeapNode(const KeyType &key, const DataType &data) :
				key_(key), data_(data) { }               ///< Contructor
		/* explicit */ HeapNode(const HeapNode &rhs) :
				key_(rhs.key_), data_(rhs.data_) { }     ///< Copy Contructor

		KeyType key_;
		DataType data_;

		bool operator>(const HeapNode &rhs) const {
			return key_>rhs.key_; }
		bool operator<(const HeapNode &rhs) const {
			return key_<rhs.key_;}
		bool operator>=(const HeapNode &rhs) const {
			return key_>=rhs.key_;}
		bool operator<=(const HeapNode &rhs) const {
			return key_<=rhs.key_;}
		bool operator==(const HeapNode &rhs) const {
			return key_==rhs.key_;}

		/**
		 * \brief copies fields of ReferencingNode
		 */
		HeapNode &operator=(const HeapNode &rhs)
		{
			key_ = rhs.key_;
			data_ = rhs.data_;
			return *this;
		}

	}; // END CLASS HEAPNODE

	struct Index_lr
	{
		Index_lr(const unsigned int &layer, const unsigned int &rel_index) :
			layer(layer), rel_index(rel_index)
		{ }
		unsigned int layer;
		unsigned int rel_index;
	};


	template <class ... Args> class HeapArray;

	template <typename T>
	class HeapArray<T>
	{
	public :
		explicit HeapArray();
		explicit HeapArray(const unsigned int &minimum_layers, const bool &force_never_decrease);
		~HeapArray();

		typedef unsigned int Index_i;
		typedef unsigned int Index_l;


		void resize(const Index_i &new_nData);
		void insert(const T &item);
		void remove(const Index_i &i);
		T pop(const unsigned int &i=0);
		T& operator()(const Index_i &i);
		T  operator()(const Index_i &i) const;
		T& operator()(const Index_lr &i);
		T  operator()(const Index_lr &i) const;

		bool is_empty(void) const {return nData_==0;}
		bool is_MinHeap(const Index_i &i = 0) const;

		void increase_key(const Index_i &i, const T &new_key);
		void decrease_key(const Index_i &i, const T &new_key);
		void change_key(const Index_i &i, const T &newKey);

		// various Find functions
//		template<typename Func>
//		bool Find(Func IsEqual) const;
//		template<typename Func>
//		bool Find(unsigned int &iter, Func IsEqual) const;
//		template<typename Func>
//		bool Find(const T key,
//				Func IsEqual = [] (const T &a, const T &b) {return a==b;}) const;

		template<typename Func>
		bool find_(Index_i &iter, Func IsEqual) const;
		bool find(const T &key, Index_i &iter) const;


	//protected :

		Index_lr get_index(Index_i i) const;
		Index_l  get_layer(Index_i i);
		void clean();
		void build();

		T** ppData_;
		Index_i nData_;
		Index_l nLayers_;
		Index_l nMinLayers_;
		bool force_never_decrease_;


		void swap(const Index_i &a, const Index_i &b);
		void swap(const Index_lr &a, const Index_lr &b);

		Index_i left(const Index_i &i) const {
			return 2*i+1; }
		Index_lr left(const Index_lr &i) const {
			return Index_lr(i.layer+1,2*i.rel_index); }

		Index_i  right(const Index_i &i) const {
			return 2*i+2;}
		Index_lr right(const Index_lr &lr) const {
			return Index_lr(lr.layer+1,2*lr.rel_index+1); }

		Index_i  parent(const Index_i &i) const {
			return std::floor((i-1)/2); }
		Index_lr parent(const Index_lr &lr) const {
			return Index_lr(lr.layer-1, std::floor(lr.rel_index/2)); }





		int sift_down(Index_i i);
		int sift_up(Index_i i);
	}; // END OF CLASS ########################################################################################


	template <class KeyType, class DataType>
	class HeapArray<KeyType, DataType> : public HeapArray<HeapNode<KeyType, DataType>>
	{
	public :
		typedef unsigned int Index_i;
		typedef HeapNode<KeyType, DataType> NodeType;

		void insert(const KeyType &key, const DataType &data);

		template<typename Func>
		bool find_(Index_i &iter, Func IsEqual) const;
		bool find(const KeyType &key, Index_i &iter) const;
		//template<typename Func>
		//bool find(const KeyType &key, Index_i &iter, Func IsEqual) const;


		void increase_key(const Index_i &i, const KeyType &new_key);
		void decrease_key(const Index_i &i, const KeyType &new_key);
		void change_key(const Index_i &i, const KeyType &newKey);

	};

	template <class T>
	HeapArray<T>::HeapArray() : HeapArray<T>(0, false)
	{ }


	template <class T>
	HeapArray<T>::HeapArray(const unsigned int &nMinLayers, const bool &force_never_decrease) :
			nLayers_(0), nData_(0), ppData_(0L),
			nMinLayers_(nMinLayers),
			force_never_decrease_(force_never_decrease)
	{
		if(nMinLayers)
			resize(oMath::oPow2(nMinLayers)-1);
	}


	template <class T>
	HeapArray<T>::~HeapArray()
	{
		clean();
	}


	/**
	 * \brief swaps two elements a and b with each other
	 * \details swap utilizes the very last element in PriorityQueue::A_ for temporary storage
	 *          (this element is never used to represent a regular node within the tree)
	 * \param[in] a First element to swap
	 * \param[in] b Second element to swap
	 */
	template <class T>
	void HeapArray<T>::swap(const Index_i &a, const Index_i &b)
	{
		T t = operator()(b);
		operator()(b) = operator()(a);
		operator()(a) = t;
		return;
	}


	template <class T>
	void HeapArray<T>::swap(const Index_lr &a, const Index_lr &b)
	{
		T t = operator()(b);
		operator()(b) = operator()(a);
		operator()(a) = t;
		return;
	}


	template <class T>
	void HeapArray<T>::resize(const Index_i &new_nData)
	{

		if(new_nData==0)
		{
			clean();
			return;
		}

		nData_ = new_nData;
		unsigned int new_nLayers = get_layer(new_nData);
		bool increase = new_nLayers > nLayers_ ? true : false;


		if(new_nLayers==nLayers_)
			return; // no old number of layers equals new number

		//if( !increase && force_never_decrease_ )
		//	return;
		//if( new_nLayers < nMinLayers_)
		//	return;




		unsigned int n_common_layers = oMath::min<unsigned int>(nLayers_, new_nLayers);
		unsigned int n_excess_layers = oMath::max<unsigned int>(nLayers_, new_nLayers);

		T** temp_data = new T*[new_nLayers];
		for(int i=0; i<new_nLayers; ++i)
			temp_data[i] = 0L;

		// move layers that old and new structure have in common
		for(unsigned int layer=0; layer < n_common_layers; ++layer)
			temp_data[layer] = ppData_[layer];

		// create or delete excess layers depending on
		// increasing or decreasing the data structure
		for(unsigned int layer = n_common_layers; layer < n_excess_layers; ++layer)
		{
			if(increase)
				temp_data[layer] = new T[oMath::oPow2(layer)];
			else
				delete[] ppData_[layer];
		}
		if(ppData_!=0L)
			delete[] ppData_;
		nLayers_ = new_nLayers;
		ppData_ = temp_data;
		return;
	}


	/**
	 *  \brief Adds an item to the heap
	 *  \details Insert() automatically handles reallocation of the heaps memory if
	 *  necessary and restores minimum heap condition.
	 *  Insert Item after the last one in array- A_
     * sift Item up until equilibrium is reached
	 *
	 *  \param[in] item The item to be added to the heap
	 *  \return Error-code: Return 0 on success and -1 otherwise
	 */
	template <class T>
	void HeapArray<T>::insert(const T &item)
	{
		if (!is_MinHeap())
		{
			throw std::runtime_error("Insert: Heap Condition not met\n");
			return;
		}

		resize(nData_+1);
		operator()(nData_-1) = item;
		sift_up(nData_-1);
		return;
	}



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
	template <class T>
	bool HeapArray<T>::is_MinHeap(const Index_i &i) const
	{
		if( left(i) >= nData_ ) // no left child => no children at all => we are done
			return true;
		bool L = operator()(i) <= operator()(left(i));
		if( right(i) >= nData_ ) // no right child => no next layer => result depends on left child only
			return L;
		if( (!L) || ( operator()(i) > operator()(right(i)) ) ) // return early if heap condition is violated
			return false;
		return is_MinHeap(left(i)) &&
				is_MinHeap(right(i)); // check next layer
	}



	/**
	 *  \brief Removes an item from the heap
	 *  \details Remove() automatically handles reallocation of the heaps memory if
	 *  necessary and restores minimum heap condition
	 *
	 *  \param[in] item Index of the item to be removed from the heap
	 *  \return Copy of removed item
	 */
	template <class T>
	void HeapArray<T>::remove(const unsigned int &i)
	{
		if ( !is_MinHeap() )
			throw std::runtime_error("Remove: Heap Condition not met\n");
		if ( i >= nData_ )
			throw std::runtime_error("Remove: index i out of bound\n");

		unsigned int lastIdx = nData_-1; // remember nData_ (will be changed by resize)
		swap(i,lastIdx);
		resize(lastIdx);
		//  Im Fall i == lastIdx wurde die Heap-Eigenschaft durch das Entfernen
		// des Elements beibehalten, und i befindet sich nun ''out of bounds'',
		// weil das Array verkleinert wurde. Ein Aufruf von heapify oder
		// decrease würde zum Absturz führen.
		if ( i != lastIdx )
			if ( i == 0 || operator()(i) > operator()(parent(i)) ) // ToDo : Check this line
				sift_down(i);
			else
				sift_up(i); // decrease macht nichts, wenn H.key(i) == H.key(parent(i))
		return;
	}

	/**
	 *  \brief Removes an item from the heap
	 *  \details Remove() automatically handles reallocation of the heaps memory if
	 *  necessary and restores minimum heap condition
	 *
	 *  \param[in] item Index of the item to be removed from the heap
	 *  \return Copy of removed item
	 */
	template <class T>
	T HeapArray<T>::pop(const unsigned int &i)
	{
		if ( !is_MinHeap() )
			throw std::runtime_error("Remove: Heap Condition not met\n");
		if ( i >= nData_ )
			throw std::runtime_error("Remove: index i out of bound\n");
		T t = operator()(i);
		remove(i);
		return t;
	}


	/**
	 * \brief restores heap conditions for all elements buttom up
	 * \details Applies SiftDown for all elements in PriorityQueue::A_
	 *          beginning with the last element
	 *
	 */
	template <class T>
	void HeapArray<T>::build()
	{
		if (nData_==1)
			return;
		for (int i = nData_/2-1; i>=0; --i)
			sift_down(i);
	}


	template <class T>
	T& HeapArray<T>::operator()(const Index_i &i)
	{
		if( i >= nData_)
			throw std::runtime_error("index out of bound");
		Index_lr ij = get_index(i);
		return ppData_[ij.layer][ij.rel_index];
	}


	template <class T>
	T HeapArray<T>::operator()(const Index_i &i) const
	{
		if( i >= nData_)
			throw std::runtime_error("index out of bound");
		Index_lr lr = get_index(i);
		return ppData_[lr.layer][lr.rel_index];
	}


	template <class T>
	T& HeapArray<T>::operator()(const Index_lr &lr)
	{
		return ppData_[lr.layer][lr.rel_index];
	}


	template <class T>
	T HeapArray<T>::operator()(const Index_lr &lr) const
	{
		return ppData_[lr.layer][lr.rel_index];
	}


	template <class T>
	unsigned int HeapArray<T>::get_layer(unsigned int index)
	{
		index+=1;
		unsigned int layer = 0;
		while (index >>= 1)
			++layer;
		return layer+1;
	}



	/**
	 * \brief Calculates the layer and relative index where to access data from ab absolute index
	 *
	 * \param[in] index The absolute index, supplied by user
	 * \param[out] layer The layer the be accessed
	 * \param[out] rel_index The relative index within the layer
	 */
	template <class T>
	Index_lr HeapArray<T>::get_index(unsigned int index) const
	{
		index+=1;
		unsigned int layer = 0;
		unsigned int rel_index = index;
		int ret = 1;

		while (index >>= 1)
		{
			++layer;
			ret <<= 1;
		}
		rel_index -= ret;
		return Index_lr(layer, rel_index);
	}




	template <class T>
	void HeapArray<T>::clean()
	{
		if(ppData_!=0L) // ToDo : Null class
		{
			for(unsigned int layer=0; layer < nLayers_; ++layer)
				delete[] ppData_[layer];
			delete[] ppData_;
			nData_=0;
			nLayers_=0;
			ppData_=0L;
		}
	}



	/**
	 * \brief decreases the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for dType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	template <typename T>
	void HeapArray<T>::increase_key(const Index_i &i, const T &new_key)
	{
		if (!is_MinHeap(0))
			throw std::runtime_error("changeKey: Heap Condition not met\n");
		if( new_key < operator()(i) )
			throw std::runtime_error("increase_key: newKey was too big\n");
		operator()(i) = new_key;
		sift_down(i);
		return;
	}


	template <typename T>
	void HeapArray<T>::decrease_key(const Index_i &i, const T &new_key)
	/**
	 * \brief decreases the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for dType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	{
		if (!is_MinHeap())
			throw std::runtime_error("changeKey: Heap Condition not met\n");
		if (new_key > operator()(i))
			throw std::runtime_error("decrease_key: newKey was too small\n");
		operator()(i) = new_key;
		sift_up(i);
		return;
	}



	template <typename T>
	void HeapArray<T>::change_key(const Index_i &i, const T &newKey)
	/**
	 * \brief changes the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for dType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	{
		if (!is_MinHeap())
			throw std::runtime_error("changeKey: Heap Condition not met\n");
		if (newKey > operator()(i))
			increase_key(i,newKey);
		else if (newKey < operator()(i))
			decrease_key(i, newKey);
		return;
	}


	template <typename T>
	int HeapArray<T>::sift_down(Index_i i)
	/**
	 * \brief (aka heapify) Moves a node at index downwards within the tree by swapping with its child nodes until equilibrium is reached
	 * \details Right child has priority if left and right are equal
	 * \param[in] index Index of the node to be relocated
	 * \return Error-code: 0 on success; -1 otherwise (note used at he moment)
	 */
	{
		// ToDo : 2018-09-11 ipsch: Assert in class PriorityQueue
		if( !(is_MinHeap(left(i)) &&
				is_MinHeap(right(i))) )
		{
			throw std::runtime_error("SiftDown: Heap condition not met\n");
			return -1;
		}

		int min = i;
		if (left(i) < nData_ && (operator()(left(i)) < operator()(i)) )
			min = left(i);
		if ( right(i) < nData_ && (operator()(right(i)) < operator()(min)) )
			min = right(i);
		if (min != i)
		{
			swap(i, min);
			sift_down(min);
		}
		return 0;
	}


	/**
	 * \brief Moves a node at index up within the tree by swapping with its parent node until equilibrium is reached
	 *
	 * \param[in] index Index of the node to be relocated
	 * \return Error-code: 0 on success; -1 otherwise (note used at he moment)
	 */
	template <typename T>
	int HeapArray<T>::sift_up(Index_i i)
	{
		// ToDo : 2018-09-11 ipsch: Assert in class PriorityQueue
		//if(!isMinHeap(left(0)))


		while ( (i > 0) && ( operator()(i) < operator()(parent(i) )) )
		{
			swap(i, parent(i));
			i = parent(i);
		}
		return 0;
	}


//	template<typename T>
//	template<typename Func>
//	bool HeapArray<T>::Find(const T item, Func IsEqual) const
//	/**
//	 * \brief Searches the heap for an item (use this if item is a literal or float and its position in heap isn't of interest)
//	 *
//	 * \details
//	 * This search function is intended to be used if dType is either
//	 * a literals or float. In This case the vale of item is identical to its key.
//	 * IsEqual is by default:
//	 *
//	 * Func = [] (const dType &N, const dType &key) {return N==key;}
//	 *
//	 * And shouldn't be overridden.
//	 *
//	 * \param[in] item The item to search for
//	 * \param[in] Func Function-pointer or lambda-function to compare item to items in PriorityQueue::A_
//
//	 * \return Returns true if item was found in heap; returns false otherwise
//	 *
//	 * \sa
//	 * - if the position of item within PriorityQueue is needed to read, remove or modify item the
//	 *   method bool PriorityQueue<dType>::Find(const dType key, unsigned int &iter, Func IsEqual) const
//	 *   should be used.
//	 * - if item is a class or object with more than one field and operator== isn't defined for this
//	 *   class or the search should be applied to an other field than operator== is designed for
//	 *   the one of the following two methods should be used
//	 *   - bool PriorityQueue<dType>::Find(Func IsEqual) const
//	 *   - bool PriorityQueue<dType>::Find(unsigned int &iter, Func IsEqual) const
//	 */
//	{
//		for(unsigned int i=0; i<nData_; ++i)
//			if(IsEqual(operator()(i),item))
//				return true;
//		return false;
//	}





	/**
	 * \brief Searches the heap for an item (use this if item is a literal or float and its position in heap is of interest)
	 *
	 * \details
	 * This search function is intended to be used if dType is either
	 * a literals or float and the position of item on the heap is of interest.
	 * In This case the vale of item is identical to its key.
	 * IsEqual is by default:
	 *
	 * Func = [] (const dType &N, const dType &key) {return N==key;}
	 *
	 * And shouldn't be overridden.
	 *
	 * \param[in] item The item to search for
	 * \param[out] iter the index of item on the heap is written iter on return
	 * \param[in] Func Function-pointer or lambda-function to compare item to items in PriorityQueue::A_

	 * \return Returns true if item was found in heap; returns false otherwise
	 *
	 * \sa
	 * - if the position of item on the heap isn't the
	 *   method bool PriorityQueue<dType>::Find(const dType item, Func IsEqual) const
	 *   should be used.
	 * - if item is a class or object with more than one field and operator== isn't defined for this
	 *   class or the search should be applied to an other field than operator== is designed for
	 *   the one of the following two methods should be used
	 *   - bool PriorityQueue<dType>::Find(Func IsEqual) const
	 *   - bool PriorityQueue<dType>::Find(unsigned int &iter, Func IsEqual) const
	 */
	template<typename T>
	template<typename Func>
	bool HeapArray<T>::find_(Index_i &iter, Func IsEqual) const{
		for(unsigned int i=0; i<nData_; ++i)
			if(IsEqual( operator()(i) ))
			{
				iter = i;
				return true;
			}
		return false;
	}


	template<typename T>
	bool HeapArray<T>::find(const T &key, Index_i &iter) const
	{
		return find_(iter, [&key] (const T &t) {return t==key;} );
	}

//	template<typename T>
//	template<typename Func>
//	bool HeapArray<T>::Find(Func IsEqual) const
//	/**
//	 * \brief Searches the heap for an item (use this if item has multiple fields but no operator== or operator== isn't designed for the field you want to search for; and items position on the heap isn't of interest)
//	 *
//	 * \details
//	 * This search function is intended to be used if dType is
//	 * an object with multiple field but no operator== is defined or operator==
//	 * doesn't compare fields you actually want to compare
//	 *
//	 * This function is basically the same as
//	 * bool PriorityQueue<dType>::Find(const dType item, Func IsEqual) const
//	 * but it gets rid of the item parameter, since it's assumed that
//	 * a valid closure for comparison is supplied via Func.
//	 * Func has no default value and must be supplied.
//	 *
//	 * An example how to use this function could look like this:
//	 * \code{.cpp}
//	 * 		struct foo
//	 * 		{
//	 * 			int x,y,z;
//	 * 		};
//	 *
//	 * 		PriorityQueue<foo> bar;
//	 * 		// ... inserting some items
//	 * 		int search_value=100;
//	 *  	bool search_success = bar.Find([&search_value] (foo &item) {return item.y==search_value;});
//	 * \endcode
//	 *
//	 * This example illustrates how fields that should be searched can easily be
//	 * shwitch at the point of callin Find(..)
//	 * As result of this example, all elements of PriorityQueue::A_ would have their
//	 * field y compared to search_value.
//	 *
//	 * \param[in] Func Function-pointer or lambda-function to compare item to items in PriorityQueue::A_
//	 * \return Returns true if item was found in heap; returns false otherwise
//	 *
//	 * \sa
//	 * - Use one of the alternative search functions
//	 *   - bool PriorityQueue<dType>::Find(const dType item, unsigned int &iter, Func IsEqual) const
//	 *   - bool PriorityQueue<dType>::Find(const dType item, Func IsEqual) const
//	 *   if item is literal or float
//	 *
//	 * - If items position on the heap is of interest, but apart from that prerequisite are the same use:
//	 * bool PriorityQueue<dType>::Find(unsigned int &iter, Func IsEqual) const
//	 */
//	{
//		for(unsigned int i=0; i<nData_; ++i)
//			if(IsEqual(this(i)))
//				return true;
//		return false;
//	}
//
//
//	template<typename T>
//	template<typename Func>
//	bool HeapArray<T>::Find(unsigned int &iter, Func IsEqual) const
//	/**
//	 * \brief Searches the heap for an item (use this if item has multiple fields but no operator== or operator== isn't designed for the field you want to search for; and items position on the heap is of interest)
//	 *
//	 * \details
//	 * This search function is intended to be used if dType is
//	 * an object with multiple field but no operator== is defined or operator==
//	 * doesn't compare fields you actually want to compare
//	 *
//	 * This function is basically the same as
//	 * bool PriorityQueue<dType>::Find(const dType item, unsigned int &iter, Func IsEqual) const
//	 * but it gets rid of the item parameter, since it's assumed that
//	 * a valid closure for comparison is supplied via Func.
//	 * Func has no default value and must be supplied.
//	 *
//	 * An example how to use this function could look like this:
//	 * \code{.cpp}
//	 * 		struct foo
//	 * 		{
//	 * 			int x,y,z;
//	 * 		};
//	 *
//	 * 		PriorityQueue<foo> bar;
//	 * 		// ... inserting some items
//	 * 		int search_value=100;
//	 *  	bool search_success = bar.Find([&search_value] (foo &item) {return item.y==search_value;});
//	 * \endcode
//	 *
//	 * This example illustrates how fields that should be searched can easily be
//	 * shwitch at the point of callin Find(..)
//	 * As result of this example, all elements of PriorityQueue::A_ would have their
//	 * field y compared to search_value.
//	 *
//	 *
//	 * \param[in] item The item to search for
//	 * \param[out] iter the index of item on the heap is written iter on return
//	 * \param[in] Func Function-pointer or lambda-function to compare item to items in PriorityQueue::A_
//
//	 * \return Returns true if item was found in heap; returns false otherwise
//	 *
//	 * \sa
//	 * - Alternatice seach functions if item is literal or float
//	 *   - bool PriorityQueue<dType>::Find(const dType item, unsigned int &iter, Func IsEqual) const
//	 *   - bool PriorityQueue<dType>::Find(const dType item, Func IsEqual) const
//	 *
//	 * - if item is a class or object with more than one field and operator== isn't defined for this
//	 *   class or the search should be applied to an other field than operator== is designed for
//	 *   the one of the following two methods should be used
//	 *   - bool PriorityQueue<dType>::Find(Func IsEqual) const
//	 *   - bool PriorityQueue<dType>::Find(unsigned int &iter, Func IsEqual) const
//	 */
//	{
//		for(unsigned int i=0; i<nData_; ++i)
//			if(IsEqual(this(i)))
//			{
//				iter = i;
//				return true;
//			}
//		return false;
//	}


	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////






	template <typename KeyType, typename DataType>
	void HeapArray<KeyType, DataType>::insert(const KeyType &key, const DataType &data)
	{
		HeapNode<KeyType, DataType> tmp(key, data);

		HeapArray<HeapNode<KeyType, DataType>>::insert(tmp);
		return;
	}




	/**
	 * \brief decreases the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for dType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	template <typename KeyType, typename DataType>
	void HeapArray<KeyType, DataType>::increase_key(const Index_i &i, const KeyType &new_key)
	{
		if (!this->is_MinHeap())
			throw std::runtime_error("changeKey: Heap Condition not met\n");
		if( new_key < this->operator()(i).key_ )
			throw std::runtime_error("increase_key: newKey was too big\n");
		this->operator()(i).key_ = new_key;
		this->sift_down(i);
		return;
	}

	/**
	 * \brief decreases the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for dType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	template <typename KeyType, typename DataType>
	void HeapArray<KeyType, DataType>::decrease_key(const Index_i &i, const KeyType &new_key)

	{
		if (!this->is_MinHeap())
			throw std::runtime_error("changeKey: Heap Condition not met\n");
		if (new_key > this->operator()(i).key_)
			throw std::runtime_error("decrease_key: newKey was too small\n");
		this->operator()(i).key_ = new_key;
		this->sift_up(i);
		return;
	}


	/**
	 * \brief changes the key of the node at index i to newKey
	 *
	 * \details
	 * Note: If using some class for dType Change key will use operator= offer
	 * the class to overwirte item at index with newKey
	 *
	 * \param[in] i Index of the item that will be change
	 * \param[in] newKey The new key or item to replace item at i
	 * \return Error-code 0 on success; -1 otherwise
	 */
	template <typename KeyType, typename DataType>
	void HeapArray<KeyType, DataType>::change_key(const Index_i &i, const KeyType &newKey)
	{

		if (!this->is_MinHeap())
			throw std::runtime_error("changeKey: Heap Condition not met\n");
		if (newKey > this->operator()(i).key_)
			increase_key(i,newKey);
		else if (newKey < this->operator()(i).key_)
			decrease_key(i, newKey);
		return;
	}



	/**
		 * \brief Searches the heap for an item (use this if item is a literal or float and its position in heap is of interest)
		 *
		 * \details
		 * This search function is intended to be used if dType is either
		 * a literals or float and the position of item on the heap is of interest.
		 * In This case the vale of item is identical to its key.
		 * IsEqual is by default:
		 *
		 * Func = [] (const dType &N, const dType &key) {return N==key;}
		 *
		 * And shouldn't be overridden.
		 *
		 * \param[in] item The item to search for
		 * \param[out] iter the index of item on the heap is written iter on return
		 * \param[in] Func Function-pointer or lambda-function to compare item to items in PriorityQueue::A_

		 * \return Returns true if item was found in heap; returns false otherwise
		 *
		 * \sa
		 * - if the position of item on the heap isn't the
		 *   method bool PriorityQueue<dType>::Find(const dType item, Func IsEqual) const
		 *   should be used.
		 * - if item is a class or object with more than one field and operator== isn't defined for this
		 *   class or the search should be applied to an other field than operator== is designed for
		 *   the one of the following two methods should be used
		 *   - bool PriorityQueue<dType>::Find(Func IsEqual) const
		 *   - bool PriorityQueue<dType>::Find(unsigned int &iter, Func IsEqual) const
		 */
	/*
	template <typename KeyType, typename DataType>
	template<typename Func>
	bool HeapArray<KeyType,DataType>::find(const KeyType &key, Index_i &iter, Func IsEqual) const

	{
		for(unsigned int i=0; i<nData_; ++i)
		{
			NodeType node;
			node = operator()(i);
			if(IsEqual(node.key_, key) )
			{
				iter = i;
				return true;
			}
		}
		return false;
	}
*/




	template<typename KeyType, typename DataType>
	template<typename Func>
	bool HeapArray<KeyType,DataType>::find_(Index_i &iter, Func IsEqual) const
	{
		for(unsigned int i=0; i<this->nData_; ++i)
			if(IsEqual( this->operator()(i) ))
			{
				iter = i;
				return true;
			}
		return false;
	}



	template<typename KeyType, typename DataType>
	bool HeapArray<KeyType,DataType>::find(const KeyType &key, Index_i &iter) const
	{
		return find_(iter, [&key] (const NodeType &node) {return node.key_==key;} );
	}

	/*
	template<typename KeyType, typename DataType>
	template<typename Func>
	bool HeapArray<KeyType,DataType>::find(const KeyType &key, Index_i &iter, Func func ) const
	{
		return find_(iter, func );
	}
	*/

} // END NAMESPACE
