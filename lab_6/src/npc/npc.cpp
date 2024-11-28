#include <cmath>
#include <memory>
#include <npc/npc.h>

NPC::NPC(NPCType charType, Point position)
    : type{charType}, pos{position} {}

NPC::NPC(NPCType charType, std::ifstream &stream) 
    : type{charType} 
{
    stream >> pos.x >> pos.y;
}

const Point NPC::position() const {
    return pos;
}
    
const bool NPC::inRange(std::shared_ptr<NPC> other, int radius) const {
    double dx = other->pos.x - pos.x;
    double dy = other->pos.y - pos.y;
    double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    return distance <= radius;
}

std::ostream& operator<<(std::ostream&& os, std::shared_ptr<NPC> n) {
    os << n->pretty();
    return os;
}