#pragma once


#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <string>
#include "oTable.hpp"


using namespace oMath;
struct AnalysisRuntimeData;

template<typename T>
inline T oMax(const T &a, const T &b)
{
	return (a>=b) ? a : b;
}

void PrintAnalysis(const int &xi, const int &yi, const int &xf, const int &yf,
		const AnalysisRuntimeData &ana, const int *pOutBuffer);

void PrintAnalysis(const int &xi, const int &yi, const int &xf, const int &yf,
		const int &path_length, const unsigned int &nodes_expanded,
		const double &wall_time, const double &cpu_time, const int *pOutBuffer);






struct AnalysisRuntimeData
{
	AnalysisRuntimeData(const unsigned int &m, const unsigned int &p, const unsigned int &n, const double &wall, const double &cpu) :
		manhattan_distance_(m), path_length_(p), nodes_expanded_(n), wall_time_(wall), cpu_time_(cpu)
	{ }
	AnalysisRuntimeData(const AnalysisRuntimeData &that) :
		manhattan_distance_(that.manhattan_distance_),
		path_length_(that.path_length_),
		nodes_expanded_(that.nodes_expanded_),
		wall_time_(that.wall_time_),
		cpu_time_(that.cpu_time_)
	{ }
	int manhattan_distance_; //shortest path possible (if there were no obstacles)
	int path_length_; // shortest path (found by path finding algorithm around obstacles)
	unsigned int nodes_expanded_;
	double wall_time_;
	double cpu_time_;
};




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
	void (*CallbackOutput_)(const oTable<double> &, std::ostream &) = &oTablePrint;
	AnalysisRuntime();
	typedef std::vector<AnalysisRuntimeData> myDataType;
	int max_manhattan_distance_;
	int max_path_length_;
	myDataType data_;
	std::string output_file_name_;
};



