// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstdlib>

#pragma once

namespace gubash::core {
  class Shell {
  public:
    explicit Shell();
    Shell(Shell &&) noexcept = default;
    Shell(const Shell &) noexcept = delete;
    Shell &operator=(Shell &&) noexcept = default;
    Shell &operator=(const Shell &) noexcept = delete;
    ~Shell() noexcept = default;

    short Start();

  private:
    void ReplLoop();
  };
}
