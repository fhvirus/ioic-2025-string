#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
	vector<int> sa, rank, lcp;
	SuffixArray(const string& s) {
    int n = (int) s.size() + 1; // C++ 中 s[s.size()] 總是 '\0'
    sa = rank = lcp = vector<int>(n, 0);
    iota(begin(sa), end(sa), 0);
    sort(begin(sa), end(sa), [&](int u, int v)
        { return s[u] < s[v]; }); // O(n log n) 不影響整體
    rank[sa[0]] = 0;
    for (int i = 1; i < n; ++i) // 一樣的字元 rank 要一樣大
      rank[sa[i]] = rank[sa[i-1]] + (s[sa[i]] != s[sa[i-1]]);
    vector<int> cnt(n), psa(n), nrank(n);
    for (int k = 1; k < n; k *= 2) { // 倍增
      for (int i = 0; i < n; ++i) // 用上一次的 sa radix sort 後半
        psa[i] = sa[i] - k + (sa[i] < k ? n : 0);
      fill(begin(cnt), end(cnt), 0);
      for (int i = 0; i < n; ++i) ++cnt[rank[psa[i]]];
      partial_sum(begin(cnt), end(cnt), begin(cnt)); // 前綴和
      for (int i = n - 1; i >= 0; --i)
        sa[--cnt[rank[psa[i]]]] = psa[i];
      // 處理 rank，需要上一次的 rank 所以要多開一個陣列
      nrank[sa[0]] = 0;
      pair<int, int> prv(rank[sa[0]], rank[(sa[0] + k) % n]);
      for (int i = 1; i < n; ++i) {
        pair<int, int> cur(rank[sa[i]], rank[(sa[i] + k) % n]);
        nrank[sa[i]] = nrank[sa[i-1]] + (cur != prv);
        prv = cur;
      }
      swap(rank, nrank);
    }
		for (int i = 0, j, k = 0; i < n - 1; ++i) {
      if (k > 0) k -= 1;
      j = sa[rank[i] - 1];
      while (s[i + k] == s[j + k]) ++k;
      lcp[rank[i]] = k;
    } // 雙指標爬過原字串 s[i, k] 處理 lcp！
	}
};

int count_match(const string& T, const SuffixArray &sa, string P) {
  const auto get_lower_bound = [&](const string &s) -> int {
    int lb = (int) sa.sa.size();
    for (int l = 1 << 16; l > 0; l /= 2) if (lb - l >= 0) {
      int t = sa.sa[lb - l];
      bool lt = true; // P < T[t, ]
      for (int i = 0; i <= (int) s.size() and t + i <= (int) T.size(); ++i)
        if (s[i] != T[t + i]) { lt = (s[i] < T[t + i]); break; }
      if (lt) lb -= l;
    }
    return lb;
  };
  int lb = get_lower_bound(P);
  P.back() = char(P.back() + 1);
  return get_lower_bound(P) - lb;
}

void solve() {
  string T;
  cin >> T;

  SuffixArray sa(T);

  int Q;
  cin >> Q;
  while (Q --> 0) {
    string P;
    cin >> P;
    cout << count_match(T, sa, P) << '\n';
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
