// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstddef>

#if defined(__x86_64__) || defined(_M_X64)
  #define GUBASH_ARCH_X64 1
  #define GUBASH_PTR_SIZE 8
#elif defined(__i386__) || defined(_M_IX86)
  #define GUBASH_ARCH_X86 1
  #define GUBASH_PTR_SIZE 4
#else
  #error "Unsupported architecture."
#endif
