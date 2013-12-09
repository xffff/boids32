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
     void genFrame(int agentIndex); // mek som boobs
     void separate(int agentIndex); // rules
     void align(int agentIndex);
     void cohere(int agentIndex);
     void gravitate(int agentIndex);
     void twrap(int agentIndex);

     float clip(float n, float lower, float upper); // just a helper
};

class Agent : Swarm {
public:
     Agent() : x(0), y(0), vx(0), vy(0)
	  {
	       separation	= 0;
	       alignment	= 0;
	       coherence	= 0;
	       inertia		= 0;
	       maxvel		= 0;
	       septhresh	= 0;
	  };
     Agent(float x, float y, float vx, float vy)
	  : x(x), y(y), vx(vx), vy(vy)
	  {
	       separation	= 0;
	       alignment	= 0;
	       coherence	= 0;
	       inertia		= 0;
	       maxvel		= 0;
	       septhresh	= 0;
	  };
     float x, y, vx, vy, separation, alignment, coherence, inertia, maxvel, septhresh;
};
