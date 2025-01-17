#include <bits/stdc++.h>
using namespace std;

// z[0] = 0, z[i] = max j s.t. s[0, j) = s[i, i+j)
vector<int> z_value(const string &s) {
  // (l, r) 是目前最大的 j + z[j] 的 (j, j + z[j])
  int l = 0, r = 0, n = (int) s.size();
  vector<int> z(n);
  for (int i = 1; i < n; ++i) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    // 暴力匹配還沒看過的字串
    while (i + z[i] < n and s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) l = i, r = i + z[i]; // 更新 max j + z[j]
  }
  return z;
}
// 直接看 T 有多少個位置開頭可以匹配完 P！這招 KMP 也可以用
int count_match(const string &T, const string &P) {
  auto z = z_value(P + '$' + T);
  int ans = 0;
  for (int i = 0; i < (int) z.size(); ++i)
    ans += (z[i] == (int) P.size());
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
