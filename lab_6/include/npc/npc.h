#pragma once

#include <set>
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

using NPCSet = std::set<std::shared_ptr<NPC>>;

class NPC : public std::enable_shared_from_this<NPC> {
public:
    NPC(NPCType charType, Point position);
    NPC(NPCType charType, std::ifstream &stream);

    const Point position() const;
    const bool inRange(std::shared_ptr<NPC> other, int radius) const;

    virtual const std::string pretty() const = 0;
    virtual const std::string serialize() const = 0;

    virtual bool accept(std::shared_ptr<NPC> attacker) = 0;
    virtual bool fight(std::shared_ptr<Knight> knight) = 0;
    virtual bool fight(std::shared_ptr<Squarrel> squarrel) = 0;
    virtual bool fight(std::shared_ptr<Pegasus> pegasus) = 0;

    friend std::ostream& operator<<(std::ostream&& os, std::shared_ptr<NPC> n);

    virtual ~NPC() = default;

protected:
    NPCType type;
    Point pos;
};