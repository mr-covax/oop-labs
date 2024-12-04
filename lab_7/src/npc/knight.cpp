#include <memory>
#include "npc/knight.h"

Knight::Knight(Point position) 
    : NPC(KnightType, position, 30, 10) {}

Knight::Knight(std::ifstream &stream) : NPC(KnightType, stream) {}

const char Knight::ID() const {
    return 'K';
}

const std::string Knight::fullName() const {
    return "Knight";
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