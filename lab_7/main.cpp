#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <atomic>

#include <npc/npc.h>
#include <npc/knight.h>
#include <npc/squarrel.h>
#include <npc/pegasus.h>
#include <mics/globals.h>

std::shared_mutex mapMutex;
std::mutex coutMutex;
std::atomic<bool> gameRunning(true);

NPCVec npcs;

void initPlayers() {
    for (int i = 0; i < NPC_COUNT - 1; ++i) {
        std::shared_ptr<NPC> result;

        int type = std::rand() % 3;
        Point pos{std::rand() % MAP_SIZE, std::rand() % MAP_SIZE};
    
        if (type == KnightType)
            result = std::make_shared<Knight>(pos);
        else if (type == SquarrelType)
            result = std::make_shared<Squarrel>(pos);
        else
            result = std::make_shared<Pegasus>(pos);
        
        npcs.push_back(result);
    }
}

void moveNPCs() {
    while (gameRunning) {
        {
            std::unique_lock lock(mapMutex);
            for (auto& npc : npcs) {
                npc->move();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void handleBattles() {
    while (gameRunning) {
        {
            std::unique_lock lock(mapMutex);
            for (auto& att : npcs)
                for (auto& def : npcs)
                    if (att != def && att->alive() && def->alive())
                        if (att->inRange(def) && def->accept(att))
                            def->kill();
        }
                            
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void printMap() {
    while (gameRunning) {
        {
            std::shared_lock lock(mapMutex);
            std::vector<std::vector<char>> map(MAP_SIZE, std::vector<char>(MAP_SIZE, SPACER));
            for (const auto& npc : npcs) {
                if (npc->alive()) {
                    Point pos = npc->position();
                    map[pos.x][pos.y] = npc->ID();
                }
            }

            std::lock_guard coutLock(coutMutex);
            for (const auto& row : map) {
                for (const auto& cell : row) {
                    std::cout << ' ' << cell << ' ';
                }
                std::cout << std::endl;
            }
            std::cout << "==========================" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    initPlayers();

    std::thread moveThread(moveNPCs);
    std::thread battleThread(handleBattles);
    std::thread printThread(printMap);

    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION));
    gameRunning = false;

    moveThread.join();
    battleThread.join();
    printThread.join();

    std::lock_guard coutLock(coutMutex);
    std::cout << "Game over! Survivors:" << std::endl;
    for (const auto& npc : npcs) {
        if (npc->alive()) {
            std::cout << npc->pretty() << std::endl;
        }
    }

    return 0;
}