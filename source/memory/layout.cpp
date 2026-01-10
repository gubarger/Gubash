// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstddef>
#include <cstdint>
#include <new>

#include "layout.h"
#include "router.h"

namespace gubash::memory
{
  // Main static buffer. 
  // TODO: [[gnu::no_destroy]] - to prevent static memory from being freed when the program terminates.
  [[gnu::no_destroy]] static uint8_t gMemory[ // Automatic storage.
    ARENA_SIZE +

    SLAB32_COUNT    * 32 +
    SLAB64_COUNT    * 64 +
    SLAB128_COUNT   * 128 +
    SLAB1024_COUNT  * 1024 +

    // 1 bit per block.
    ((SLAB32_COUNT    + 7) >> 3) +
    ((SLAB64_COUNT    + 7) >> 3) +
    ((SLAB128_COUNT   + 7) >> 3) +
    ((SLAB1024_COUNT  + 7) >> 3)
  ];

  // Global pointers.
  ArenaAllocator* gArena = nullptr;

  SlabAllocator* gSlab32    = nullptr;
  SlabAllocator* gSlab64    = nullptr;
  SlabAllocator* gSlab128   = nullptr;
  SlabAllocator* gSlab1024  = nullptr;

  void InitMemory() noexcept
  {
    uint8_t* p = gMemory;

    auto alignPtr = [](uint8_t*& p, size_t align) 
    {
      uintptr_t x = reinterpret_cast<uintptr_t>(p);

      x = (x + align - 1) & ~(align - 1);
      p = reinterpret_cast<uint8_t*>(x);
    };

    // Arena
    uint8_t* arenaMemory = p; // Raw memory for ArenaAllocator.
    p += sizeof(ArenaAllocator);

    gArena = new (arenaMemory) ArenaAllocator(p, ARENA_SIZE); // Placement new.
    p += ARENA_SIZE;
  
    // Slab32
    alignPtr(p, alignof(void*));
    uint8_t* slab32Arena = p;
    p += SLAB32_COUNT * 32;

    uint8_t* slab32Bitmap = p;
    p += (SLAB32_COUNT + 7) >> 3;

    uint8_t* slab32Memory = p; // Raw memory for SlabAllocator.
    p += sizeof(SlabAllocator);

    gSlab32 = new (slab32Memory) SlabAllocator(slab32Arena, 32, SLAB32_COUNT, slab32Bitmap);

    // Slab64
    alignPtr(p, alignof(void*));
    uint8_t* slab64Arena = p;
    p += SLAB64_COUNT * 64;

    uint8_t* slab64Bitmap = p;
    p += (SLAB64_COUNT + 7) >> 3;

    uint8_t* slab64Memory = p;
    p += sizeof(SlabAllocator);

    gSlab64 = new (slab64Memory) SlabAllocator(slab64Arena, 64, SLAB64_COUNT, slab64Bitmap);

    // Slab128
    alignPtr(p, alignof(void*));
    uint8_t* slab128Arena = p;
    p += SLAB128_COUNT * 128;

    uint8_t* slab128Bitmap = p;
    p += (SLAB128_COUNT + 7) >> 3;

    uint8_t* slab128Memory = p;
    p += sizeof(SlabAllocator);

    gSlab128 = new (slab128Memory) SlabAllocator(slab128Arena, 128, SLAB128_COUNT, slab128Bitmap);

    // Slab1024
    alignPtr(p, alignof(void*));
    uint8_t* slab1024Arena = p;
    p += SLAB1024_COUNT * 1024;

    uint8_t* slab1024Bitmap = p;
    p += (SLAB1024_COUNT + 7) >> 3;

    uint8_t* slab1024Memory = p;
    p += sizeof(SlabAllocator);

    gSlab1024 = new (slab1024Memory) SlabAllocator(slab1024Arena, 1024, SLAB1024_COUNT, slab1024Bitmap);

    // Hookup.
    RouterAllocator::Init();
  }
}
