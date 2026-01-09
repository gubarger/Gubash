// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstdlib>

#include "arena.h"

namespace gubash::memory 
{
  ArenaAllocator::ArenaAllocator(uint8_t* buff, size_t size) noexcept : base_{buff}, capacity_{size}, offset_{0}
  {
  }

  ArenaAllocator::~ArenaAllocator() noexcept
  {
    // WARNING: For debugging purposes only. No delete/free should be here.
  }

  void* ArenaAllocator::Allocate(size_t size, size_t align) noexcept
  {
    size_t current = (offset_ + (align - 1)) & ~(align - 1);

    if (current + size > capacity_)
    {
      std::abort();
    }

    void* ptr = base_ + current;
    offset_ = current + size;

    return ptr;
  }

  void ArenaAllocator::Reset() noexcept
  {
    offset_ = 0;
  }

  size_t ArenaAllocator::Used() const noexcept
  {
    return offset_;
  }
}
