#include <bits/stdc++.h>

using namespace std;

const int MAX = 801;
int n, m;
vector<int> edges[MAX];
int low[MAX];
int num[MAX];
int scc_ord[MAX];
int cnt = 0;
int n_scc = 0;
vector<int> trace;

void dfs(int u) {
    low[u] = num[u] = ++cnt;
    trace.push_back(u);

    for (int v: edges[u]) {
        // Skip the vertex already in a scc
        if (scc_ord[v] != 0) continue;
        if (num[v] != 0) {
            low[u] = min(low[u], num[v]);
        } else {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if (low[u] == num[u]) {
        ++n_scc;
        int v;
        do {
            v = trace.back();
            scc_ord[v] = n_scc;
            trace.pop_back();
        } while (v != u);
    }
}


int main() {
    cin >> n >> m;

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        edges[u].push_back(v);
    }

    // tarjan
    for (int i = 1; i <= n; ++i) {
        if (num[i] == 0) {
            dfs(i);
        }
    }

    // map edges of vertex -> edges of scc
    vector<bool> check(n_scc + 1, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v: edges[u]) {
            if (scc_ord[v] != scc_ord[u]) {
                check[scc_ord[v]] = true;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n_scc; ++i) {
        ans += (!check[i]);
    }

    cout << ans;
}
