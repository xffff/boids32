class Agent : public Swarm
{
public:
    Agent(float x, float y, float vx, float vy);
    ~Agent();
protected:
    float x, y, vx, vy, separation, alignment, coherence, inertia, maxvel, septhresh;
}
