#include <bits/stdc++.h>
using namespace std;

struct Hasher {
  static const uint64_t mod = 1e9 + 7, p = 131;
  vector<uint64_t> pow_p, h;
  Hasher (const string& s) : pow_p(1, 1), h(s.size() + 1, 0) {
    while (pow_p.size() <= s.size())
      pow_p.push_back(pow_p.back() * p % mod);
    for (int i = 0; i < (int) s.size(); ++i)
      h[i + 1] = (h[i] * p + (uint64_t) s[i]) % mod;
  }
  uint64_t get_hash(int l, int r) { // [l, r], 0-base
    return (h[r + 1] - h[l] * pow_p[r - l + 1] % mod + mod) % mod;
  }
};

int count_match(const string &T, const string &P) {
  int ans = 0, n = (int) P.size();
  Hasher h(T);
  uint64_t h_P = Hasher(P).get_hash(0, n - 1);
  for (int i = 0; i + n - 1 < (int) T.size(); ++i)
    ans += (h.get_hash(i, i + n - 1) == h_P);
  return ans;
}

void solve() {
  string T;
  cin >> T;

  int Q;
  cin >> Q;
  while (Q --> 0) {
    string P;
    cin >> P;
    cout << count_match(T, P) << '\n';
  }
}


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
