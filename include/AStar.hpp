/** \file
 * 		AStar.hpp
 *
 *  \brief
 *  	Provides pathfinding capabilities (A*-algorithm)
 *
 *  \details
 *  	AStar.hpp was written as a part of project pdx_pathfinding.
 * 		AStar.hpp contains declaration of class AStar and
 * 		an interface to function int FindPath(..):
 * 		- Class AStar provides pathfinding capabilities.
 * 		  It is an implementation of the A*-algorithm (see reference in class documentation).
 *   	  The class must be supplemented by a representation of a graph/map to work on.
 * 		- The function int FindPath(..) is an interface to meet the
 *   	  requirements by Paradox on how to call the implemented path finding algorithm.
 *        It delegates its inputs to an instance of class AStar.
 *
 *  \version
 *  	version 2018-10-05 ipsch: 1.0.0 final
 *
 *  \author
 * 		ipsch: Ingmar Schnell
 * 		contact: i.p.schnell(at)gmail.com
 *  \sa
 *  	class Map in Map.hpp for map/graph representation
 *
 */

#pragma once
#ifndef ASTAR_HPP_
#define ASTAR_HPP_


#include "Map.hpp"           // A class to represent the game map
#include "BinaryHeap.hpp"	 // Priority queue used for the open_list_
#include "RedBlackTree.hpp"  // Binary self balancing tree class used for the closed_list_


// interface function documented in AStar.cpp
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);


// interface function with additional diagnostics documented in AStar.cpp
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize, unsigned int &nodes_expanded);


namespace pathfinder
{


	/** \brief provides pathfinding capabilities (implements A*-algorithm)
	 *
	 *  \detail Implementation details:
	 *  	- Buffer to write computed path to is owned by caller
	 *  	- Early return if computed path exceeds buffer size
	 *
	 *  \sa
	 *  	See AStar.cpp for implementation details on AStars methods
	 *
	 * 	\references
	 *  	- P. E. Hart, N. J. Nilsson, B. Raphael:
	 *  	  A Formal Basis for the Heuristic Determination of Minimum Cost Paths.
	 *  	  IEEE Transactions on Systems Science and Cybernetics SSC4 (2), 1968, S. 100–107.
	 *	    - P. E. Hart, N. J. Nilsson, B. Raphael:
	 *	      Correction to „A Formal Basis for the Heuristic Determination of Minimum Cost Paths“.
	 *	      SIGART Newsletter, 37, 1972, S. 28–29.
	 */
	class AStar
	{
	public :
		explicit AStar(o_graph::Map &map, int *p_buffer, int size_buffer);
		int FindPath(const int &iS, const int &jS, const int &iT, const int &jT);

		unsigned int nodes_expanded_; //< for diagnostics

	protected :
		typedef o_graph::Map Map;
		typedef o_graph::MapNode MapNode;
		typedef o_data_structures::BinaryHeap<float, MapNode*> OpenList;
		typedef o_data_structures::BinaryHeapNode<float, MapNode*> OpenListItem;
		typedef o_data_structures::RedBlackTree<unsigned int, MapNode*> ClosedList;
		typedef o_data_structures::RedBlackNode<unsigned int, MapNode*> ClosedListItem;

		AStar();
		void ExpandNode(MapNode *predecessor);
		int BacktrackPath(MapNode *node_on_path) const;
		void ClearLists();

		int output_buffer_size_;  //< size of Buffer for returning computed path
		int *p_output_buffer_;    //< pointer to buffer for returning computed path (memory owned by caller)
		Map &map_;                //< Reference to the game map (provided by caller)
		OpenList open_list_;      //< Priority queue containing all Nodes that need processing
		ClosedList closed_list_;  //< Binary search tree containing all visited nodes

	}; // END OF CLASS AStar

} // END OF NAMESPACE pathfinder

#endif // END OF ASTAR_HPP_

