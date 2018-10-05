#include "PathfinderDiagnostics.hpp"




void PrintAnalysis(const int &xi, const int &yi, const int &xf, const int &yf,
		const int &path_length, const unsigned int &nodes_expanded,
		const double &wall_time, const double &cpu_time, const int *pOutBuffer)
{
	bool print_header = false;
	if(print_header)
	{
		// print header
	    std::cout << "x_i\t";
	    std::cout << "y_i\t";
	    std::cout << "x_f\t";
	    std::cout << "x_f\t";
	    std::cout << "M_dist\t";
		std::cout << "return_val\t";
		std::cout << "wall_time\t";
		std::cout << "cpu_time\t";
		std::cout << "pOutBuffer\n";
		return;
	}



    std::cout << xi << "\t";
    std::cout << yi << "\t";
    std::cout << xf << "\t";
    std::cout << yf << "\t";
    std::cout << abs(xf-xi) + abs(yf-yi) << "\t";
	std::cout << path_length << "\t";
	std::cout << nodes_expanded << "\t";
	std::cout << wall_time << "\t";
	std::cout << cpu_time;
	if(false)
	{
		std::cout << "\t{";
		for(int i=0; i<path_length; ++i)
			std::cout << pOutBuffer[i] << "\t";
		std::cout << "}";
	}
	std::cout << std::endl;


	// fancy output
    //std::cout << map_names[iter_map] ;
    //std::cout << "\t" << test;
    //std::cout << "\t(" << nStartX << "," << nStartY << ") -> ";
    //std::cout << "(" << nTargetX << "," << nTargetY << ")\t";
	//std::cout << FindPathResult << "\t";
	//std::cout << "wall: " << wall1 - wall0 << "\t";
	//std::cout << "cpu:  " << cpu1 - cpu0 << "\t";
	//std::cout << "pOutBuffer: ";
	//for(int i=0; i<nBufferSize; ++i)
	//	std::cout << pOutBuffer[i] << "\t";
	//std::cout << "\n";

	return;
}

void PrintAnalysis(const int &xi, const int &yi, const int &xf, const int &yf,
		const AnalysisRuntimeData &ana, const int *pOutBuffer)
{

	PrintAnalysis(xi, yi, xf, yf,
			ana.path_length_, ana.nodes_expanded_,
			ana.wall_time_, ana.wall_time_, pOutBuffer);
	return;
}



AnalysisRuntime::AnalysisRuntime() :
	max_manhattan_distance_(0),
	max_path_length_(0),
	output_file_name_("")
{ };


AnalysisRuntime::AnalysisRuntime(const int &nMapWidth, const int &nMapHeight, const std::string &output_file_name) :
	max_manhattan_distance_(nMapWidth+nMapHeight-2),
	max_path_length_(0),
	output_file_name_(output_file_name)
{ };

AnalysisRuntime::~AnalysisRuntime()
{ }


void AnalysisRuntime::AddData(const AnalysisRuntimeData &data)
{
	data_.push_back(data);
	max_path_length_ = oMax<int>(max_path_length_, data.path_length_);
	return;
}

void AnalysisRuntime::AddData(const unsigned int &manhattan_distance,
		const unsigned int &path_length,
		const unsigned int &nodes_expanded,
		const double &wall_time,
		const double &cpu_time)
{
	AddData(AnalysisRuntimeData(manhattan_distance, path_length, nodes_expanded, wall_time, cpu_time));

	return;
}


/*
void AnalysisRuntime::Evaluate()
{
	oTable<double> table_sum_of_runtime(max_path_length_+1,max_manhattan_distance_+1);
	oTable<unsigned int> table_number_of_runs(max_path_length_+1,max_manhattan_distance_+1);
	table_sum_of_runtime.set(.0);
	table_number_of_runs.set(0);

	// sorting raw data into tables
	for(myDataType::iterator it = data_.begin(); it != data_.end(); it++)
	{
		AnalysisRuntimeData current(*it);
		int i = current.path_length_;
		int j = current.manhattan_distance_;
		table_sum_of_runtime(i,j) += current.time_;
		table_number_of_runs(i,j) += 1;
	}

	// doing statistics
	for(unsigned int j=0; j<=max_manhattan_distance_; ++j)
		for(unsigned int i=0; i<=max_path_length_; ++i)
			if(table_number_of_runs(i,j)>0)
				table_sum_of_runtime(i,j) = table_sum_of_runtime(i,j) / ( (double) table_number_of_runs(i,j));


	if(CallbackOutput_==0L)
		throw("no output defined");
	else if(stream_to_output_.is_open())
		CallbackOutput_(table_sum_of_runtime, false, std::cout);
	else
		CallbackOutput_(table_sum_of_runtime, false, std::cout);

	return;
}
*/



int FindBin(const double &x0, const double &x1, const int &n, const double &x)
// The interval [x0,x1) is divided into n equally spaced sub-intervals;
// FindBind returns the number of the one sub-interval x is located in.
// Note: a sub-interval given by [xa,xb)
//
// Example for n=7
//   x0                          x             x1
//   |-----|-----|-----|-----|-----|-----|-----|
//      0     1     2     3     4     5     6
// Return value is FindBin=4
{
	if(x1<=x0)
		throw("invalid interval range");
	if( (x<x0) || (x1<=x) )
		throw("x out of range");
	if(n<0)
		throw("invalid number of bins");

	double xa,xb;
	double dx = (x1-x0) / ((double) n );
	int i=0;

	do
	{
		xa = x0 + i*dx;
		xb = xa+dx;
		if( (xa<x) && (x<xb) )
			return i;
		++i;
	} while(xb<x1);
	return -1;
}


void AnalysisRuntime::CalcMean()
{
	int N=0;
	double mean_cpu_time = .0;
	double mean_wall_time = .0;

	for(myDataType::iterator it = data_.begin(); it != data_.end(); it++)
	{
		++N;
		mean_cpu_time += (*it).cpu_time_;
		mean_wall_time += (*it).wall_time_;
	}

	mean_cpu_time = mean_cpu_time / (double) N;
	mean_wall_time = mean_wall_time / (double) N;

	std::cout << "--------------------------------------------------\n";
	std::cout << mean_cpu_time << "\t" << mean_wall_time << std::endl;

}


void AnalysisRuntime::Evaluate()
{
	int n_bins_path = 20; // number_of_bins_for_path_length = 100;
	int n_bins_dist = 20; // number_of_bins_for_manhattan_distance_length = 100;

	double delta_bin_path = (double) max_path_length_/ (double) n_bins_path;
	double delta_bin_dist = (double) max_manhattan_distance_/ (double) n_bins_dist;

	oTable<double> table_sum_of_runtime(n_bins_path,n_bins_dist);
	oTable<unsigned int> table_number_of_runs(n_bins_path,n_bins_dist);

	for(int i=0; i<n_bins_path; ++i)
	{
		double delta_path = (double) max_path_length_ / (double) n_bins_path;
		std::stringstream sstr;
		sstr << i*delta_path;
		table_sum_of_runtime.row_axis_[i] = sstr.str();
		table_number_of_runs.row_axis_[i] = sstr.str();
	}

	for(int j=0; j<n_bins_dist; ++j)
	{
		double delta_dist = (double) max_manhattan_distance_ / (double) n_bins_dist;
		std::stringstream sstr;
		sstr << j*delta_dist;
		table_sum_of_runtime.col_axis_[j] = sstr.str();
		table_number_of_runs.col_axis_[j] = sstr.str();
	}


	table_sum_of_runtime.set(.0);
	table_number_of_runs.set(0);

	// sorting raw data into tables
	for(myDataType::iterator it = data_.begin(); it != data_.end(); it++)
	{
		AnalysisRuntimeData current(*it);
		//double p = current.path_length_;
		//double d = current.manhattan_distance_;
		//table_sum_of_runtime(i,j) += current.time_;
		//table_number_of_runs(i,j) += 1;


		int p = FindBin(
				.0,
				(double) (max_path_length_+1),
				n_bins_path,
				(double) current.path_length_);
		int d = FindBin(
				.0,
				(double) (max_manhattan_distance_+1),
				n_bins_dist,
				(double) current.manhattan_distance_);

		if( (p!=-1) && (d!=-1) )
		{
			table_sum_of_runtime(p,d) += current.wall_time_;
			table_number_of_runs(p,d) += 1;
		}

	}


	// doing statistics
	for(unsigned int j=0; j<n_bins_dist; ++j)
		for(unsigned int i=0; i<n_bins_path; ++i)
			if(table_number_of_runs(i,j)>0)
				table_sum_of_runtime(i,j) = table_sum_of_runtime(i,j) / ( (double) table_number_of_runs(i,j));


	std::ofstream stream_to_output(output_file_name_, std::ios::out);
	if(CallbackOutput_==0L)
		throw("no output defined");
	else if(stream_to_output.good())
		CallbackOutput_(table_sum_of_runtime, stream_to_output);
	else
		CallbackOutput_(table_sum_of_runtime, std::cout);
	if(stream_to_output.is_open())
		stream_to_output.close();

	return;
}
