#include "TritSet.h"
#include "gtest/gtest.h"

TEST(MemoryTests, ConstructorAllocationTest) {
    for (int i = 0; i <= 1000; ++i) {
        TritSet set(i);

        size_t allocLength = set.capacity();
        EXPECT_GE(allocLength, i * 2 / 8 / sizeof(unsigned int));
    }
}

TEST(MemoryTests, TritMemoryUnknown) {
    TritSet set(6);
    EXPECT_TRUE(set[5] == Trit::UNKNOWN);
}

TEST(MemoryTests, TritMemory) {
    TritSet set(6);
    set[0] = Trit::TRUE;
    set[1] = Trit::FALSE;
    set[2] = Trit::TRUE;
    set[3] = Trit::TRUE;
    set[4] = Trit::UNKNOWN;
    set[5] = Trit::FALSE;

    EXPECT_TRUE(set[0] == Trit::TRUE);
    EXPECT_TRUE(set[1] == Trit::FALSE);
    EXPECT_TRUE(set[2] == Trit::TRUE);
    EXPECT_TRUE(set[3] == Trit::TRUE);
    EXPECT_TRUE(set[4] == Trit::UNKNOWN);
    EXPECT_TRUE(set[5] == Trit::FALSE);
}

TEST(MemoryTests, tritOperationAllocation) {
    TritSet setA(1000);
    TritSet setB(2000);

    TritSet setC = setA | setB;

    EXPECT_EQ(setB.capacity(), setC.capacity());
}

TEST(tritOperationTests, OrTest) {
    TritSet setA(3);
    TritSet setB(3);

    setA[0] = Trit::FALSE;
    setA[1] = Trit::TRUE;
    setA[2] = Trit::UNKNOWN;

    setB[0] = Trit::TRUE;
    setB[1] = Trit::FALSE;
    setB[2] = Trit::UNKNOWN;

    TritSet setC = setA | setB;

    EXPECT_TRUE(setC[0] == Trit::TRUE);
    EXPECT_TRUE(setC[1] == Trit::TRUE);
    EXPECT_TRUE(setC[2] == Trit::UNKNOWN);
}

TEST(tritOperationTests, AndTest) {
    TritSet setA(3);
    TritSet setB(3);

    setA[0] = Trit::FALSE;
    setA[1] = Trit::TRUE;
    setA[2] = Trit::UNKNOWN;

    setB[0] = Trit::TRUE;
    setB[1] = Trit::FALSE;
    setB[2] = Trit::UNKNOWN;

    TritSet setC = setA & setB;

    EXPECT_TRUE(setC[0] == Trit::FALSE);
    EXPECT_TRUE(setC[1] == Trit::FALSE);
    EXPECT_TRUE(setC[2] == Trit::UNKNOWN);
}

TEST(tritOperationTests, NotTest) {
    TritSet setA(3);

    setA[0] = Trit::TRUE;
    setA[1] = Trit::FALSE;
    setA[2] = Trit::UNKNOWN;

    TritSet setC = !setA;

    EXPECT_TRUE(setC[0] == Trit::FALSE);
    EXPECT_TRUE(setC[1] == Trit::TRUE);
    EXPECT_TRUE(setC[2] == Trit::UNKNOWN);
}

TEST(OtherFunctionsTests, CardinalityFunctionTest) {
    TritSet set(3);

    set[0] = Trit::TRUE;
    set[1] = Trit::UNKNOWN;
    set[2] = Trit::FALSE;

    EXPECT_EQ(set.cardinality(Trit::FALSE), 1);
    EXPECT_EQ(set.cardinality(Trit::TRUE), 1);
    EXPECT_EQ(set.cardinality(Trit::UNKNOWN), 1);
}

TEST(OtherFunctionsTests, CardinalityMapTest) {
    TritSet set(11);

    set[0] = Trit::TRUE;
    set[1] = Trit::UNKNOWN;
    set[2] = Trit::FALSE;
    set[3] = Trit::FALSE;
    set[4] = Trit::UNKNOWN;
    set[5] = Trit::FALSE;
    set[6] = Trit::UNKNOWN;
    set[7] = Trit::UNKNOWN;
    set[8] = Trit::TRUE;
    set[9] = Trit::UNKNOWN;
    set[10] = Trit::FALSE;

    auto a = set.cardinality();

    EXPECT_EQ(a[Trit::TRUE], 2);
    EXPECT_EQ(a[Trit::FALSE], 4);
    EXPECT_EQ(a[Trit::UNKNOWN], 5);
}

TEST(OtherFunctionsTests, LenTest) {
    TritSet set(20);

    set[0] = Trit::TRUE;
    set[1] = Trit::UNKNOWN;
    set[17] = Trit::FALSE;

    EXPECT_EQ(set.length(), 18);
}

TEST(OtherFunctionsTests, TrimTest) {
    TritSet set(7);

    set[0] = Trit::TRUE;
    set[1] = Trit::UNKNOWN;
    set[2] = Trit::FALSE;
    set[3] = Trit::FALSE;
    set[4] = Trit::UNKNOWN;
    set[5] = Trit::TRUE;
    set[6] = Trit::UNKNOWN;

    set.trim(2);
    EXPECT_TRUE(set[2] == Trit::UNKNOWN &&
                set[3] == Trit::UNKNOWN &&
                set[4] == Trit::UNKNOWN &&
                set[5] == Trit::UNKNOWN &&
                set[6] == Trit::UNKNOWN);
}

TEST(MemoryTests, ShrinkMemoryFree) {
    TritSet set(1000);

    set[3] = Trit::TRUE;
    EXPECT_EQ(set.get_count(), 1000);

    set.shrink();
    EXPECT_EQ(set.get_count(), 4);
}

TEST(MemoryTests, ComparingOutOfBound) {
    TritSet set(1000);
    size_t allocLength = set.capacity();

    EXPECT_FALSE(set[2000000000] == Trit::TRUE);
    EXPECT_EQ(allocLength, set.capacity());
}

TEST(MemoryTests, UnknownOutOfBound)
{
    TritSet set(1000);
    size_t allocLength = set.capacity();

    set[1000000000] = Trit::UNKNOWN;
    EXPECT_EQ(allocLength, set.capacity());
}

TEST(MemoryTests, OutOfBoundAllocation) {
    TritSet set(1000);
    size_t allocLength = set.capacity();

    set[1000000000] = Trit::TRUE;
    EXPECT_LT(allocLength, set.capacity());
}
