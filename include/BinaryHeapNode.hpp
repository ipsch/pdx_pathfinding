/** \file
 * 		BinaryHeapNode.hpp
 *
 *  \brief
 *  	Provides NodeType to be used with class BinaryHeap.hpp
 *
 *  \details
 *  	Nodes consist of two fields key_ and data_.
 *  	Operators for order relations are provided
 *
 * \version
 * 		2018-10-11: 1.1.0 (ipsch) modified to work with Paradox Problem A
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */

#ifndef BINARYHEAPNODE_HPP_
#define BINARYHEAPNODE_HPP_

namespace o_data_structures
{

	/** \brief a Node that provides two fields (key and data)
	 *
	 *  \details
	 * 	Class BinaryHeapNode can be used in a tree structure or search algorithm.
	 * 	Main idea is to use a pointer as type for data_ if the Object data_ is referring to
	 * 	shouldn't be move in memory (for example if the object is addressed by another pointer as well
	 * 	or the object is very big).
	 *
	 * 	the defined operators >,<, >=, <= and == operate on the field key_ and leave data_ untouched
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
			key_(), data_()
	{
		// Nothing to do here
	}


	template<typename KeyType, typename DataType>
	BinaryHeapNode<KeyType,DataType>::BinaryHeapNode(const KeyType &key, DataType data) :
			key_(key), data_(data)
	{
		// Nothing to do here
	}


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



	/** \brief copies fields of ReferencingNode
	 */
	template<typename KeyType, typename DataType>
	inline BinaryHeapNode<KeyType,DataType> &BinaryHeapNode<KeyType,DataType>::operator=(const BinaryHeapNode &rhs)
	{
		key_ = rhs.key_;
		data_ = rhs.data_;
		return *this;
	}


} // END OF NAMESPACE o_data_structures

#endif // END OF BINARYHEAPNODE_HPP_
