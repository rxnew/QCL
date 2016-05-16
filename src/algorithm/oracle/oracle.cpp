/**
 * @file oracle.cpp
 * @brief implementation of algorithm for quantum oracle
 */

#include "../oracle.hpp"

#include "../general.hpp"

namespace qc {
auto collectCbits(const Circuit& circuit) -> BitList {
  BitList bits;
  for(const auto& gate : circuit.getGateList()) {
    for(const auto& cbit : gate->getCbitList()) {
      bits.insert(cbit.bitno_);
    }
  }
  return std::move(bits);
}

auto collectTbits(const Circuit& circuit) -> BitList {
  BitList bits;
  for(const auto& gate : circuit.getGateList()) {
    for(const auto& tbit : gate->getTbitList()) {
      bits.insert(tbit.bitno_);
    }
  }
  return std::move(bits);
}

auto isMctCircuit(const Circuit& circuit) -> bool {
  const auto cbits_no = qc::collectCbits(circuit);
  const auto tbits_no = qc::collectTbits(circuit);
  return !util::container::isIntersected(cbits_no, tbits_no);
}

auto sortGatesByCbits(Circuit& circuit) -> void {
  const auto f = [](const GatePtr& lhs, const GatePtr& rhs) {
    return util::container::Compare()(lhs->getCbitList(), rhs->getCbitList(),
                                      [](const Cbit& lhs, const Cbit& rhs) {
                                        return Bit(lhs) < Bit(rhs);});
  };
  circuit.getGateList().sort(f);
}

auto sortGatesByTbits(Circuit& circuit) -> void {
  const auto f = [](const GatePtr& lhs, const GatePtr& rhs) {
    return util::container::Compare()(lhs->getTbitList(), rhs->getTbitList());
  };
  circuit.getGateList().sort(f);
}

auto sortGates(Circuit& circuit) -> void {
  qc::sortGatesByCbits(circuit);
  qc::sortGatesByTbits(circuit);
}

auto decompIntoSingleTargetCircuits(const Circuit& circuit)
  -> std::unordered_map<Tbit, Circuit> {
  std::unordered_map<Tbit, Circuit> result;
  for(const auto& gate : circuit.getGateList()) {
    for(const auto& gate_s : qc::decompIntoSingleTargetGates(gate)) {
      result[qc::getTbit(gate_s)].addGate(gate_s->clone());
    }
  }
  return std::move(result);
}
}