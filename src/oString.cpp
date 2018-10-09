/** \file
 * 		oString.cpp
 *
  *  \brief
 *  	Collection of helper functions for operations on 'std::string's
 *
 *  \detail
 *  	Contains definitions to
 *  	accompanying header file oString.hpp.
 *  	The collection of helper functions is part of
 * 		namespace o_string (my own string helpers collection)
 *
 * 	\version
 * 		2018-10-08 ipsch: 1.0.0 final
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 */

#include "oString.hpp"

namespace o_string
{

	/** \brief Search for and replace all occurrences of certain substring in a string
	 *
	 *  \param[in] str String that is being searched for occurrences of substring fnd
	 *  \param[in] fnd Substring that is searched for
	 *  \param[in] rpl Substring that replaces every occurrence of fnd
	 *  \return New string with replacements
	 */
	std::string FindAndReplaceAll(std::string str, const std::string &fnd, const std::string &rpl)
	{
		std::size_t pos = str.find(fnd);
		if (pos == std::string::npos)
			return str;
		do
		{
			str.replace(pos, fnd.length(), rpl);
			pos = str.find(fnd,pos+rpl.length());
		} while (pos != std::string::npos);
		return str;
	}

} // END OF NAMESPACE o_string
