



#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>


#include <stdexcept>

#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <ostream>

#include "oString.hpp"


/**
 * \brief A struct to represent
 *
 *
 */
struct coordinate
{
	coordinate(const int &i, const int &j) : x(i), y(j) { }
	int x;
	int y;
};



/**
 * \brief A struct that consists of the most essential information about the game map
 *
 *
 *
 *
 *
 *
 */
struct MapMetaObject
{
	MapMetaObject() :
		nMapWidth_(0), nMapHeight_(0), pMap_(0L) { }
	MapMetaObject(const unsigned int &width, const unsigned int &height, unsigned char *data) :
		nMapWidth_(width), nMapHeight_(height), pMap_(data) { }
	int unsigned nMapWidth_;
	int unsigned nMapHeight_;
	unsigned char * pMap_;
};

MapMetaObject LoadMap(const std::string &path_to_file);

/**
 *  \brief A class to represent the game map
 *
 *
 *
 *
 */




class Map
{
public :
	explicit Map(const MapMetaObject &map) :
		width_(map.nMapWidth_), height_(map.nMapHeight_), data_(map.pMap_),
		i0_(0), j0_(0), max_manhattan_(.0)
	{ }
	explicit Map(const int &width, const int &height, const unsigned char *data) :
		width_(width), height_(height), data_(data),
		i0_(0), j0_(0), max_manhattan_(.0) { }
	//void Load(const std::string &path_and_file_name);

	void set_heuristic(const int &i, const int &j);
	void set_heuristic(const int &id);
	int i0_;
	int j0_;
	double max_manhattan_;
	const unsigned char *data_;
	const int width_;
	const int height_;

	coordinate GetIJ(const int &index) const;
	int GetIndex(const int &i, const int &j) {return i + j*width_;}
	void GetNeighbourList(std::vector<unsigned int> &node_list, const unsigned int &predecessor);
	unsigned char operator()(const int &i, const int &j) const
		{return data_[i + j*width_];}

	bool Traversable(const int &i, const int &j) const
		{return (operator()(i,j)==Map::terrain_traversable_);}
	friend MapMetaObject LoadMap(const std::string &path_to_file);

	double heuristic(const int &i, const int &j) const;
	double heuristic(const unsigned int &id) const;
private :
	explicit Map() : data_(0L), width_(0), height_(0),
			i0_(0), j0_(0), max_manhattan_(.0){ }
	static const unsigned char terrain_traversable_;
	static const unsigned char terrain_blocked_;
	// terrain encoding


};


void PrintMap(const Map &map, std::ostream &output_stream = std::cout);







#endif
