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

void solve() {
  string T;
  cin >> T;

  Hasher h(T);

  int Q;
  cin >> Q;

  vector<string> P(Q);
  for (string& s : P) cin >> s;

  vector<bool> need(T.size() + 1);
  vector<map<uint64_t, int>> hs(T.size() + 1);
  for (const string& s : P)
    need[s.size()] = true;
  for (int len = 1; len <= (int) T.size(); ++len) {
    if (not need[len]) continue;
    for (int i = 0; i + len - 1 < (int) T.size(); ++i)
      hs[len][h.get_hash(i, i + len - 1)] += 1;
  }

  for (const string& s : P) {
    int len = (int) s.size();
    uint64_t h_s = Hasher(s).get_hash(0, len - 1);
    cout << hs[len][h_s] << '\n';
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
