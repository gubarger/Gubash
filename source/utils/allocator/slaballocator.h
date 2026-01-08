// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include "bitmap.h"

namespace gubash::utils::allocator {
  class SlabAllocator {
  public:
    SlabAllocator(size_t blockSize, size_t blockCount);
    SlabAllocator(SlabAllocator &&) noexcept = default;
    SlabAllocator(const SlabAllocator &) noexcept = delete;
    SlabAllocator &operator=(SlabAllocator &&) noexcept = default;
    SlabAllocator &operator=(const SlabAllocator &) noexcept = delete;
    ~SlabAllocator() noexcept;

    void* Allocate() noexcept;
    void Deallocate(void* ptr) noexcept;

  private:
    struct BlockHeader
    {
      BlockHeader* next_;
    };

    size_t blockSize_;
    size_t blockCount_;

    uint8_t* arena_;
    BlockHeader* freeList_;
    Bitmap usedBlocks_; // bitmap for tracking busyness.
  };
}
