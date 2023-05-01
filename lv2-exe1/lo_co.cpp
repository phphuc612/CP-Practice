#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e3 + 1;

int n;
int arr[MAX];
vector<int> edges[MAX];
int cnt[MAX];
int ans = 1;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    vector<pair<int, int>> st;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int k = lower_bound(arr, arr + n, arr[i] + arr[j]) - arr;
            if (k < n && arr[k] == arr[i] + arr[j]) {
                edges[i].push_back(k);
                edges[j].push_back(k);
            }
        }
    }

    // Block (1)
    //for (int i = 0; i < n; ++i){
    //    if (edges[i].size() > 0)
    //        swap(edges[i][0], edges[i][edges[i].size() - 1]);
    //}

    for (int i = 0; i < n; ++i) {
        if (cnt[i] == 0) {
            vector<int> st;
            st.push_back(i);
            // This only applies for sorted edge list. Experiment with block (1)
            // Or else, we should implement ordinary DFS
            while (!st.empty()) {
                int u = st.back();
                bool fl = true;
                for (const int& v: edges[u]) {
                    if (cnt[v] != 0) {
                        cnt[u] = max(cnt[u], cnt[v] + 1);
                    } else {
                        cnt[v] = 1;
                        st.push_back(v);
                        fl = false;
                    }
                }
                if (fl) {
                    st.pop_back();
                }
            }

            ans = max(ans, cnt[i]);
        }
    }
    cout << ans;
}
