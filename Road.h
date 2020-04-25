#ifndef ROAD_H
#define ROAD_H

#include "Section.h"
#include "Lane.h"
#include "Parameters.h"
using namespace std;

class Road
{
	private:
		Section neIntersection;
		Section nwIntersection;
		Section seIntersection;
		Section swIntersection;
		Lane northBound;
		Lane southBound;
		Lane eastBound;
		Lane westBound;
		
	
	public:
		int roadSize;
		Road();
		Road(Parameters params);

		


};
#endif