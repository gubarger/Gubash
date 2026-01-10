// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstdio>

#include "utils/fgstring.h"
#include "memory/layout.h"

int main()
{
  gubash::memory::InitMemory();
  gubash::utils::Fgstring str;

  str.Append('Y');
  str.Append("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeb", 900);

  printf("size=%zu, empty=%d, str='%s'\n", str.Size(), str.Empty(), str.Cstr());
}
