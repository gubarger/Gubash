// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstdlib>

#include "slab.h"

namespace gubash::memory 
{
  SlabAllocator::SlabAllocator(uint8_t* arena, uint32_t blockSize, uint32_t blockCount, uint8_t* bitmapSt) noexcept
    : arena_{arena},
      blockSize_{blockSize < sizeof(Block) ? sizeof(Block) : blockSize},
      blockCount_{blockCount},
      free_{nullptr},
      used_{blockCount, bitmapSt}
  {
    for (uint32_t i = 0; i < blockCount_; ++i) 
    {
      auto* n = reinterpret_cast<Block*>(arena_ + i * blockSize_);

      n->next = free_;
      free_ = n;
    }
  }

  void* SlabAllocator::Allocate() noexcept
  {
    if (!free_)
    {
      std::abort();
    }

    Block* n = free_;
    free_ = n->next;

    uint32_t i = (reinterpret_cast<uint8_t*>(n) - arena_) / blockSize_;

    used_.Set(i);

    return n;
  }

  void SlabAllocator::Deallocate(void* ptr) noexcept
  {
    if (!ptr)
    {
      return;
    }

    Block* n = static_cast<Block*>(ptr);
    uint32_t i = (reinterpret_cast<uint8_t*>(ptr) - arena_) / blockSize_;

    used_.Clear(i);

    free_ = n;
  }
}
