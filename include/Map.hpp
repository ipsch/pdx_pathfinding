/** \file
 * 		Map.hpp
 *
 *  \brief
 *  	Classes and functions to represent a 2d game map
 *
 *  \detail
 * 		Defines everything related to the representation of
 * 		a 2d game map and and infrastructure needed for
 * 		graph expansion done by AStar (or similar algorithm).
 *
 *  \version
 *  	2018-09-25 ipsch: semi-final (ToDo: cleanup+doc in Map.hpp)
 *
 *  \authors
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 */

#pragma once

#include <iostream>      // printing result of LoadMap to screen
#include <fstream>       // handling files
#include <sstream>       // translate built-in types to string
#include <string>        // strings for filenames & output to cout
#include <cmath>         // fabs(..) & abs(..)
#include <stdexcept>     // exception handling
#include "oString.hpp"   // find & replace for std::string
#include "ListLIFO.hpp"  // simple list to store map nodes temporary


namespace o_graph
{




	class MapNode
	{
	public :
		MapNode() : id_(0), fvalue_(0), path_cost_(0), p_predecessor_(0L) { }
		unsigned int id_;
		float fvalue_;
		int path_cost_;
		MapNode *p_predecessor_;

		// ToDo : 2918-09-25 ipsch: not sure if to move member definitions to cpp
		inline bool operator>(const MapNode &rhs) const {
			return this->fvalue_>rhs.fvalue_;}
		inline bool operator<(const MapNode &rhs) const {
			return this->fvalue_<rhs.fvalue_;}
		inline bool operator>=(const MapNode &rhs) const {
			return this->fvalue_>=rhs.fvalue_;}
		inline bool operator<=(const MapNode &rhs) const {
			return this->fvalue_<=rhs.fvalue_;}
		inline bool operator==(const MapNode &rhs) const {
			return this->fvalue_==rhs.fvalue_;}

		MapNode &operator=(const MapNode &rhs)
		{
			id_ = rhs.id_;
			fvalue_ = rhs.fvalue_;
			path_cost_ = rhs.path_cost_;
			p_predecessor_ = rhs.p_predecessor_;
			return *this;
		}
	};


	class Map
	{
	public :
		Map(const Map &map);
		explicit Map(const int &width, const int &height, const unsigned char *data);
		//void Load(const std::string &path_and_file_name);

		void set_heuristic(const int &i, const int &j);
		void set_heuristic(const int &id);
		double heuristic(const int &i, const int &j) const;
		double heuristic(const unsigned int &id) const;


		const int width_;
		const int height_;
		const unsigned char *data_;

		int i0_;
		int j0_;
		double max_manhattan_;




		o_data_structures::ListLIFO<unsigned int, 4> neighbour_list_;

		void get_ij(const int &index, int &i, int &j) const;

		int get_index(const int &i, const int &j) const {return i + j*width_;}
		void get_neighbours(const MapNode * node);
		unsigned char operator()(const int &i, const int &j) const
			{return data_[i + j*width_];}

		bool is_traversable(const int &i, const int &j) const
			{return (operator()(i,j)==Map::terrain_traversable_);}



	protected :

		//! /brief Struct to represent a single position (x,y) in 2d space
		typedef struct coordinate
		{
			coordinate(const int &i, const int &j) : x(i), y(j) { }
			int x;
			int y;
		} Coordinate;


		Coordinate GetIJ(const int &index) const;

		explicit Map();
		static const unsigned char terrain_traversable_;
		static const unsigned char terrain_blocked_;

		friend Map LoadMap(const std::string &path_to_file);
	};


	void PrintMap(const Map &map, std::ostream &output_stream = std::cout);

	Map LoadMap(const std::string &path_to_file);


}



