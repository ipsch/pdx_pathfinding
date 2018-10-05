/** \file
 * 		AStar.hpp
 *
 *  \brief
 *  	Provides pathfinding capabilities (A*-algorithm)
 *
 *  \version
 *  	version 2018-10-05: 0.9.0 (ipsch) final pre-shipping (development features to be removed)
 *
 *  \autor
 *
 *
 *  \details
 *  	AStar.hpp was written as a part of project pdx_pathfinding.
 * 		AStar.hpp contains declaration of class AStar and
 * 		an interface to function int FindPath(..):
 * 		- Class AStar provides the pathfinding capabilities, it's
 *   	  an implementation of the A*-algorithm first described
 *   	  by Peter Hart, Nils J. Nilsson and Bertram Raphael in 1968.
 *   	  The class must be supplemented by a representation of a graph to work on (see Map.hpp).
 * 		- The function int FindPath(..) is an interface to meet the
 *   	  requirements by Paradox Studios on how to call the implemented pathfinding algorithm.
 *        It delegates its inputs to an instance of class AStar.
 *
 *  \sa
 * 		- Class AStar is documented in AStar.hpp (this file) along with its declaration.
 * 		- Class AStars methods are documented in AStar.cpp along with their definitions.
 * 		- int FindPath(..) is documented in AStar.cpp along with its definition.
 * 		- The graph representation class AStar works on can be found in Map.hpp (and Map.cpp accordingly)
 *
 *
 * 	\section section_AStar_history Development History
 * 		\version 2018-06-25: 0.0.1 (ipsch) (file creation)
 * 		\version 2018-07-20: 0.3.0 (ipsch) (component completion)
 * 		\version 2018-08-01: 0.5.0 (ipsch) (first executable code)
 * 		\version 2018-09-05: 0.8.0 (ipsch) (feature complete documentation missing)
 *		\version 2018-10-05: 0.9.0 (ipsch) final pre-shipping (development features to be removed)
 *  \author
 * 	ipsch (Ingmar Palle Schnell)
 *
 * contact: i.p.schnell(at)gmail.com
 *
 */

#pragma once


#include "Map.hpp"           // A class to represent the game map
#include "BinaryHeap.hpp"	 // Priority queue used for the open_list_
#include "RedBlackTree.hpp"  // Binary self balancing tree class used for the closed_list_


// interface function documented in AStar.cpp
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);


// interface function with additional diagnostics documented in AStar.cpp
// ToDO: remove in shipping version
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize, unsigned int &nodes_expanded);


namespace pathfinder
{
	// ToDO: documentation
	/** \brief provides pathfinding capabilities in a graph
	 *
	 *  \detail Implementation details:
	 *  - Buffer to write computed path to is owned by caller
	 *  - Early return if computed path exceeds buffer size
	 *  - For implementation details on class AStars methods
	 *    see documentation in AStar.cpp
	 *
	 */
	class AStar
	{
	public :
		explicit AStar(o_graph::Map &map, int *p_buffer, int size_buffer);
		int FindPath(const int &iS, const int &jS, const int &iT, const int &jT);

		unsigned int nodes_expanded_; //< for diagnostics ToDO : remove in shipping version

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

