#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct SuffixAutomaton {
  enum { sigma = 26, alpha = 'a' };
  vector<array<int, sigma>> ch;
  vi link, len, cnt;
  int last;
  int new_node() {
    ch.emplace_back();
    fill(all(ch.back()), -1);
    link.push_back(-1);
    len.push_back(0);
    cnt.push_back(0);
    return sz(ch) - 1;
  } 
  void insert(char c) {
    int cur = new_node();
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    int p = last;
    while (p != -1 and ch[p][c - alpha] == -1) {
      ch[p][c - alpha] = cur;
      p = link[p];
    }
    if (p == -1) link[cur] = 0;
    else {
      int q = ch[p][c - alpha];
      if (len[p] + 1 == len[q])
        link[cur] = q;
      else {
        int clone = new_node();
        len[clone] = len[p] + 1;
        ch[clone] = ch[q];
        link[clone] = link[q];
        while (p != -1 and ch[p][c - alpha] == q) {
          ch[p][c - alpha] = clone;
          p = link[p];
        }
        link[q] = link[cur] = clone;
      }
    }
    last = cur;
  }
  SuffixAutomaton(const string &T) : last(0) {
    new_node();
    for (char c : T) insert(c);
    vi ind(sz(ch), 0);
    for (int i: link) if (i != -1) ind[i] += 1;
    queue<int> q;
    rep (i, 0, sz(ch)) if (ind[i] == 0) q.push(i);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (link[u] == -1) continue;
      cnt[link[u]] += cnt[u];
      ind[link[u]] -= 1;
      if (ind[link[u]] == 0)
        q.push(link[u]);
    }
  }
  int query(const string &P) {
    int u = 0;
    for (char c : P) {
      if (ch[u][c - alpha] == -1) return 0;
      u = ch[u][c - alpha];
    }
    return cnt[u];
  }
};

void solve() {
  string T;
  cin >> T;
  SuffixAutomaton sam(T);

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; ++i) {
    string P;
    cin >> P;
    cout << sam.query(P) << '\n';
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
