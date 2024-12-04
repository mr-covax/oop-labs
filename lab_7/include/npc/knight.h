#pragma once

#include "npc/npc.h"

class Knight final : public NPC {
public:
    Knight(Point position);
    Knight(std::ifstream &stream);

    const char ID() const override;
    const std::string fullName() const override;

    bool accept(std::shared_ptr<NPC> attacker) override;
    bool fight(std::shared_ptr<Knight> knight) override;
    bool fight(std::shared_ptr<Squarrel> squarrel) override;
    bool fight(std::shared_ptr<Pegasus> pegasus) override;

    ~Knight() override = default;
};