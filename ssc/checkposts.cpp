#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;
const int MOD = 1e9 + 7;

int n, m;
vector<int> vert[MAX];
int fee[MAX];
bool found[MAX] = {false};
int low[MAX];
int num[MAX];
int scc_id[MAX];
int cnt_visit = 0;
int n_scc;
vector<int> scc_fee;
vector<int> scc_cnt;
vector<int> trace;

void tarjan(int u) {
    num[u] = low[u] = ++cnt_visit;
    trace.push_back(u);

    for (const auto& v: vert[u]) {
        if (found[v]) continue;
        if (num[v] != 0) {
            low[u] = min(low[u], num[v]);
        } else {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if (num[u] == low[u]) {
        ++n_scc;
        scc_fee.push_back(fee[u]);
        while (!trace.empty()) {
            int v = trace.back();
            trace.pop_back();
            found[v] = true;
            scc_id[v] = n_scc;

            scc_fee.back() = min(scc_fee.back(), fee[v]);

            if (v == u) break;
        }
    }
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> fee[i];
    }

    cin >> m;

    int a, b;
    for (int i = 1; i <= m; ++i) {
        cin >> a >> b;
        vert[a].push_back(b);
    }

    scc_fee.push_back(0);
    for (int i = 1; i <= n; ++i) {
        if (!found[i]) {
            tarjan(i);
        }
    }

    scc_cnt.assign(n_scc + 1, 0);
    for (int i = 1; i <= n; ++i) {
        scc_cnt[scc_id[i]] += (fee[i] == scc_fee[scc_id[i]] ? 1 : 0);
    }

    long long total = 0;
    long long total_cnt = 1;
    for (int i = 1; i <= n_scc; ++i) {
        total += scc_fee[i];
        total_cnt = (total_cnt * scc_cnt[i]) % MOD;
    }

    cout << total << " " << total_cnt;
}
