// Copyright (c) 2026 Gubarger. All Rights Reserved.

#pragma once

#include <cstddef>
#include <cstdint>

namespace gubash::memory 
{
  class ArenaAllocator
  {
  public:
    ArenaAllocator(uint8_t* buff, size_t size) noexcept;
    ~ArenaAllocator() noexcept;

    void* Allocate(size_t size, size_t align = alignof(void*)) noexcept;
    
    void Reset() noexcept;
    size_t Used() const noexcept;

  private:
    uint8_t* base_;
    size_t capacity_;
    size_t offset_;
  };
  
}
