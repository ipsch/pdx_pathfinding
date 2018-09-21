/**
 * file time_measure.hpp
 *
 * \brief Provides functions for time time measurement
 *
 * \details compatible on windows and Linux
 * (check _WIN32 flag. If not set Linux is assumed)
 */
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

#endif // IFNDEF TIME_MEASURE_HPP_
