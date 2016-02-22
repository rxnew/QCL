/**
 * @file measurement.hpp
 * @brief header of quantum measurement classes
 */

#pragma once

#include "matrix.hpp"

#include "bit.hpp"

namespace qc {
class Measurement;

using MeasurementPtr = std::unique_ptr<Measurement>;
using MeasurementList = std::list<MeasurementPtr>;

/**
 * @brief quantum measurement class
 */
class Measurement {
 protected:
  Tbit tbit_;
  Vector basis_;

 public:
  Measurement(const Tbit& tbit, const Vector& basis);
  Measurement(const Measurement& other);
  Measurement(Measurement&& other) noexcept;
  virtual ~Measurement() = default;
  auto operator=(const Measurement& other) -> Measurement&;
  auto operator=(Measurement&& other) -> Measurement&;
  auto operator==(const Measurement& other) const -> bool;
  auto operator!=(const Measurement& other) const -> bool;
};

class MeasurementX : public Measurement {
 public:
  MeasurementX(const Tbit& tbit);
  MeasurementX(const Measurement& other);
  MeasurementX(Measurement&& other) noexcept;
};

class MeasurementZ : public Measurement {
 public:
  MeasurementZ(const Tbit& tbit);
  MeasurementZ(const Measurement& other);
  MeasurementZ(Measurement&& other) noexcept;
};

inline Measurement::Measurement(const Tbit& tbit, const Vector& basis)
  : tbit_(tbit), basis_(basis) {
}

inline Measurement::Measurement(const Measurement& other)
  : tbit_(other.tbit_), basis_(other.basis_) {
}

inline Measurement::Measurement(Measurement&& other) noexcept
  : tbit_(std::move(other.tbit_)), basis_(std::move(other.basis_)) {
}

inline auto Measurement::operator=(const Measurement& other) -> Measurement& {
  this->tbit_ = other.tbit_;
  this->basis_ = other.basis_;
  return *this;
}

inline auto Measurement::operator=(Measurement&& other) -> Measurement& {
  this->tbit_ = std::move(other.tbit_);
  this->basis_ = std::move(other.basis_);
  return *this;
}

inline auto Measurement::operator==(const Measurement& other) const -> bool {
  return this->tbit_ == other.tbit_ && this->basis_ == other.basis_;
}

inline auto Measurement::operator!=(const Measurement& other) const -> bool {
  return !(*this == other);
}

inline MeasurementX::MeasurementX(const Tbit& tbit) : tbit_(tbit), basis_() {
}

inline MeasurementX::MeasurementX(const Measurement& other) : Measurement(other) {
}

inline MeasurementX::MeasurementX(Measurement&& other) noexcept
  : Measurement(std::move(other)) {
}

inline MeasurementZ::MeasurementZ(const Tbit& tbit) : tbit_(tbit), basis_() {
}

inline MeasurementZ::MeasurementZ(const Measurement& other) : Measurement(other) {
}

inline MeasurementZ::MeasurementZ(Measurement&& other) noexcept
  : Measurement(std::move(other)) {
}
}
