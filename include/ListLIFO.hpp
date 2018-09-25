/** \file
 * 		ListLIFO.hpp
 *
 *  \brief
 *  	contains template class ListLifo (simple list to store some items)
 *
 *  \version
 *  	2018-09-25 ipsch: 1.0
 *
 *  \authors
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */
#pragma once

namespace o_data_structures
{

    /** \brief simple but fast class to maintain a List of items
	 *  \details ListLIFO (last out first out) can store N items of type T.
	 *    access via members push and pop.
	 *    Provides no guards against incorrect reading/writing! <br>
	 *    2018-09-25 ipsch: intended to store neighbouring nodes
	 *    in graph expansion
	 *  \sa Map::get_neighbours(..)
	 */
	template <class T, unsigned int N>
	class ListLIFO
	{
	public :
		ListLIFO();
		bool is_empty() const;         // checks if empty
		void push(const T &rhs);       // writing
		T pop();                       // read + removal
	private :
		T data_[N];				       //!< internal item list
		unsigned int iter_;            //!< number of items stored
	};


	//! \brief Constructor for completeness
	template <class T, unsigned int N>
	ListLIFO<T,N>::ListLIFO() :
			iter_(0)
	{
		// nothing to do here
	}


	/** \brief checks if ListLIFO is empty
	 *  \return true if at least one item is stored
	 */
	template <class T, unsigned int N>
	bool ListLIFO<T,N>::is_empty() const
	{
		return (iter_<=0);
	}


	/** \brief Stores an item in ListLIFO
	 *  \param[in] rhs The item of type T to be stored
	 */
	template <class T, unsigned int N>
	void ListLIFO<T,N>::push(const T &rhs)
	{
		data_[iter_] = rhs;
		++iter_;
		return;
	}


	/** \brief accesses and removes last stored item
	 *  \return The last stored item
	 */
	template <class T, unsigned int N>
	T ListLIFO<T,N>::pop()
	{
		--iter_;
		return data_[iter_];
	}

} // END OF NAMESPACE





