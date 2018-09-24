#include "Map.hpp"


namespace o_graph
{


	const unsigned char Map::terrain_traversable_ = 1;
	const unsigned char Map::terrain_blocked_ = 0;


	Map::Map() : data_(0L), width_(0), height_(0),
			i0_(0), j0_(0), max_manhattan_(.0)
	{
		// noting to do here
	}


	Map::Map(const MapMetaObject &map) :
			width_(map.nMapWidth_), height_(map.nMapHeight_), data_(map.pMap_),
			i0_(0), j0_(0), max_manhattan_(.0)
	{
		// noting to do here
	}


	Map::Map(const int &width, const int &height, const unsigned char *data) :
		width_(width), height_(height), data_(data),
		i0_(0), j0_(0), max_manhattan_(.0)
	{
		// noting to do here
	}






	coordinate Map::GetIJ(const int &index) const
	{
		int j = index / width_;
		int i = index - j*width_;
		return coordinate(i,j);
	}


	void Map::get_neighbours(
			std::vector<unsigned int> &node_list,
			const sNode * node)
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


	// ToDO 2018-09-11 ipsch: Rework GetNeighbourList(..)
	// no need to calculate position first (map knows width & heigth)
	void Map::GetNeighbourList(std::vector<unsigned int> &node_list, const unsigned int &predecessor)
	{
		coordinate pos = GetIJ(predecessor);

		if( (pos.x+1<width_) && (operator()(pos.x+1,pos.y)==terrain_traversable_))
			node_list.push_back(GetIndex(pos.x+1,pos.y));
		if( (pos.x-1>=0) && (operator()(pos.x-1,pos.y)==terrain_traversable_))
			node_list.push_back(GetIndex(pos.x-1,pos.y));
		if( (pos.y+1<height_) && (operator()(pos.x,pos.y+1)==terrain_traversable_) )
			node_list.push_back(GetIndex(pos.x,pos.y+1));
		if( (pos.y-1>=0) && (operator()(pos.x,pos.y-1)==terrain_traversable_))
			node_list.push_back(GetIndex(pos.x,pos.y-1));
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
		return heuristic(vec.x, vec.y);
	}

	/*
	void Map::Load(const std::string &path_and_file_name)
	{
		std::string line;
		std::string::size_type sz;
		std::ifstream map_data_stream(path_and_file_name.c_str(),std::ifstream::in);

		if(!map_data_stream.good())
			throw("file couldn't be opened");
		if(data_!=0L)
			delete[] data_;

		do // handle map header data.
		   // Header is located before bulk data in *.map file
		   // bulk data is indicated by "pMap=" keyword.
		{
			getline(map_data_stream,line);
			if(line.find("MapWidth")!=std::string::npos)
				width_ = std::stoi(FindAndReplaceAll(line,"MapWidth=",""),&sz);
			if(line.find("MapHeight")!=std::string::npos)
				height_ = std::stoi(FindAndReplaceAll(line,"MapHeight=",""),&sz);



		} while( (!(line.find("MapData")!=std::string::npos))
				&& map_data_stream.good());

		unsigned int size = width_*height_;
		data_ = new unsigned char[size]();


		unsigned int iter=0;
		do // handle map bulk data
		{
			getline(map_data_stream,line);
			for(std::size_t column=0; column < line.size(); ++column)
			{
				switch (line[column])
				{
				case terrain_traversable_:
					data_[iter]=1;
					break;
				case terrain_blocked_:
					data_[iter]=0;
					break;
				default :
					data_[iter]=terrain_traversable_;
					break;
				}
				++iter;

			}
		} while(map_data_stream.good()); // END READING FROM FILE


		map_data_stream.close();
		return;
	}
	*/




	/**
	 *  \brief A class to represent the game map
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
				width = std::stoi(FindAndReplaceAll(line,"MapWidth=",""),&sz);
			if(line.find("MapHeight")!=std::string::npos)
				height = std::stoi(FindAndReplaceAll(line,"MapHeight=",""),&sz);

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




	MapMetaObject LoadMap(const std::string &path_to_file)
	{

		unsigned char *data;
		unsigned int width;
		unsigned int height;

		std::ifstream MapStream(path_to_file.c_str(),std::ifstream::in);

		if(!MapStream.good())
			throw std::runtime_error("file coudn't be opened");


		std::string line;
		std::string::size_type sz;

		do // handle map header data.
		   // Header is located before bulk data in *.map file
		   // bulk data is indicated by "pMap=" keyword.
		{
			getline(MapStream,line);
			if(line.find("MapWidth")!=std::string::npos)
				width = std::stoi(FindAndReplaceAll(line,"MapWidth=",""),&sz);
			if(line.find("MapHeight")!=std::string::npos)
				height = std::stoi(FindAndReplaceAll(line,"MapHeight=",""),&sz);



		} while( (!(line.find("MapData")!=std::string::npos))
				&& MapStream.good());


		data = new unsigned char [width*height+2];


		unsigned int iter=0;
		do // handle map bulk data
		{
			getline(MapStream,line);
			for(std::size_t collumn=0; collumn < line.size(); ++collumn)
			{

				switch (line[collumn])
				{
				case '.':
					data[iter]=Map::terrain_traversable_;
					break;
				case '@':
					data[iter]=Map::terrain_blocked_;
					break;
				default :
					data[iter]=Map::terrain_traversable_;
					break;
				}
				++iter;

			}


		} while(MapStream.good()); // END READING FROM FILE





		MapStream.close();

		MapMetaObject temporary_meta_map;
		temporary_meta_map.nMapHeight_ = height;
		temporary_meta_map.nMapWidth_ = width;
		temporary_meta_map.pMap_ = data;


		return temporary_meta_map;
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

}



