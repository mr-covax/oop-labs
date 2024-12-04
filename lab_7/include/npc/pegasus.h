#pragma once

#include "npc.h"

class Pegasus final : public NPC {
public:
    Pegasus(Point position);
    Pegasus(std::ifstream &stream);

    const char ID() const override;
    const std::string fullName() const override;

    bool accept(std::shared_ptr<NPC> attacker) override;
    bool fight(std::shared_ptr<Knight> knight) override;
    bool fight(std::shared_ptr<Squarrel> squarrel) override;
    bool fight(std::shared_ptr<Pegasus> pegasus) override;
};