#include <bits/stdc++.h>
using namespace std;
unsigned long long n, m, a[1000000];
int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; i ++)
    {
        cin >> a[i];
        if(a[i] > m) 
        {
            i --;
            n --;
        }
    } 
    a[n] = m;
    sort(a, a + n + 1);
    if(a[0] != 1) 
    {
        cout << "No answer!!!";
        return 0;
    }
    unsigned long long t = 0,ans = 0;
    for(int i = 0; i < n; i ++)
    {
        if(t < a[i + 1] - 1)
        {
            unsigned long long k = (a[i + 1] - t - 1 + a[i] - 1) / a[i];
            ans += k;
            t += k * a[i];
            if(t >= m)
            {
                cout << ans << endl;
                return 0;
            }
        }
        
    }
    cout << ans + 1 << endl;
}