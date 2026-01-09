// Copyright (c) 2026 Gubarger. All Rights Reserved.

#pragma once

#include <cstddef>
#include <cstdint>

namespace gubash::memory 
{
  class Bitmap 
  {
  public:
    Bitmap() noexcept = default;
    Bitmap(uint32_t bits, uint8_t* st) noexcept;

    void Set(uint32_t i) noexcept;
    void Clear(uint32_t i) noexcept;
    bool Test(uint32_t i) const noexcept;

  private:
    uint8_t* data_;
  };

  inline Bitmap::Bitmap(uint32_t bits, uint8_t* st) noexcept : data_{st}
  {
    uint32_t bytes = (bits + 7) >> 3;

    for (uint32_t i = 0; i < bytes; ++i) 
    {
      data_[i] = 0;
    }
  }

  inline void Bitmap::Set(uint32_t i) noexcept
  {
    data_[i >> 3] |= (1u << (i & 7));
  }

  inline void Bitmap::Clear(uint32_t i) noexcept
  {
    data_[i >> 3] &= ~(1u << (i & 7));
  }

  inline bool Bitmap::Test(uint32_t i) const noexcept
  {
    return data_[i >> 3] & (1u << (i & 7));
  }
}
