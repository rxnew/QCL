/**
 * @file aliases.hpp
 * @brief header of aliases
 */

#pragma once

#include <unordered_map>

#include "../../util/string/istring/hash.hpp"

namespace qc {
extern const std::unordered_map<util::string::istring, std::string>
    gate_type_aliases;
}
