// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstddef>

#include "routerallocator.h"

namespace gubash::utils::allocator {
  void* RouterAllocator::Allocate(size_t size) noexcept
  {
    if (size <= 32)
    {
      return slab32_.Allocate();
    }

    if (size <= 64)
    {
      return slab64_.Allocate();
    }

    if (size <= 32)
    {
      return slab128_.Allocate();
    }

    return nullptr; // TODO: or fallback.
  }

  void RouterAllocator::Deallocate(void* ptr, size_t size) noexcept
  {
    if (size <= 32)
    {
      return slab32_.Deallocate(ptr);
    }

    if (size <= 64)
    {
      return slab64_.Deallocate(ptr);
    }

    if (size <= 32)
    {
      return slab128_.Deallocate(ptr);
    }
  }
}
