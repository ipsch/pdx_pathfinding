#include "LoadMap.hpp"




/*

int LoadMap(const std::string &path, unsigned int &width, unsigned int &height, unsigned char *&data)
{

	std::ifstream MapStream(path.c_str(),std::ifstream::in);

	if(!MapStream.good()) return -1;
	std::string line;
	std::string::size_type sz;

	do // handle map header data.
	   // Header is located before bulk data in *.map file
	   // bulk data is indicated by "pMap=" keyword.
	{
		getline(MapStream,line);
		if(line.find("MapWidth")!=std::string::npos)
			width = std::stoi(FindAndReplaceAll(line,"MapWidth=",""),&sz);
		if(line.find("MapHeight")!=std::string::npos)
			height = std::stoi(FindAndReplaceAll(line,"MapHeight=",""),&sz);



	} while( (!(line.find("MapData")!=std::string::npos))
			&& MapStream.good());

	if(data!=0L)
		delete[] data;
	unsigned int size = width*height;
	data = new unsigned char[size]();


	unsigned int iter=0;
	do // handle map bulk data
	{
		getline(MapStream,line);
		for(std::size_t collumn=0; collumn < line.size(); ++collumn)
		{

			switch (line[collumn])
			{
			case '.':
				data[iter]=1;
				break;
			case '@':
				data[iter]=0;
				break;
			default :
				data[iter]=1;
				break;
			}
			++iter;

		}


	} while(MapStream.good()); // END READING FROM FILE






	MapStream.close();
	return 0;
}




MapMetaObject LoadMap(const std::string &path_to_file)
{

	unsigned int width;
	unsigned int height;

	std::ifstream MapStream(path_to_file.c_str(),std::ifstream::in);

	if(!MapStream.good())
		throw("file coudn't be opened");


	std::string line;
	std::string::size_type sz;

	do // handle map header data.
	   // Header is located before bulk data in *.map file
	   // bulk data is indicated by "pMap=" keyword.
	{
		getline(MapStream,line);
		if(line.find("MapWidth")!=std::string::npos)
			width = std::stoi(FindAndReplaceAll(line,"MapWidth=",""),&sz);
		if(line.find("MapHeight")!=std::string::npos)
			height = std::stoi(FindAndReplaceAll(line,"MapHeight=",""),&sz);



	} while( (!(line.find("MapData")!=std::string::npos))
			&& MapStream.good());


	unsigned int size = width*height;
	unsigned char *data = new unsigned char[size]();


	unsigned int iter=0;
	do // handle map bulk data
	{
		getline(MapStream,line);
		for(std::size_t collumn=0; collumn < line.size(); ++collumn)
		{

			switch (line[collumn])
			{
			case '.':
				data[iter]=1;
				break;
			case '@':
				data[iter]=0;
				break;
			default :
				data[iter]=1;
				break;
			}
			++iter;

		}


	} while(MapStream.good()); // END READING FROM FILE






	MapStream.close();
	return 0;
}


*/
