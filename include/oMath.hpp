#pragma once


namespace o_math
{

	unsigned int oPow2(unsigned int e);


	template <typename T>
	T max(const T &a, const T &b)
	{
		return a>b ? a : b;
	}

	template <typename T>
	T min(const T &a, const T &b)
	{
		return a<b ? a : b;
	}


} // END namespace


