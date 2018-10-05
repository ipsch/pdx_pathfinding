/** \file
 * 		time_measure.hpp
 *
 *  \brief
 *  	Provides functions for time time measurement
 *
 *  \details
 *  	compatible on windows and Linux
 *  	Checks for _WIN32 flag; If _WIN32  isn't set Linux is assumed.
 *
 *  \version
 *  	2018-10-05 ipsch: 1.0.2 final / reworked naming added documentation
 *
 *  \author
 *      AYee: Alexander Yee (original design posted on stackoverflow.com)
 *  	contact: a-yee@u.northwestern.edu
 *  \author
 *  	ipsch: Ingmar Schnell
 *      contact: i.p.schnell(at)gmail.com
 *
 *  \reference
 *  	https://stackoverflow.com/questions/17432502/how-can-i-measure-cpu-time-and-wall-clock-time-on-both-linux-windows
 */

#pragma once
#ifndef TIME_MEASURE_HPP_
#define TIME_MEASURE_HPP_

#ifdef _WIN32
#include <Windows.h>
#else  //  Posix/Linux
#include <time.h>
#include <sys/time.h>
#endif // IFDEF _WIN31

double get_wall_time();
double get_cpu_time();

#endif // END OF TIME_MEASURE_HPP_
