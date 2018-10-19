/** \file
 * 		UniformCostSearch.cpp
 *
 *  \brief
 *  	Provides pathfinding capabilities
 *
 *  \details
 *		Uniform Cost Search is a variation of Dijkstra-algorithm
 *
 *  \version
 *  	version 2018-10-17 ipsch: 1.0.0 final
 *
 *  \author
 * 		ipsch: Ingmar Schnell
 * 		contact: i.p.schnell(at)gmail.com
 *
 * 	\references
 * 		- Mehlhorn, Kurt; Sanders, Peter (2008). "Chapter 10. Shortest Paths" (PDF).
 * 		  Algorithms and Data Structures: The Basic Toolbox.
 * 		  Springer. doi:10.1007/978-3-540-77978-0. ISBN 978-3-540-77977-3.
 * 		- Dijkstra, E. W. (1959). "A note on two problems in connexion with graphs"
 *
 */


#include "UniformCostSearch.hpp"



//std::mutex ucs_mutex;



//! \brief Note Type for open list
typedef struct Node
{
	Node() :
		id(0), cost(0)
	{
		// nothing to do here
	}
	Node(const Node &rhs) :
		id(rhs.id), cost(rhs.cost)
	{
		// nothing to do here
	}
	Node(const unsigned int &id, const int &cost ) :
		id(id), cost(cost)
	{
		// nothing to do here
	}

	unsigned int id;  //< unique id to identify the node
	int cost;         //< path cost to reach this node
} Node;


bool operator<(const Node &a, const Node &b) {
	return a.cost < b.cost;
}


bool operator>(const Node &a, const Node &b) {
	return a.cost > b.cost;
}


bool operator<=(const Node &a, const Node &b) {
	return a.cost <= b.cost;
}


bool operator>=(const Node &a, const Node &b) {
	return a.cost >= b.cost;
}


bool operator==(const Node &a, const Node &b) {
	return a.cost == b.cost;
}


/** \brief calculates a nodes x-coordinate from its id
 *  \param[in] id The nodes id
 *  \param[in] width the maps width
 *  \return The nodes x-coordinate
 */
inline unsigned int GetId(const int &x, const int &y, const int &width)
{
	return x + y*width;
}


/** \brief calculates a nodes x-coordinate from its id
 *  \param[in] id The nodes id
 *  \param[in] width the maps width
 *  \return The nodes x-coordinate
 */
inline int GetX(const unsigned int &id, const int &width) {
	return id % width;
}


/** \brief calculates a nodes y-coordinate from its id
 *  \param[in] id The nodes id
 *  \param[in] width the maps width
 *  \return The nodes y-coordinate
 */
inline int GetY(const unsigned int &id, const int &width) {
	return id / width;
}



/** \brief Function for expanding the graph
 *  \details calculates ids of neighbouring nodes
 *  for a given node and puts ids to NeighbourList
 *
 *  \param[in] id Id of note to be expanded
 *  \param[in] width Width of the map
 *  \param[in] height Height of the map
 *  \param[in] pNeighbourList Buffer to write ids of neighbours into
 *  \param[in] Pointer to the game map
 *
 *  return number of ids written into pNeighbourList
 */
int FillNeighbourList(const unsigned int id,
		int width,
		int height, unsigned int * pNeighbourList,
		const unsigned char * pMap)
{
	int nNeighbours = 0;

	int x = GetX(id,width);
	int y = GetY(id,width);

	if(((x + 1) < width) && (pMap[id + 1] == 1) )
	{
		pNeighbourList[nNeighbours] = id + 1;
		++nNeighbours;
	}

	if(((x - 1) >= 0 ) && (pMap[id - 1] == 1) )
	{
		pNeighbourList[nNeighbours] = id - 1;
		++nNeighbours;
	}

	if(((y + 1) < height) && (pMap[id + width] == 1))
	{
		pNeighbourList[nNeighbours] = id + width;
		++nNeighbours;
	}

	if(((y - 1) >= 0) && (pMap[id - width] == 1))
	{
		pNeighbourList[nNeighbours] = id - width;
		++nNeighbours;
	}

	return nNeighbours;
}


/** \brief Writes path (calculated by main-loop) to oOutBuffer starting
 *  from the goal position
 *
 *  \param[in] goal The target node
 *  \param[in] pOutBuffer Pointer to Buffer to write the path to (owned by caller)
 *  \param[in] pPredecessorIds Data to reconstruct path from index resembles a node ode
 *             field value resembles predecessors id of index
 */
void ReconstructPath(Node goal, int* pOutBuffer, unsigned int *pPredecessorIds)
{
	int buffer_pos = goal.cost;
	unsigned int current_id = goal.id;
	while(current_id != pPredecessorIds[current_id]) // start node is its own predecessor
	{
		pOutBuffer[buffer_pos-1] = current_id;
		current_id = pPredecessorIds[current_id];
		--buffer_pos;
	}
	return;
}


/** \brief uniform cost searchs main loop
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
			 int* pOutBuffer, const int nOutBufferSize)
{
	//std::lock_guard<std::mutex> ucs_guard(ucs_mutex);
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> qOpenList;
	bool * pClosedList = new bool[nMapWidth*nMapHeight]();

	unsigned int neighbour_list[4];

	unsigned int * pPredecessorIds = new unsigned int[nMapWidth*nMapHeight];
	unsigned int nStartId = GetId(nStartX, nStartY, nMapWidth);
	unsigned int nTargetId = GetId(nTargetX, nTargetY, nMapWidth);
	int nPathLength = -1;

	Node nodeCurrent(nStartId, 0);
	pPredecessorIds[nStartId] = nStartId;
	pClosedList[nStartId] = true;
	qOpenList.push(nodeCurrent);

	while(!qOpenList.empty())
	{
		nodeCurrent = qOpenList.top();
		qOpenList.pop();

		if (nodeCurrent.id == nTargetId)
		{
			nPathLength = nodeCurrent.cost;
			ReconstructPath(nodeCurrent, pOutBuffer, pPredecessorIds);
			break;
		}

		int nNeighbours = FillNeighbourList(nodeCurrent.id, nMapWidth, nMapHeight, neighbour_list, pMap);
		for (int i=0; i<nNeighbours; ++i)
			if (!pClosedList[neighbour_list[i]] && (nodeCurrent.cost < nOutBufferSize))
			{
				qOpenList.push(Node(neighbour_list[i], nodeCurrent.cost + 1));
				pClosedList[neighbour_list[i]] = true;
				pPredecessorIds[neighbour_list[i]] = nodeCurrent.id;
			}
	}

	delete[] pClosedList;
	delete[] pPredecessorIds;
	return nPathLength;
}



