/**
*    author:  ekusiadadus
*    created: 27.03.2022 07:07:49
**/

#include <bits/stdc++.h>
#include "fpConfig.h"


using namespace std;
using i64 = long long;

#ifdef USE_FIXED_POINT
#include "fixed_point/FixedPoint.hpp"
#endif

// #include "fixed_point/FixedPoint.hpp"

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(false);
#ifdef USE_FIXED_POINT
  FixedPoint<uint32_t, 8> t(3.14f);
  cout << "Using Fixed Point: " << float(t) << endl;
#else
  float t = 3.14f;
  cout << float(t) << endl;
  cout << "Using Float: " << float(t) << endl;
#endif
  // FixedPoint<uint32_t, 8> t(3.14f);
  // cout << "Using Fixed Point: " << float(t) << endl;
  return 0;
}