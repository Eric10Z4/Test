#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n, x, y; 
    cin >> n >> x >> y;
    int a[n + 5], b[n + 5], cnta = 0, cntb = 0, minb = n + 6,minbt = 0, mina = n + 6, minat = 0;
    for(int i = 0; i < x; i ++)
    {
        cin >> a[cnta ++];
        if(mina > a[cnta - 1])
        {
            minat = cnta - 1;
            mina = a[cnta - 1];
        }
    }
    for(int i = x; i < y; i ++)
    {
        cin >> b[cntb ++];
        if(minb > b[cntb - 1])
        {
            minbt = cntb - 1;
            minb = b[cntb - 1];
        }
    }
    
    for(int i = y; i < n; i ++)
    {
        cin >> a[cnta ++];
        if(mina > a[cnta - 1])
        {
            minat = cnta - 1;
            mina = a[cnta - 1];
        }
    }
    // for(int i = 0; i < cnta; i ++) cout << a[i] << " ";
    // cout << endl;
    // for(int i = 0; i < cntb; i ++) cout << b[i] << " ";
    // cout << endl;
    bool flag = 1;
    for(int i = 0; i < cnta; i ++)
    {
        int d = i;
        if(a[d] > b[minbt] && flag)
        {
            flag = 0;
            for(int j = 0; j < cntb; j ++)
            {
                int k = (j + minbt) % cntb;
                cout << b[k] << " ";
            }
        }
        cout << a[d] << " ";
    }
    if(flag)
    {
        for(int j = 0; j < cntb; j ++)
            {
                int k = (j + minbt) % cntb;
                cout << b[k] << " ";
            }
    }
    cout << endl;
}
int main()
{
    int t;
    cin >> t;
    while(t --) solve();
}