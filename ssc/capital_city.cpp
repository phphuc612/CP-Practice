#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;

int n, m;
vector<int> vert[MAX];

bool found[MAX];
int low[MAX];
int num[MAX];
int scc_id[MAX];
vector<int> trace;

int n_scc = 0;
int cnt = 0;

void tarjan(int u) {
    low[u] = num[u] = ++cnt;
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

    if (low[u] == num[u]) {
        ++n_scc;
        while (!trace.empty()) {
            int v = trace.back();
            trace.pop_back();
            scc_id[v] = n_scc;
            found[v] = true;
            if (u == v) {
                break;
            }
        }
    }
}

int main() {
    cin >> n >> m;

    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        vert[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i) {
        if (!found[i]) {
            tarjan(i);
        }
    }

    vector<bool> in_degree(n_scc + 1, true);
    int cnt = n_scc;

    // If a component has in-degree = 0 -> potential
    // If it's the only one answer -> choose vetex in that component
    // If there are two or above => no answer

    for (int u = 1; u <= n; ++u) {
        for (const auto& v: vert[u]) {
            if (scc_id[v] == scc_id[u]) continue;
            if (in_degree[scc_id[v]] == true) {
                --cnt;
                in_degree[scc_id[v]] = false;
            }
        }
    }

    if (cnt == 1) {
        stringstream out;
        int cnt_ans = 0;
        for (int u = 1; u <= n; ++u) {
            if (in_degree[scc_id[u]]) {
                ++cnt_ans;
                out << u << " ";
            }
        }
        cout << cnt_ans << endl << out.str();
    } else {
        cout << 0;
    }

}
