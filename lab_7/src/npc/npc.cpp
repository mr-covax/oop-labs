#include <cmath>
#include <sstream>
#include <memory>
#include <npc/npc.h>
#include <mics/globals.h>

NPC::NPC(NPCType charType, std::ifstream &stream) : npcType{charType} {
    stream >> pos.x >> pos.y >> moveDistance >> killDistance;
}

NPC::NPC(NPCType charType, Point position, size_t move, size_t kill)
    : npcType{charType}, pos{position}, moveDistance{move}, killDistance{kill} {}

void NPC::move() {
    if (!isAlive) return;
    pos.x = (pos.x + (std::rand() % (2 * moveDistance + 1)) - moveDistance + MAP_SIZE) % MAP_SIZE;
    pos.y = (pos.y + (std::rand() % (2 * moveDistance + 1)) - moveDistance + MAP_SIZE) % MAP_SIZE;
}

void NPC::kill() {
    isAlive = false;
}

const bool NPC::alive() const {
    return isAlive;
}

const Point NPC::position() const {
    return pos;
}

const std::string NPC::pretty() const {
    std::ostringstream output;
    output << fullName() << "@(" << pos.x << ", " << pos.y << ')';
    return output.str();
}

const std::string NPC::serialize() const {
    std::ostringstream output;
    output << ID() << ' ' << pos.x << ' ' << pos.y;
    return output.str();
}
    
const bool NPC::inRange(std::shared_ptr<NPC> other) const {
    double dx = other->pos.x - pos.x;
    double dy = other->pos.y - pos.y;
    double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    return distance <= killDistance;
}

std::ostream& operator<<(std::ostream&& os, std::shared_ptr<NPC> n) {
    os << n->pretty();
    return os;
}