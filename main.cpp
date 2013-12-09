/* simple test in the console */

#include <iostream>
#include "Swarm.h"

typedef std::vector< std::vector<float> > vvfloat;

int main(int argc, char** argv)
{
    std::cout<<"win32 boids v20131205\n";
    Swarm s = Swarm(10);
    vvfloat v;
    for(int n=0; n<20; n++){
	 v = s.getBoids();
	 std::cout<<n+1<<". ****************************************"<<std::endl;

	 for(int i=0; i<s.numAgents; i++) {
	      std::vector<float> agentData = v[i];
	      std::cout<<"Agent "<<i<<": ";
	      std::vector<float>::iterator it;
	      for(it = agentData.begin(); it != agentData.end(); ++it)
		  { std::cout<<*it<<", "; }
	      std::cout<<std::endl;
	 }
    }
    return 0;
}

