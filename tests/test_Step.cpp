#include "gtest/gtest.h"
#include <workflow/Step.h>


TEST(TestStep, test_hash) {
    std::vector<std::string> empty;
    auto step1 = std::make_shared<workflow::Step>("step1", empty, empty, nullptr);
    auto step2 = std::make_shared<workflow::Step>("step2", empty, empty, nullptr);
    auto step3 = std::make_shared<workflow::Step>("step1", empty, empty, nullptr);
    std::unordered_map<std::shared_ptr<workflow::Step>, std::shared_ptr<workflow::Step>> map;
    map.emplace(step1, step1);
    map.emplace(step2, step2);
    map.emplace(step3, step3);

    EXPECT_EQ(map.at(step1)->identifier, step1->identifier);
    EXPECT_EQ(map.at(step1)->name, step1->name);
    EXPECT_EQ(map.at(step2)->identifier, step2->identifier);
    EXPECT_EQ(map.at(step2)->name, step2->name);
    EXPECT_EQ(map.at(step3)->identifier, step3->identifier);
    EXPECT_EQ(map.at(step3)->name, step3->name);

    map[step1] = step2;
    EXPECT_EQ(map.at(step1)->identifier, step2->identifier);
    EXPECT_EQ(map.at(step1)->name, step2->name);
}
