#include "Stack.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using chip8::Stack;
using ::testing::Eq;

TEST(StackTest, StackIsEmptyWhenCreated)
{
    Stack stack;

    ASSERT_THAT(stack.isEmpty(), Eq(true));
}

TEST(StackTest, PushInsertsAnElementAtTheTopOfTheStack)
{
    Stack stack;
    
    stack.push(123);
    ASSERT_THAT(stack.top(),Eq(123));
    
    stack.push(234);
    ASSERT_THAT(stack.top(),Eq(234));
    
    stack.push(345);
    ASSERT_THAT(stack.top(),Eq(345));
}

TEST(StackTest, TopReturnsTheElementLastInserted)
{
    Stack stack;

    stack.push(1);
    ASSERT_THAT(stack.top(), Eq(1));
}

TEST(StackTest, WeCanModifyTheElementAtTheTopIfTheStackIsMutable)
{
    Stack stack;

    stack.push(3);
    ASSERT_THAT(stack.top(), Eq(3));

    stack.top() = 2;
    ASSERT_THAT(stack.top(), Eq(2));
}

TEST(StackTest, PopRemovesTheMostRecentlyInsertedElement)
{
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();

    ASSERT_THAT(stack.top(), Eq(2));
}

TEST(StackTest, SizeGetsTheCapacityOfTheStack)
{
    Stack stack;

    ASSERT_THAT(stack.size(), Eq(0));
}