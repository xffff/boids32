#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"
#include "Agent.h"

Swarm::Swarm(int numAgents)
{
    srand(time(NULL));
    if(numAgents > 0) {
	for(int i=0; i<numAgents; i++) {
	    double vals[4];
	    for(int j=0; j<4; j++) { vals[j] = (rand() % 10) * 0.1; }
	    std::unique_ptr<Agent> a(new Agent(vals[0], vals[1], vals[2], vals[3]));
	    agents.push_back(std::move(a));
	}
    }
}
