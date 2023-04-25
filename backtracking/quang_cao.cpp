#include <bits/stdc++.h>

using namespace std;

bool arr[11][101];
int n, m;
int res = 0;
int row_trace = 0;
vector<bool> col_trace;

void neg(int k) {
    int i = 0;
    int tmp = 1;
    while (tmp <= k) {
        if (tmp & k) {
            for (int j = 0; j < m; ++j) {
                arr[i][j] = !arr[i][j];
            }
        }
        
        tmp <<= 1;
        ++i;
    }
}

bool Try(int k) {
    neg(k);

    int ans = 0;
    vector<bool> tmp_trace;
    for (int j = 0; j < m; ++j) {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += arr[i][j];
        }

        tmp_trace.push_back(n - cnt > cnt);
        ans += max(n - cnt, cnt);
    }

    neg(k);
    if (res < ans) {
        res = ans;
        col_trace = tmp_trace;
        return true;
    } 
    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
            res += arr[i][j];
        }
    }

    col_trace.assign(m, false);
    row_trace = 0;
    for (int k = 0; k < (1 << n); ++k) {
        if (Try(k)) {
            row_trace = k;
        }
    }

    cout << res << endl;

    int cnt = 0;
    int tmp = 1;
    while (tmp <= row_trace) {
        if (tmp & row_trace) 
            ++cnt;
        tmp <<= 1;
    }
    for (const auto& tmp: col_trace) {
        cnt += tmp;
    }

    cout << cnt << endl;


    int id = 0;
    tmp = 1;
    while (tmp <= row_trace) {
        if (tmp & row_trace) 
            cout << 'R' << id + 1 << endl;
        tmp <<= 1;
        ++id;

    }
    for (int i = 0; i < col_trace.size(); ++i) {
        if (col_trace[i]) {
            cout << 'C' << i + 1 << endl;
        }
    }
}