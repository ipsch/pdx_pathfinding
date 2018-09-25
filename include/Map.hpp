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






#include <iostream>                    //
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include "oString.hpp"  //




namespace o_graph
{

	//! /brief Struct to represent a single position (x,y) in 2d space
	struct coordinate
	{
		coordinate(const int &i, const int &j) : x(i), y(j) { }
		int x;
		int y;
	};


	class GraphNode
	{
	public :
		GraphNode() : id_(0), fvalue_(0), path_cost_(0), p_predecessor_(0L) { }
		unsigned int id_;
		float fvalue_;
		int path_cost_;
		GraphNode *p_predecessor_;

		// ToDo : 2918-09-25 ipsch: not sure if to move member definitions to cpp
		inline bool operator>(const GraphNode &rhs) const {
			return this->fvalue_>rhs.fvalue_;}
		inline bool operator<(const GraphNode &rhs) const {
			return this->fvalue_<rhs.fvalue_;}
		inline bool operator>=(const GraphNode &rhs) const {
			return this->fvalue_>=rhs.fvalue_;}
		inline bool operator<=(const GraphNode &rhs) const {
			return this->fvalue_<=rhs.fvalue_;}
		inline bool operator==(const GraphNode &rhs) const {
			return this->fvalue_==rhs.fvalue_;}

		GraphNode &operator=(const GraphNode &rhs)
		{
			id_ = rhs.id_;
			fvalue_ = rhs.fvalue_;
			path_cost_ = rhs.path_cost_;
			p_predecessor_ = rhs.p_predecessor_;
			return *this;
		}
	};



	/** \brief simple but fast class to maintain a List of items
	 *  \details ListLIFO (last out first out) can store N items of type T.
	 *    access via members push and pop.
	 *    Provides no guards against incorrect reading/writing! <br>
	 *    2018-09-25 ipsch: intended to store neighbouring nodes
	 *    in graph expansion
	 *  \sa Map::get_neighbours(..)
	 */
	template <class T, unsigned int N>
	class ListLIFO
	{
	public :
		ListLIFO();
		bool is_empty() const;         // checks if empty
		void push(const T &rhs);       // writing
		T pop();                       // read + removal
	private :
		T data_[N];				       //!< internal item list
		unsigned int iter_;            //!< number of items stored
	};







	/** \brief A struct that consists of the most essential information about the game map
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







	class Map
	{
	public :
		explicit Map(const MapMetaObject &map);
		explicit Map(const int &width, const int &height, const unsigned char *data);
		//void Load(const std::string &path_and_file_name);

		void set_heuristic(const int &i, const int &j);
		void set_heuristic(const int &id);
		double heuristic(const int &i, const int &j) const;
		double heuristic(const unsigned int &id) const;

		int i0_;
		int j0_;
		double max_manhattan_;
		const unsigned char *data_;
		const int width_;
		const int height_;

		ListLIFO<unsigned int, 4> neighbour_list_;

		void get_ij(const int &index, int &i, int &j) const;
		coordinate GetIJ(const int &index) const;
		int GetIndex(const int &i, const int &j) const {return i + j*width_;}
		void get_neighbours(const GraphNode * node);
		unsigned char operator()(const int &i, const int &j) const
			{return data_[i + j*width_];}

		bool Traversable(const int &i, const int &j) const
			{return (operator()(i,j)==Map::terrain_traversable_);}
		friend MapMetaObject LoadMap(const std::string &path_to_file);



	protected :
		explicit Map();
		static const unsigned char terrain_traversable_;
		static const unsigned char terrain_blocked_;


	};


	void PrintMap(const Map &map, std::ostream &output_stream = std::cout);

	MapMetaObject LoadMap(const std::string &path_to_file);


}



