#include <gtest/gtest.h>
#include "../include/Array.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"

TEST(PointTest, BasicOperations) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus<int> r;
    std::istringstream input("0 0 1 1 2 0 1 -1");
    input >> r;
    
    EXPECT_NEAR(static_cast<double>(r), 2.0, 1e-6);
}

TEST(ArrayTest, PushAndAccess) {
    Array<std::shared_ptr<Figure<int>>> arr;
    auto fig = std::make_shared<Rhombus<int>>();
    arr.push_back(fig);
    
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], fig);
}

TEST(ArrayTest, MoveSemantics) {
    Array<std::string> arr;
    arr.push_back("test");
    arr.push_back("move");
    
    EXPECT_EQ(arr[0], "test");
    EXPECT_EQ(arr[1], "move");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}