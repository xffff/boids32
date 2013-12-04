#include "Agent.h"

Agent::Agent()
    : x(0), y(0), vx(0), vy(0)
{}

Agent::Agent(float x, float y, float vx, float vy)
{
    self->x = x;
    self->y = y;
    self->vx = vx;
    self->vy = vy;
}
