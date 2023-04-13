// https://cses.fi/problemset/task/1679/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;

int n, m;
int in[MAX];
vector<int> arr[MAX];
vector<int> result;

int main()
{
    cin >> n >> m;

    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        arr[a].push_back(b);
        ++in[b];
    }

    queue<int> qu;
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0) {
            qu.push(i);
        }
    }

    while (!qu.empty()) {
        a = qu.front();
        result.push_back(a);
        qu.pop();

        for (const int& b: arr[a]) {
            if (--in[b] == 0) {
                qu.push(b);
            }
        }
    }

    if (result.size() == n) {
        for (const int& a: result) {
            cout << a << " ";
        }
    } else {
        cout << "IMPOSSIBLE";
    }
}
