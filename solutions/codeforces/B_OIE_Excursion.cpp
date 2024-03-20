#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    ll m;
    cin >> n >> m;

    vector<ll> d(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll a;
        cin >> a;
        d[i] = (m - (a + i) % m) % m;
    }

    ll l = (d[1] + 1) % m;
    ll r = (d[1] - 1 + m) % m;
    bool ok = true;

    auto dis = [&](ll x, ll y) {
        return (y - x + m) % m;
    };

    for (int i = 2; i <= n; ++i) {
        ll x = d[i];
        if (dis(l, x) <= dis(l, r)) {
            if (x == r && l == r) {
                ok = false;
                break;
            }
            if (x != r) l = (x + 1) % m;
        }
        r = (x - 1 + m) % m;
    }

    cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}