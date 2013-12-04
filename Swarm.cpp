#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

void Swarm::Swarm(int numAgents)
{
    srand(time(NULL));
    if(numAgents > 0) {
	for(int i=0; i<numAgents; i++) {
	    double vals[4];
	    for(int j=0; j<4; j++) { vals[j] = (rand() % 10) * 0.1; }       
	    agents.push_back(new Agent(vals[0], vals[1], vals[2], vals[3]));
	}
    }
}

void Swarm::~Swarm()
{
    for(int i=0; i<agents.size(); i++)
	delete agents[i];
}

void Swarm::killSwarm(int numAgents)
{

}

void Swarm::setMax(float maxSpeed)
{

}

void Swarm::tick()
{

}
