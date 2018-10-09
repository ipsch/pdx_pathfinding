/** \file
 * 		NRRan.hpp
 *
 * 	\brief
 * 		Random number generator from 'NUMERICAL RECIPES'
 *
 *	\details
 *		contains class Ran which is the first-to-use-on-first-trial
 *		random number generate recommended by Numerical Recipes.
 *		Class Ran is part of namespace nr_rngs
 *		(collection of numerical recipes random number generators)
 *
 * 	\version
 * 		2018-10-05 ipsch: 0.9.2 pre-final (detailed documentation needed)
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

#pragma once
#ifndef NRRAN_HPP_
#define NRRAN_HPP_

namespace nr_rngs
{

	typedef unsigned long long int Ullong;
	typedef double Doub;
	typedef unsigned int Uint;

	struct Ran
	{
		Ran(Ullong j);

		Ullong u,v,w;

		/** \brief get random number
 		 *  \return Returns a random number of type unsigned long long int
		 */
		inline Ullong int64()
		{
			u = u * 2862933555777941757LL + 7046029254386353087LL;
			v ^= v >> 17;
			v ^= v << 31;
			v ^= v >> 8;
			w = 4294957665U*(w & 0xffffffff) + (w >> 32);

			Ullong x = u ^ (u <<21);
			x ^= x >> 35;
			x ^= x << 4;
			return (x+v)^w;
		}


		/** \brief get random number
 		 *  \return Returns a random number of type double in the range [0.,1.]
		 */
		inline Doub doub()
		{
			return 5.42101086242752217E-20 * int64();
		}

		/** \brief get random number
 		 *  \return Returns a random number of type unsigned int
		 */
		inline Uint int32()
		{
			return (Uint) int64();
		}

	};

} // END OF NAMESPACE nr_rngs

#endif // END OF NRRAN_HPP_
