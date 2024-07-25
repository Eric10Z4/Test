#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t --)
    {
        int n;
        cin >> n;
        string x;
        cin >> x;
        int u = 0,cnt = 0;
        char k[n + 5];
        k[cnt ++] = x[0];
        for(int i = 1; i < n; i ++)
        {
            if(k[cnt - 1] == x[i])
            {
                cnt -= 1;
                u += 2;
            }
            else 
                k[cnt ++] = x[i];
        }
        if(u == n) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}