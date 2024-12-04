#pragma once

#include <vector>
#include <memory>
#include <fstream>

enum NPCType : char {
    KnightType, 
    SquarrelType,
    PegasusType
};

struct Point {
    int x, y;
};

class NPC;
class Knight;
class Squarrel;
class Pegasus;

using NPCVec = std::vector<std::shared_ptr<NPC>>;

class NPC : public std::enable_shared_from_this<NPC> {
public:
    NPC(NPCType charType, std::ifstream &stream);
    NPC(NPCType charType, Point position, size_t move, size_t kill);

    void move();
    void kill();

    const bool alive() const;
    const bool inRange(std::shared_ptr<NPC> other) const;
    const Point position() const;

    const std::string pretty() const;
    const std::string serialize() const;

    virtual const char ID() const = 0;
    virtual const std::string fullName() const = 0;

    virtual bool accept(std::shared_ptr<NPC> attacker) = 0;
    virtual bool fight(std::shared_ptr<Knight> knight) = 0;
    virtual bool fight(std::shared_ptr<Squarrel> squarrel) = 0;
    virtual bool fight(std::shared_ptr<Pegasus> pegasus) = 0;

    friend std::ostream& operator<<(std::ostream&& os, std::shared_ptr<NPC> n);

    virtual ~NPC() = default;

protected:
    Point pos;
    NPCType npcType;
    size_t moveDistance;
    size_t killDistance;
    bool isAlive = true;
};