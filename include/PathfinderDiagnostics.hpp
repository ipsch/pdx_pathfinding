/** \file
 * 		PathfinderDiagnostics.hpp
 *
 * 	\brief
 * 		Tools to evaluate a pathfinding algorithms performance
 *
 *  \details
 *  	Classes provided by PathfinderDiagnostics.hpp are
 *  	designed to be used in project pdx_pathfinding project.
 *  	Class AnalysisRuntimeData can help to determine how a path finding
 *  	algorithm performs if confronted with a labyrinth like map
 *  	in contrast to a map with very few obstacles.
 *
 *
 * 	\version
 * 		2018-10-11 ipsch: 1.0.0 final
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 */

#pragma once
#ifndef PATHFINDER_DIAGNOSTICS_HPP_
#define PATHFINDER_DIAGNOSTICS_HPP_

#include <vector>      // temporary storage for large amounts of data
#include <iostream>    // output to std::cout
#include <iomanip>     // output format (std::scientific, std::width etc.)
#include <fstream>     // output to files
#include <ostream>     // standard output
#include <string>      // handling file names
#include "oTable.hpp"  // class to represent data + compatibility to gnuplot
#include "oMath.hpp"   // Mathematical helper functions




struct AnalysisRuntimeData;

void PrintAnalysis(const int &xi, const int &yi, const int &xf, const int &yf,
		const AnalysisRuntimeData &ana, const int *pOutBuffer);

void PrintAnalysis(const int &xi, const int &yi, const int &xf, const int &yf,
		const int &path_length, const unsigned int &nodes_expanded,
		const double &wall_time, const double &cpu_time, const int *pOutBuffer);


/** \brief Data class for measured quantities
 *  \detail AnalysisRuntimeData is designed
 *  to be used alongside AnalysisRuntime.
 *  It represents a single Data point of measured data.
 *  A set of Data points can be evaluated by AnalysisRuntime
 */
struct AnalysisRuntimeData
{
	//! \brief Constructor
	AnalysisRuntimeData(const unsigned int &m, const unsigned int &p, const unsigned int &n, const double &wall, const double &cpu) :
		manhattan_distance_(m), path_length_(p), nodes_expanded_(n), wall_time_(wall), cpu_time_(cpu)
	{ }

	//! \brief Copy constructor
	AnalysisRuntimeData(const AnalysisRuntimeData &that) :
		manhattan_distance_(that.manhattan_distance_),
		path_length_(that.path_length_),
		nodes_expanded_(that.nodes_expanded_),
		wall_time_(that.wall_time_),
		cpu_time_(that.cpu_time_)
	{ }

	int manhattan_distance_;       //< shortest path possible (if there were no obstacles)
	int path_length_;              //< shortest path (found by path finding algorithm around obstacles)
	unsigned int nodes_expanded_;  //< numbers of nodes that were expanded to reach goal (or abort)
	double wall_time_;             //< wall time used to reach goal (or abort)
	double cpu_time_;              //< cpu time used to reach goal (or abort)
};



/** \brief class to evaluate collected data
 *
 *  \details
 *  	AnalysisRuntime can help to determine how a path finding
 *  	algorithm performs if confronted with a labyrinth like map
 *  	in contrast to a map with very few obstacles.
 *
 *		It assumes that on a single map a number of paths had to be found
 *		between random start and target positions.
 *		From this set of data it calculates a heatmap (x,y,z(x,y)), where:
 *  	- x = shortest distance between start and target (if there were no obstacles)
 *  	- y = actual path length (with obstacles)
 *  	- z = average runtime to solve pathfinding problem
 *
 *  	In the process of algorithm optimization you can use the heat map
 *  	to evaluate your optimization steps; for example:
 *  	- change in run time for long paths with only minor obstructions
 *  	  is an indicator for the efficiency of your expand node function
 *  	- change in run time for long paths with major obstructions
 *  	  is an indicator for the efficiency of open/closed lists find functions
 *  	- change in run time for short paths can indicate problems with
 *  	  too complex initialization or data structures
 *
 *  \note
 *  	- Data is so be collected the main program
 *        in form of a std::vector<AnalysisRuntimeData>.
 */
class AnalysisRuntime
{
public :
	explicit AnalysisRuntime(const int &nMapWidth,
			const int &nMapHeight,
			const std::string &output_file_name);
	~AnalysisRuntime();
	void AddData(const AnalysisRuntimeData &data);
	void AddData(const unsigned int &manhattan_distance,
			const unsigned int &path_length,
			const unsigned int &nodes_expanded,
			const double &wall_time,
			const double &cpu_time);
	void Evaluate();
	void CalcMean();
private :
	AnalysisRuntime();
	typedef std::vector<AnalysisRuntimeData> myDataType;

	void (*CallbackOutput_)(const o_math::oTable<double> &, std::ostream &) =
			&o_math::oTablePrint;   //< Callback for printing oTables
	int max_manhattan_distance_;    //< supremum of all paths evaluated
	int max_path_length_;           //< supremum of all paths evaluated
	myDataType data_;               //< data to evaluate
	std::string output_file_name_;  //< file name for output
};

#endif // END OF PATHFINDER_DIAGNOSTICS_HPP_


