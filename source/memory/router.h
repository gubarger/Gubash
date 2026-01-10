// Copyright (c) 2026 Gubarger. All Rights Reserved.

#pragma once

#include <cstddef>
#include <cstdlib>

#include "slab.h"

namespace gubash::memory 
{
  class RouterAllocator 
  {
  public:
    ~RouterAllocator() noexcept = default;

    static inline size_t Normalize(size_t size) noexcept;

    static void* Allocate(size_t size) noexcept;
    static void Deallocate(void* ptr, size_t size) noexcept;

    static void Init() noexcept;

  private:
    static inline SlabAllocator* slab32_;
    static inline SlabAllocator* slab64_;
    static inline SlabAllocator* slab128_;
    static inline SlabAllocator* slab1024_;
  };

  inline size_t RouterAllocator::Normalize(size_t size) noexcept
  {
    if (size <= 32)
    {
      return 32;
    }

    if (size <= 64)
    {
      return 64;
    }

    if (size <= 128)
    {
      return 128;
    }

    if (size <= 1024)
    {
      return 1024;
    }

    std::abort();
  }
}
