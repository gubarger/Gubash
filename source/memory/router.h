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

    static void* Allocate(size_t size) noexcept;
    static void Deallocate(void* ptr, size_t size) noexcept;

    static void Init() noexcept;

  private:
    static inline SlabAllocator* slab32_;
    static inline SlabAllocator* slab64_;
    static inline SlabAllocator* slab128_;
    static inline SlabAllocator* slab1024_;
  };
}
