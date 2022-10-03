#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft ref = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft imf = { 2.0f , -1.0,  -5.0, 0.0};
  auto z = eve::as_complex_t<wide_ft>(ref, imf);

  std::cout
    << "---- simd" << '\n'
    << "<- z       = " << z << '\n'
    << "-> asinh(z) = " << eve::asinh(z)  << '\n';
  return 0;
}