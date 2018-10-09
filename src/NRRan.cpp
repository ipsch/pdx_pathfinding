/** \file
 * 		NRRan.cpp
 *
 * 	\brief
 * 		Random number generator from 'NUMERICAL RECIPES'
 *
 *	\detail
 *		Contains definitions to
 *  	accompanying header file oString.hpp.
 *		a template class.
 *
 * 	\version
 * 		2018-10-09 ipsch: 1.0.0 final (detailed documentation needed)
 *
 *  \author
 *  	William H. Press (NUMERICAL RECIPES)
 *  \author
 *      Saul A. Teukolsky (NUMERICAL RECIPES)
 *  \author
 *  	William T. Vetterling (NUMERICAL RECIPES)
 *  \author
 *      Bian P. Flannery (NUMERICAL RECIPES)
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 *
 *  \reference
 *      'Numerical Recipes 3rd Edition',
 *      Cambridge University Press (2007), pp.342-343
 */

#include "NRRan.hpp"

namespace nr_rngs
{
		/** \brief constructor
		 *  \param[in] j Seed for RNG
		 */
		Ran::Ran(Ullong j) : v(4101842887655102017LL), w(1)
		{
			u = j ^ v; int64();
			v = u; int64();
			w = v; int64();
		}

} // END OF NAMESPACE nr_rngs



