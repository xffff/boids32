#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

Swarm::Swarm(int numAgents)
{
    srand(time(NULL)); // seed random gen
    std::cout<<"Swarm creating " <<numAgents<< " Agents...\n";
}

void Swarm::addAgent()
{
    float vals[4];
    for(int i=0; i<4; i++) vals[i] = (float)(((rand() % RAND_MAX) / RAND_MAX) * 2) - 1;
    std::unique_ptr<Agent> temp(new Agent());
    agents.push_back(std::move(temp));
}
