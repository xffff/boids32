#include <iostream>
#include "Swarm.h"

typedef std::vector< std::vector<float> > vvfloat;

int main(int argc, char** argv)
{
    std::cout<<"win32 boids v20131204\n";
    Swarm s = Swarm(10);
    vvfloat v;
    v = s.getBoids();
    for(int i=0; i<s.numAgents; i++) {
	std::vector<float> agentData = v[i];
	std::cout<<"Agent "<<i<<": ";
	for(std::vector<float>::iterator it = agentData.begin(); it != agentData.end(); ++it)
	    { std::cout<<*it<<", "; }
	std::cout<<std::endl;
    }
    return 0;
}

