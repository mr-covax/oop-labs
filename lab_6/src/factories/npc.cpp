#include <iostream>

#include <factories/npc.h>

#include <npc/knight.h>
#include <npc/squarrel.h>
#include <npc/pegasus.h>

std::shared_ptr<NPC> npcFactory(NPCType type, int x, int y) {
    std::shared_ptr<NPC> newNPC;

    switch (type) {
        case KnightType: 
            newNPC = std::make_shared<Knight>(Point{x, y});
            break;
        case SquarrelType:
            newNPC = std::make_shared<Squarrel>(Point{x, y});
            break;
        case PegasusType:
            newNPC = std::make_shared<Pegasus>(Point{x, y});
            break;
        default:
            std::cerr << "Error: Invalid NPCType provided.\n";
            break;
    }

    return newNPC;
}

std::shared_ptr<NPC> npcFactory(std::ifstream& stream) {
    std::shared_ptr<NPC> result;
    char ID;

    if (stream >> ID) {
        switch (ID) {
            case 'K':
                return std::make_shared<Knight>(stream);
                break;
            case 'S':
                result = std::make_shared<Squarrel>(stream);
                break;
            case 'P':
                result = std::make_shared<Pegasus>(stream);
                break;
            default:
                std::cout << "Error: Invalid NPC type in stream: " << ID << std::endl;
                break;
        }
    } else {
        std::cout << "Error: Failed to read NPC type from stream.\n";
    }

    return result;
}
