/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_PRE_DEC_HPP
#define SPROUT_FUNCTIONAL_PRE_DEC_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// pre_dec
	//
	template<typename T = void>
	struct pre_dec;
	template<>
	struct pre_dec<void> {
	public:
		typedef void is_transparent;
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(--std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_IF_EXPR(--std::declval<T>())
		{
			return --SPROUT_FORWARD(T, x);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_PRE_DEC_HPP
