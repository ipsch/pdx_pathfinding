/*!
 * project: pdx_pathfinding
 *
 * \file main.cpp
 *
 * \brief contains main() to pdx_pathfinding project + documentation
 *
 * \version 0.1.0 (project creation)
 * \date 2018-06-19
 * \author ipsch (Ingmar Palle Schnell)
 *
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
 * \section section_history_main_cpp
 *          Development History:
 * \version 2018-06-19: 0.0.1 (project creation)
 * \version 2018-06-25: 0.2.0 (research done + literature collection)
 * \version 2018-07-20: 0.3.0 (component completion)
 * \version 2018-08-01: 0.5.0 (first executable code)
 * \version 2018-09-04: 0.8.0 (feature complete documentation missing)
 *
 * \author ipsch (Ingmar Palle Schnell)
 *
 * contact: i.p.schnell(at)gmail.com
 *
 *
 */




//============================================================================
// Project     : pdx_pathfinding
// Name        : main.cpp
// Author      : ipsch (Ingmar Palle Schnell)
// contact     : i.p.schnell(at)gmail.com
// created      : 2018-06-19
// Version     : 0.02 pre-working-state (2018-06-20)
//               0.90 feature complete (2018-09-04)
// Copyright   : CC:by-nc-sa
// Description : path finding problem from paradox interactive
// Reference   : https://paradox.kattis.com/problems/paradoxpath
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





#include <iostream>
#include <ostream>
#include <fstream>
#include <cmath>                       // used
#include <string>                      // used for filenames
#include <stdexcept>                   // used for exception handling
#include <vector>                      // list of filenames

#include "oString.hpp"                 // helper functions for string handling
#include "LoadMap.hpp"
#include "time_measure.hpp"
#include "Map.hpp"                     //
#include "AStar.hpp"
#include "NRRan.hpp"
#include "Class_AnalysisRuntime.hpp"



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

Ran RNG(19840827);

const int nBufferSize = 10000; // 1024;
int * pOutBuffer;

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







void RandomizeCoordinates(int &x, int &y, o_graph::Map &map)
{
	bool valid = false;
	while(!valid)
	{
		x = (int) (RNG.doub()*map.width_);
		y = (int) (RNG.doub()*map.height_);
		if(map.Traversable(x,y))
			valid = true;
	}
	return;
}


AnalysisRuntimeData Core(int nStartX, int nStartY, int nTargetX, int nTargetY,
		const o_graph::Map &map, std::string map_name)
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


AnalysisRuntime RunNTimes(unsigned int nRuns, o_graph::Map &map, std::string map_name)
{

	std::string file_analysis;
	file_analysis = FindAndReplaceAll(map_name,"/maps/","/benchmark/");
	file_analysis = FindAndReplaceAll(file_analysis,".map",".log");
	AnalysisRuntime analysis(map.width_, map.height_, file_analysis);

	for(unsigned int i=0; i<nRuns; ++i)
	{
		int StartX, StartY, TargetX, TargetY;
		RandomizeCoordinates(StartX, StartY, map);
		RandomizeCoordinates(TargetX, TargetY, map);

		std::cout << i << ":\t";
		AnalysisRuntimeData result = Core(StartX, StartY, TargetX, TargetY,
				map, map_name);

	    analysis.AddData(result);
	}

	return analysis;
}


void SingleMapOnce(const std::string &file_name, int xStart, int yStart, int xTarget, int yTarget)
{
	o_graph::MapMetaObject GameMap = o_graph::LoadMap(file_name);
	o_graph::Map map(GameMap);

	std::cout << "map name: " << file_name << "\n";
	std::cout << "size: ";
	std::cout << map.width_ << "x";
	std::cout << map.height_ << " @ ";
	std::cout << "pMap: " << map.data_ << "\n";

	AnalysisRuntimeData result = Core(xStart, yStart, xTarget, yTarget,
			map, file_name);

	//PrintTestResultToFile(); // print header
	PrintAnalysis(xStart, yStart, xTarget, yTarget,
			result.path_length_, result.nodes_expanded_,
			result.wall_time_, result.cpu_time_,
			pOutBuffer); // print test result

	return;
}


void SingleMapNTimes(const std::string &file_name, int runs_per_map = 1)
{
	o_graph::MapMetaObject GameMap = o_graph::LoadMap(file_name);
	o_graph::Map map(GameMap);

	std::cout << "map name: " << file_name << "\n";
	std::cout << "size: ";
	std::cout << map.width_ << "x";
	std::cout << map.height_ << " @ ";
	std::cout << "pMap: " << map.data_ << "\n";

	AnalysisRuntime analysis = RunNTimes(runs_per_map, map, file_name);
	analysis.Evaluate();
	return;
}


void MultiMapsNTimes(int runs_per_map = 1)
{
	for(auto iter_map=MAPS.begin(); iter_map!=MAPS.end(); ++iter_map)
		SingleMapNTimes(*iter_map, runs_per_map);
	return;
}



struct setting
{
	setting(int x0, int y0, int x1, int y1, std::string file_name, int runs, int run_opt) :
			x0(x0), y0(y0), x1(x1), y1(y1), file_name(file_name), runs(runs), run_opt(run_opt) { }

	int x0;
	int y0;
	int x1;
	int y1;
	std::string file_name;
	int runs;
	int run_opt;
};


int main(void)
{
	pOutBuffer = new int[nBufferSize];

	setting setting(391,5,418,23, "./maps/maze512-1-0.map", 10000, 2);

	//setting setting(0,0,1,2, "./maps/pdx_example.map", 1, 0);

    try{
    	switch(setting.run_opt)
    	{
    	case 0 :
    		SingleMapOnce(setting.file_name, setting.x0,setting.y0,setting.x1,setting.y1);
    		break;
    	case 1 :
    		SingleMapNTimes(setting.file_name, setting.runs);
    		break;
    	case 2:
    		MultiMapsNTimes(setting.runs);
			break;
    	}
	}
    catch(const std::exception& e)
    {
		std::cout << e.what() << '\n';
	}


    delete[] pOutBuffer;
    std::cout << "done" << std::endl;
	return 0;
}


