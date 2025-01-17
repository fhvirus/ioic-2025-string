#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
	enum { sigma = 26, first = 'a' }; // 字元集大小，第一個字元
	struct Node {
		int fl, next[sigma]; // fail link, 轉移
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> nd;
	vector<int> ord; // 節點照深度排序，reserve for low ML 
	AhoCorasick() : nd(1, -1) { nd.reserve(350053); }
	int insert(const string& s) { // 普通的 Trie 建構
		int u = 0;
		for (char c : s) {
			int &v = nd[u].next[c - first];
			if (v == -1) {
        u = v = (int) nd.size();
        nd.emplace_back(-1);
      } else u = v;
		}
    return u;
	} // 回傳字串結尾所在節點
  void build() {
		nd[0].fl = (int) nd.size();
		nd.emplace_back(0); // 加入虛點，方便建構
    ord.push_back(0);
    for (int i = 0; i < (int) ord.size(); ++i) {
			int u = ord[i], pre = nd[u].fl;
      for (int c = 0; c < sigma; ++c) {
				int &v = nd[u].next[c], y = nd[pre].next[c];
				if (v == -1) v = y;
				else nd[v].fl = y, ord.push_back(v);
			} // nd[pre].next[c] 一定處理好了
		} // 要嘛是可以走的，要嘛是他的 fail link
	} // 所以遇到不能走的（不匹配）直接放心跳過去！
};

vector<int> count_match(const string &T,
    int Q, const vector<string> &P) {
  AhoCorasick ac;
  vector<int> pos(Q);
  for (int i = 0; i < Q; ++i)
    pos[i] = ac.insert(P[i]);
  ac.build();
  vector<int> cnt(ac.nd.size(), 0);
  for (int u = 0, i = 0; i < (int) T.size(); ++i) {
    u = ac.nd[u].next[T[i] - ac.first];
    cnt[u] += 1;
  }
  reverse(begin(ac.ord), end(ac.ord));
  for (int u : ac.ord)
    cnt[ac.nd[u].fl] += cnt[u];
  vector<int> ans(Q);
  for (int i = 0; i < Q; ++i)
    ans[i] = cnt[pos[i]];
  return ans;
}

void solve() {
  string T;
  cin >> T;

  int Q;
  cin >> Q;

  vector<string> P(Q);
  for (string &s : P) cin >> s;

  auto ans = count_match(T, Q, P);

  for (int i = 0; i < Q; ++i)
    cout << ans[i] << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
