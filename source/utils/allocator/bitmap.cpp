//Copyright (c) 2026 Gubarger. All Rights Reserved.

#include "bitmap.h"

namespace gubash::utils::allocator {
  Bitmap::Bitmap(size_t size) : size_{size}
  {
    data_ = new uint8_t[(size + 7) / 8](); // +7 for rounding up.
  }

  Bitmap::~Bitmap()
  {
    delete[] data_;
  }

  void Bitmap::Set(size_t index)
  {
    data_[index / 8] |= (static_cast<uint8_t>(1) << (index & 7)); // Equivalent (1 << (index % 8))
  }

  void Bitmap::Clear(size_t index)
  {
    data_[index / 8] &= ~(static_cast<uint8_t>(1) << (index & 7));
  }

  bool Bitmap::Get(size_t index) const
  {
    return (data_[index / 8] & (static_cast<uint8_t>(1) << (index & 7))) != 0;
  }

  size_t Bitmap::GetSize() const
  {
    return size_;
  }
}
