#include <vector>
#include <memory>

class Swarm
{
public:
    Swarm(){};
    Swarm(int numAgents);
    ~Swarm(){};
    void setMaxSpeed(float maxSpeed);
    void setNumAgents(int numAgents);
    void setFriction(float friction);
private:
    enum mode {NORMAL, AVERAGE};
    static int numagents;
    float friction, gravity;
    float gravpoint[2], avgvelocity[2], centroid[2]; // x, y
};
