class Agent;
class Swarm
{
public:
    Swarm(int numAgents);
    ~Swarm(){};
    void setMaxSpeed(float maxSpeed);
    void setNumAgents(int numAgents);
    void setFriction(float friction);
    std::vector<std::unique_ptr<float>> getAgents();
private:
    std::vector<std::unique_ptr<Agent>> agents;
    enum mode {NORMAL, AVERAGE};
    int numagents;
    float friction, gravity;
    float gravpoint[2], avgvelocity[2], centroid[2]; // x, y
    void genFrame(std::unique_ptr<Agent>);
};
