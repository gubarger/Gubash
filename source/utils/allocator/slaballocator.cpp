// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include "routerallocator.h"

namespace gubash::utils::allocator {
  SlabAllocator::SlabAllocator(size_t blockSize, size_t blockCount)
    : blockSize_{blockSize < sizeof(BlockHeader) ? sizeof(BlockHeader) : blockSize},
      blockCount_{blockCount},
      arena_{nullptr},
      freeList_{nullptr},
      usedBlocks_{blockCount}
  {
    arena_ = new uint8_t[blockSize_ * blockCount_]; // A large piece of memory.

    // Build free-list.
    for (size_t i = 0; i < blockCount_; ++i)
    {
      auto* block = reinterpret_cast<BlockHeader*>(arena_ + i * blockSize_);

      block->next_ = freeList_;
      freeList_ = block;
    }
  }

  SlabAllocator::~SlabAllocator() noexcept
  {
    delete[] arena_;
  }

  void* SlabAllocator::Allocate() noexcept
  {
    if (!freeList_) 
    {
      return nullptr; // slab is overcrowded.
    }

    BlockHeader* block = freeList_;
    freeList_ = block->next_;

    size_t index = (reinterpret_cast<uint8_t*>(block) - arena_) / blockSize_;

    usedBlocks_.Set(index);

    return block;
  }

  void SlabAllocator::Deallocate(void* ptr) noexcept
  {
    if (!ptr)
    {
      return;
    }

    auto* block = reinterpret_cast<BlockHeader*>(ptr);
    size_t index = (reinterpret_cast<uint8_t*>(block) - arena_) / blockSize_;

    if (!usedBlocks_.Get(index))
    {
      static_assert("Double free detected.");
    }

    usedBlocks_.Clear(index);

    block->next_ = freeList_;
    freeList_ = block;
  }
}
