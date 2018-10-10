/** \file
 * 		AStar.cpp
 *
 * 	\brief
 * 		contains definitions to class AStar (pathfinding capabilities)
 * 		declared in accompanying header file AStar.hpp
 *
 * 	\details
 * 		This file is part of project pdx_pathfinding
 *
 *
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 *
 */

#include "AStar.hpp"







/** \brief Interface function that delegates the task of finding a path to a class AStar object
 *
 *  \details Interface function to make AStar class compatible to Paradoxs requirements;
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
 *
 *  \return Returns the length of the shortest path between Start and
 *  Target, or -1 if no such path exists
 *
 *  \note If the shortest path consists of more visited nodes than
 *  can be stored in pOutBuffer all surplus nodes are discarded.
 */
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
{
	o_graph::Map map(nMapWidth,nMapHeight,pMap);
	pathfinder::AStar Pathfinder(map,pOutBuffer,nOutBufferSize);
	return Pathfinder.FindPath(nStartX, nStartY, nTargetX, nTargetY);
}


/** \brief Interface function that delegates the task of finding a path to a class AStar object
 *
 *  \details Version of Interface with additional diagnostic capbilities;
 *  NOT compatible to paradox requirements!!
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
 *
 *  \return Returns the length of the shortest path between Start and
 *  Target, or -1 if no such path exists
 *
 *  \note If the shortest path consists of more visited nodes than
 *  can be stored in pOutBuffer all surplus nodes are discarded.
 */
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize, unsigned int &nodes_expanded)
{
	int return_value;
	o_graph::Map map(nMapWidth,nMapHeight,pMap);
	pathfinder::AStar Pathfinder(map,pOutBuffer,nOutBufferSize);
	return_value = Pathfinder.FindPath(nStartX, nStartY, nTargetX, nTargetY);
	nodes_expanded = Pathfinder.nodes_expanded_;
	return return_value;
}


namespace pathfinder
{

	/** \brief Constructor
	 *  \param[in] map Reference to the game map represented by an instance of class Map
	 *  \param[in] p_buffer Pointer to the output buffer where the path is written to (Memory ownership by caller)
	 *  \param[in] size_buffer length of the buffer p_buffer
	 */
	AStar::AStar(o_graph::Map &map, int *p_buffer, int size_buffer) :
			map_(map), p_output_buffer_(p_buffer), output_buffer_size_(size_buffer), nodes_expanded_(0)
	{
		// nothing to do here
	}


	/** \brief Method to expand the node supplied by AStars main loop (AStar::FindPath(..))
	 *
	 *  \param[in] Pointer to the node that will be expanded
	 *  (supplied by AStar::FindPath(int iS, int jS, int iT, int jT))
	 */
	void AStar::ExpandNode(MapNode *predecessor)
	{
		map_.fill_neighbour_list(predecessor);
		while(!map_.neighbour_list_.is_empty())
		{
			unsigned int successor_id = map_.neighbour_list_.pop();

			// search closed list for successor
			if (closed_list_.find(successor_id))
				continue;

			int path_cost = predecessor->path_cost_ + 1; // 1 = distance(predecessor, successor);

			// search open list if item with successor_id already exists
			unsigned int search_index;
			bool search_success = open_list_.find_(
					search_index,
					[&successor_id] (OpenListItem &item) {return item.data_->id_ == successor_id;} );

			if (search_success)
				if(path_cost >= open_list_.A_[search_index].data_->path_cost_ )
					continue;

			float fvalue = map_.get_heuristic(successor_id) + (double) path_cost;

			++nodes_expanded_;

			if (search_success)
				open_list_.change_key(search_index, fvalue);
			else
			{
				MapNode *p_successor = new MapNode();
				p_successor->id_ = successor_id;
				p_successor->p_predecessor_ = predecessor;
				p_successor->path_cost_ = path_cost;
				p_successor->fvalue_ = fvalue;
				open_list_.insert(fvalue, p_successor);
			}
		}
		return;
	}


	/** \brief Reconstructs the shortest path found by AStar::FindPath() and writes it to Buffer p_output_buffer
	 *
	 *  \details BacktrackPath(..) will trace back the path by looking
	 *  at the node by which target was expanded (its predecessor) and
	 *  then again at targets predecessors predecessor and so on.
	 *
	 *  \note Notes:
	 *  	- The starting node is excluded from output buffer
	 *  	  AStar::p_output_buffer_ as required by paradox.
	 * 		- For a version that include the first node change:
	 *        while{..} to do{..} while and
	 *        remove offset of -1 in addressing p_output_buffer.
	 *
	 *  \param[in] target The final node on the path.
	 *  \return Length of the path from to arrive at target node
	 */
	int AStar::BacktrackPath(MapNode *target) const
	{
		MapNode *current = target;
		while (current->p_predecessor_ != 0L)
		{
			p_output_buffer_[current->path_cost_-1] = current->id_;
			current = current->p_predecessor_;
		}
		return target->path_cost_;
	}


	/** \brief 'AStar's main-loop: Finds the shortest path between a start- and target-position
	 *
	 *  \detail For details on the A-Star algorithm we like to point to standard literature
	 *  and online sources:
	 *  - https://www.redblobgames.com/pathfinding/a-star/introduction.html (date: 2018-10-04)
	 *  - https://de.wikipedia.org/wiki/A*-Algorithmus (date: 2018-10-04)
	 *  or orignal papers:
	 *  - P. E. Hart, N. J. Nilsson, B. Raphael:
	 *    A Formal Basis for the Heuristic Determination of Minimum Cost Paths.
	 *    IEEE Transactions on Systems Science and Cybernetics SSC4 (2), 1968, S. 100�107.
     *  - P. E. Hart, N. J. Nilsson, B. Raphael:
     *    Correction to �A Formal Basis for the Heuristic Determination of Minimum Cost Paths�.
     *    SIGART Newsletter, 37, 1972, S. 28�29.
	 *
	 *  \note Note slight differences to standard literature:
	 *  - Before entering main loop the heuristics (owned by AStar.map_) need to
	 *    be setup: input starting point as point of reference
	 *  - If target position is found we need to break loop (not returning at this point)
	 *    since memory needs to be free (clear_lists(..)).
	 *
	 *  \param[in] iS The zero based x-coordinate of the start position
	 *  \param[in] jS The zero based y-coordinate of the start position
	 *  \param[in] iT The zero based x-coordinate of the target position
	 *  \param[in] jT The zero based y-coordinate of the target position
	 *
	 *	\return length of the path from starting position to target;
	 *  -1 if no path exist or path length exceeded length of output buffer
	 */
	int AStar::FindPath(const int &iS, const int &jS, const int &iT, const int &jT)
	{
		int path_length = -1; // will be set to actual length if path exists

		MapNode *p_start_node = new MapNode();
		p_start_node->id_ = map_.get_id(iS,jS);

		unsigned int target_node_id = map_.get_id(iT,jT);

		map_.set_heuristic(iT,jT);
		open_list_.insert(p_start_node->fvalue_,p_start_node);

		do
		{
			// move current note from open- to closed list
			MapNode *p_current_node = open_list_.A_[0].data_;
			open_list_.remove(0);
			closed_list_.insert(p_current_node->id_, p_current_node );

			// check if target reached
			if (p_current_node->id_ == target_node_id)
			{
				path_length = BacktrackPath(p_current_node);
				break;
			}

			ExpandNode(p_current_node);

		} while (open_list_.n_items_ != 0);

		ClearLists(); // free memory allocated for starting node and by ExpandNode(..)
		return path_length;
	}


	/** \brief Frees memory allocated by expand_node(..)
	 *
	 *  \detail Memory for GraphNodes is allocated by expand_node(..) but
	 *  the nodes (and ownership of memory) are transferred to open_list_ and closed_list_;
	 * 	ClearLists() goes through both lists items and deletes the their data field (==graph node).
	 *
	 *  \note Note that both lists only manage nodes through pointers.
	 *  They didn't allocate memory for nodes, so they aren't in charge of deleting them.
	 */
	void AStar::ClearLists()
	{
		closed_list_.traverse_LRN(
				[](ClosedListItem *item) { delete item->data_; },
				closed_list_.root_);
		for(unsigned int i=0; i< open_list_.n_items_; ++i)
			delete open_list_.A_[i].data_;
		return;
	}

} // END OF NAMESPACE pathfinder
