#include <gtest/gtest.h>
#include "Vector.hpp"
#include <string>
#include <random>

struct Node{
    int a;
    double b;
};
class VectorTest : public ::testing::Test
{
  protected:
    VectorTest() {}
    ~VectorTest() {}

    void SetUp() override {
        intv.push_back(a); intv.push_back(b); intv.push_back(c);
    }
    void TearDown() override {

    }

    Vector<int> intv;
    Vector<double> doublev;
    Vector<std::string> stringv;
    Vector<Node> nodev;
    int a = 1, b = 2, c = 3;
};

TEST_F(VectorTest, EmptyVectorSizeEqualsZero){
    ASSERT_EQ(intv.size(), 0);
    ASSERT_EQ(stringv.size(), 0);
    ASSERT_EQ(nodev.size(), 0);
}

TEST_F(VectorTest, PushedValuesAreInVector){
    ASSERT_EQ(intv[0], a);
    ASSERT_EQ(intv[1], b);
    ASSERT_EQ(intv[2], c);
}

TEST_F(VectorTest, AtGivesSameValueAsSquareBracketsOperator){
    ASSERT_EQ(intv[0], intv.at(0));
    ASSERT_EQ(intv[1], intv.at(1));
    ASSERT_EQ(intv[2], intv.at(2));
}
TEST_F(VectorTest, RetrieveOperatorsThrowsIfOutOfRange){
    ASSERT_THROW(intv[-1], std::out_of_range);
    ASSERT_THROW(intv[3], std::out_of_range);

    ASSERT_THROW(intv.at(-1), std::out_of_range);
    ASSERT_THROW(intv.at(3), std::out_of_range);
}


TEST_F(VectorTest, PopedValuesAreReallyPopped){
    for(int i = 0; i < 3; i++)
        intv.pop_back();
    ASSERT_EQ(intv.size(), 0);
    ASSERT_THROW(intv[0], std::out_of_range);
}

TEST_F(VectorTest, CopyConstructorCopies){
     Vector<int> other {intv};

    ASSERT_EQ(other[0], a);
    ASSERT_EQ(other[1], b);
    ASSERT_EQ(other[2], c);

    ASSERT_EQ(intv[0], a);
    ASSERT_EQ(intv[1], b);
    ASSERT_EQ(intv[2], c);
}

TEST_F(VectorTest, MoveConstructorMoves){
    Vector<int> other {std::move(intv)};

    ASSERT_EQ(other[0], a);
    ASSERT_EQ(other[1], b);
    ASSERT_EQ(other[2], c);

    ASSERT_ANY_THROW(intv[0]);
}

TEST_F(VectorTest, CopyAssignmentCopies){
    Vector<int> other = {3, 4, 5};
    other = intv;

    ASSERT_EQ(other[0], a);
    ASSERT_EQ(other[1], b);
    ASSERT_EQ(other[2], c);

    ASSERT_EQ(intv[0], a);
    ASSERT_EQ(intv[1], b);
    ASSERT_EQ(intv[2], c);
}

TEST_F(VectorTest, MoveAssignmentMoves){
    Vector<int> other = {3, 4, 5};
    other = std::move(intv);

    ASSERT_EQ(other[0], a);
    ASSERT_EQ(other[1], b);
    ASSERT_EQ(other[2], c);

    ASSERT_ANY_THROW(intv[0]);
}