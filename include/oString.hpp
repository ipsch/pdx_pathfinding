/** \file
 * 		oString.hpp
 *
 * 	\brief
 * 		Collection of helper functions for operations on 'std::string's
 *
 *	\detail
 *		The collection of helper functions is part of
 * 		namespace o_string (my own string helpers collection)
 *
 * 	\version
 * 		2018-10-08 ipsch: 1.0.0 final
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 */

#pragma once
#ifndef OSTRING_HPP_
#define OSTRING_HPP_


#include <string>

namespace o_string
{

	std::string FindAndReplaceAll(std::string str, const std::string &fnd, const std::string &rpl);

}

#endif // END OF OSTRING_HPP_
