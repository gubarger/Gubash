// Copyright (c) 2026 Gubarger. All Rights Reserved.

#pragma once

#include <cstddef>
#include <cstdint>

#include "arena.h"
#include "slab.h"

namespace gubash::memory 
{
  // Constants
  constexpr size_t ARENA_SIZE       = 256 * 1024; // 256 KB per command.

  constexpr uint32_t SLAB32_COUNT   = 1024;
  constexpr uint32_t SLAB64_COUNT   = 512;
  constexpr uint32_t SLAB128_COUNT  = 256;
  constexpr uint32_t SLAB1024_COUNT = 64;

  // Globals
  extern ArenaAllocator* gArena;

  extern SlabAllocator* gSlab32;
  extern SlabAllocator* gSlab64;
  extern SlabAllocator* gSlab128;
  extern SlabAllocator* gSlab1024;

  void InitMemory() noexcept;
}
