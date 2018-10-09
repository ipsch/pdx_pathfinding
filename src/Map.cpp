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
 *  	2018-09-25 ipsch: semi-final (ToDo: cleanup+doc in Map.cpp)
 *
 *  \authors
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */


#include "Map.hpp"  // accompanying header

namespace o_graph
{

	const unsigned char Map::terrain_traversable_ = 1;
	const unsigned char Map::terrain_blocked_ = 0;


	Map::Map() : width_(0), height_(0), data_(0L),
			i0_(0), j0_(0), max_manhattan_(.0)
	{
		// noting to do here
	}


	Map::Map(const Map &map) :
			width_(map.width_), height_(map.height_), data_(map.data_),
			i0_(0), j0_(0), max_manhattan_(.0)
	{
		// noting to do here
	}


	Map::Map(const int &width, const int &height, const unsigned char *data) :
		height_(height), width_(width), data_(data),
		i0_(0), j0_(0), max_manhattan_(.0)
	{
		// noting to do here
	}



	inline void Map::get_ij(const int &index, int &i, int &j) const
	{
		j = index / width_;
		i = index - j*width_;
		return;
	}


	Map::Coordinate Map::GetIJ(const int &index) const
	{
		int j = index / width_;
		int i = index - j*width_;
		return coordinate(i,j);
	}


	void Map::get_neighbours(const MapNode * node)
	{

		unsigned int prev_id = 0 - 1;
		if ( node->p_predecessor_ != 0L )
			prev_id = node->p_predecessor_->id_;

		unsigned int id = node->id_;
		coordinate pos = GetIJ(node->id_);

		if( (pos.x+1<width_) && (data_[id+1]==terrain_traversable_)
				&& ( ( id + 1 ) != prev_id ) )
			neighbour_list_.push(id + 1);

		if( (pos.x-1>=0) && (data_[id-1]==terrain_traversable_)
				&& ( ( id - 1 ) != prev_id ) )
			neighbour_list_.push(id - 1);

		if( (pos.y+1<height_) && (data_[id+width_]==terrain_traversable_)
				&& ( ( id + width_ ) != prev_id ) )
			neighbour_list_.push(id+width_);

		if( (pos.y-1>=0) && (data_[id-width_]==terrain_traversable_)
				&& ( ( id - width_ ) != prev_id ) )
			neighbour_list_.push(id-width_);

		return;
	}




	void Map::set_heuristic(const int &id)
	{
		coordinate vec = GetIJ(id);
		return set_heuristic(vec.x, vec.y);

	}

	void Map::set_heuristic(const int &i, const int &j)
	{
		i0_ = i;
		j0_ = j;
		max_manhattan_ = (double) (height_ + width_ - 2);
		return;
	}

	double Map::heuristic(const int &i, const int &j) const
	{
		double dx = (double) (i-i0_);
		double dy = (double) (j-j0_);
		double manhattan = fabs(dx) + fabs(dy);
		return manhattan + (manhattan/max_manhattan_);
	}


	double Map::heuristic(const unsigned int &id) const
	{
		coordinate vec = GetIJ(id);
		double dx = (double) (vec.x-i0_);
		double dy = (double) (vec.y-j0_);
		double manhattan = fabs(dx) + fabs(dy);
		return manhattan + (manhattan/max_manhattan_);
	}



	/** \brief A class to represent the game map
	 *
	 *
	 *
	 *
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


	Map LoadMap(const std::string &path_to_file)
	{
		unsigned char *data = 0L;
		unsigned int width = 0;
		unsigned int height = 0;
		LoadMap(path_to_file, width, height, data);
		return Map(width, height, data);
	}



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
