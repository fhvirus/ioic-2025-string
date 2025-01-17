#include <bits/stdc++.h>
using namespace std;


const uint64_t mod = 1e9 + 7, p = 131;

void solve() {
  string T;
  cin >> T;

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

    uint64_t p_len = 1;
    for (int i = 0; i < len; ++i) p_len = p_len * p % mod;

    uint64_t h = 0;
    for (int i = 0; i < (int) T.size(); ++i) {
      h = (h * p + T[i]) % mod;
      if (i >= len) h = (h - T[i - len] * p_len % mod + mod) % mod;
      if (i >= len - 1) hs[len][h] += 1;
    }
  }

  for (const string& s : P) {
    int len = (int) s.size();
    uint64_t h_s = 0;
    for (char c : s) h_s = (h_s * p + c) % mod;
    auto it = hs[len].find(h_s);
    cout << (it == end(hs[len]) ? 0 : it->second) << '\n';
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
