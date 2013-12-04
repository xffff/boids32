#include "Swarm.h"

class Agent : public Swarm {
public:
    Agent() : x(0), y(0), vx(0), vy(0)
	{};
    Agent(float x, float y, float vx, float vy);
protected:
    float x, y, vx, vy, separation, alignment, coherence, inertia, maxvel, septhresh;
};
