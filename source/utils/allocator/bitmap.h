// Copyright (c) 2026 Gubarger. All Rights Reserved.

#include <cstddef>
#include <cstdint>

namespace gubash::utils::allocator {
  class Bitmap {
  public:
    Bitmap(size_t size);
    Bitmap(Bitmap &&) noexcept = default;
    Bitmap(const Bitmap &) noexcept = delete;
    Bitmap &operator=(Bitmap &&) noexcept = default;
    Bitmap &operator=(const Bitmap &) noexcept = delete;
    ~Bitmap() noexcept;

    void Set(size_t index);
    void Clear(size_t index);
    bool Get(size_t index) const;
    size_t GetSize() const;

  private:
    size_t size_;
    uint8_t* data_;
  };
}
