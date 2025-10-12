#include <bits/stdc++.h>

#define ll long long

using namespace std;

constexpr ll mod = 998244353;

int main()
{
    int t = 1;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        
        ll b = 0;
        set<int> st;
        int c = 0;
        
        for (int i = 1; i <= n; i++) {
            if (st.find(a[i]) != st.end()) {
                b += a[i] * 2;
                st.erase(a[i]);
                c += 2;
            } else {
                st.insert(a[i]);
            }
        }
        
        if (b == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<int> nw;
        ll mx = b;
        for (auto x : st) {
            nw.push_back(x);
            if (b > x)
                mx = max(mx, b + x);
        }
        
        ll s = b;
        for (int i = 0; i < nw.size(); i++) {
            int l = i + 1, r = nw.size() - 1, re = -1;
            while (l <= r) {
                int m = l + (r - l) / 2;
                if (b + nw[i] > nw[m]) {
                    re = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            if (re != -1)
                s = max(s, b + nw[i] + nw[re]);
        }
        
        if (c == 2 && mx == b && s == b)
            cout << 0 << "\n";
        else
            cout << max(mx, s) << "\n";
    }
    
    return 0;
}