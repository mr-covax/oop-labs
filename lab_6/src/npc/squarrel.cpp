#include <sstream>
#include "npc/squarrel.h"

Squarrel::Squarrel(Point position) : NPC(SquarrelType, position) {}

Squarrel::Squarrel(std::ifstream &stream) : NPC(SquarrelType, stream) {}

const std::string Squarrel::pretty() const {
    std::ostringstream output;
    output << "Squarrel@(" << pos.x << ", " << pos.y << ')';
    return output.str();
}

const std::string Squarrel::serialize() const {
    std::ostringstream output;
    output << 'S' << ' ' << pos.x << ' ' << pos.y;
    return output.str();
}

bool Squarrel::accept(std::shared_ptr<NPC> attacker) {
    return attacker->fight(std::static_pointer_cast<Squarrel>(shared_from_this()));
}

bool Squarrel::fight(std::shared_ptr<Knight> Squarrel) {
    return false;
}

bool Squarrel::fight(std::shared_ptr<Squarrel> squarrel) {
    return false;
}

bool Squarrel::fight(std::shared_ptr<Pegasus> pegasus) {
    return true;
}