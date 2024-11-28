#include <memory>
#include <sstream>
#include <iostream>
#include "npc/knight.h"

Knight::Knight(Point position) : NPC(KnightType, position) {}

Knight::Knight(std::ifstream &stream) : NPC(KnightType, stream) {}

const std::string Knight::pretty() const {
    std::ostringstream output;
    output << "Knight@(" << pos.x << ", " << pos.y << ')';
    return output.str();
}

const std::string Knight::serialize() const {
    std::ostringstream output;
    output << 'K' << ' ' << pos.x << ' ' << pos.y;
    return output.str();
}

bool Knight::accept(std::shared_ptr<NPC> attacker) {
    return attacker->fight(std::static_pointer_cast<Knight>(shared_from_this()));
}

bool Knight::fight(std::shared_ptr<Knight> knight) {
    return false;
}

bool Knight::fight(std::shared_ptr<Squarrel> squarrel) {
    return true;
}

bool Knight::fight(std::shared_ptr<Pegasus> pegasus) {
    return false;
}