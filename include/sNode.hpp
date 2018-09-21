#ifndef MY_SNODE_HPP_
#define MY_SNODE_HPP_



//#include <iostream>


class sNode
{
private :
	//sNode() : id_(0), fvalue_(0), path_cost_(0), p_predecessor_(0L)
	//{
	//	std::cout << "alloc: " << this << "\t " << id_ << std::endl;
	//}
public :
	sNode() : id_(0), fvalue_(0), path_cost_(0), p_predecessor_(0L) { }
	//sNode(const unsigned int &id) : id_(id), fvalue_(0), path_cost_(0), p_predecessor_(0L)
	//{
	//	std::cout << "alloc: " << this << "\t " << id_ << std::endl;
	//}
	//~sNode()
	//{
	//	std::cout << "free: " << this << "\t " << id_ << std::endl;
	//}
	unsigned int id_;
	float fvalue_;
	int path_cost_;
	sNode *p_predecessor_;

	bool operator>(const sNode &rhs) const
	{

		return this->fvalue_>rhs.fvalue_;
	}
	bool operator<(const sNode &rhs) const
	{
		return this->fvalue_<rhs.fvalue_;
	}
	bool operator>=(const sNode &rhs) const { return this->fvalue_>=rhs.fvalue_;}
	bool operator<=(const sNode &rhs) const { return this->fvalue_<=rhs.fvalue_;}
	bool operator==(const sNode &rhs) const { return this->fvalue_==rhs.fvalue_;}

	sNode &operator=(const sNode &rhs)
	{
		id_ = rhs.id_;
		fvalue_ = rhs.fvalue_;
		path_cost_ = rhs.path_cost_;
		p_predecessor_ = rhs.p_predecessor_;
		return *this;
	}
};



template <typename T>
class ReferencingNode
/**
 * \brief a Node that provides two fields (first a key and second a reference to an instance of an Object)
 *
 * \details
 * This class can be used in a tree structure or search algorithm if the Objects referenced by ReferencingNode
 * shouldn't be moved in memory (for example if they are addressed by some pointer or are very big)
 *
 * the defined operators >,<, >=, <= and == operate on the field key_ and leave reference_ untouched
 */
{
public :
	explicit ReferencingNode() :
			key_(0), data_(0L) { }
	explicit ReferencingNode(const unsigned int &key, T *data) :
			key_(key), data_(data) { }               ///< Contructor
	/* explicit */ ReferencingNode(const ReferencingNode &rhs) :
			key_(rhs.key_), data_(rhs.data_) { }     ///< Copy Contructor
	float key_;                               ///< the key (used as order relation)
	T *data_;                                        ///< reference to some Object

	bool operator>(const ReferencingNode &rhs) const
	{
		return key_>rhs.key_;
	}                 ///< operating on key_
	bool operator<(const ReferencingNode &rhs) const
	{
		return key_<rhs.key_;
	}                 ///< operating on key_
	bool operator>=(const ReferencingNode &rhs) const
			{ return key_>=rhs.key_;}                ///< operating on key_
	bool operator<=(const ReferencingNode &rhs) const
			{ return key_<=rhs.key_;}                ///< operating on key_
	bool operator==(const ReferencingNode &rhs) const
			{ return key_==rhs.key_;}                ///< operating on key_

	ReferencingNode &operator=(const ReferencingNode &rhs)
	/**
	 * \brief copies fields of ReferencingNode
	 */
	{
		key_ = rhs.key_;
		data_ = rhs.data_;
		return *this;
	}
};



#endif
