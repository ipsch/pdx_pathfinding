/** \file
 * 		main.cpp
 *
 *  \brief
 * 		contains main() to pdx_pathfinding project + projects documentation main page
 *
 *  \detail
 *  	path finding problem from paradox interactive
 *  	project: pdx_pathfinding
 *
 *  \version
 *  	2018-06-19 ipsch: 0.1.0 (project creation)
 *
 *  \author
 *  	ipsch (Ingmar Schnell)
 *  	contact: i.p.schnell(at)gmail.com
 *
 *	\sa References:
 *		- Paradoxs pathfinding test on kattis https://paradox.kattis.com/problems/paradoxpath
 *
 *
 * \mainpage Project overview
 *
 * \tableofcontents
 *
 * \section section_about About this Project:
 *   This project was created as part of a job application at Paradox Studios (Sweden).
 *   The task was to implement a path-finding algorithm in C++ that finds and returns
 *   a shortest path between two points in a 2-dimensional rectangular grid.
 *   In Order to repurpose this code after the application the project is divided
 *   in two parts - namely the core part that includes everything needed to solve
 *   the pure path finding problem and secondly an auxiliary part that was used
 *   to test and benchmark the path finding algorithm.
 *
 * \section Project components
 *
 * \subsection section_core Core part
 *
 * \subsection section_auxiliary Auxiliary part
 *
 *
 *
 * Constraints
 * You may safely assume following relations are always true:
 *   (1<=nMapWidth)
 *   (1<=nMapHeight)
 *   (0<=nStartX)
 *	 (nTargetX<nMapWidth)
 *   (0<=nStartY), (nTargetY<nMapHeight)
 *   Both Start and Target are empty locations,
 *   (nOutBufferSize>=0)
 *
 *
 * \section project_dev_history_
 *          Development History:
 * \version 2018-06-19: 0.0.1 (project creation)
 * \version 2018-06-25: 0.2.0 (research done + literature collection)
 * \version 2018-07-20: 0.3.0 (component completion)
 * \version 2018-08-01: 0.5.0 (first executable code)
 * \version 2018-09-04: 0.8.0 (feature complete documentation missing)
 *
 *
 * Copyright   : CC:by-nc-sa
 *
 */


//============================================================================
//
// nStartX and nStartY are the 0 based coordinates of the start position.
// nTargetX and nTargetY are the 0-based coordinates of the target position.
// pMap describes a grid of width nMapWidth and height nMapHeight.
//   The grid is given in row-major order, each row is given in order of
//   increasing x-coordinate, and the rows are given in order of increasing
//   y-coordinate. Traversable locations of the grid are indicated by 1,
//   and impassable locations are indicated by 0.
//   Locations are considered to be adjacent horizontally and
//   vertically but not diagonally.
// pOutBuffer is where the positions visited in the found path are stored,
//   excluding the starting position but including the final position.
//   Entries in pOutBuffer are indices into pMap. If there is more than one
//   shortest path from Start to Target, any one of them will be accepted.
// nOutBufferSize is the maximum number of entries that can be
//   written to pOutBuffer.
// The function must return the length of the shortest path between Start and
//   Target, or -1 if no such path exists.
// If the shortest path is longer than nOutBufferSize, the calling function
//   might either give up or choose to call FindPath again with a larger output buffer.









#include <iostream>
#include "AStar.hpp"                  // Path finding algorithm



void exa_1()
{
	 //    For this input FindPath must return 3
	 // and the first three positions of pOutBuffer must be populated with {1, 5, 9}.
	std::cout << "exa_1()\n";

	unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
	int pOutBuffer[12];
    int result = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    std::cout << "buffer=\t";
    for(int i=0; i<12; ++i)
    {
    	std::cout << pOutBuffer[i] << "\t";
    }

    return;
}


 void exa_2()
 {
	 //For this input FindPath must return -1
	 std::cout << "exa_2()\n";

	 unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
	 int pOutBuffer[7];
	 int result = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

     std::cout << "result=\t" << result << std::endl;

     std::cout << "buffer=\t";
     for(int i=0; i<7; ++i)
     {
     	std::cout << pOutBuffer[i] << "\t";
     }

     return;
 }






int main(void)
{

	exa_1();
	exa_2();

	return 0;
}


