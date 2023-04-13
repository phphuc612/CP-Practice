#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> vert;

int n_scc, cnt;
vector<int> num, low;
vector<bool> found;
vector<int> trace;
vector<int> scc_id;

void init() {
    vert.assign(n + 1, vector<int>());
    num.assign(n + 1, -1);
    low.assign(n + 1, -1);
    found.assign(n + 1, false);
    scc_id.assign(n + 1, -1);
    trace.clear();
    n_scc = 0;
    cnt = 0;
}

void tarjan(int u) {
    num[u] = low[u]= cnt++;
    trace.push_back(u);

    for (const auto& v: vert[u]) {
        if (found[v])
            continue;

        if (num[v] != -1) {
            low[u] = min(low[u], num[v]);
        } else {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if (num[u] == low[u]) {
        ++n_scc;

        while (!trace.empty()) {
            int v = trace.back();
            trace.pop_back();

            scc_id[v] = n_scc;
            found[v] = true; // VERY IMPORTANT
            if (v == u) break;
        }
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        cin >> n >> m;

        init();

        int a, b;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b;
            vert[a].push_back(b);
        }

        for (int i = 1; i <= n; ++i) {
            if (!found[i]) {
                tarjan(i);
            }
        }

        vector<int> in_degree = vector<int>(n_scc + 1, 0);

        for (int u = 1; u <= n; ++u) {
            for (const int& v: vert[u]) {
                if (scc_id[u] != scc_id[v]) {
                    ++in_degree[scc_id[v]];
                }
            }
        }

        int ans = 0;

        for (int i = 1; i <= n_scc; ++i) {
            ans += (in_degree[i] == 0 ? 1 : 0);
        }

        cout << ans << endl;

    }
}
