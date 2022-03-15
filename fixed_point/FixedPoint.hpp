#ifndef FIXEDPOINT_HPP
#define FIXEDPOINT_HPP


#include <cstddef>
#include <cstdint>
#include <type_traits>

//! FixedPoint
//! \tparam I       the base integer type used to store the fixed point numbner.
//! \tparam F       the number of bits of the I used to store the fraction
template <typename I, unsigned int F>
class FixedPoint {
  std::enable_if_t<std::is_integral<I>::value, I> val;

 public:
  FixedPoint();
  FixedPoint(I value, bool raw = 0);
  FixedPoint(float value);

  operator I() const;
  operator float() const;
  I raw() const;

  template <unsigned int F2>
  operator FixedPoint<I, F2>() const;
  template <typename I2>
  operator FixedPoint<I2, F>() const;
  template <typename I2, unsigned int F2>
  operator FixedPoint<I2, F2>() const;

  FixedPoint<I, F>& operator+=(FixedPoint<I, F> const& rhs);
  FixedPoint<I, F>& operator-=(FixedPoint<I, F> const& rhs);
  FixedPoint<I, F>& operator*=(FixedPoint<I, F> const& rhs);
  FixedPoint<I, F>& operator/=(FixedPoint<I, F> const& rhs);
  FixedPoint<I, F>& operator++();
  FixedPoint<I, F>& operator--();
  FixedPoint<I, F> operator++(int);
  FixedPoint<I, F> operator--(int);

  FixedPoint<I, F> operator-() const;

  bool operator==(FixedPoint<I, F> const& rhs) const;
  bool operator>(FixedPoint<I, F> const& rhs) const;
};

template <typename I, unsigned int F>
FixedPoint<I, F> operator+(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);
template <typename I, unsigned int F>
FixedPoint<I, F> operator-(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);
template <typename I, unsigned int F>
FixedPoint<I, F> operator*(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);
template <typename I, unsigned int F>
FixedPoint<I, F> operator/(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);

template <typename I, unsigned int F>
bool operator!=(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);
template <typename I, unsigned int F>
bool operator<(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);
template <typename I, unsigned int F>
bool operator>=(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);
template <typename I, unsigned int F>
bool operator<=(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs);

template <typename I, unsigned int F>
FixedPoint<I, F>::FixedPoint() : val() {}

template <typename I, unsigned int F>
FixedPoint<I, F>::FixedPoint(I value, bool raw) : val(raw ? value : value << F) {}

template <typename I, unsigned int F>
FixedPoint<I, F>::FixedPoint(float value) {
  std::uint32_t value_int = *reinterpret_cast<std::uint32_t*>(&value);
  std::uint32_t mantissa = (value_int & 0x007FFFFF) | 0x00800000;
  std::int8_t exponent = ((value_int >> 23) & 0x000000FF) - 150 + F;
  if (exponent >= 0)
    mantissa <<= exponent;
  else
    mantissa >>= -exponent;
  val = (value_int & 0x80000000) ? -static_cast<I>(mantissa) : static_cast<I>(mantissa);
}

template <typename I, unsigned int F>
FixedPoint<I, F>::operator float() const {
  if (val == 0) return 0.f;
  std::uint32_t mantissa = (val >= 0) ? val : -val;
  std::uint8_t fbs = 31;
#if defined(__GNUC__) || defined(__clang__)
  fbs -= __builtin_clz(mantissa);
#elif defined(_MSC_VER)
  fbs -= __lzcnt(mantissa);
#else
  for (std::uint32_t copy = mantissa; copy & 0x80000000; --fbs) copy <<= 1;
#endif
  if (fbs <= 23)
    mantissa <<= 23 - fbs;
  else
    mantissa >>= fbs - 23;
  mantissa &= 0x007FFFFF;
  mantissa |= (val < 0) ? 0x80000000 : 0;
  mantissa |= static_cast<std::uint32_t>(127 + fbs - F) << 23;
  return *reinterpret_cast<float*>(&mantissa);
}

template <typename I, unsigned int F>
I FixedPoint<I, F>::raw() const {
  return val;
}

template <typename I, unsigned int F>
template <unsigned int F2>
FixedPoint<I, F>::operator FixedPoint<I, F2>() const {
  if (F >= F2)
    return {static_cast<I>(val >> (F - F2)), true};
  else
    return {static_cast<I>(val << (F2 - F)), true};
}

template <typename I, unsigned int F>
template <typename I2>
FixedPoint<I, F>::operator FixedPoint<I2, F>() const {
  return {static_cast<I2>(val), true};
}

template <typename I, unsigned int F>
template <typename I2, unsigned int F2>
FixedPoint<I, F>::operator FixedPoint<I2, F2>() const {
  if (F >= F2)
    return {static_cast<I2>(static_cast<I2>(val) >> (F - F2)), true};
  else
    return {static_cast<I2>(static_cast<I2>(val) >> (F2 - F)), true};
}

template <typename I, unsigned int F>
FixedPoint<I, F>& FixedPoint<I, F>::operator+=(FixedPoint<I, F> const& rhs) {
  val += rhs.val;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F>& FixedPoint<I, F>::operator-=(FixedPoint<I, F> const& rhs) {
  val -= rhs.val;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F>& FixedPoint<I, F>::operator*=(FixedPoint<I, F> const& rhs) {
  val = ((+val) * (+rhs.val)) >> F;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F>& FixedPoint<I, F>::operator/=(FixedPoint<I, F> const& rhs) {
  val = ((+val) << F) / rhs.val;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F>& FixedPoint<I, F>::operator++() {
  val++;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F>& FixedPoint<I, F>::operator--() {
  val--;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F> FixedPoint<I, F>::operator++(int) {
  FixedPoint<I, F> result = *this;
  ++*this;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F> FixedPoint<I, F>::operator--(int) {
  FixedPoint<I, F> result = *this;
  --*this;
  return *this;
}

template <typename I, unsigned int F>
FixedPoint<I, F> FixedPoint<I, F>::operator-() const {
  return {static_cast<I>(-val), true};
}

template <typename I, unsigned int F>
bool FixedPoint<I, F>::operator==(FixedPoint<I, F> const& rhs) const {
  return val == rhs.val;
}

template <typename I, unsigned int F>
bool FixedPoint<I, F>::operator>(FixedPoint<I, F> const& rhs) const {
  return val > rhs.val;
}

template <typename I, unsigned int F>
FixedPoint<I, F> operator+(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs) {
  return lhs += rhs;
}

template <typename I, unsigned int F>
FixedPoint<I, F> operator-(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs) {
  return lhs -= rhs;
}

template <typename I, unsigned int F>
FixedPoint<I, F> operator*(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs) {
  return lhs *= rhs;
}

template <typename I, unsigned int F>
FixedPoint<I, F> operator/(FixedPoint<I, F> lhs, FixedPoint<I, F> const& rhs) {
  return lhs /= rhs;
}

template <typename I, unsigned int F>
bool operator!=(FixedPoint<I, F> const& lhs, FixedPoint<I, F> const& rhs) {
  return !(lhs == rhs);
}

template <typename I, unsigned int F>
bool operator<(FixedPoint<I, F> const& lhs, FixedPoint<I, F> const& rhs) {
  return rhs > lhs;
}

template <typename I, unsigned int F>
bool operator>=(FixedPoint<I, F> const& lhs, FixedPoint<I, F> const& rhs) {
  return !(rhs > lhs);
}

template <typename I, unsigned int F>
bool operator<=(FixedPoint<I, F> const& lhs, FixedPoint<I, F> const& rhs) {
  return !(lhs > rhs);
}

#endif