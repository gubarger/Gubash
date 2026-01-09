// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include "memory/layout.h"
#include "memory/router.h"

int main() {
  gubash::memory::InitMemory();

  void* a = gubash::memory::RouterAllocator::Allocate(32);
  gubash::memory::RouterAllocator::Deallocate(a, 32);

  void* b = gubash::memory::gArena->Allocate(64);
  gubash::memory::gArena->Reset();

  return 0;
}
