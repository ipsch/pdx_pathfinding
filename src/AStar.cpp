/**
 * \file AStar.cpp
 * this file is part of project pdx_pathfinding
 *
 * \brief definitions to class AStar and interface function int FindPath()
 *
 *
 *
 */

#include "AStar.hpp"








int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
/**
 * \brief Interface function that redirects the task of finding a path to an class AStar object.
 *
 * \details Interface function to make AStar class compatible to Paradoxs requirements
 *
 * \param[in] nStartX The zero based x-coordinate of the start position
 * \param[in] nStartY The zero based y-coordinate of the start position
 * \param[in] nTargetX The zero based x-coordinate of the target position
 * \param[in] nTargetY The zero based y-coordinate of the target position
 * \param[in] pMap A pointer to the grid data (see \ref Map.hpp)
 * \param[in] nMapWidth the width of the map (its extent in x-direction)
 * \param[in] nMapHeight the height of the map (its extent in y-direction)
 * \param[out] pOutBuffer Pointer to a buffer where the indices of visited grid points are
 *   stored (excluding the starting position)
 * \param[in] nOutBufferSize length of the buffer pOutBuffer
 *
 * \return Returns the length of the shortest path between Start and
 *   Target, or -1 if no such path exists
 *
 * \note If the shortest path consists of more visited nodes than
 *   can be stored in pOutBuffer all surplus nodes are discarded.
 *
 */
{

	Map map(nMapWidth,nMapHeight,pMap);
	AStar Pathfinder(map,pOutBuffer,nOutBufferSize);
	return Pathfinder.FindPath(nStartX, nStartY, nTargetX, nTargetY);
}



int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize, unsigned int &nodes_expanded)
{
	int return_value;
	Map map(nMapWidth,nMapHeight,pMap);
	AStar Pathfinder(map,pOutBuffer,nOutBufferSize);
	return_value = Pathfinder.FindPath(nStartX, nStartY, nTargetX, nTargetY);
	nodes_expanded = Pathfinder.nodes_expanded_;
	return return_value;
}



//AStar::AStar() //:
		//output_buffer_size_(0), p_output_buffer_(0L), map_(0L)
/** Constructor (made private to not be accessible form the outside) */
//{ }


AStar::AStar(Map &map, int *p_buffer, int size_buffer) :
		map_(map), p_output_buffer_(p_buffer), output_buffer_size_(size_buffer), nodes_expanded_(0)
/**\brief Constructor
 * \param[in] map Reference to the game map represented by an instance of class Map
 * \param[in] p_buffer Pointer to the output buffer where the path is written to (Memory ownership by caller)
 * \param[in] size_buffer length of the buffer p_buffer
 */
{ }


int AStar::ExpandNode(sNode *predecessor)
/**
 * \brief Method to expand the node supplied by AStar::FindPath(..) and put its neigbours on the AStar::open_list_
 *
 * \param[in] predecessor The Node supplied by AStar::FindPath(int iS, int jS, int iT, int jT) to be expanded next
 *
 * \return Returns error-code (Not used at the moment)
 */
{
	std::vector<unsigned int> list_of_successor_ids;
	map_.GetNeighbourList(list_of_successor_ids, predecessor->id_);

	for(auto successor_id : list_of_successor_ids)
	{

        if (closed_list_.find(successor_id)) // successor already visited
            continue;

        int path_cost = predecessor->path_cost_ + 1.; // 1 = distance(predecessor, successor);


		unsigned int search_index;
		bool search_success = open_list_.find(search_index,
				[&successor_id] (ReferencingNode<sNode> &N) {return N.data_->id_==successor_id;});

        if (search_success)
        	if(path_cost >= open_list_.A_[search_index].data_->path_cost_ )
        		continue;

        float fvalue = map_.heuristic(successor_id) + (double) path_cost;//heuristic_(map_.GetIJ(successor_id));

		//sNode successor;
        ++nodes_expanded_;
        sNode *p_successor = new sNode();
        p_successor->id_ = successor_id;
        p_successor->p_predecessor_ = predecessor;
        p_successor->path_cost_ = path_cost;
        p_successor->fvalue_ = fvalue;

		ReferencingNode<sNode> r_successor(p_successor->fvalue_,p_successor);

		// ToDO 2018-09-13 ipsch: mem-leak in AStar::Expand node
		// ChangeKey referencing Node new item
		// old referencing node get's deleted, but old item isn't
		if (search_success)
            open_list_.change_key(search_index, r_successor);
        else
        	open_list_.insert(r_successor);
	}
    return 0;
}

int AStar::BacktrackPath(sNode *target)
/**
 * \brief Reconstructs the shortest path found by AStar::FindPath() and writes it to Buffer p_output_buffer;
 *
 * \details BacktrackPath(..) will trace back the path by looking
 * at the node by which target was expanded (its predecessor) and then again at targets predecessors predecessor and so on.
 * Note: The first node is excluded from output buffer AStar::p_output_buffer_ as required by paradox.
 * notes for an version that include the first node:
 *  - while{...} changed to do{...} while
 *  - Addressing p_output_buffer: remove offset -1
 *
 * \details
 * \param[in] target The final node on the path.
 *
 * \return Length of the path from to arrive at target node
 *
 * \sa
 * - Backtrack relies on class sNode::p_predecessor_
 *
 */
{
	sNode *current = target;
	while (current->p_predecessor_ != 0L)
	{
		p_output_buffer_[current->path_cost_-1] = current->id_;
		current = current->p_predecessor_;
	}
	return target->path_cost_;
}





int AStar::FindPath(const int &iS, const int &jS, const int &iT, const int &jT)
/**
 * \brief A*s main-loop: Finds the shortest path between a start- and target-position
 *
 *
 * \note
 *
 * \par on ownership of memory
 * Memory associated with graph nodes is owned by the instance of AStar.
 * Memory is allocated by AStar::ExpandNode(..)
 *
 * are not owned by openlist or closedlist either.
 * Owner is the instance of AStar.  allocates memory that is in turn
 * linked by one of the lists. AStar has no way of accessing this memory exect through
 * those lists
 *
 *
 */
{
	int path_length = -1; // will be set to actual length if path exists

	sNode *p_start_node = new sNode();
	p_start_node->id_ = map_.GetIndex(iS,jS);
	p_start_node->fvalue_ = 0;
	p_start_node->path_cost_ = 0;
	p_start_node->p_predecessor_ = 0L;

	unsigned int target_node_id = map_.GetIndex(iT,jT);


	map_.set_heuristic(target_node_id);
	open_list_.insert(ReferencingNode<sNode>(p_start_node->fvalue_,p_start_node));


    do
    {
    	sNode *p_current_node = open_list_.A_[0].data_;
    	open_list_.remove(0);

        // check if target reached
        if ( p_current_node->id_ == target_node_id )
        {
        	path_length = BacktrackPath(p_current_node);
            break;
        }

    	// move to closed list
        closed_list_.Insert(
        		/* key: */ p_current_node->id_,
				/* p_data: */ p_current_node );

        ExpandNode(p_current_node);

    } while (open_list_.n_items_);

    ClearLists();
    return path_length;
}


void AStar::ClearLists()
/**
 * \brief frees memory allocated for graph nodes
 * Memory is allocated by AStar::ExpandNode(..) and managed by open- and closed list.
 */
{
	closed_list_.TraverseLRN(
			[](RedBlackTree<unsigned int, sNode*>::NodeType *N) {delete N->data_;},
			closed_list_.root_);
	for(unsigned int i=0; i< open_list_.n_items_; ++i)
		delete open_list_.A_[i].data_;
	return;
}

