#include "Swarm.h"
#include "Agent.h"

Agent::Agent()
    : x(0), y(0), vx(0), vy(0)
{}

Agent::Agent(float x, float y, float vx, float vy)
{
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
}
