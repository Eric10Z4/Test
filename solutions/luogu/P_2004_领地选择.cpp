#include <bits/stdc++.h>
using namespace std;
int a[1005][1005], c, n, m, x, y, h[1005][1005];
int main()
{
    cin >> n >> m >> c;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
        {
            cin >> a[i][j];
            h[i][j] = h[i - 1][j] + (h[i][j - 1] - h[i - 1][j - 1]) + a[i][j]; 
        }

    int ans = -2147483648;
    for(int i = 1; i <= n - c + 1; i ++)
        for(int j = 1; j <= m - c + 1; j ++)
        {
            int u = ans;
            ans = max(ans, h[i + c - 1][j + c - 1] - h[i - 1][j + c - 1] - h[i + c - 1][j - 1] + h[i - 1][j - 1]);
            if(ans != u)
            {
                x = i, y = j;
            }
        }
    cout << x << " " << y << endl;
}