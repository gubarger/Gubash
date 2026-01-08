// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include "string.h"
#include "allocator/routerallocator.h"

namespace gubash::utils {
  bool ShString::IsSmall() const noexcept 
  {
    return large_.capacity_ == 0;
  }

  void ShString::DestroyLarge() noexcept 
  {
    if (!IsSmall())
    {
      allocator::RouterAllocator::Deallocate(large_.data_, large_.capacity_ + 1);
      large_.capacity_ = 0;
    }
  }


  ShString::ShString() noexcept : size_(0) 
  {
    small_[0] = '\0';
  }

  ShString::ShString(const char* s) : ShString(s, std::strlen(s)) 
  {
  }

  ShString::ShString(const char* s, size_t len) : size_(0)
  {
    Assign(s, len);
  }

  ShString::~ShString() noexcept 
  {
    DestroyLarge();
  }

  ShString::ShString(const ShString& other) : size_(0)
  {
    Assign(other.Cstr(), other.size_);
  }

  ShString::ShString(ShString&& other) noexcept : size_(other.size_)
  {
    if (other.IsSmall()) 
    {
      std::memcpy(small_, other.small_, size_ + 1);
    } 
    else 
    {
      large_.data_ = other.large_.data_;
      large_.capacity_ = other.large_.capacity_;

      other.large_.capacity_ = 0;
      other.size_ = 0;
      other.small_[0] = '\0';
    }
  }

  ShString& ShString::operator=(const ShString& other) 
  {
    if (this != &other) 
    {
        Assign(other.Cstr(), other.size_);
    }
    
    return *this;
  }

  ShString& ShString::operator=(ShString&& other) noexcept {
    if (this != &other) 
    {
      DestroyLarge();

      size_ = other.size_;

      if (other.IsSmall()) 
      {
        std::memcpy(small_, other.small_, size_ + 1);
      } 
      else 
      {
        large_.data_ = other.large_.data_;
        large_.capacity_ = other.large_.capacity_;

        other.large_.capacity_ = 0;
        other.size_ = 0;
        other.small_[0] = '\0';
      }
    }

    return *this;
  }

  void ShString::Clear() noexcept {
    DestroyLarge();
  
    size_ = 0;
    small_[0] = '\0';
  }

  void ShString::Assign(const char* s, size_t len) {
    if (len <= SSO_CAPACITY_) 
    {
      DestroyLarge();
      std::memcpy(small_, s, len);
      
      small_[len] = '\0';
      size_ = static_cast<uint32_t>(len);
    }
    else
    {
      if (IsSmall() || large_.capacity_ < len) 
      {
        DestroyLarge();

        large_.capacity_ = static_cast<uint32_t>(len);
        large_.data_ = static_cast<char*>(allocator::RouterAllocator::Allocate(len + 1));
      }
    
      std::memcpy(large_.data_, s, len);
    
      large_.data_[len] = '\0';
      size_ = static_cast<uint32_t>(len);
    }
  }

  void ShString::Append(char c) {
    if (IsSmall())
    {
      if (size_ < SSO_CAPACITY_)
      {
        small_[size_++] = c;
        small_[size_] = '\0';
      }
      else
      {
        // Jump to small -> large
        uint32_t newCap = size_ + 1;

        large_.capacity_ = newCap;
        large_.data_ = static_cast<char*>(allocator::RouterAllocator::Allocate(newCap + 1));

        std::memcpy(large_.data_, small_, size_);

        large_.data_[size_++] = c;
        large_.data_[size_] = '\0';
      }
    }
    else
    {
      if (size_ < large_.capacity_)
      {
        large_.data_[size_++] = c;
        large_.data_[size_] = '\0';
      }
      // Intentionally NOTHING.
    }
  }

  const char* ShString::Cstr() const noexcept {
    return IsSmall() ? small_ : large_.data_;
  }

  size_t ShString::Size() const noexcept {
    return size_;
  }

  bool ShString::Empty() const noexcept {
    return size_ == 0;
  }

  char ShString::operator[](size_t i) const noexcept {
    return IsSmall() ? small_[i] : large_.data_[i];
  }
}
