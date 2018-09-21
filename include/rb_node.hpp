#ifndef REDBLACKNODE_HPP_
#define REDBLACKNODE_HPP_
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
//        - red-black nodes (class: RedBlackNodes) come as two different kinds
//          first as nodes that only hold a key for sorting
//          and second nodes that can additionally hold some kind of data (or pointer).
//        - The color of RedBlackNode is implemented as a bool
//          color_=true represents the color BLACK.
//          color_=false represents red accordingly

#include "tuple.hpp"

template <class ... Args> struct RedBlackNode {};

template <class KeyType>
class RedBlackNode<KeyType>
{
public :
	typedef RedBlackNode<KeyType> NodeType;
	NodeType *left_child_;
	NodeType *right_child_;
	NodeType *parent_;
	KeyType key_;
	bool color_;
	RedBlackNode(KeyType key) :
		key_(key), left_child_(0L), right_child_(0L), parent_(0L), color_(true) { };
};



template <class KeyType, class DataType>
class RedBlackNode<KeyType, DataType>
{
public :
	typedef RedBlackNode<KeyType, DataType> NodeType;
	NodeType *left_child_;
	NodeType *right_child_;
	NodeType *parent_;
	KeyType key_;
	DataType data_;
	bool color_;
	RedBlackNode(KeyType key, DataType data) :
		key_(key), data_(data), left_child_(0L), right_child_(0L), parent_(0L), color_(true) { };
};



template <class KeyType, class ... Args>
class RedBlackNode<KeyType, Args ...>
{
public :
	typedef RedBlackNode<KeyType, Args...> NodeType;
	NodeType *left_child_;
	NodeType *right_child_;
	NodeType *parent_;
	KeyType key_;
	tuple<Args...> data_;
	bool color_;
	RedBlackNode(KeyType key, Args ... args) :
		key_(key), data_(args...), left_child_(0L), right_child_(0L), parent_(0L), color_(true) { };
};



template <class KeyType>
void CopyContent(RedBlackNode<KeyType> &target, RedBlackNode<KeyType> &source)
{
	target.key_ = source.key_;
	return;
}

template <class KeyType, class ... Args>
void CopyContent(RedBlackNode<KeyType, Args...> &target, RedBlackNode<KeyType, Args...> &source)
{
	target.key_ = source.key_;
	target.data_ = source.data_;
	return;
}


#endif // END define REDBLACKNODE_HPP_
