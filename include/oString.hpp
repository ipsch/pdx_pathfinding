/** \file
 * 		oString.hpp
 *
 * 	\brief
 * 		Helper functions to handle 'std::string's
 *
 * 	\version
 * 		2018-10-05 ipsch: 0.9.1 pre-final (detailed documentation needed)
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 */
#pragma once
#ifndef OSTRING_HPP_
#define OSTRING_HPP_

#include <string>

std::string FindAndReplaceAll(std::string str,
		const std::string &fnd,
		const std::string &rpl);
// Helper function to search a string for a certain substring
// an replace all occurrences with a replacement-string
// str - input sting that is being searched
// fnd - substring that is searched for
// rpl - substring that will replace fnd
// return value is a new string with replacements

#endif // END OF OSTRING_HPP_
