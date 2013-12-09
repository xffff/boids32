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

    p->separation	= 0.2f;
    p->alignment	= 0.05f;
    p->coherence	= 0.02f;
    p->inertia		= 0.4f;
    p->maxvel		= 0.3f;
    p->septhresh	= 0.2f;
    
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

void Swarm::genFrame(int a)
{
    float px = agents[a]->vx;
    float py = agents[a]->vy;

    // @TODO: rules go here
    separate(a);
    
    // inertia
    agents[a]->vx = (px*agents[a]->inertia) + (agents[a]->vx*(1-agents[a]->inertia));
    agents[a]->vy = (px*agents[a]->inertia) + (agents[a]->vy*(1-agents[a]->inertia));

    // velocity
    agents[a]->vx = clip(agents[a]->vx,agents[a]->maxvel * -1,agents[a]->maxvel);
    agents[a]->vy = clip(agents[a]->vy,agents[a]->maxvel * -1,agents[a]->maxvel);

    // friction
    agents[a]->x += agents[a]->vx * (1-friction);
    agents[a]->y += agents[a]->vy * (1-friction);

    // wrap agent in torus space (could convert this to a bounce or something???)
    twrap(a);
}


void Swarm::twrap(int a)
{
     if(agents[a]->x < 0)	{ agents[a]->x += 1; }
     else if(agents[a]->x > 1)	{ agents[a]->x -= 1; }
     if(agents[a]->y < 0)	{ agents[a]->y += 1; }
     else if(agents[a]->y > 1)	{ agents[a]->y -= 1; }
}

float Swarm::clip(float n, float lower, float upper)
{
    return std::max(lower, std::min(n, upper));
}

void Swarm::separate(int a)
{
    for(int i=0; i<numAgents; i++) {
	if(a != i) {
	    float mag = 0;
	    float dx = agents[i]->x - agents[a]->x;
	    float dy = agents[i]->y - agents[a]->y;
	    if(dx > 0.5) { dx--; } else if(dx < -0.5) { dx++; }
	    if(dy > 0.5) { dy--; } else if(dy < -0.5) { dy++; }
	    if(abs(dx) > 0.0001 && abs(dy) > 0.0001)
		{ mag = dx*dx + dy*dy; }
	    else
		{ mag = 0.01; }
	    if(mag < agents[a]->septhresh) {
		float proxscale = 0;
		if(mag < 0.0001) {
		    proxscale = 8;
		} else {
		    proxscale = agents[a]->septhresh /
			(agents[a]->septhresh - (agents[a]->septhresh - mag));
		}
		agents[a]->vx -= dx*agents[a]->separation*proxscale;
		agents[a]->vy -= dy*agents[a]->separation*proxscale;
	    }
	}
    }
}

void Swarm::align(int a)
{
    float dvx = avgvelocity[0] - agents[a]->vx;
    float dvy = avgvelocity[1] - agents[a]->vy;
    agents[a]->vx += dvx*agents[a]->alignment;
    agents[a]->vy += dvy*agents[a]->alignment;
}

void Swarm::cohere(int a)
{
    float dx = centroid[0] - agents[a]->x;
    float dy = centroid[1] - agents[a]->y;
    agents[a]->vx += (dx*agents[a]->coherence);
    agents[a]->vy += (dy*agents[a]->coherence);
}

void Swarm::gravitate(int a)
{
    float dx = gravpoint[0] - agents[a]->x;
    float dy = gravpoint[1] - agents[a]->y;
    agents[a]->vx += dx*gravity;
    agents[a]->vy += dy*gravity;
}
