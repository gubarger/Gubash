// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "../source/utils/fgstring.h"
#include "../source/memory/layout.h"

using namespace gubash::utils;

class FgstringTest : public ::testing::Test
{
protected:
  void SetUp() override;
};

void FgstringTest::SetUp()
{
  gubash::memory::InitMemory();
}

TEST_F(FgstringTest, DefaultConstructor) 
{
  Fgstring str;

  EXPECT_TRUE(str.Empty());
  EXPECT_EQ(str.Size(), 0u);
  EXPECT_STREQ(str.Cstr(), "");
  EXPECT_TRUE(str.IsSmall());
}

TEST_F(FgstringTest, SmallStringOperations) 
{
  Fgstring str;

  for (int i = 0; i < 10; ++i)
  {
    str.Append('a' + i);
  }
 
  EXPECT_FALSE(str.Empty());
  EXPECT_EQ(str.Size(), 10u);
  EXPECT_STREQ(str.Cstr(), "abcdefghij");
  EXPECT_TRUE(str.IsSmall());
}

TEST_F(FgstringTest, SmallToMediumTransition) 
{
  Fgstring str;

  size_t ssoCapacity = sizeof(MediumLayout) - 1;
 
  for (size_t i = 0; i < ssoCapacity; ++i) 
  {
    str.Append('x');
  }
 
  EXPECT_TRUE(str.IsSmall());
  EXPECT_EQ(str.Size(), ssoCapacity);
 
  str.Append('y');
 
  EXPECT_FALSE(str.IsSmall());
  EXPECT_EQ(str.Size(), ssoCapacity + 1);
 
  std::string expected(ssoCapacity, 'x');
  expected += 'y';
  EXPECT_STREQ(str.Cstr(), expected.c_str());
}

TEST_F(FgstringTest, ConstructorFromCString) 
{
  const char* testStr = "Hello, World!";
  Fgstring str(testStr);

  EXPECT_EQ(str.Size(), strlen(testStr));
  EXPECT_STREQ(str.Cstr(), testStr);
 
  Fgstring empty("");
  EXPECT_TRUE(empty.Empty());
  EXPECT_STREQ(empty.Cstr(), "");

  Fgstring fromNull(nullptr);
  EXPECT_TRUE(fromNull.Empty());
}

TEST_F(FgstringTest, CopyConstructor) 
{
  // Small string
  {
    Fgstring original("Small");
    Fgstring copy(original);

    EXPECT_EQ(original.Size(), copy.Size());
    EXPECT_STREQ(original.Cstr(), copy.Cstr());
    EXPECT_TRUE(copy.IsSmall());

    original.Append('X');
    EXPECT_STRNE(original.Cstr(), copy.Cstr());
  }

  // Medium string
  {
    Fgstring original;
    size_t ssoCapacity = sizeof(MediumLayout) - 1;

    for (size_t i = 0; i < ssoCapacity + 10; ++i) 
    {
      original.Append('m');
    }

    EXPECT_FALSE(original.IsSmall());
    Fgstring copy(original);

    EXPECT_EQ(original.Size(), copy.Size());
    EXPECT_STREQ(original.Cstr(), copy.Cstr());
    EXPECT_FALSE(copy.IsSmall());
  }
}

TEST_F(FgstringTest, MoveConstructor) 
{
  // Small string
  {
    Fgstring original("Hello");
    size_t originalSize = original.Size();
    const char* originalCstr = original.Cstr();

    Fgstring moved(std::move(original));

    EXPECT_EQ(moved.Size(), originalSize);
    EXPECT_STREQ(moved.Cstr(), originalCstr);
    EXPECT_TRUE(original.Empty());  // original must null
    EXPECT_STREQ(original.Cstr(), "");
  }

  // Medium string
  {
    Fgstring original;
    size_t ssoCapacity = sizeof(MediumLayout) - 1;

    for (size_t i = 0; i < ssoCapacity + 20; ++i) 
    {
      original.Append('M');
    }

    size_t originalSize = original.Size();
    const char* originalCstr = original.Cstr();

    Fgstring moved(std::move(original));

    EXPECT_EQ(moved.Size(), originalSize);
    EXPECT_STREQ(moved.Cstr(), originalCstr);
    EXPECT_TRUE(original.Empty());
    EXPECT_TRUE(original.IsSmall());  // small
  }
}

TEST_F(FgstringTest, CopyAssignment)
{
  Fgstring str1("First");
  Fgstring str2("Second");

  str1 = str2;

  EXPECT_EQ(str1.Size(), str2.Size());
  EXPECT_STREQ(str1.Cstr(), str2.Cstr());

  // Self-assignment
  str1 = str1;
  EXPECT_STREQ(str1.Cstr(), "Second");
}

TEST_F(FgstringTest, MoveAssignment) 
{
  Fgstring str1;
  Fgstring str2("Hello World");

  size_t str2Size = str2.Size();
  const char* str2Cstr = str2.Cstr();

  str1 = std::move(str2);

  EXPECT_EQ(str1.Size(), str2Size);
  EXPECT_STREQ(str1.Cstr(), str2Cstr);
  EXPECT_TRUE(str2.Empty());
}

TEST_F(FgstringTest, AppendString) 
{
  Fgstring str("Hello");
  const char* toAppend = ", World!";

  str.Append(toAppend, strlen(toAppend));

  EXPECT_STREQ(str.Cstr(), "Hello, World!");
  EXPECT_EQ(str.Size(), strlen("Hello, World!"));
}

TEST_F(FgstringTest, LargeAppend) 
{
  Fgstring str;

  // str > SSO capacity
  std::string large(1000, 'A');
  str.Append(large.c_str(), large.size());

  EXPECT_EQ(str.Size(), 1000u);
  EXPECT_FALSE(str.IsSmall());

  // Check.
  for (size_t i = 0; i < 1000; ++i) 
  {
    EXPECT_EQ(str.Cstr()[i], 'A');
  }
 
  EXPECT_EQ(str.Cstr()[1000], '\0');
}

TEST_F(FgstringTest, MultipleAppends) 
{
  Fgstring str;

  str.Append('H');
  str.Append('e');
  str.Append("ll", 2);
  str.Append("o, ", 2);
  str.Append("World!", 6);

  EXPECT_STREQ(str.Cstr(), "Hello, World!");
  EXPECT_EQ(str.Size(), 13u);
}

TEST_F(FgstringTest, EmptyAppend) 
{
  Fgstring str("Hello");

  str.Append(nullptr, 0);
  str.Append("", 0);

  EXPECT_STREQ(str.Cstr(), "Hello");
  EXPECT_EQ(str.Size(), 5u);
}

TEST_F(FgstringTest, CapacityGrowth) 
{
  Fgstring str;

  for (int i = 0; i < 20; ++i) 
  {
    str.Append('a');
  }

  EXPECT_TRUE(str.IsSmall());

  for (int i = 0; i < 100; ++i) 
  {
    str.Append('b');
  }

  EXPECT_FALSE(str.IsSmall());
  EXPECT_EQ(str.Size(), 120u);

  const char* cstr = str.Cstr();
 
  for (int i = 0; i < 20; ++i) 
  {
    EXPECT_EQ(cstr[i], 'a');
  }
  for (int i = 0; i < 100; ++i) 
  {
    EXPECT_EQ(cstr[20 + i], 'b');
  }
}

TEST_F(FgstringTest, StressTest) 
{
  Fgstring str;

  for (int i = 0; i < 10000; ++i) 
  {
    str.Append('0' + (i % 10));
  }

  EXPECT_EQ(str.Size(), 10000u);

  const char* cstr = str.Cstr();
 
  for (int i = 0; i < 10000; ++i) 
  {
    EXPECT_EQ(cstr[i], '0' + (i % 10));
  }
}

TEST_F(FgstringTest, MemoryLeakCheck) 
{
  for (int i = 0; i < 100; ++i) 
  {
    Fgstring str;
 
    for (int j = 0; j < 100; ++j) 
    {
      str.Append('x');
    }

    Fgstring copy = str;
    Fgstring moved = std::move(str);

    EXPECT_EQ(copy.Size(), 100u);
    EXPECT_TRUE(str.Empty());
  }
}

TEST_F(FgstringTest, ComparisonWithStdString) 
{
  std::string stdStr;
  Fgstring fgStr;

  const char* testData[] = {
    "Hello",
    "World",
    "This is a longer string",
    "Another test string with more content",
    "A"
  };

  for (const char* test : testData) 
  {
    stdStr = test;
    fgStr = Fgstring(test);

    EXPECT_EQ(fgStr.Size(), stdStr.size());
    EXPECT_STREQ(fgStr.Cstr(), stdStr.c_str());
  }
}
