#ifndef ROAD_H
#define ROAD_H



#include "Section.h"
#include "Lane.h"
#include "Parameters.h"
using namespace std;

class Road
{
	public:
		Road();
		Road(Parameters params);
		Section NEIntersection;
	private:
		int roadSize;
		
		
		Section NWIntersection;
		Section SEIntersection;
		Section SWIntersection;
		Lane northBound;
		Lane southBound;
		Lane eastBound;
		Lane westBound;

};
#endif