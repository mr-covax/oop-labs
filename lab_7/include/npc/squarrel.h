#pragma once

#include "npc/npc.h"

class Squarrel final : public NPC {
public:
    Squarrel(Point position);
    Squarrel(std::ifstream &stream);

    const char ID() const override;
    const std::string fullName() const override;

    bool accept(std::shared_ptr<NPC> attacker) override;
    bool fight(std::shared_ptr<Knight> knight) override;
    bool fight(std::shared_ptr<Squarrel> squarrel) override;
    bool fight(std::shared_ptr<Pegasus> pegasus) override;
};