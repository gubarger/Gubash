// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <gtest/gtest.h>

#include "../source/memory/layout.h"
#include "../source/memory/router.h"
#include "../source/memory/arena.h"
#include "../source/memory/slab.h"

class MemoryTest : public ::testing::Test 
{
protected:
  void SetUp() override;    // Called before each test.
  void TearDown() override; // Called after each test.
};

void MemoryTest::SetUp()
{
  gubash::memory::InitMemory();
}

void MemoryTest::TearDown()
{
  // TODO: Here you can add leak checks. I won't do this yet, ok?
}

// Tests
TEST_F(MemoryTest, BasicAllocationDeallocation)
{
  // Test RouterAllocator
  void* ptr1 = gubash::memory::RouterAllocator::Allocate(32);
  ASSERT_NE(ptr1, nullptr) << "Allocation failed for 32 bytes";

  gubash::memory::RouterAllocator::Deallocate(ptr1, 32);

  void* ptr2 = gubash::memory::RouterAllocator::Allocate(64);
  ASSERT_NE(ptr2, nullptr) << "Allocation failed for 64 bytes";

  gubash::memory::RouterAllocator::Deallocate(ptr2, 64);

  void* ptr3 = gubash::memory::RouterAllocator::Allocate(128);
  ASSERT_NE(ptr3, nullptr) << "Allocation failed for 128 bytes";

  gubash::memory::RouterAllocator::Deallocate(ptr3, 128);

  void* ptr4 = gubash::memory::RouterAllocator::Allocate(1024);
  ASSERT_NE(ptr4, nullptr) << "Allocation failed for 1024 bytes";

  gubash::memory::RouterAllocator::Deallocate(ptr4, 1024);
}

// Edge case test.
TEST_F(MemoryTest, BoundaryCases)
{
  // Size 0.
  // void* ptr = gubash::memory::RouterAllocator::Allocate(0);

  // Size > MAX_SIZE (abort).
  // ASSERT_DEATH(gubash::memory::RouterAllocator::Allocate(2000), ".*");

  // The size exactly matches the border.
  void* ptr33 = gubash::memory::RouterAllocator::Allocate(33);
  ASSERT_NE(ptr33, nullptr) << "Allocation failed for 33 bytes";

  gubash::memory::RouterAllocator::Deallocate(ptr33, 33);

  void* ptr65 = gubash::memory::RouterAllocator::Allocate(65);
  ASSERT_NE(ptr65, nullptr) << "Allocation failed for 65 bytes";

  gubash::memory::RouterAllocator::Deallocate(ptr65, 65);
}

// Multiple allocation test.
TEST_F(MemoryTest, MultipleAllocations)
{
  const int count = 10;
  void* pointers[count];

  // Allocate more blocks.
  for (int i = 0; i < count; ++i) 
  {
    pointers[i] = gubash::memory::RouterAllocator::Allocate(32);
    ASSERT_NE(pointers[i], nullptr) << "Allocation failed at iteration " << i;
  }

  // Deallocate (in reverse order).
  for (int i = count - 1; i >= 0; --i) 
  {
    gubash::memory::RouterAllocator::Deallocate(pointers[i], 32);
  }
}

// Test ArenaAllocator
TEST_F(MemoryTest, ArenaAllocator) 
{
  void* ptr1 = gubash::memory::gArena->Allocate(100);
  ASSERT_NE(ptr1, nullptr) << "Arena allocation failed";

  void* ptr2 = gubash::memory::gArena->Allocate(200);
  ASSERT_NE(ptr2, nullptr) << "Second arena allocation failed";

  // Checking that the pointers are different.
  ASSERT_NE(ptr1, ptr2) << "Arena returned same pointer for different allocations";

  gubash::memory::gArena->Reset();

  void* ptr3 = gubash::memory::gArena->Allocate(50);
  ASSERT_NE(ptr3, nullptr) << "Arena allocation failed after reset";
}

// Test SlabAllocator directly.
TEST_F(MemoryTest, SlabAllocatorDirect) 
{
  // Test slab32 with global ptr.
  void* ptr1 = gubash::memory::gSlab32->Allocate();
  ASSERT_NE(ptr1, nullptr) << "Slab32 allocation failed";

  void* ptr2 = gubash::memory::gSlab32->Allocate();
  ASSERT_NE(ptr2, nullptr) << "Second slab32 allocation failed";
  ASSERT_NE(ptr1, ptr2) << "Slab returned same pointer";

  gubash::memory::gSlab32->Deallocate(ptr1);
  gubash::memory::gSlab32->Deallocate(ptr2);
}

// Memory exhaustion test.
TEST_F(MemoryTest, ExhaustionTest) {
  // Exhaustion all blocks in slab32.
  const uint32_t maxAllocations = gubash::memory::SLAB32_COUNT;
  void* pointers[maxAllocations];

  for (uint32_t i = 0; i < maxAllocations; ++i) 
  {
    pointers[i] = gubash::memory::RouterAllocator::Allocate(32);
    ASSERT_NE(pointers[i], nullptr) << "Allocation failed at " << i << "/" << maxAllocations;
  }

  // WARNING: this is abort (exit programm).
  // ASSERT_DEATH(gubash::memory::RouterAllocator::Allocate(32), ".*");

  // Delete all.
  for (uint32_t i = 0; i < maxAllocations; ++i) 
  {
    gubash::memory::RouterAllocator::Deallocate(pointers[i], 32);
  }

  void* ptr = gubash::memory::RouterAllocator::Allocate(32);
  ASSERT_NE(ptr, nullptr) << "Allocation failed after freeing all blocks";
  
  gubash::memory::RouterAllocator::Deallocate(ptr, 32);
}

// Test alignment.
TEST_F(MemoryTest, AlignmentTest) 
{
  // Verify that the pointers are aligned.
  for (size_t size : {32, 64, 128, 1024}) 
  {
    void* ptr = gubash::memory::RouterAllocator::Allocate(size);
    ASSERT_NE(ptr, nullptr) << "Allocation failed for size " << size;

    uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
    const uintptr_t alignment = 8;

    EXPECT_EQ(address % alignment, 0u) << "Pointer " << ptr << " is not aligned to " << alignment 
      << " bytes for allocation size " << size;

    gubash::memory::RouterAllocator::Deallocate(ptr, size);
  }
}

// Test reuse memory
TEST_F(MemoryTest, ReuseTest)
{
  std::set<void*> allocatedPointers;

  for (int iteration = 0; iteration < 3; ++iteration) 
  {
    void* ptr = gubash::memory::RouterAllocator::Allocate(64);
    ASSERT_NE(ptr, nullptr) << "Allocation failed at iteration " << iteration;

    allocatedPointers.insert(ptr);
    
    gubash::memory::RouterAllocator::Deallocate(ptr, 64);
  }

  EXPECT_LE(allocatedPointers.size(), 3u) 
    << "Expected memory reuse, but got too many unique pointers";
}
