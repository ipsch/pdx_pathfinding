
#include <queue>
#include <vector>

#ifndef UNIFORMCOSTSEARCH_HPP_
#define UNIFORMCOSTSEARCH_HPP_

	/** \brief Interface to use uniform cost search
	 *
	 *  \param[in] nStartX The zero based x-coordinate of the start position
	 *  \param[in] nStartY The zero based y-coordinate of the start position
	 *  \param[in] nTargetX The zero based x-coordinate of the target position
	 *  \param[in] nTargetY The zero based y-coordinate of the target position
	 *  \param[in] pMap A pointer to the grid data (see \ref Map.hpp)
	 *  \param[in] nMapWidth the width of the map (its extent in x-direction)
	 *  \param[in] nMapHeight the height of the map (its extent in y-direction)
	 *  \param[out] pOutBuffer Pointer to a buffer where the indices of visited grid points are
	 *  stored (excluding the starting position)
	 *  \param[in] nOutBufferSize length of the buffer pOutBuffer
	 */
	int FindPath(const int nStartX, const int nStartY,
				 const int nTargetX, const int nTargetY,
				 const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
				 int* pOutBuffer, const int nOutBufferSize);


#endif
