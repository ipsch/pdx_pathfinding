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


	/** \brief Loads a map from a data file
	 *
	 *  \detail The map data is organized in its header data (width & height),
	 *  and its bulk data (information about single tiles)
	 *
	 *  This is the content of an example data-file :
	 *  \code
	 *  MapWidth=4
	 *  MapHeight=3
     *  MapData
     *  ....
     *  @.@.
     *  @...
	 *  \endcode
	 *  . represents a traversable tile
	 *  @ represents a blocked tile
	 *
	 *  \detail LoadMap(..) is a factory function:
	 *  memory is allocated for the bulk data.
	 *  Ownership is transferred to caller and
	 *  Memory has to be freed by caller.
	 *
	 *  \param[in] path Path to the date file containing map data
	 *  \param[out] width The width of the map
	 *  \param[out] heigth The height of the map
	 *  \param[out] data Pointer to the bulk data of the map (allocated by LoadMap(..))
	 *  \return Error code: 0 on success; 1 otherwise
	 */
	int LoadMap(const std::string &path, unsigned int &width, unsigned int &height, unsigned char *&data)
	{

		std::ifstream MapStream(path.c_str(),std::ifstream::in);

		if(!MapStream.good()) return -1;
		std::string line;
		std::string::size_type sz;

		do // handle map header data.
		   // Header is located before bulk data in *.map file
		   // bulk data is indicated by "pMap=" keyword.
		{
			getline(MapStream,line);
			if(line.find("MapWidth")!=std::string::npos)
				width = std::stoi(o_string::FindAndReplaceAll(line,"MapWidth=",""),&sz);
			if(line.find("MapHeight")!=std::string::npos)
				height = std::stoi(o_string::FindAndReplaceAll(line,"MapHeight=",""),&sz);

		} while( (!(line.find("MapData")!=std::string::npos))
				&& MapStream.good());

		if(data!=0L)
			delete[] data;
		unsigned int size = width*height;
		data = new unsigned char[size]();

		unsigned int iter=0;
		do // handle map bulk data
		{
			getline(MapStream,line);
			for(std::size_t collumn=0; collumn < line.size(); ++collumn)
			{

				switch (line[collumn])
				{
				case '.':
					data[iter]=1;
					break;
				case '@':
					data[iter]=0;
					break;
				default :
					data[iter]=1;
					break;
				}
				++iter;

			}
		} while(MapStream.good()); // END READING FROM FILE
		MapStream.close();
		return 0;
	}


	/** \brief Delegates map loading to int LoadMap(..)
	 *
	 *  \details returns a instance of map instead the errorcode
	 *  \param[in] path Path to the date file containing map data
	 *  \return Instance of the map loaded from file
	 */
	Map LoadMap(const std::string &path_to_file)
	{
		unsigned char *data = 0L;
		unsigned int width = 0;
		unsigned int height = 0;
		LoadMap(path_to_file, width, height, data);
		return Map(width, height, data);
	}


	/** \brief function to print map data to output
	 *
	 *  \param[in] The map to be printet
	 *  \output_stram[in] the output to print data to (default: std::cout)
	 */
	void PrintMap(const Map &map, std::ostream &output_stream)
	{
		for(unsigned int j=0; j<map.height_; ++j)
		{
			for(unsigned int i=0; i<map.width_; ++i)
				output_stream << (int) map(i,j);
			output_stream << "\n";
		}
		return;
	}


} // END NAMESPACE o_graph
