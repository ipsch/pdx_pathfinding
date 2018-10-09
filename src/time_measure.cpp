/** \file
 * 		time_measure.cpp
 *
 *  \brief
 *  	Provides functions for time time measurement
 *
 *  \details
 *  	time_measure.cpp contains definitions to time_measure.hpp
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

#include "time_measure.hpp"


#ifdef _WIN32
double get_wall_time()
/** \brief function to measure wall time
 *  \detail this is the Windows variant of get_wall_time()
 *  \return Returns a timestamp of current wall time in seconds
 */
{
    LARGE_INTEGER time,freq;
    if (!QueryPerformanceFrequency(&freq))
    {
        //  Handle error
        return 0;
    }
    if (!QueryPerformanceCounter(&time))
    {
        //  Handle error
        return 0;
    }
    return (double) time.QuadPart / freq.QuadPart;
}


double get_cpu_time()
/** \brief function to measure cpu time
 *  \detail this is the Windows variant of get_cpu_time()
 *  \return Returns a timestamp of current cpu time in seconds
 */
{
    FILETIME CreationTime;
    // receives the creation time of the process.
    FILETIME ExitTime;
    // receives the exit time of the process. If the process has not exited,
    // the content of this structure is undefined.
    FILETIME KernelTime;
    // receives the amount of time that the process has executed in kernel mode.
    // The time that each of the threads of the process has executed in kernel mode
    // is determined, and then all of those times are summed together to obtain this value.
    FILETIME UserTime;
    // receives the amount of time that the process has executed in user mode.
    // The time that each of the threads of the process has executed in user mode
    // is determined, and then all of those times are summed together to obtain this value.
    // Note that this value can exceed the amount of real time elapsed (between lpCreationTime and lpExitTime)
    // if the process executes across multiple CPU cores.
    if (GetProcessTimes(GetCurrentProcess(), &CreationTime, &ExitTime, &KernelTime, &UserTime) != 0)
    {
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        return
            (double)(UserTime.dwLowDateTime |
            ((unsigned long long)UserTime.dwHighDateTime << 32)) * 0.0000001;
    }
    else
    {
        //  Handle error
        return 0;
    }
}

//  Posix/Linux
#else
#include <time.h>
#include <sys/time.h>

/** \brief function to measure wall time
 *  \detail this is the Windows variant of get_wall_time()
 *  \return Returns a timestamp of current wall time in seconds
 */
double get_wall_time()
{
    struct timeval time;
    if (gettimeofday(&time,NULL))
    {
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


/** \brief function to measure cpu time
 *  \detail this is the Windows variant of get_cpu_time()
 *  \return Returns a timestamp of current cpu time in seconds
 */
double get_cpu_time()
{
    return (double)clock() / CLOCKS_PER_SEC;
}
#endif
