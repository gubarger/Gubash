// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <unistd.h>
#include <cstdio>

#include "shell.h"
#include "utils/string.h"

namespace gubash::core {
  Shell::Shell()
  {
  }

  short Shell::Start()
  {
    gubash::utils::ShString str("hello");
    printf("[%s]\n", str);
    ReplLoop();
    return EXIT_SUCCESS;
  }

  void Shell::ReplLoop()
  {
    while (true)
    {
    }
  }
}
