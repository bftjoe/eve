//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_1_IS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE4_1_IS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // sse4_1
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_equal_(EVE_SUPPORTS(sse4_1_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;
    using a_t = wide<as_integer_t<T>,N>;

    if constexpr(std::is_same_v<T, float>) return l_t(_mm_cmpeq_ps(v0, v1));
    if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpeq_pd(v0, v1));
    if constexpr(std::is_integral_v<T> && sizeof(T) == 1) return l_t(_mm_cmpeq_epi8(v0, v1));
    if constexpr(std::is_integral_v<T> && sizeof(T) == 2) return l_t(_mm_cmpeq_epi16(v0, v1));
    if constexpr(std::is_integral_v<T> && sizeof(T) == 4) return l_t(_mm_cmpeq_epi32(v0, v1));
    if constexpr(std::is_integral_v<T> && sizeof(T) == 8) return l_t(_mm_cmpeq_epi64(v0, v1));
    if constexpr(is_logical_v<T>) return is_equal(bitwise_cast<a_t>(v0), bitwise_cast<a_t>(v1));
  }
}

#endif
