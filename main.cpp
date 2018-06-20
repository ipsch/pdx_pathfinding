//============================================================================
// Projekt     : pdx_pathfinding
// Name        : main.cpp
// Author      : ipsch (Ingmar Palle Schnell)
// ceated      : 2018-06-19
// Version     : 0.01 (2018-06-19)
// Copyright   : Your copyright notice
// Description : path finding problem from paradox interactive
//               reference: https://paradox.kattis.com/problems/paradoxpath
//============================================================================


// Task: Implement a path-finding algorithm in C++ that finds and returns
// a shortest path between two points in a 2-dimensional grid.
//
// Notes :
// - This specific problem can only be solved using C++.
// - The algorithm should provide an implementation of the function
//   "int FindPath(..)" for details see below (code).
//
// Constraints
// You may safely assume following relations are always true:
//   (1<=nMapWidth)
//   (1<=nMapHeight)
//   (0<=nStartX)
//	 (nTargetX<nMapWidth)
//   (0<=nStartY), (nTargetY<nMapHeight)
//   Both Start and Target are empty locations,
//   (nOutBufferSize>=0)


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
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

{


	return -1;
}










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




#include <iostream>
#include <fstream>
#include <string>
#include <sstream>




std::string FindAndReplaceAll(std::string str,
		const std::string &fnd,
		const std::string &rpl)
// str - input sting that is being searched
// fnd - substring that is searched for
// rpl - substring that will replace fnd
// return value is a new string with replacements
{
    std::size_t pos = str.find(fnd);

    if (pos == std::string::npos) return str;
    do
    {
    	str.replace(pos, fnd.length(), rpl);
    	pos = str.find(fnd,pos+rpl.length());
    } while (pos != std::string::npos);
	return str;
}




int example_pdx()
{
	int xStart=0, yStart=0;
	int xTarget=0, yTarget=0;
	int pOutBuffer=0;
	int MapHeight=0;
	int MapWidth=0;
	int *pMap;

	std::string path="./maps/pdx_example.map";
	std::ifstream MapStream(path.c_str(),std::ifstream::in);

	if(!MapStream.good()) return -1;
	std::string line;
	std::string::size_type sz;

	do
	{
		getline(MapStream,line);

		if(line.find("xStart")!=std::string::npos)
			xStart = std::stoi(FindAndReplaceAll(line,"xStart=",""),&sz);
		if(line.find("yStart")!=std::string::npos)
			yStart = std::stoi(FindAndReplaceAll(line,"yStart=",""),&sz);
		if(line.find("xTarget")!=std::string::npos)
			xTarget = std::stoi(FindAndReplaceAll(line,"xTarget=",""),&sz);
		if(line.find("yTarget")!=std::string::npos)
			yTarget = std::stoi(FindAndReplaceAll(line,"yTarget=",""),&sz);
		if(line.find("pOutBuffer")!=std::string::npos)
			pOutBuffer = std::stoi(FindAndReplaceAll(line,"pOutBuffer=",""),&sz);
		if(line.find("MapHeight")!=std::string::npos)
			MapHeight = std::stoi(FindAndReplaceAll(line,"MapHeight=",""),&sz);
		if(line.find("MapWidth")!=std::string::npos)
			MapWidth = std::stoi(FindAndReplaceAll(line,"MapWidth=",""),&sz);

		if(line.find("pMap")!=std::string::npos)
		{
			line = FindAndReplaceAll(line,"pMap=","");
		    line = FindAndReplaceAll(line,",","");
			int NMap = MapHeight*MapWidth;
			pMap = new int[NMap];
			int i=0;
			std::stringstream sstr(line);
			while (sstr.good() && i < NMap)
			{
				std::cout << i << std::endl;
			        sstr >> pMap[i];
			        ++i;
			 }

			std::cout << i << "?=" << NMap << std::endl;
			if(i!=NMap) return -1;
		} // END IF pMap handling
	} while(MapStream.good()); // END READING FROM FILE


  #define VERBOSE
  # if defined (VERBOSE)
	std::cout << "map read with following values\n";
	std::cout << "xStart= " << xStart << "\n";
	std::cout << "yStart= " << yStart << "\n";
	std::cout << "xTarget= " << xTarget << "\n";
	std::cout << "yTarget= " << yTarget << "\n";
	std::cout << "pOutBuffer= " << pOutBuffer << "\n";
	std::cout << "MapHeight= " << MapHeight << "\n";
	std::cout << "MapWidth= " << MapWidth << "\n";
	std::cout << "pMap= ";
	for(int i=0; i<MapHeight*MapWidth; ++i)
		std::cout << pMap[i] << " ";
	std::cout << "\n";
   #endif

	return 0;
};

int main(void)
{



	example_pdx();

	return 0;
}
