/**
 * @file bit_impl.hpp
 * @brief implementation header of Cbit and Tbit class
 */

#pragma once

namespace qc {
inline Bit::Bit(Bitno bitno) : bitno_(bitno) {
}

inline auto Bit::operator==(const Bit& other) const -> bool {
  return this->bitno_ == other.bitno_;
}

inline auto Bit::operator!=(const Bit& other) const -> bool {
  return !(*this == other);
}

inline auto Bit::operator<(const Bit& other) const -> bool {
  return this->bitno_ < other.bitno_;
}

template <class... Args>
inline Cbit::Cbit(Args&&... args)
  : Bit(std::forward<Args>(args)...), polarity_(true) {
}

inline Cbit::Cbit(Bitno bitno, bool polarity)
  : Bit(bitno), polarity_(polarity) {
}

inline auto Cbit::operator==(const Cbit& other) const -> bool {
  return Bit::operator==(other) && this->polarity_ == other.polarity_;
}

inline auto Cbit::operator!=(const Cbit& other) const -> bool {
  return !(*this == other);
}

inline auto Cbit::operator<(const Cbit& other) const -> bool {
  return this->bitno_ == other.bitno_ ? \
    !this->polarity_ : Bit::operator<(other);
}

template <class... Args>
inline Tbit::Tbit(Args&&... args) : Bit(std::forward<Args>(args)...) {
}

inline auto operator<<(std::ostream& os, const Cbit& obj) -> std::ostream& {
  const char* const sign = obj.polarity_ ? "" : "!";
  return os << sign << obj.bitno_;
}

inline auto operator<<(std::ostream& os, const Tbit& obj) -> std::ostream& {
  return os << 'T' << obj.bitno_;
}
}

namespace std {
inline auto hash<qc::Tbit>::operator()(const qc::Tbit& obj) const -> size_t {
  return hash<unsigned short>()(static_cast<unsigned short>(obj.bitno_));
}
}
