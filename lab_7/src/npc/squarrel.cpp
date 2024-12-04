#include "npc/squarrel.h"

Squarrel::Squarrel(Point position) 
    : NPC(SquarrelType, position, 5, 5) {}

Squarrel::Squarrel(std::ifstream &stream) : NPC(SquarrelType, stream) {}

const char Squarrel::ID() const {
    return 'S';
}

const std::string Squarrel::fullName() const {
    return "Squarrel";
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