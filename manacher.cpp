#include <bits/stdc++.h>
using namespace std;

// p[i * 2 + 1] - 1 是以 i 為中心的奇回文半徑
// p[i * 2 + 2] - 1 是以 [i, i + 1] 為中心的偶回文半徑
vector<int> Manacher(string s) {
  int n = (int) s.size() * 2 + 1;
  string t(n, '.');
  for (int i = 0; i < (int) s.size(); ++i) t[i * 2 + 1] = s[i];
  int m = 0, r = 0;
  vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    p[i] = (r > i ? min(r - i, p[m - (i - m)]) : 1);
    while (0 <= i - p[i] and i + p[i] < n and
        t[i - p[i]] == t[i + p[i]]) ++p[i];
    if (i + p[i] > r) m = i, r = i + p[i];
  }
  return p;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string S;
  cin >> S;

  auto a = Manacher(S);

  for (int i = 1; i < (int) a.size() - 1; ++i)
    cout << a[i] - 1 << " \n"[i == (int) a.size() - 2];

  return 0;
}
