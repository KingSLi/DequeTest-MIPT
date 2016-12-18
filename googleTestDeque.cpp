

#include "gtest/gtest.h"
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <string>
#include <deque>
#include "deque.h"

const int SIZE_TEST_DEQUE = 200000;
const int SIZE_STRING_TEST_DEQUE = 50000;
const int RAND_SIZE_TEST_DEQUE = 100;

TEST(DequeTest, testIntPushFront) {
    Deque<int> d;
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        d.push_front(i);
    }
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        ASSERT_EQ(d[i], SIZE_TEST_DEQUE - 1 - i);
    }
}

TEST(DequeTest, testIntPushPopBack) {
    Deque<int> d;
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        d.push_back(i);
    }
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        ASSERT_EQ(d[i], i);
    }
    size_t lowSize = d.size();
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        d.pop_back();
    }
    ASSERT_EQ(lowSize - SIZE_TEST_DEQUE, d.size());
}

TEST(DequeTest, testIntPushPopFront) {
    Deque<int> d;
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        d.push_front(i);
    }
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        ASSERT_EQ(d[i], SIZE_TEST_DEQUE - i - 1);
    }
    size_t lowSize = d.size();
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        d.pop_front();
    }
    ASSERT_EQ(lowSize - SIZE_TEST_DEQUE, d.size());
}
TEST(DequeTest, testIntIterator) {
    Deque<int> d;
    std::deque<int> correct;
    for (size_t i = 0; i < SIZE_TEST_DEQUE; ++i) {
        if (rand() % (RAND_SIZE_TEST_DEQUE) < RAND_SIZE_TEST_DEQUE / 2) {
            d.push_front(i);
            correct.push_front(i);
        }
        else {
            d.push_back(i);
            correct.push_back(i);
        }
    }
    auto corIt = correct.begin();
    for (auto it : d) {
        ASSERT_EQ(it, *corIt);
        ++corIt;
    }
}
TEST(DequeTest, testIntReverseIterator) {
    Deque<int> d;
    std::deque<int> correct;
    for (int i = 0; i < SIZE_TEST_DEQUE; ++i) {
        if (rand() % (SIZE_TEST_DEQUE) < SIZE_TEST_DEQUE / 2) {
            d.push_front(i);
            correct.push_front(i);
        }
        else {
            d.push_back(i);
            correct.push_back(i);
        }
    }
    auto corIt = correct.rbegin();
    auto testIt = d.rbegin();
    for (auto testIt = d.rbegin(); testIt != d.rend(); ++testIt, ++corIt) {
        ASSERT_EQ(*testIt, *corIt);
    }
}
TEST(DequeTest, testStringPushPopBack) {
    Deque<std::string> d;
    std::deque<std::string> correct;
    std::string test = "tr";

    for (size_t i = 0; i < SIZE_STRING_TEST_DEQUE; ++i) {
        if (rand() % (10) < 10 / 2) {
            d.push_front(test);
            correct.push_front(test);
        }
        else {
            d.push_back(test);
            correct.push_back(test);
        }
    }
    auto corIt = correct.rbegin();
    auto testIt = d.rbegin();
    for (auto testIt = d.rbegin(); testIt != d.rend(); ++testIt, ++corIt) {
        ASSERT_EQ(*testIt, *corIt);
    }
}
TEST(DequeTest, testSstringIterator) {
    Deque<std::string> d;
    std::deque<std::string> correct;
    std::string test = "";
    for (size_t i = 0; i < SIZE_STRING_TEST_DEQUE; ++i) {
        test = std::to_string(i);
        if (rand() % (RAND_SIZE_TEST_DEQUE) < RAND_SIZE_TEST_DEQUE / 2) {
            d.push_front(test);
            correct.push_front(test);
        }
        else {
            d.push_back(test);
            correct.push_back(test);
        }
    }
    auto corIt = correct.begin(); 
    for (auto it : d) {
        ASSERT_EQ(it, *corIt);
        ++corIt;
    }
}
TEST(DequeTest, testStringReverseIterator) {
    Deque<std::string> d;
    std::deque<std::string> correct;
    std::string test = "";
    for (size_t i = 0; i < SIZE_TEST_DEQUE; ++i) {
        test = std::to_string(i);
        if (rand() % (RAND_SIZE_TEST_DEQUE) < RAND_SIZE_TEST_DEQUE / 2) {
            d.push_front(test);
            correct.push_front(test);
        }
        else {
            d.push_back(test);
            correct.push_back(test);
        }
    }
    auto corIt = correct.rbegin();
    auto testIt = d.rbegin();
    for (auto testIt = d.rbegin(); testIt != d.rend(); ++testIt, ++corIt) {
        ASSERT_EQ(*testIt, *corIt);
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
