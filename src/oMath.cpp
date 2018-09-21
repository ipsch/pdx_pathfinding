#include "oMath.hpp"

namespace o_math
{

	unsigned int oPow2(unsigned int e)
	{
		unsigned int ret = 1;
		for(unsigned int i=0; i<e; ++i)
			ret <<= 1;
		return ret;
	}


} // END NAMESPACE
