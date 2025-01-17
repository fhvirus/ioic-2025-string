#include <bits/stdc++.h>
using namespace std;

int count_match(const string &T, const string &P) {
  int ans = 0, len = (int) P.size();
  for (int i = 0; i + len <= (int) T.size(); ++i)
    ans += (T.substr(i, len) == P);
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
