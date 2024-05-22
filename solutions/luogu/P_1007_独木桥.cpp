#include <bits/stdc++.h>
using namespace std;
int t, n, a[5005];
int main ()
{
    cin >> t >> n;
    if(!n) 
    {
        cout << "0 0";
        return 0;
    }
    int maxs = 0,mins = 0;
    for(int i = 0; i < n; i ++) 
    {
        cin >> a[i];
        int d = t + 1 - a[i];
        mins = max(min(d, a[i]), mins);
    }
    sort(a, a + n);
    maxs = max(t + 1 - a[0], a[n - 1]);
    cout << mins << " " << maxs << endl;
}