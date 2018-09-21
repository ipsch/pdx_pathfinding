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






#endif
