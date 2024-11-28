#include <memory>
#include <gtest/gtest.h>

#include <npc/npc.h>
#include <npc/knight.h>
#include <npc/pegasus.h>
#include <npc/squarrel.h>

TEST(NPCTest, ConstructorPosition) {
    Point position = {5, 10};
    auto knight = std::make_shared<Knight>(position);
    EXPECT_EQ(knight->position().x, 5);
    EXPECT_EQ(knight->position().y, 10);

    auto squarrel = std::make_shared<Squarrel>(position);
    EXPECT_EQ(squarrel->position().x, 5);
    EXPECT_EQ(squarrel->position().y, 10);

    auto pegasus = std::make_shared<Pegasus>(position);
    EXPECT_EQ(pegasus->position().x, 5);
    EXPECT_EQ(pegasus->position().y, 10);
}

TEST(NPCTest, PrettyPrint) {
    Point position = {1, 1};
    auto pegasus = std::make_shared<Pegasus>(position);
    EXPECT_FALSE(pegasus->pretty().empty());
}

TEST(NPCTest, RangeDetection) {
    Point position1 = {0, 0};
    Point position2 = {3, 4}; // Distance = 5
    auto knight = std::make_shared<Knight>(position1);
    auto squarrel = std::make_shared<Squarrel>(position2);

    EXPECT_TRUE(knight->inRange(squarrel, 5));
    EXPECT_FALSE(knight->inRange(squarrel, 4));
}

TEST(NPCTest, FightMechanics) {
    auto knight1 = std::make_shared<Knight>(Point{0, 0});
    auto knight2 = std::make_shared<Knight>(Point{1, 1});
    auto squarrel = std::make_shared<Squarrel>(Point{2, 2});
    auto pegasus = std::make_shared<Pegasus>(Point{3, 3});

    // Test Knight fights
    EXPECT_FALSE(knight1->fight(knight2));
    EXPECT_TRUE(knight1->fight(squarrel));
    EXPECT_FALSE(knight1->fight(pegasus));

    // Test Squarrel fights
    EXPECT_FALSE(squarrel->fight(knight1));
    EXPECT_FALSE(squarrel->fight(knight2));
    EXPECT_TRUE(squarrel->fight(pegasus));

    // Test Pegasus fights
    EXPECT_FALSE(pegasus->fight(knight1));
    EXPECT_FALSE(pegasus->fight(squarrel));
    EXPECT_FALSE(pegasus->fight(knight2));
}

TEST(NPCTest, AcceptMechanics) {
    auto knight = std::make_shared<Knight>(Point{0, 0});
    auto squarrel = std::make_shared<Squarrel>(Point{1, 1});
    auto pegasus = std::make_shared<Pegasus>(Point{2, 2});

    EXPECT_TRUE(squarrel->accept(knight));
    EXPECT_FALSE(pegasus->accept(knight));
    EXPECT_FALSE(knight->accept(squarrel));
}
