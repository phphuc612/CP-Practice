#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> vert;
unordered_map<string, int> umap;
vector<string> rev_map;
vector<bool> found;
vector<int> low, num;
vector<int> trace;
int cnt;
string s1, s2;
int n, m, t(0);

void init() {
    vert.assign(n, vector<int>());
    umap.clear();
    rev_map.clear();
    found.assign(n, false);
    low.assign(n, -1);
    num.assign(n, -1);
    trace.clear();
    cnt = 0;
}

void tarjan(int u) {
    trace.push_back(u);
    low[u] = num[u] = cnt++;

    for (const int& v: vert[u]) {
        if (found[v]) continue;
        if (num[v] != -1) {
            low[u] = min(low[u], num[v]);
        } else {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if (low[u] == num[u]) {
        while (!trace.empty()) {
            int vertex = trace[trace.size() - 1];
            found[vertex] = true;
            trace.pop_back();
            if (vertex == u) {
                cout << rev_map[u] << endl;
                return;
            } else {
                cout << rev_map[vertex] << ", ";
            }
        }
    }
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }

        ++t;
        if (t != 1) {
            cout << endl;
        }

        init();

        for (int i = 0; i < m; i++) {
            cin >> s1 >> s2;
            if (umap.find(s1) == umap.end()) {
                umap[s1] = cnt++; // string -> int : map
                rev_map.push_back(s1); // int -> string : map / vector
            }
            if (umap.find(s2) == umap.end()) {
                umap[s2] = cnt++;
                rev_map.push_back(s2);
            }

            int u = umap[s1];
            int v = umap[s2];

            vert[u].push_back(v);
        }

        cout << "Calling circles for data set " << t << ":\n";

        cnt = 0; // reset count
        for (int i = 0; i < n; ++i) {
            if (!found[i]) {
                tarjan(i);
            }
        }
    }
}
