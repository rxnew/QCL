#pragma once

#include <vector>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

namespace qc {
namespace util {
namespace tmpl {
template <class T>
struct template_class {};
 
template <template <class...> class T, class... Args1>
struct template_class<T<Args1...>> {
  template <class... Args2>
    using type = T<Args2...>;
};

template <template <class...> class T, template <class...> class U>
struct is_same_template : std::false_type {};

template <template <class...> class T>
struct is_same_template<T, T> : std::true_type {};

template <template <class...> class T>
struct is_array_template {
  static constexpr bool value =
    is_same_template<T, std::vector>::value ||
    is_same_template<T, std::list>::value   ||
    is_same_template<T, std::deque>::value  ||
    is_same_template<T, std::set>::value    ||
    is_same_template<T, std::unordered_set>::value;
};

template <template <class...> class T>
struct is_map_template {
  static constexpr bool value =
    is_same_template<T, std::map>::value ||
    is_same_template<T, std::unordered_map>::value;
};

template <template <class...> class T>
struct is_container_template {
  static constexpr bool value =
    is_array_template<T>::value || is_map_template<T>::value;
};

template <class E>
struct is_array {
  static constexpr bool value = false;
};

template <template <class...> class T, class... Args>
struct is_array<T<Args...>> : is_array_template<T> {};

template <class E>
struct is_map {
  static constexpr bool value = false;
};

template <template <class...> class T, class... Args>
struct is_map<T<Args...>> : is_map_template<T> {};

template <class E>
struct is_container {
  static constexpr bool value = false;
};

template <template <class...> class T, class... Args>
struct is_container<T<Args...>> : is_container_template<T> {};
}
}
}
