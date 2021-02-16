#pragma once

#include <cstdint>

namespace bad
{
template <unsigned int SIZE>
struct mmio_traits
{
};
template <>
struct mmio_traits<8>
{
  using internal_type = std::uint8_t;
};
template <>
struct mmio_traits<16>
{
  using internal_type = std::uint16_t;
};
template <>
struct mmio_traits<32>
{
  using internal_type = std::uint32_t;
};
template <>
struct mmio_traits<64>
{
  using internal_type = std::uint64_t;
};

class read_only
{
};
class write_only
{
};
class read_write : public read_only, public write_only
{
};

template <std::size_t SIZE = 32, typename Register_Ty = read_write>
class mmio
{
 private:
  using reg_type = typename mmio_traits<SIZE>::internal_type;

  volatile reg_type* raw_ptr;

  class bit_proxy
  {
   public:
    // Read
    operator mmio::reg_type() const
    {
      return read(Register_Ty{});
    }
    // Write
    void operator=(mmio::reg_type val)
    {
      write(val, Register_Ty{});
    }

   private:
    friend class mmio<SIZE>;
    mmio<SIZE>*  owner;
    unsigned int bit_num;

   protected:
    bit_proxy(mmio<SIZE>* reg, unsigned int num)
        : owner(reg), bit_num(num) {}
  };

  template <typename trait>
  constexpr assert_if_not(const char&& error_string)
  {
    if constexpr (!is_base_of<trait, Register_Ty>())
      {
        static_assert(dependent_false<Register_Ty>(), error_string);
      }
  }

 public:
  explicit mmio(std::uint32_t address)
      : raw_ptr{reinterpret_cast<volatile std::uint32_t*>(address)}
  {
  }

  mmio& operator=(reg_type bit_mask);
  void  operator=(reg_type bit_mask)
  {
    assert_if_not<write_only>("Writing to read-only object");
    *raw_ptr = bit_mask;
  }
  operator reg_type() const
  {
    assert_if_not<read_only>("Reading from write-only object");
    return *raw_ptr;
  }
  void operator|=(reg_type bit_mask)
  {
    assert_if_not<read_write>("Object must be read-write");
    *raw_ptr |= bit_mask;
  }
  void operator&=(reg_type bit_mask)
  {
    assert_if_not<read_write>("Object must be read-write");
    *raw_ptr &= bit_mask;
  }

  operator reg_type();

  inline mmio& operator|=(reg_type bit_mask)
  {
    *raw_ptr |= bit_mask;
    return *this;
  }

  inline mmio& operator&=(reg_type bit_mask);

  inline mmio& operator^=(reg_type bit_mask);

  bit_proxy operator[](unsigned int index)
  {
    // Check that index is valid...
    return bit_proxy{this, index};
  }
};

}  // namespace bad

void mmio_test()
{
  bad::mmio reg(0x2000);
  bad::mmio mask(0x10);

  reg |= mask;

  reg[15] = 1;
}