#include "Agent.h"
#include <vector>

class Swarm
{
public:
    Swarm(int numAgents);
    ~Swarm();
    void setMaxSpeed(float maxSpeed);
    void setNumAgents(int numAgents);
    void setFriction(float friction);
private:
    std::vector<Agent> agents;
    enum mode {NORMAL, AVERAGE};
    int numagents;
    float friction, gravity, *gravpoint, *avgvelocity, *centroid;
}
