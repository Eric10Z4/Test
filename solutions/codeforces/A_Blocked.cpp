#include <bits/stdc++.h>
using namespace std;

int a[205];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];

        sort(a + 1, a + n + 1);

        bool ok = true;
        for (int i = 2; i <= n; ++i) {
            if (a[i] == a[i - 1]) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << -1 << '\n';
            continue;
        }

        for (int i = n; i >= 1; --i) {
            if (i != n) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }

    return 0;
}