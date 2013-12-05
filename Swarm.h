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
    std::vector<std::unique_ptr<Agent> > agents;
private:
    void addAgent();
    enum mode {NORMAL, AVERAGE};
    static int numagents;
    float friction, gravity;
    float gravpoint[2], avgvelocity[2], centroid[2]; // x, y
};

class Agent : public Swarm {
public:
    Agent() : x(0), y(0), vx(0), vy(0) {};
    Agent(float x, float y, float vx, float vy)
	: x(x), y(y), vx(vx), vy(vy) {};
protected:
    float x, y, vx, vy, separation, alignment, coherence, inertia, maxvel, septhresh;
};
