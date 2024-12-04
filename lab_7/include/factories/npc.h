#pragma once

#include "npc/npc.h"

std::shared_ptr<NPC> npcFactory(NPCType type, int x, int y);

std::shared_ptr<NPC> npcFactory(std::ifstream& stream);