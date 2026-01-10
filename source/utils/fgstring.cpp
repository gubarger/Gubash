// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include "fgstring.h"
#include "../memory/router.h"

namespace gubash::utils
{
  Fgstring::Fgstring() noexcept : category_(Category::Small), small_size_(0)
  {
    small_[0] = '\0'; // Small str is default.
  }

  Fgstring::Fgstring(const char* str) noexcept : Fgstring()
  {
    if (!str)
    {
      return;
    }

    Append(str, static_cast<uint32_t>(std::strlen(str)));
  }

  Fgstring::Fgstring(const Fgstring& other) noexcept 
    : category_(other.category_), small_size_(other.small_size_)
  {
    if (other.IsSmall())
    {
      std::memcpy(small_, other.small_, small_size_ + 1);
    }
  }

  Fgstring::Fgstring(Fgstring&& other) noexcept 
    : category_(other.category_), small_size_(other.small_size_)
  {
    if (other.IsSmall())
    {
      std::memcpy(small_, other.small_, small_size_ + 1);
    }

    other.small_size_ = 0;
    other.small_[0] = '\0';
  }

  Fgstring& Fgstring::operator=(const Fgstring& other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }

    category_ = other.category_;
    small_size_ = other.small_size_;

    if (other.IsSmall())
    {
      std::memcpy(small_, other.small_, small_size_ + 1);
    }

    return *this;
  }

  Fgstring& Fgstring::operator=(Fgstring&& other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }

    category_ = other.category_;
    small_size_ = other.small_size_;

    if (other.IsSmall())
    {
      std::memcpy(small_, other.small_, small_size_ + 1);
    }

    other.small_size_ = 0;
    other.small_[0] = '\0';

    return *this;
  }

  Fgstring::~Fgstring() noexcept
  {
    DestroyMedium();
  }

  void Fgstring::Append(char c) noexcept
  {
    if (IsSmall())
    {
      if (small_size_ < SSO_CAPACITY)
      {
        small_[small_size_++] = c;
        small_[small_size_] = '\0';

        return;
      }

      GrowToMedium(small_size_ + 1);
    }

    // Medium.
    if (medium_.size < medium_.capacity)
    {
      medium_.data[medium_.size++] = c;
      medium_.data[medium_.size] = '\0';
    }
  }

  void Fgstring::Append(const char* str, uint32_t len) noexcept
  {
    if (!str || len == 0)
    {
      return;
    }

    if (IsSmall())
    {
      if (small_size_ + len <= SSO_CAPACITY)
      {
        std::memcpy(small_ + small_size_, str, len);

        small_size_ += len;
        small_[small_size_] = '\0';

        return;
      }

      GrowToMedium(small_size_ + len);
    }

    if (medium_.size + len <= medium_.capacity)
    {
      std::memcpy(medium_.data + medium_.size, str, len);

      medium_.size += len;
      medium_.data[medium_.size] = '\0';
    }
  }

  const char* Fgstring::Cstr() const noexcept
  {
    return IsSmall() ? small_ : medium_.data;
  }

  size_t Fgstring::Size() const noexcept
  {
    return IsSmall() ? small_size_ : medium_.size;
  }

  bool Fgstring::Empty() const noexcept
  {
    return IsSmall() ? (small_size_ == 0) : (medium_.size == 0);
  }

  bool Fgstring::IsSmall() const noexcept
  {
    return category_ == Category::Small;
  }

  void Fgstring::GrowToMedium(uint32_t minCap) noexcept
  {
    uint32_t cap = NextCapacity(minCap);

    char* mem = static_cast<char*>(memory::RouterAllocator::Allocate(cap + 1));

    // Copy when small.
    std::memcpy(mem, small_, small_size_ + 1);
    
    mem[small_size_] = '\0';

    medium_.data = mem;
    medium_.size = small_size_;
    medium_.capacity = cap;

    category_ = Category::Medium;
  }

  void Fgstring::DestroyMedium() noexcept
  {
    if (category_ == Category::Medium)
    {
      memory::RouterAllocator::Deallocate(medium_.data, medium_.capacity + 1);
    }
  }

  uint32_t Fgstring::NextCapacity(uint32_t min) const noexcept
  {
    uint32_t cap = 32;

    while (cap < min)
    {
      cap <<= 1;
    }

    if (cap > 1024)
    {
      cap = 1024;
    }

    return cap - 1;
  }
}
