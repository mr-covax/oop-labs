#include <sstream>
#include "npc/pegasus.h"

Pegasus::Pegasus(Point position) : NPC(PegasusType, position) {}

Pegasus::Pegasus(std::ifstream &stream) : NPC(PegasusType, stream) {}

const std::string Pegasus::pretty() const {
    std::ostringstream output;
    output << "Pegasus@(" << pos.x << ", " << pos.y << ')';
    return output.str();
}

const std::string Pegasus::serialize() const {
    std::ostringstream output;
    output << 'S' << ' ' << pos.x << ' ' << pos.y;
    return output.str();
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