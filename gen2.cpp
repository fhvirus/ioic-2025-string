#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const uint64_t mod = 1e9 + 7, p = 131;

  const int alpha = 62;
  const string sigma = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  const int len = 7;
  const string S = "IOICamp";
  uint64_t h_S = 0;
  for (char c : S) h_S = (h_S * p + c) % mod;

  string T = S;
  uint64_t h_T;
  mt19937 mt(7122);
  bool found = false;
  uint64_t iter = 0;
  while (not found) {
    ++iter;
    h_T = 0;
    for (int i = 0; i < len; ++i) {
      T[i] = sigma[mt() % alpha];
      h_T = (h_T * p + T[i]) % mod;
    }
    if (h_T == h_S and S != T) {
      found = true;
      break;
    }
  }

  cout << "Found H(" << S << ") = H(" << T << ") = " << h_T << endl;
  cout << iter << " iterations taken" << endl;

  return 0;
}
