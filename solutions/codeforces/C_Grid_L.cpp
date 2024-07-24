#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	ll p, q;
	cin >> p >> q;

	ll s = p + 2 * q;
	ll x = 2 * s + 1;

	for (ll d = 1; d * d <= x; ++d) {
		if (x % d) continue;

		ll a = d;
		ll b = x / d;

		if ((a & 1) == 0 || (b & 1) == 0) continue;

		ll n = (a - 1) / 2;
		ll m = (b - 1) / 2;

		if (n <= 0 || m <= 0) continue;

		ll h = (n + 1) * m;
		ll v = (m + 1) * n;

		if (min(h, v) >= q) {
			cout << n << ' ' << m << '\n';
			return;
		}
	}

	cout << -1 << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) solve();

	return 0;
}
