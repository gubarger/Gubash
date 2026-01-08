// Copyright (c) 2026 Gubarger. All Rights Reserved.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace gubash::utils {
  class ShString {
  public:
    ShString() noexcept;
    ShString(const char* str);
    ShString(const char* str, size_t len);

    ShString(const ShString& other);
    ShString(ShString&& other) noexcept;

    ShString& operator=(const ShString& other);
    ShString& operator=(ShString&& other) noexcept;

    ~ShString() noexcept;

    // Basic opsions.
    void Assign(const char* str, size_t len);
    void Append(char c);
    void Clear() noexcept;
    
    // Access
    const char* Cstr() const noexcept;
    size_t Size() const noexcept;
    bool Empty() const noexcept;

    char operator[](size_t i) const noexcept;

  private:
  bool IsSmall() const noexcept;
  void DestroyLarge() noexcept;

  private:
    static constexpr uint32_t SSO_CAPACITY_ = 23;
 
    union {
      struct {
        char* data_;
        uint32_t capacity_;
      } large_;

      char small_[SSO_CAPACITY_ + 1]; // +1 for '\0'.
    };

    uint32_t size_;
  };
}
