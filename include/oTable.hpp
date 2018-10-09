/** \file
 * 		oTable.hpp
 *
 * 	\brief
 * 		Class to represent a 2d table (with outputs compatible to gnuplot)
 *
 *  \detail
 *		Contains class oTable.
 *		oTable is intended to store data in a table format that can
 *		comfortably written to standard output for later processing
 *		with gnuplot.
 *		oTable is part of namespace o_math (my own mathematical helpers collection)
 *
 *  \version
 *  	2018-10-09 ipsch: 1.9.1 final
 *
 *  \author
 *  	ipsch: Ingmar Schnell
 *  	contact: i.p.schnell(at)gmail.com
 */

#pragma once
#ifndef OTABLE_HPP_
#define OTABLE_HPP_


#include <ostream>  // writing data to output
#include <iomanip>  // for setting output format (scientific, width etc.)
#include <string>   // strings used for labels
#include <sstream>  // converting actual data to labels

namespace o_math
{

	template <typename T>
	class oTable
	{
	public :
		explicit oTable(const unsigned int &m, const unsigned int &n);
		~oTable();
		void set(const T &val);
		T& operator()(const unsigned int &row, const unsigned int &column)
			{return data_[index(row,column)];}
		T operator()(const unsigned int &row, const unsigned int &column) const
			{return data_[index(row,column)];}

		const unsigned int rows_;
		const unsigned int cols_;
		const unsigned int size_;

		std::string * col_axis_;
		std::string * row_axis_;
	private :
		unsigned int index(const unsigned int &i, const unsigned int &j) const
		{
			if(i>rows_) throw ("oTable row index out of bound");
			if(j>cols_) throw ("oTable column index out of bound");
			return j + i*cols_;
		}
		oTable() : rows_(0), cols_(0), data_(0L), row_axis_(0L), col_axis_(0L) { }
		T* data_;
	};



	template <typename T>
	oTable<T>::oTable(const unsigned int &m, const unsigned int &n) :
			rows_(m), cols_(n), size_(m*n)
	{
		data_ = new T[size_];
		col_axis_ = new std::string[cols_];
		for(unsigned int i=0; i<cols_; ++i)
		{
			std::stringstream sstr;
			sstr << i;
			col_axis_[i] = sstr.str();
		}
		row_axis_ = new std::string[rows_];
		for(unsigned int i=0; i<rows_; ++i)
		{
			std::stringstream sstr;
			sstr << i;
			row_axis_[i] = sstr.str();
		}
	} // end of constructor oTable


	template <typename T>
	oTable<T>::~oTable()
	{
		delete[] data_;
		delete[] col_axis_;
		delete[] row_axis_;
	}


	template <typename T>
	void oTable<T>::set(const T &val)
	{
		for(unsigned int index=0; index<size_; ++index)
			data_[index] = val;
		return;
	}



	template <typename T>
	void oTablePrint(const oTable<T> &data, std::ostream &output_stream)
	{


		for(unsigned int i=0; i<data.rows_; ++i)
		{
			for(unsigned int j=0; j<data.cols_; ++j)
			{
				//output_stream << i << "\t";
				//output_stream << j << "\t";
				output_stream << data.row_axis_[i] << "\t";
				output_stream << data.col_axis_[j] << "\t";
				output_stream << std::scientific;
				output_stream << std::setprecision(6);
				output_stream << data(i,j) << "\n";
			}
			output_stream << "\n";
		}

		return;
	}

} // END namespace oMath

#endif // END OF OTABLE_HPP_
