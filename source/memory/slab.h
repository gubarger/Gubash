// Copyright (c) 2026 Gubarger. All Rights Reserved.

#pragma once

#include <cstddef>
#include <cstdint>

#include "bitmap.h"

namespace gubash::memory 
{
  class SlabAllocator 
  {
  public:
    SlabAllocator(uint8_t* arena, uint32_t blockSize, uint32_t blockCount, uint8_t* bitmapSt) noexcept;
    ~SlabAllocator() noexcept = default;

    void* Allocate() noexcept;
    void Deallocate(void* ptr) noexcept;

  private:
    struct Block 
    {
      Block* next;
    };

    uint8_t* arena_;
    uint32_t blockSize_;
    uint32_t blockCount_;

    Block* free_;
    Bitmap used_;
  };
}
