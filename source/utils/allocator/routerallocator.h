// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include "slaballocator.h"

namespace gubash::utils::allocator {
  class RouterAllocator {
  public:
    RouterAllocator() noexcept = default;
    RouterAllocator(RouterAllocator &&) noexcept = default;
    RouterAllocator(const RouterAllocator &) noexcept = delete;
    RouterAllocator &operator=(RouterAllocator &&) noexcept = default;
    RouterAllocator &operator=(const RouterAllocator &) noexcept = delete;
    ~RouterAllocator() noexcept = default;

    static void* Allocate(size_t size) noexcept;
    static void Deallocate(void* ptr, size_t size) noexcept;

  private:
    static inline SlabAllocator slab32_{32, 1024};
    static inline SlabAllocator slab64_{64, 512};
    static inline SlabAllocator slab128_{128, 256};
  };
}
