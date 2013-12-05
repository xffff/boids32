#include <vector>
#include <memory>

class Agent;
class Swarm
{
public:
    Swarm(){};
    Swarm(int numAgents);
    void setMaxSpeed(float maxSpeed);
    void setNumAgents(int numAgents);
    void setFriction(float friction);
    std::vector<std::vector<float> > getBoids();
    int numAgents;
private:
    std::vector<std::unique_ptr<Agent> > agents;
    void addAgent();
    enum mode {NORMAL, AVERAGE};
    float friction, gravity;
    float gravpoint[2], avgvelocity[2], centroid[2]; // x, y
    void genFrame(int agentIndex);
    float clip(float n, float lower, float upper);
};

class Agent : Swarm {
public:
    Agent() : x(0), y(0), vx(0), vy(0) {};
    Agent(float x, float y, float vx, float vy)
	: x(x), y(y), vx(vx), vy(vy) {};
    float x, y, vx, vy, separation, alignment, coherence, inertia, maxvel, septhresh;
};
