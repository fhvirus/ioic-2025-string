#include <bits/stdc++.h>
using namespace std;

struct SuffixBST {
  const double alpha = 0.75;
  struct Node { int siz, lc, rc; double tag; };
  string s;
  int root;
  vector<Node> nd;
  vector<int> buf;
  bool cmp(int u, int v) { // 用 tag O(1) 比較
    if (s[u] != s[v]) return s[u] < s[v];
    return nd[u + 1].tag < nd[v + 1].tag;
  }
  int siz(int u) { return u == -1 ? 0 : nd[u].siz; }
  void pull(int u) { nd[u].siz = siz(nd[u].lc) + 1 + siz(nd[u].rc); }
  bool balanced(int u) { return alpha * nd[u].siz > max(siz(nd[u].lc), siz(nd[u].rc)); }
  void flatten(int u) { if (u != -1) { flatten(nd[u].lc); buf.push_back(u); flatten(nd[u].rc); } }
  void build(int &u, int l, int r, double lb, double rb) {
    int m = (l + r) / 2;
    double mb = (lb + rb) / 2;
    u = buf[m];
    nd[u].tag = mb;
    if (l < m) build(nd[u].lc, l, m, lb, mb);
    else nd[u].lc = -1;
    if (m + 1 < r) build(nd[u].rc, m + 1, r, mb, rb);
    else nd[u].rc = -1;
    pull(u);
  }
  void insert(int &u, int i, double lb, double rb) {
    if (u == -1) {
      u = i;
      nd[u].siz = 1;
      nd[u].lc = nd[u].rc = -1;
      nd[u].tag = (lb + rb) / 2;
      return;
    }
    if (cmp(i, u)) insert(nd[u].lc, i, lb, nd[u].tag);
    else insert(nd[u].rc, i, nd[u].tag, rb);
    pull(u);
    if (not balanced(u)) {
      buf.clear();
      flatten(u);
      build(u, 0, (int) buf.size(), lb, rb);
    }
  }
  SuffixBST(string _s) : s(_s), root(-1), nd((int) s.size() + 1) {
    for (int i = (int) s.size() - 1; i >= 0; --i)
      insert(root, i, 0, 1);
  }
  vector<int> sa() { buf.clear(); flatten(root); return buf; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;
  SuffixBST sbst(s);

  auto sa = sbst.sa();
  for (int i = 0; i < (int) s.size(); ++i)
    cout << sa[i] << " \n"[i + 1 == (int) s.size()];
  
  return 0;
}

