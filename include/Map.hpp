#pragma once






#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cmath>
#include <vector>
#include <iomanip>

#include <stdexcept>


#include "sNode.hpp"
#include "oString.hpp"
#include "metrics_helpers.hpp"

namespace o_graph
{


	class GraphNode
	{
	public :
		GraphNode() : id_(0), fvalue_(0), path_cost_(0), p_predecessor_(0L) { }
		//sNode(const unsigned int &id) : id_(id), fvalue_(0), path_cost_(0), p_predecessor_(0L)
		//{
		//	std::cout << "alloc: " << this << "\t " << id_ << std::endl;
		//}
		//~sNode()
		//{
		//	std::cout << "free: " << this << "\t " << id_ << std::endl;
		//}
		unsigned int id_;
		float fvalue_;
		int path_cost_;
		GraphNode *p_predecessor_;

		bool operator>(const GraphNode &rhs) const {
			return this->fvalue_>rhs.fvalue_;}
		bool operator<(const GraphNode &rhs) const {
			return this->fvalue_<rhs.fvalue_;}
		bool operator>=(const GraphNode &rhs) const {
			return this->fvalue_>=rhs.fvalue_;}
		bool operator<=(const GraphNode &rhs) const {
			return this->fvalue_<=rhs.fvalue_;}
		bool operator==(const GraphNode &rhs) const {
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



	template <class T, unsigned int N>
	class ListLIFO
	{
	public :
		ListLIFO() : iter_(0) { }
		void push(const T &rhs)
		{
			data_[iter_] = rhs;
			++iter_;
			return;
		}
		T pop()
		{
			--iter_;
			return data_[iter_];
		}
		bool is_empty() const
		{
			return (iter_<=0);
		}
	private :
		T data_[N];
		unsigned int iter_;


	};



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



	class Heuristic_2d_discrete
	{
	private :
		int x0_;
		int y0_;
	public :
		void Set(const coordinate &target)
		{
			x0_=target.x;
			y0_=target.y;
			return;
		}
		int operator()(const coordinate &position) const
		{
			return DiscreteMeasure(position.x-x0_, position.y-y0_);
		}
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

		ListLIFO<unsigned int, 3> neighbour_list_;

		void get_ij(const int &index, int &i, int &j) const;
		coordinate GetIJ(const int &index) const;
		int GetIndex(const int &i, const int &j) const {return i + j*width_;}
		void get_neighbours(const sNode * node);
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



