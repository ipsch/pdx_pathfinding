#ifndef METRICS_HELPERS_HPP_
#define METRICS_HELPERS_HPP_


#include <cmath>

template <class DiscreteType>
DiscreteType DiscreteMeasure(DiscreteType i)
{
	return std::abs(i);
}


template <class DiscreteType, class ... Args>
DiscreteType DiscreteMeasure(DiscreteType i, Args ... args)
{
	return std::abs(i) + DiscreteMeasure(args...);
}



#endif // END OF METRICS_HELPSER_HPP_
