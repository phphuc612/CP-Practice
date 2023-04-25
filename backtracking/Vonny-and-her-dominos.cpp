#include <bits/stdc++.h>

using namespace std;

int arr[7][8];
bool valid[67];
long long ans = 0;

void Try(int, int, int, int);
void backtrack(int, int);

void init() {
    ans = 0;
    for (int i = 0; i < 67; ++i) {
        valid[i] = true;
    }
}

void neg(int i,int j) {
    arr[i][j] = ~arr[i][j];
}

void Try(int x1, int y1, int x2, int y2) {
    int value = arr[x1][y1] * 10 + arr[x2][y2];
    int tmp = arr[x2][y2] * 10 + arr[x1][y1];

    if (valid[value]) {
        neg(x1, y1);
        neg(x2, y2);
        valid[value] = false;
        valid[tmp] = false;

        backtrack(x1, y1 + 1);

        neg(x1, y1);
        neg(x2, y2);
        valid[value] = true;
        valid[tmp] = true;
    }
}

void backtrack(int i, int j) {
    if (i == 7) {
        ++ans;
        return;
    }

    if (j == 8) {
        return backtrack(i + 1, 0);
    }

    if (arr[i][j] < 0) {
        return backtrack(i, j + 1);
    }

    if (i < 6 && arr[i + 1][j] >= 0) {
        Try(i, j, i + 1, j);
    }

    if (j < 7 && arr[i][j + 1] >= 0) {
        Try(i, j, i, j + 1);        
    }
}

void solve() {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 8; ++j) {
            cin >> arr[i][j];
        }
    }

    backtrack(0, 0);
}

int main() {
    int t;

    cin >> t;

    while (t--) {
        init();
        solve();

        cout << ans << endl;
    }
}