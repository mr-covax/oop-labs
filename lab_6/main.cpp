#include <iostream>
#include <memory>
#include <cstring>

#include <npc/npc.h>
#include <npc/knight.h>
#include <npc/squarrel.h>
#include <npc/pegasus.h>

#include <logging/structures.h>
#include <logging/display.h>
#include <logging/file.h>

#include <factories/npc.h>

void displayHelp(char* progName) {
    std::cout 
        << "Usage: " << progName << " <mode> <map-file>" 
        << std::endl;

    std::cout
        << "\tmode: the operation to perform. "
        << "'generate' will create a random map. "
        << "'play' will take the map from 'map-file' and run it."
        << std::endl;

    std::cout
        << "\tmap-file: the file with the characters and their positions."
        << std::endl;
}

void generateField() {
    NPCSet npcSet;

    for (size_t i = 0; i < 100; ++i)
        npcSet.insert(npcFactory(
            NPCType(std::rand() % 3), 
            std::rand() % 500,
            std::rand() % 500
        ));

    std::ofstream output("map.txt");
    output << npcSet.size() << '\n';
    
    for (auto &npc : npcSet) {
        output << npc->serialize() << '\n';
    }

    output.flush();
    output.close();

    std::cout << "Generation complete!" << std::endl;
}

NPCSet loadField(std::string path) {
    NPCSet result;
    
    std::ifstream input(path);
    if (!input.good() || !input.is_open()) {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    }

    int count;
    input >> count;
    for (int i = 0; i < count; ++i) {
        result.insert(npcFactory(input));
    }
    
    input.close();
    return result;
}

LogMonitor setupLogging() {
    LogMonitor logger;
    auto displayLog = std::make_shared<DisplayLogger>();
    auto fileLog = std::make_shared<FileLogger>("output.txt");

    logger.attach(fileLog); 
    logger.attach(displayLog);

    return logger;
}

NPCSet battle(LogMonitor &log, NPCSet npcs, size_t radius) {
    NPCSet dead;

    for (const auto &attacker : npcs) {
        for (const auto &defender : npcs) {
            if (attacker != defender && attacker->inRange(defender, radius)) {
                if (defender->accept(attacker)) {
                    dead.insert(defender);
                    log << "Murder: " 
                        << attacker->pretty() << " killed " << defender->pretty()
                        << "\n";
                }
            }
        }
    }
    return dead;
}


NPCSet runGame(LogMonitor &log, NPCSet &array) {
    for (size_t radius = 20; (radius <= 100) && !array.empty(); radius += 10) {
        log << "----- Distance = " << radius << " -----" << "\n\n";

        auto dead = battle(log, array, radius);

        for (auto &d : dead)
            array.erase(d);
        
        if (dead.size() > 0)
            log << "\n--- Killed: " << dead.size() << "\n\n";
        else
            log << "No deaths in this round\n\n";

    }
    return array;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        displayHelp(argv[0]);
        return 1;
    } else if (std::strcmp(argv[1], "generate") == 0) {
        generateField();
        return 1;
    } else if (std::strcmp(argv[1], "run") != 0 || argc != 3) {
        displayHelp(argv[0]);
        return 1;
    }

    LogMonitor logger = setupLogging();
    NPCSet array = loadField(argv[2]);
    NPCSet remaining = runGame(logger, array);

    logger << "----- Game over! -----" << "\n"; 
    logger << "--- Survived: " << remaining.size() << "\n";
    for (auto& npc : remaining) {
        logger << "\t" << npc->pretty() << "\n";
    }

    return 0;
}