/** \file
 * 		Map.cpp
 *
 *  \brief
 *  	Classes and functions to represent a 2d game map
 *
 *  \detail
 *  	Contains definitions to
 *  	accompanying header file Map.hpp
 *
 *  \version
 *  	2018-10-10 ipsch: 1.0.0 final
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */


#include "Map.hpp"  // accompanying header

namespace o_graph
{

	const unsigned char Map::terrain_traversable_ = 1;
	const unsigned char Map::terrain_blocked_ = 0;


	//! \brief unaccessible constructor (made private)
	Map::Map() : width_(0), height_(0), data_(0L),
			x0_(0), y0_(0), max_manhattan_(.0)
	{
		// noting to do here
	}


	//! \brief Copy constructor (designed to work with LoadMap(..))
	Map::Map(const Map &map) :
			width_(map.width_), height_(map.height_), data_(map.data_),
			x0_(0), y0_(0), max_manhattan_(height_ + width_ - 2)
	{
		// noting to do here
	}


	//! \brief Constructor (designed to work with Paradoxs interface)
	Map::Map(const int &width, const int &height, const unsigned char *data) :
		height_(height), width_(width), data_(data),
		x0_(0), y0_(0), max_manhattan_(height_ + width_ - 2)
	{
		// noting to do here
	}


	/** \brief Calculates ids of the neighbours of a node
	 *
	 *  \detail
	 *  - The ids are pused into Map::neighbour_list_
	 *  - The backward node (nodes predecessor) isn't
	 *    pushed to the list
	 *
	 *  \param[in] node Pointer to node that is to be expanded
	 *  by the pathfinder class
	 */
	void Map::fill_neighbour_list(const MapNode * node)
	{

		unsigned int prev_id = 0 - 1;
		if ( node->p_predecessor_ != 0L )
			prev_id = node->p_predecessor_->id_;

		unsigned int id = node->id_;
		int x = get_x(id);
		int y = get_y(id);

		if( ((x+1) < width_) && (data_[id+1]==terrain_traversable_)
				&& ( ( id + 1 ) != prev_id ) )
			neighbour_list_.push(id + 1);

		if( ((x-1) >= 0) && (data_[id-1]==terrain_traversable_)
				&& ( ( id - 1 ) != prev_id ) )
			neighbour_list_.push(id - 1);

		if( ((y+1) < height_) && (data_[id+width_]==terrain_traversable_)
				&& ( ( id + width_ ) != prev_id ) )
			neighbour_list_.push(id+width_);

		if( ((y-1) >= 0) && (data_[id-width_]==terrain_traversable_)
				&& ( ( id - width_ ) != prev_id ) )
			neighbour_list_.push(id-width_);

		return;
	}


	/** \brief Sets the reference point for the heuristic
	 *
	 *  \detail the reference point is the target of the search
	 *  done by the pathfinder class
	 *
	 *  \param[in] x0 The targets x-coordinate
	 *  \param[in] y0 The targets y-coordinate
	 */
	void Map::set_heuristic(const int &x0, const int &y0)
	{
		x0_ = x0;
		y0_ = y0;
		return;
	}


	/** \brief Calculates the heuristic (h-value)
	 *  \detail The heuristic is calculated in reference to
	 *  the target node that was early set (set_heuristic(..))
	 *  \param[in] id The id of the node to calculate the heuristic for
	 *  \return The value of the heuristic
	 */
	double Map::get_heuristic(const unsigned int &id) const
	{
		int dx = get_x(id) - x0_;
		int dy = get_y(id) - y0_;
		double manhattan = (double) (abs(dx) + abs(dy));
		return manhattan*(1. + 1./max_manhattan_);
	}


} // END NAMESPACE o_graph
