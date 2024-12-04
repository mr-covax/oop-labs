#include "npc/pegasus.h"

Pegasus::Pegasus(Point position) 
    : NPC(PegasusType, position, 30, 10) {}

Pegasus::Pegasus(std::ifstream &stream) : NPC(PegasusType, stream) {}

const char Pegasus::ID() const {
    return 'P';
}

const std::string Pegasus::fullName() const {
    return "Pegasus";
}

bool Pegasus::accept(std::shared_ptr<NPC> attacker) {
    return attacker->fight(std::static_pointer_cast<Pegasus>(shared_from_this()));
}

bool Pegasus::fight(std::shared_ptr<Knight> Pegasus) {
    return false;
}

bool Pegasus::fight(std::shared_ptr<Squarrel> squarrel) {
    return false;
}

bool Pegasus::fight(std::shared_ptr<Pegasus> pegasus) {
    return false;
}