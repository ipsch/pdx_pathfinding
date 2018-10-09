/** \file
 * 		oMath.cpp
 *
 * 	\brief
 * 		Collection of mathematical helper functions
 *
 *	\details
 *		Contains definitions to
 *  	accompanying header file oMath.hpp.
 *  	This collection of helper functions is part of
 * 		namespace o_math (my own mathematical helpers collection)
 *
 * 	\version
 * 		2018-10-08 ipsch: 1.0.0 final
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 */

#include "oMath.hpp"

namespace o_math
{

	/** \brief Calculates b^e with b=2
	 *  \details oPow2 gives up on flexibility for performance:
	 *   - implemented for unsigned int only!!
	 *  \param[in] e The exponent in b^e
	 *  \return Returns the result of 2^e
	 */
	unsigned int oPow2(unsigned int e)
	{
		unsigned int ret = 1;
		for(unsigned int i=0; i<e; ++i)
			ret <<= 1;
		return ret;
	}


} // END NAMESPACE
