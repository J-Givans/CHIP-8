#include "Stack.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using chip8::Stack;
using ::testing::Eq;
using ::testing::Test;

class StackTest : public Test
{
public:
    Stack stack;
};

TEST_F(StackTest, StackIsEmptyWhenCreated)
{
    ASSERT_THAT(stack.isEmpty(), Eq(true));
}

TEST_F(StackTest, PushInsertsAnElementAtTheTopOfTheStack)
{
    stack.push(123);
    ASSERT_THAT(stack.top(),Eq(123));
    
    stack.push(234);
    ASSERT_THAT(stack.top(),Eq(234));
    
    stack.push(345);
    ASSERT_THAT(stack.top(),Eq(345));
}

TEST_F(StackTest, TopReturnsTheElementLastInserted)
{
    stack.push(1);
    ASSERT_THAT(stack.top(), Eq(1));
}

TEST_F(StackTest, WeCanModifyTheElementAtTheTopIfTheStackIsMutable)
{
    stack.push(3);
    ASSERT_THAT(stack.top(), Eq(3));

    stack.top() = 2;
    ASSERT_THAT(stack.top(), Eq(2));
}

TEST_F(StackTest, PopRemovesTheMostRecentlyInsertedElement)
{
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();

    ASSERT_THAT(stack.top(), Eq(2));
}

TEST_F(StackTest, SizeGetsTheNumberOfElementsInTheStack)
{
    ASSERT_THAT(stack.size(), Eq(0));
}