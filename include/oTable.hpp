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


	/** \brief Class to represent a 2d table (with outputs compatible to gnuplot)
	 */
	template <typename T>
	class oTable
	{
	public :
		explicit oTable(const unsigned int &m, const unsigned int &n);
		~oTable();

		void set(const T &val);
		T& operator()(const unsigned int &row, const unsigned int &column);
		T operator()(const unsigned int &row, const unsigned int &column) const;

		const unsigned int rows_;  //< number of rows in the table
		const unsigned int cols_;  //< number of columns in the table
		const unsigned int size_;  //< number of table entries (=rows_*cols_)

		std::string * col_axis_;   //< labels for the columns
		std::string * row_axis_;   //< labels for the rows
	protected :
		oTable();
		unsigned int index(const unsigned int &i, const unsigned int &j) const;
		T* data_;                  //< Table content
	};


	//! \brief Constructor (protected to be unaccessible)
	template <typename T>
	oTable<T>::oTable() : rows_(0), cols_(0), data_(0L), row_axis_(0L), col_axis_(0L)
	{
		// nothing to do here
	}


	/** \brief Constructor
	 *  \param[in] m number of rows
	 *  \param[in] n number of columns
	 */
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


	//! Destructor
	template <typename T>
	oTable<T>::~oTable()
	{
		delete[] data_;
		delete[] col_axis_;
		delete[] row_axis_;
	}


	/** \briefs Set all table entries to a supplied value
	 *  \param[in] val The value to be applied to all table entries
	 */
	template <typename T>
	void oTable<T>::set(const T &val)
	{
		for(unsigned int index=0; index<size_; ++index)
			data_[index] = val;
		return;
	}


	/** \brief Calculates index of table element from row and column value
	 *  \param[in] i row index
	 *  \param[in] j column index
	 *  \return index of element at (i,j)
	 */
	template <typename T>
	unsigned int oTable<T>::index(const unsigned int &i, const unsigned int &j) const
	{
		if(i>rows_) throw ("oTable row index out of bound");
		if(j>cols_) throw ("oTable column index out of bound");
		return j + i*cols_;
	}


	/** \brief Accessor for table content (lvalue)
	 *  \param[in] row row index
	 *  \param[in] col column index
	 *  \return Value (lvalue) of table content at (row,col)
	 */
	template <typename T>
	T& oTable<T>::operator()(const unsigned int &row, const unsigned int &column)
	{
		return data_[index(row,column)];
	}


	/** \brief Accessor for table content (rvalue)
	 *  \param[in] row row index
	 *  \param[in] col column index
	 *  \return Value (rvalue) of table content at (row,col)
	 */
	template <typename T>
	T oTable<T>::operator()(const unsigned int &row, const unsigned int &column) const
	{
		return data_[index(row,column)];
	}


	/** \brief Print table content to output
	 *  \detail print the bulk data of the table in a gnuplot (splot) compatible order
	 *  \param[in] data The table we want to plot
	 *  \param[in] output_stream The output we want the table to plot to
	 */
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
