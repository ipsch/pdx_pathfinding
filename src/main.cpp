/** \file
 * 		main.cpp
 *
 *  \brief
 * 		contains main() to pdx_pathfinding project + projects documentation main page
 *
 *  \detail
 *  	path finding problem from paradox interactive
 *  	project: pdx_pathfinding
 *
 *  \version
 *  	2018-06-19 ipsch: 0.1.0 (project creation)
 *
 *  \author
 *  	ipsch (Ingmar Schnell)
 *  	contact: i.p.schnell(at)gmail.com
 *
 *	\sa References:
 *		- Paradoxs pathfinding test on kattis https://paradox.kattis.com/problems/paradoxpath
 *
 *
 * \mainpage Project overview
 *
 * \tableofcontents
 *
 * \section section_about About this Project:
 *   This project was created as part of a job application at Paradox Studios (Sweden).
 *   The task was to implement a path-finding algorithm in C++ that finds and returns
 *   a shortest path between two points in a 2-dimensional rectangular grid.
 *   In Order to repurpose this code after the application the project is divided
 *   in two parts - namely the core part that includes everything needed to solve
 *   the pure path finding problem and secondly an auxiliary part that was used
 *   to test and benchmark the path finding algorithm.
 *
 * \section Project components
 *
 * \subsection section_core Core part
 *
 * \subsection section_auxiliary Auxiliary part
 *
 *
 *
 * Constraints
 * You may safely assume following relations are always true:
 *   (1<=nMapWidth)
 *   (1<=nMapHeight)
 *   (0<=nStartX)
 *	 (nTargetX<nMapWidth)
 *   (0<=nStartY), (nTargetY<nMapHeight)
 *   Both Start and Target are empty locations,
 *   (nOutBufferSize>=0)
 *
 *
 * \section project_dev_history_
 *          Development History:
 * \version 2018-06-19: 0.0.1 (project creation)
 * \version 2018-06-25: 0.2.0 (research done + literature collection)
 * \version 2018-07-20: 0.3.0 (component completion)
 * \version 2018-08-01: 0.5.0 (first executable code)
 * \version 2018-09-04: 0.8.0 (feature complete documentation missing)
 *
 *
 * Copyright   : CC:by-nc-sa
 *
 */


//============================================================================
//
// nStartX and nStartY are the 0 based coordinates of the start position.
// nTargetX and nTargetY are the 0-based coordinates of the target position.
// pMap describes a grid of width nMapWidth and height nMapHeight.
//   The grid is given in row-major order, each row is given in order of
//   increasing x-coordinate, and the rows are given in order of increasing
//   y-coordinate. Traversable locations of the grid are indicated by 1,
//   and impassable locations are indicated by 0.
//   Locations are considered to be adjacent horizontally and
//   vertically but not diagonally.
// pOutBuffer is where the positions visited in the found path are stored,
//   excluding the starting position but including the final position.
//   Entries in pOutBuffer are indices into pMap. If there is more than one
//   shortest path from Start to Target, any one of them will be accepted.
// nOutBufferSize is the maximum number of entries that can be
//   written to pOutBuffer.
// The function must return the length of the shortest path between Start and
//   Target, or -1 if no such path exists.
// If the shortest path is longer than nOutBufferSize, the calling function
//   might either give up or choose to call FindPath again with a larger output buffer.






#include <iostream>					  // output to std::cout
#include <string>                     // used for filenames
#include <stdexcept>                  // used for exception handling
#include <vector>                     // list of filenames

#include "oString.hpp"                // helper functions for string handling
#include "time_measure.hpp"           // functions to measure wall- / cpu-time
#include "Map.hpp"                    // representation of game map
#include "AStar.hpp"                  // Path finding algorithm
#include "NRRan.hpp"                  // Numerical Recipes random number generator
#include "PathfinderDiagnostics.hpp"  // Tool to evaluate pathfinder performance


std::vector<std::string> MAPS
{
	"./maps/maze512-1-0.map",
	"./maps/maze512-1-1.map",
	"./maps/maze512-1-2.map",
	"./maps/maze512-1-3.map",
	"./maps/maze512-1-4.map",
	"./maps/maze512-1-5.map",
	"./maps/maze512-1-6.map",
	"./maps/maze512-1-7.map",
	"./maps/maze512-1-8.map",
	"./maps/maze512-1-9.map",
	"./maps/maze512-2-0.map",
	"./maps/maze512-2-1.map",
	"./maps/maze512-2-2.map",
	"./maps/maze512-2-3.map",
	"./maps/maze512-2-4.map",
	"./maps/maze512-2-5.map",
	"./maps/maze512-2-6.map",
	"./maps/maze512-2-7.map",
	"./maps/maze512-2-8.map",
	"./maps/maze512-2-9.map",
	"./maps/maze512-4-0.map",
	"./maps/maze512-4-1.map",
	"./maps/maze512-4-2.map",
	"./maps/maze512-4-3.map",
	"./maps/maze512-4-4.map",
	"./maps/maze512-4-5.map",
	"./maps/maze512-4-6.map",
	"./maps/maze512-4-7.map",
	"./maps/maze512-4-8.map",
	"./maps/maze512-4-9.map",
	"./maps/maze512-8-0.map",
	"./maps/maze512-8-1.map",
	"./maps/maze512-8-2.map",
	"./maps/maze512-8-3.map",
	"./maps/maze512-8-4.map",
	"./maps/maze512-8-5.map",
	"./maps/maze512-8-6.map",
	"./maps/maze512-8-7.map",
	"./maps/maze512-8-8.map",
	"./maps/maze512-8-9.map",
	"./maps/maze512-16-0.map",
	"./maps/maze512-16-1.map",
	"./maps/maze512-16-2.map",
	"./maps/maze512-16-3.map",
	"./maps/maze512-16-4.map",
	"./maps/maze512-16-5.map",
	"./maps/maze512-16-6.map",
	"./maps/maze512-16-7.map",
	"./maps/maze512-16-8.map",
	"./maps/maze512-16-9.map",
	"./maps/maze512-32-0.map",
	"./maps/maze512-32-1.map",
	"./maps/maze512-32-2.map",
	"./maps/maze512-32-3.map",
	"./maps/maze512-32-4.map",
	"./maps/maze512-32-5.map",
	"./maps/maze512-32-6.map",
	"./maps/maze512-32-7.map",
	"./maps/maze512-32-8.map",
	"./maps/maze512-32-9.map"
};

 nr_rngs::Ran RNG(19840827);



//    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
//    int pOutBuffer[12];
//    FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
//    For this input FindPath must return 3
// and the first three positions of pOutBuffer must be populated with {1, 5, 9}.

//unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
//int pOutBuffer[7];
//FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

//For this input FindPath must return -1



// Additional considerations
// Consider performance, memory usage and assume that your code may be called from a multi-threaded environment.



struct setting
{
	setting(int x0, int y0, int x1, int y1, std::string file_name, int runs, int run_opt,
			bool iterate, bool random) :
			x0(x0), y0(y0), x1(x1), y1(y1), file_name(file_name), runs_per_map(runs), run_opt(run_opt),
			iterate_maps(iterate), randomize_xy(random) { }

	int x0;
	int y0;
	int x1;
	int y1;
	std::string file_name;
	int runs_per_map;
	int run_opt;
	bool iterate_maps;
	bool randomize_xy;
};



void RandomizeCoordinates(int &x, int &y, o_graph::Map &map)
{
	bool valid = false;
	while(!valid)
	{
		x = (int) (RNG.doub()*map.width_);
		y = (int) (RNG.doub()*map.height_);
		if(map.is_traversable(x,y))
			valid = true;
	}
	return;
}


o_graph::Map OpenMap(std::string file_name)
{
	o_graph::Map map = o_graph::LoadMap(file_name);

	std::cout << "map name: " << file_name << "\n";
	std::cout << "size: ";
	std::cout << map.width_ << "x";
	std::cout << map.height_ << " @ ";
	std::cout << "pMap: " << map.data_ << "\n";

	return map;
}


AnalysisRuntimeData Core(int nStartX, int nStartY, int nTargetX, int nTargetY,
		const o_graph::Map &map, std::string map_name, const int &nBufferSize, int * pOutBuffer )
{
	int path_length;
	unsigned int nodes_expanded;

	// Measurement section
	double wall0 = get_wall_time();
	double cpu0  = get_cpu_time();
	path_length = FindPath(nStartX, nStartY, nTargetX, nTargetY, map.data_,
			map.width_, map.height_,
			pOutBuffer, nBufferSize,
			nodes_expanded);
	double wall1 = get_wall_time();
	double cpu1  = get_cpu_time();
	// END Measurement section


	AnalysisRuntimeData result(
			abs(nTargetX-nStartX) + abs(nTargetY-nStartY),  // manhattan-distance
			path_length,                                    // path length
			nodes_expanded,                                 // nodes expanded
			wall1 - wall0,                                  // wall time
			cpu1 - cpu0);                                   // cpu time

	PrintAnalysis(nStartX, nStartY, nTargetX, nTargetY,
			result, pOutBuffer);

	return result;
}


void IterateRuns(setting &s, o_graph::Map &map, const int &nBufferSize, int * pOutBuffer)
{

	std::string file_analysis;
	file_analysis = o_string::FindAndReplaceAll(s.file_name,"/maps/","/benchmark/");
	file_analysis = o_string::FindAndReplaceAll(file_analysis,".map",".log");
	AnalysisRuntime analysis(map.width_, map.height_, file_analysis);

	for(unsigned int i=0; i<s.runs_per_map; ++i)
	{
		if(s.randomize_xy)
		{
			RandomizeCoordinates(s.x0, s.y0, map);
			RandomizeCoordinates(s.x1, s.y1, map);
		}

		std::cout << i << ":\t";
		AnalysisRuntimeData result = Core(s.x0, s.y0, s.x1, s.y1,
				map, s.file_name, nBufferSize, pOutBuffer);

	    analysis.AddData(result);
	}
	analysis.CalcMean();
	analysis.Evaluate();
	return;
}


void IterateMaps(setting s, const int &nBufferSize, int * pOutBuffer)
{
	if (s.iterate_maps)
	{
		for(auto iter_map=MAPS.begin(); iter_map!=MAPS.end(); ++iter_map)
		{
			o_graph::Map map = OpenMap(*iter_map);
			IterateRuns(s, map, nBufferSize, pOutBuffer);
			delete[] map.data_;
		}
	}
	else
	{
		o_graph::Map map = OpenMap(s.file_name);
		IterateRuns(s, map, nBufferSize, pOutBuffer);
		delete[] map.data_;
	}
	return;
}






int main(void)
{
	AnalysisRuntime::printable_buffer = true;
	AnalysisRuntime::disabled_analysis = true;
	const int nBufferSize = 31; // 1024;
	int * pOutBuffer;
	pOutBuffer = new int[nBufferSize];

	//setting setting(391,5,418,23, "./maps/maze512-1-0.map", 10000, 2,true, true);

	//setting setting(475,123,455,189, "./maps/maze512-1-0.map", 10000, 2,false, false);

	//setting setting(0,0,1,2, "./maps/pdx_example.map", 1, 0, false, false);


	setting setting(1,0,15,15, "./maps/empty_16x16.map", 1, 0, false, false);


    try{
    	IterateMaps(setting, nBufferSize, pOutBuffer);
	}
    catch(const std::exception& e)
    {
		std::cout << e.what() << '\n';
	}


    delete[] pOutBuffer;
    std::cout << "done" << std::endl;
	return 0;
}


