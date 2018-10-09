/** \file
 * 		oMath.hpp
 *
 * 	\brief
 * 		Collection of mathematical helper functions
 *
 * 	\detail
 * 		This collection of helper functions is part of
 * 		namespace o_math (my own mathematical helpers collection)
 *
 * 	\version
 * 		2018-10-08 ipsch: 1.0.0 final
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


	//! \brief Calculates max{a, b}
	template <typename T>
	T max(const T &a, const T &b)
	{
		return a>b ? a : b;
	}


	//! \brief Calculates min{a, b}
	template <typename T>
	T min(const T &a, const T &b)
	{
		return a<b ? a : b;
	}


} // END namespace

#endif // END OF OMATH_HPP_


