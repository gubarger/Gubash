// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <gtest/gtest.h>

#include <cstdint>

#include "../source/memory/layout.h"
#include "../source/memory/router.h"
#include "../source/memory/arena.h"
#include "../source/memory/slab.h"

using namespace gubash::memory;

class MemoryTest : public ::testing::Test 
{
protected:
  void SetUp() override;
  void TearDown() override;
};

void MemoryTest::SetUp()
{
  gubash::memory::InitMemory();
}

void MemoryTest::TearDown()
{
  if (gArena)
  {
    gArena->Reset();
  }
}

TEST_F(MemoryTest, ArenaBasicAllocation) 
{
  ASSERT_NE(gArena, nullptr);

  void* ptr1 = gArena->Allocate(100);
  void* ptr2 = gArena->Allocate(200);

  EXPECT_NE(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_NE(ptr1, ptr2);

  // Check: within the arena?
  uint8_t* base = reinterpret_cast<uint8_t*>(gArena) + sizeof(ArenaAllocator);
  EXPECT_GE(ptr1, base);
  EXPECT_LT(ptr1, base + ARENA_SIZE);

  // Write and read data.
  int* intPtr = static_cast<int*>(ptr1);
  *intPtr = 42;
  EXPECT_EQ(*intPtr, 42);
}

TEST_F(MemoryTest, ArenaAlignment) 
{
  void* ptr1 = gArena->Allocate(1, 1);
  void* ptr2 = gArena->Allocate(1, 16);
  void* ptr3 = gArena->Allocate(1, 64);

  EXPECT_NE(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_NE(ptr3, nullptr);

  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr2) % 16, 0u);
  EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr3) % 64, 0u);
}

TEST_F(MemoryTest, ArenaReset) 
{
  size_t initialUsed = gArena->Used();

  void* ptr1 = gArena->Allocate(1000);
  EXPECT_GT(gArena->Used(), initialUsed);

  gArena->Reset();
  EXPECT_EQ(gArena->Used(), 0u);

  void* ptr2 = gArena->Allocate(500);
  EXPECT_NE(ptr2, nullptr);
}

TEST_F(MemoryTest, Slab32Allocation) 
{
  // Slab32
  void* blocks[SLAB32_COUNT];
 
  for (uint32_t i = 0; i < SLAB32_COUNT; ++i) 
  {
    blocks[i] = RouterAllocator::Allocate(32);
    EXPECT_NE(blocks[i], nullptr);
 
    // Check: can write the data?
    memset(blocks[i], i % 256, 32);
  }

  for (uint32_t i = 0; i < SLAB32_COUNT; ++i) 
  {
    RouterAllocator::Deallocate(blocks[i], 32);
  }
}

TEST_F(MemoryTest, Slab64Allocation) 
{
  void* blocks[SLAB64_COUNT];

  for (uint32_t i = 0; i < SLAB64_COUNT; ++i) 
  {
    blocks[i] = RouterAllocator::Allocate(64);
    EXPECT_NE(blocks[i], nullptr);

    int* data = static_cast<int*>(blocks[i]);
    *data = i * 10;
    EXPECT_EQ(*data, i * 10);
  }

  for (uint32_t i = 0; i < SLAB64_COUNT; ++i) 
  {
    RouterAllocator::Deallocate(blocks[i], 64);
  }
}

TEST_F(MemoryTest, RouterAllocatorSizeNormalization) 
{
  EXPECT_EQ(RouterAllocator::Normalize(1), 32u);
  EXPECT_EQ(RouterAllocator::Normalize(32), 32u);
  EXPECT_EQ(RouterAllocator::Normalize(33), 64u);
  EXPECT_EQ(RouterAllocator::Normalize(64), 64u);
  EXPECT_EQ(RouterAllocator::Normalize(65), 128u);
  EXPECT_EQ(RouterAllocator::Normalize(128), 128u);
  EXPECT_EQ(RouterAllocator::Normalize(129), 1024u);
  EXPECT_EQ(RouterAllocator::Normalize(1024), 1024u);

  // TODO: Implementation of a large amount of data has not been implemented at the moment.
  // Now - abort.
  EXPECT_DEATH(RouterAllocator::Normalize(1025), "");
}

TEST_F(MemoryTest, MixedAllocations) 
{
  void* ptr32 = RouterAllocator::Allocate(10);    // 10 -> 32
  void* ptr64 = RouterAllocator::Allocate(50);    // 50 -> 64
  void* ptr128 = RouterAllocator::Allocate(100);  // 100 -> 128
  void* ptr1024 = RouterAllocator::Allocate(500); // 500 -> 1024

  EXPECT_NE(ptr32, nullptr);
  EXPECT_NE(ptr64, nullptr);
  EXPECT_NE(ptr128, nullptr);
  EXPECT_NE(ptr1024, nullptr);

  // Check: any pointers?
  EXPECT_NE(ptr32, ptr64);
  EXPECT_NE(ptr32, ptr128);
  EXPECT_NE(ptr32, ptr1024);

  RouterAllocator::Deallocate(ptr32, 10);
  RouterAllocator::Deallocate(ptr64, 50);
  RouterAllocator::Deallocate(ptr128, 100);
  RouterAllocator::Deallocate(ptr1024, 500);
}

TEST_F(MemoryTest, ReuseDeallocatedBlocks) 
{
  void* ptr1 = RouterAllocator::Allocate(32);
  void* ptr2 = RouterAllocator::Allocate(32);

  int* p1 = static_cast<int*>(ptr1);
  int* p2 = static_cast<int*>(ptr2);
  *p1 = 0xDEADBEEF;
  *p2 = 0xCAFEBABE;

  RouterAllocator::Deallocate(ptr1, 32);
  RouterAllocator::Deallocate(ptr2, 32);

  void* ptr3 = RouterAllocator::Allocate(32);
  void* ptr4 = RouterAllocator::Allocate(32);

  int* p3 = static_cast<int*>(ptr3);
  int* p4 = static_cast<int*>(ptr4);
  *p3 = 42;
  *p4 = 24;

  EXPECT_EQ(*p3, 42);
  EXPECT_EQ(*p4, 24);

  RouterAllocator::Deallocate(ptr3, 32);
  RouterAllocator::Deallocate(ptr4, 32);
}

TEST_F(MemoryTest, SlabExhaustion) 
{
  std::vector<void*> blocks;

  for (uint32_t i = 0; i < SLAB32_COUNT; ++i) 
  {
    void* ptr = RouterAllocator::Allocate(32);
    EXPECT_NE(ptr, nullptr);
    blocks.push_back(ptr);
  }
 
  // abort.
  EXPECT_DEATH(RouterAllocator::Allocate(32), "");

  for (void* ptr : blocks) 
  {
    RouterAllocator::Deallocate(ptr, 32);
  }
}

TEST_F(MemoryTest, MemoryCorruptionDetection) 
{
#ifdef DEBUG
  void* validPtr = RouterAllocator::Allocate(32);
 
  // Create incorrect pointer.
  uint8_t* invalidPtr = reinterpret_cast<uint8_t*>(validPtr) - 100;

  // abort.
  EXPECT_DEATH(RouterAllocator::Deallocate(invalidPtr, 32), "");

  RouterAllocator::Deallocate(validPtr, 32);
#endif
}
