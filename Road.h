#include "Section.h"
#include "TrafficLight.h"


class Road
{
	public:
		Road();
		Road(Parameters params);
	private:
		int roadSize;
		TrafficLight tl_NS;
		TrafficLight tl_EW;
		Section NEIntersection;
		Section NWIntersection;
		Section SEIntersection;
		Section SWIntersection;


};
