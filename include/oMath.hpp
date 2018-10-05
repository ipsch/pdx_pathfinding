/** \file
 * 		oMath.hpp
 *
 * 	\brief
 * 		Mathematicla helper functions
 *
 * 	\version
 * 		2018-10-05 ipsch: 0.9.1 pre-final (detailed documentation needed)
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 */
#pragma once
#ifndef OMATH_HPP_
#define OMATH_HPP_

namespace o_math
{

	unsigned int oPow2(unsigned int e);


	template <typename T>
	T max(const T &a, const T &b)
	{
		return a>b ? a : b;
	}

	template <typename T>
	T min(const T &a, const T &b)
	{
		return a<b ? a : b;
	}


} // END namespace

#endif // END OF OMATH_HPP_


