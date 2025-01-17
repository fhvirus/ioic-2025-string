#include <bits/stdc++.h>
using namespace std;

// f[0] = 0
// f[i] = max j s.t. j <= i and s[0, j-1] = s[i-j+1, i]
vector<int> fail_function(const string &s) {
  int n = (int) s.size();
  vector<int> f(n);
  for (int i = 1; i < n; ++i) {
    int j = f[i - 1];
    while (j > 0 and s[j] != s[i]) j = f[j - 1];
    f[i] = j + (s[i] == s[j]);
  }
  return f;
}

int count_match(const string &T, const string &P) {
  auto f = fail_function(P + '$' + T);
  int ans = 0;
  for (int i = 0; i < (int) f.size(); ++i)
    ans += (f[i] == (int) P.size());
  return ans;
}

int count_match_fast(const string &T, const string &P) {
  auto f = fail_function(P + '$');
  int ans = 0, j = 0;
  for (int i = 0; i < (int) T.size(); ++i) {
    while (j > 0 and T[i] != P[j]) j = f[j - 1];
    j += (T[i] == P[j]);
    ans += (j == (int) P.size());
  }
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
