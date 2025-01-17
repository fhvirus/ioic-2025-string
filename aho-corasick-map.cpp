#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct AhoCorasick {
  vector<map<char, int>> ch;
  vi link;
  AhoCorasick() : ch(1), link(1, 0) {
    ch.reserve(350053); // for low ML
  }
  int insert(const string &s) {
    int u = 0;
    for (char c : s) {
      int &v = ch[u][c];
      if (v == 0) {
        v = sz(ch);
        ch.emplace_back();
        link.push_back(0);
      }
      // &v is destroyed by ch.emplace_back()
      u = ch[u][c];
    }
    return u;
  }
  vi ord;
  void build() {
    ord.push_back(0);
    for (int i = 0; i < sz(ord); ++i) {
      int u = ord[i];
      for (auto [c, v] : ch[u]) {
        if (v == 0) continue;
        int f = link[u];
        while (f != 0 and ch[f][c] == 0) f = link[f];
        if (u != 0) link[v] = ch[f][c]; // remember u ?= 0 !
        ord.push_back(v);
      }
    }
  }
  vi cnt;
  void calc(const string& T) {
    cnt.assign(sz(ch), 0);
    int u = 0;
    for (char c : T) {
      while (u != 0 and ch[u][c] == 0) u = link[u];
      u = ch[u][c];
      cnt[u] += 1;
    }
    reverse(begin(ord), end(ord));
    ord.pop_back();
    for (int i : ord)
      cnt[link[i]] += cnt[i];
  }
};

void solve() {
  string T;
  cin >> T;

  int Q;
  cin >> Q;

  AhoCorasick ac;
  vi pos(Q);
  for (int i = 0; i < Q; ++i) {
    string P;
    cin >> P;
    pos[i] = ac.insert(P);
  }

  ac.build();
  ac.calc(T);

  for (int i = 0; i < Q; ++i)
    cout << ac.cnt[pos[i]] << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
