#include <iostream>

#include "ap_int.h"
#include "ap_fixed.h"

int main() {
  ap_uint<8> a = -1;
  ap_uint<11> b = a * 8;
  ap_uint<11> c = a * 7;
  ap_uint<11> d = a * 6;
  ap_uint<11> e = a * 5;
  ap_uint<11> f = a * 4;

  std::cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << std::endl;
  std::cout << a.to_string(2) << " " << b.to_string(2) << " " << c.to_string(2) << " " << d.to_string(2) << " " << e.to_string(2) << " " << f.to_string(2) << std::endl;

  return 0;
}
