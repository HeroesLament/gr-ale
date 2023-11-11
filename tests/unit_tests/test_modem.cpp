#include "gtest/gtest.h"
#include "modem.h"  

TEST(ModemTest, TestInterleave) {
    Modem modem;
    unsigned int golayCoderA = /*...*/;
    unsigned int golayCoderB = /*...*/;
    unsigned int expectedInterleaved = /*...*/;
    ASSERT_EQ(expectedInterleaved, modem.interleave(golayCoderA, golayCoderB));
}

TEST(ModemTest, TestDeinterleave) {
    Modem modem;
    unsigned int interleavedWord = /*...*/;
    auto [expectedCoderA, expectedCoderB] = /*...*/;
    auto [actualCoderA, actualCoderB] = modem.deinterleave(interleavedWord);
    ASSERT_EQ(expectedCoderA, actualCoderA);
    ASSERT_EQ(expectedCoderB, actualCoderB);
}
