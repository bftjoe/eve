//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/is_not_equal.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/nb_values.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/half.hpp>

namespace eve
{
 template<typename Options>
  struct ulpdist_t : elementwise_callable<ulpdist_t, Options>
  {
    template<value T,  value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T a, U b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ulpdist_t, ulpdist_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var ulpdist
//!   @brief Computes the unit in the last place distance of its arguments.
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T, eve::value U >
//!      eve::common_value_t<T, U> ulpdist(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      Computes [elementwise](@ref glossary_elementwise) the
//!      'units in the last place' distance
//!      between `x` and `y`. This is semantically equivalent to:`
//!
//!      * if is_ordered(x,y), nb_values(x,y)/2.0 is returned
//!      * otherwise a `Nan` is returned
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/ulpdist.cpp}
//!
//! @}
//================================================================================================

  inline constexpr auto ulpdist = functor<ulpdist_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T ulpdist_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      if constexpr( integral_value<T> )
      {
        return dist(a, b);
      }
      else if constexpr( scalar_value<T> )
      {
        if( is_equal[numeric](a, b) ) return T(0);
        if( is_unordered(a, b) ) return inf(eve::as<T>());
        return nb_values(a, b)*half(eve::as(a));
      }
      else if constexpr( simd_value<T> )
      {
        auto inen = is_not_equal[numeric](a, b);
        return half[inen](eve::as(a))*(eve::inf[is_unordered(a, b)&&inen](as(a))+convert(nb_values(a, b), eve::as<eve::element_type_t<T>>()));
      }
    }
  }
}
