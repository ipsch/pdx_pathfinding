//============================================================================
// Projekt     : oDataStructs
// Name        : rb_node.cpp
// Author      : ipsch (Ingmar Palle Schnell)
// contact     : i.p.schnell(at)gmail.com
// ceated      : 2018-07-27
// Version     : 1.1
// Copyright   : CC:by-nc-sa
// Description : data structure "red-black node" for usage in a red-black tree
//               (an implementation of self balancing 2-3-Trees)
// Reference   : Rudolf Bayer (1972). "Symmetric binary B-Trees:
//               Data structure and maintenance algorithms".
//               Acta Informatica. 1 (4): 290–306. doi:10.1007/BF00289509.
//============================================================================

// Note : - C++11 standard is needed in order to compile (variadic templates)
//        - red-black nodes (class: BinaryHeapNodes) come as two different kinds
//          first as nodes that only hold a key for sorting
//          and second nodes that can additionally hold some kind of data (or pointer).
//        - The color of BinaryHeapNode is implemented as a bool
//          color_=true represents the color BLACK.
//          color_=false represents red accordingly

#pragma once

namespace o_data_structures
{

	/** \brief a Node that provides two fields (first a key and second a reference to an instance of an Object)
	 *
	 *  \details
	 * This class can be used in a tree structure or search algorithm if the Objects referenced by ReferencingNode
	 * shouldn't be moved in memory (for example if they are addressed by some pointer or are very big)
	 *
	 * the defined operators >,<, >=, <= and == operate on the field key_ and leave reference_ untouched
	 */
	template <typename KeyType, typename DataType>
	class BinaryHeapNode
	{
	public :
		explicit BinaryHeapNode();
		explicit BinaryHeapNode(const KeyType &key, DataType data);
		//explicit BinaryHeapNode(const BinaryHeapNode<KeyType,DataType> &rhs);

		KeyType key_;                  ///< the key (used as order relation)
		DataType data_;                ///< reference to some Object

		bool operator>(const BinaryHeapNode &rhs) const;
		bool operator<(const BinaryHeapNode &rhs) const;
		bool operator>=(const BinaryHeapNode &rhs) const;
		bool operator<=(const BinaryHeapNode &rhs) const;
		bool operator==(const BinaryHeapNode &rhs) const;
		BinaryHeapNode &operator=(const BinaryHeapNode &rhs);
	}; // END OF CLASS BinaryHeapNode





	template<typename KeyType, typename DataType>
	BinaryHeapNode<KeyType,DataType>::BinaryHeapNode() :
			key_(0), data_(0L)
	{
		// Nothing to do here
	}


	template<typename KeyType, typename DataType>
	BinaryHeapNode<KeyType,DataType>::BinaryHeapNode(const KeyType &key, DataType data) :
			key_(key), data_(data)
	{
		// Nothing to do here
	}


	/** \brief Copy Contructor
	 */
	//template<typename KeyType, typename DataType>
	//BinaryHeapNode<KeyType,DataType>::BinaryHeapNode(const BinaryHeapNode &rhs) :
	//		key_(rhs.key_), data_(rhs.data_)
	//{
	//	// Nothing to do here
	//}


	template<typename KeyType, typename DataType>
	inline bool BinaryHeapNode<KeyType,DataType>::operator>(const BinaryHeapNode &rhs) const
	{
		return key_>rhs.key_;
	}


	template<typename KeyType, typename DataType>
	inline bool BinaryHeapNode<KeyType,DataType>::operator<(const BinaryHeapNode &rhs) const
	{
		return key_<rhs.key_;
	}


	template<typename KeyType, typename DataType>
	inline bool BinaryHeapNode<KeyType,DataType>::operator>=(const BinaryHeapNode &rhs) const
	{
		return key_>=rhs.key_;
	}


	template<typename KeyType, typename DataType>
	inline bool BinaryHeapNode<KeyType,DataType>::operator<=(const BinaryHeapNode &rhs) const
	{
		return key_<=rhs.key_;
	}


	template<typename KeyType, typename DataType>
	inline bool BinaryHeapNode<KeyType,DataType>::operator==(const BinaryHeapNode &rhs) const
	{
		return key_==rhs.key_;
	}



	/**
	 * \brief copies fields of ReferencingNode
	 */
	template<typename KeyType, typename DataType>
	inline BinaryHeapNode<KeyType,DataType> &BinaryHeapNode<KeyType,DataType>::operator=(const BinaryHeapNode &rhs)
	{
		key_ = rhs.key_;
		data_ = rhs.data_;
		return *this;
	}


} // END OF NAMESPACE o_data_structures

