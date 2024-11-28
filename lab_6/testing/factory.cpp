#include <gtest/gtest.h>

#include <npc/npc.h>
#include <npc/knight.h>
#include <npc/pegasus.h>
#include <npc/squarrel.h>

#include <factories/npc.h>
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

TEST(NPCTest, FactoryByType) {
    auto knight = npcFactory(NPCType::KnightType, 5, 10);
    EXPECT_EQ(knight->position().x, 5);
    EXPECT_EQ(knight->position().y, 10);

    auto squarrel = npcFactory(NPCType::SquarrelType, 15, 20);
    EXPECT_EQ(squarrel->position().x, 15);
    EXPECT_EQ(squarrel->position().y, 20);

    auto pegasus = npcFactory(NPCType::PegasusType, -5, -10);
    EXPECT_EQ(pegasus->position().x, -5);
    EXPECT_EQ(pegasus->position().y, -10);
}

TEST(NPCTest, FactoryByFile) {
    // Create a temporary file path
    const std::string temp_file = "npc_test_file.txt";

    // Write a serialized Knight to the file
    {
        std::ofstream outfile(temp_file);
        outfile << "K 5 10"; // Assuming 'K' for KnightType serialization format
    }

    // Read the file using npcFactory
    {
        std::ifstream infile(temp_file);
        auto knight = npcFactory(infile);
        EXPECT_EQ(knight->position().x, 5);
        EXPECT_EQ(knight->position().y, 10);
    }

    // Cleanup temporary file
    std::filesystem::remove(temp_file);
}

TEST(NPCTest, SerializeAndDeserializeUsingFile) {
    // Create a temporary file path
    const std::string temp_file = "npc_test_serialization.txt";

    // Serialize a Knight to the file
    {
        auto knight = std::make_shared<Knight>(Point{7, 14});
        std::ofstream outfile(temp_file);
        outfile << knight->serialize();
    }

    // Deserialize the Knight from the file
    {
        std::ifstream infile(temp_file);
        auto knight = npcFactory(infile);
        EXPECT_EQ(knight->position().x, 7);
        EXPECT_EQ(knight->position().y, 14);
    }

    // Cleanup temporary file
    std::filesystem::remove(temp_file);
}



TEST(NPCTest, SerializeDeserialize) {
    // Create a temporary file path
    const std::string temp_file = "npc_test_serialization_temp.txt";

    // Step 1: Serialize a Knight to the file
    {
        Point position = {3, 7};
        auto knight = std::make_shared<Knight>(position);
        std::ofstream outfile(temp_file);
        outfile << knight->serialize();
    }

    // Step 2: Deserialize the Knight from the file
    {
        std::ifstream infile(temp_file);
        auto deserializedKnight = npcFactory(infile);
        EXPECT_EQ(deserializedKnight->position().x, 3);
        EXPECT_EQ(deserializedKnight->position().y, 7);
    }

    // Step 3: Cleanup the temporary file
    std::filesystem::remove(temp_file);
}