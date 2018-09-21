#ifndef BinaryHeapNode_HPP_
#define BinaryHeapNode_HPP_
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

#include "tuple.hpp"

template <class ... Args> struct BinaryHeapNode {};

template <class KeyType>
class BinaryHeapNode<KeyType>
{
public :
	typedef BinaryHeapNode<KeyType> NodeType;
	KeyType key_;
	BinaryHeapNode(KeyType key) :
		key_(key) { };
};



template <class KeyType, class DataType>
class BinaryHeapNode<KeyType, DataType>
{
public :
	typedef BinaryHeapNode<KeyType, DataType> NodeType;
	KeyType key_;
	DataType data_;
	BinaryHeapNode(KeyType key, DataType data) :
		key_(key), data_(data) { };
};



template <class KeyType, class ... Args>
class BinaryHeapNode<KeyType, Args ...>
{
public :
	typedef BinaryHeapNode<KeyType, Args...> NodeType;
	KeyType key_;
	tuple<Args...> data_;
	BinaryHeapNode(KeyType key, Args ... args) :
		key_(key), data_(args...) { };
};



template <class KeyType>
void CopyContent(BinaryHeapNode<KeyType> &target, BinaryHeapNode<KeyType> &source)
{
	target.key_ = source.key_;
	return;
}

template <class KeyType, class ... Args>
void CopyContent(BinaryHeapNode<KeyType, Args...> &target, BinaryHeapNode<KeyType, Args...> &source)
{
	target.key_ = source.key_;
	target.data_ = source.data_;
	return;
}


#endif // END define BinaryHeapNode_HPP_
