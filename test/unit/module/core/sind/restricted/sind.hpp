//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sind.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted_(eve::sind) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::sind)(T()), T);
}

TTS_CASE_TPL("Check eve::restricted_(eve::sind) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::sind)(eve::Nan<T>() ) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::sind)(eve::Inf<T>() ) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::sind)(eve::Minf<T>()) , eve::Nan<T>() );
  }

  TTS_IEEE_EQUAL(eve::restricted_(eve::sind)(T( 0 ))  , T(0)          );
  TTS_IEEE_EQUAL(eve::restricted_(eve::sind)(T(-0.))  , T(0)          );
  TTS_IEEE_EQUAL(eve::restricted_(eve::sind)( T(90.0)), eve::Nan<T>() );
  TTS_IEEE_EQUAL(eve::restricted_(eve::sind)(-T(90.0)), eve::Nan<T>() );


  TTS_ULP_EQUAL(eve::big_(eve::sind)( T(1)    ) , T(1.745240643728351281941897851631619247225272030714e-2)  , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)(-T(1)    ) , T(-1.745240643728351281941897851631619247225272030714e-2) , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)( T(45.0) ) , T(0.70710678118654752440084436210484903928483593768847)   , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)(-T(45.0) ) , T(-0.70710678118654752440084436210484903928483593768847)  , 3.0);
}
