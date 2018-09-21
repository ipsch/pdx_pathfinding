/*!
 * \file AStar.hpp
 * AStar.hpp was written as a part of project pdx_pathfinding
 *
 * \brief Provides pathfinding capabilities
 *
 * \details AStar.hpp contains declarations for class AStar and
 * an interface function int FindPath(..):
 * - Class AStar provides the pathfinding capabilities, it's basically
 *   a realization of the A*-algorithm first described
 *   by Peter Hart, Nils J. Nilsson and Bertram Raphael in 1968.
 *   The class must be supplemented by a representation of a graph to work on (see Map.hpp).
 *   It comes alongside with methods for interfacing with the main program and handling internal (sub-)tasks.
 *   Its internal data structure is not meant to be accessed directly from the outside
 * - The function int FindPath() serves as an interface to meet the
 *   requirements by Paradox Studios on how to call the implemented pathfinding algorithm.
 *   It redirects its inputs to an instance of class AStar.
 *
 * \sa
 * - Class AStar is documented in AStar.hpp (this file) along with its declaration.
 * - Class AStars methods are documented in AStar.cpp along with their definitions.
 * - int FindPath(..) is documented in AStar.cpp along with its definition.
 * - The graph representation class AStar works on can be found in Map.hpp (and Map.cpp accordingly)
 *
 *
 * \section section_AStar_history Development History
 * \version 2018-06-25: 0.0.1 (ipsch) (file creation)
 * \version 2018-07-20: 0.3.0 (ipsch) (component completion)
 * \version 2018-08-01: 0.5.0 (ipsch) (first executable code)
 * \version 2018-09-05: 0.8.0 (ipsch) (feature complete documentation missing)
 *
 * \author ipsch (Ingmar Palle Schnell)
 *
 * contact: i.p.schnell(at)gmail.com
 *
 */

#ifndef ASTAR_HPP_
#define ASTAR_HPP_

// ToDo 2018-09-11 ipsch: cmath still needed in AStar?
#include <cmath>                    // Cs math needed for ???
#include <vector>					// needed for list of neighbouring Nodes in function ExpandNode

#include "BinaryHeap.hpp"			// priority queque used for the open_list_
#include "rb_tree.hpp"				// binary self balancing tree class used for the closed_list_

// ToDo : 2018-09-11 ipsch: rework heuristics
// metrics should belont to heuristics also to maps
#include "metrics_helpers.hpp"
#include "sNode.hpp"				// A data-struct to encapsulate information about single grid node
#include "Map.hpp"                  // A class to representation the game map
#include "PriorityQueue.hpp"

using namespace PriorityQueue;

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);
// nStartX and nStartY are the 0 based coordinates of the start position.
// nTargetX and nTargetY are the 0-based coordinates of the target position.


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize, unsigned int &nodes_expanded);






class Heuristic_2d_discrete
{
private :
	int x0_;
	int y0_;
public :
	void Set(const coordinate &target)
	{
		x0_=target.x;
		y0_=target.y;
		return;
	}
	int operator()(const coordinate &position) const
	{
		return DiscreteMeasure(position.x-x0_, position.y-y0_);
	}
};







class AStar
/**
 * \brief provides pathfinding capabilities in a graph
 *
 * For implementation details on class AStars methods see documentation in AStar.cpp
 *
 *
 *
 * \section section_AStar_details Implementation details
 *
 *
 */
{
public :
	explicit AStar(Map &map, int *p_buffer, int size_buffer);
	int FindPath(const int &iS, const int &jS, const int &iT, const int &jT);
	unsigned int nodes_expanded_;
private :

	typedef ReferencingNode<sNode> NodeType;
	AStar();
	void ClearLists();
	int ExpandNode(sNode *predecessor);
	int BacktrackPath(sNode *node_on_path);
	// ToDo : 2018-09-11 ipsch: rework heuristics
	// should belong to map
	Heuristic_2d_discrete heuristic_;
	BinaryHeap<NodeType> open_list_;   /**< Priority queue containing all Nodes that need processing */
	//HeapArray<float, sNode*> open_list_;   /**< Priority queue containing all Nodes that need processing */

	RedBlackTree<unsigned int, sNode*>
		closed_list_;                  /**< Binary search tree containing all visited nodes  */
	Map &map_;                         /**< Reference to the game map (provided by caller) */
	int* p_output_buffer_;             /**< pointer to buffer where the shortest path is written to if found by AStar::FindPath(..)
	                                    *  \details - ownership of memory is handled by caller */
	int output_buffer_size_; 	       /**< size of the Buffer \ref p_output_buffer_ */
};










#endif
