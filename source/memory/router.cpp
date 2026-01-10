// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstdlib>

#include "router.h"
#include "layout.h"

namespace gubash::memory 
{
  void* RouterAllocator::Allocate(size_t size) noexcept
  {
    size = Normalize(size);

    if (size == 32)
    {
      return slab32_->Allocate();
    }

    if (size == 64)
    {
      return slab64_->Allocate();
    }

    if (size == 128)
    {
      return slab128_->Allocate();
    }

    if (size == 1024)
    {
      return slab1024_->Allocate();
    }

    std::abort();
  }

  void RouterAllocator::Deallocate(void* ptr, size_t size) noexcept
  {
    size = Normalize(size);

    if (size == 32)
    {
      return slab32_->Deallocate(ptr);
    }

    if (size == 64)
    {
      return slab64_->Deallocate(ptr);
    }

    if (size == 128)
    {
      return slab128_->Deallocate(ptr);
    }

    if (size == 1024)
    {
      return slab1024_->Deallocate(ptr);
    }

    std::abort();
  }

  void RouterAllocator::Init() noexcept
  {
    slab32_   = gSlab32;
    slab64_   = gSlab64;
    slab128_  = gSlab128;
    slab1024_ = gSlab1024;
  }
}
