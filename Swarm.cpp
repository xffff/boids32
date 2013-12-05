#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

Swarm::Swarm(int numAgents) : numAgents(numAgents), friction(0.25), gravity(0.02)
{
    srand(time(NULL)); // seed random gen
    std::cout<<"Swarm creating " <<numAgents<< " Agents...\n";
    for(int i=0; i<numAgents; i++) { addAgent(); }
}

void Swarm::addAgent()
{
    float vals[4];
    for(int i=0; i<4; i++) 
	{ vals[i] = ((float) rand() / (RAND_MAX)) * 2 - 1; }

    std::unique_ptr<Agent> p(new Agent(vals[0], vals[1], vals[2], vals[3]));
    agents.push_back(std::move(p));    
}

std::vector<std::vector<float> > Swarm::getBoids()
{
    float cx, cy, cvx, cvy;
    std::vector<std::vector<float> > swarmVals; // return this
    
    for(int i=0; i<numAgents; i++) {
    	std::vector<float> agentVals;
    	genFrame(i);
    	cx += agents[i]->x;
    	cy += agents[i]->y;
    	cvx += agents[i]->vx;
    	cvy += agents[i]->vy;
    	agentVals.push_back(agents[i]->x);
    	agentVals.push_back(agents[i]->y);
    	agentVals.push_back(agents[i]->vx);
    	agentVals.push_back(agents[i]->vy);
    	swarmVals.push_back(agentVals);
    }
    centroid[0] = cx/numAgents;
    centroid[1] = cy/numAgents;
    avgvelocity[0] = cvx/numAgents;
    avgvelocity[1] = cvy/numAgents;

    return swarmVals;
}

void Swarm::genFrame(int i)
{
    float px = agents[i]->vx;
    float py = agents[i]->vy;

    // @TODO: rules go here

    // inertia
    agents[i]->vx = (px*agents[i]->inertia) + (agents[i]->vx*(1-agents[i]->inertia));
    agents[i]->vy = (px*agents[i]->inertia) + (agents[i]->vy*(1-agents[i]->inertia));

    // velocity
    agents[i]->vx = clip(agents[i]->vx,agents[i]->maxvel * -1,agents[i]->maxvel);
    agents[i]->vy = clip(agents[i]->vy,agents[i]->maxvel * -1,agents[i]->maxvel);

    // friction
    agents[i]->x = agents[i]->x + (agents[i]->vx * (1-friction));
    agents[i]->y = agents[i]->y + (agents[i]->vy * (1-friction));
}


float Swarm::clip(float n, float lower, float upper)
{
    return std::max(lower, std::min(n, upper));
}
