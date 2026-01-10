// Copyright (c) 2026 Gubarger. All Rights Reserved.

#pragma once

#include <cstdint>
#include <cstring>

#include "../core/arch.h"

namespace gubash::utils
{
  enum class Category : uint8_t 
  {
    Small = 0,
    Medium = 1,
    Large = 2 // NOTE: So far reserved.
  };

  struct MediumLayout 
  {
    char* data;
    uint32_t size;
    uint32_t capacity;
  };

  class Fgstring 
  {
  public:
    Fgstring() noexcept;
    Fgstring(const char* str) noexcept;
    Fgstring(const Fgstring& other) noexcept;
    Fgstring(Fgstring&& other) noexcept;

    Fgstring& operator=(const Fgstring& other) noexcept;
    Fgstring& operator=(Fgstring&& other) noexcept;

    ~Fgstring() noexcept;

    void Append(char c) noexcept;
    void Append(const char* str, uint32_t len) noexcept;

    const char* Cstr() const noexcept;
    size_t Size() const noexcept;
    bool Empty() const noexcept;

    bool IsSmall() const noexcept;

  private:
    void GrowToMedium(uint32_t minCap) noexcept;
    void DestroyMedium() noexcept;
    uint32_t NextCapacity(uint32_t min) const noexcept;

  private:
    // For x86 = 11, x64 = 15.
    static constexpr size_t SSO_CAPACITY = sizeof(MediumLayout) - 1; // -1 for '\0'

    Category category_;

    union
    {
      char small_[sizeof(MediumLayout)];
      MediumLayout medium_;
    };

    uint8_t small_size_;
  };
}
