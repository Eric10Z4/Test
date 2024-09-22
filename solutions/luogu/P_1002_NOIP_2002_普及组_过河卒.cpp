#include <bits/stdc++.h>
using namespace std;
long long  m, n, a, b, dp[25][25], flag[25][25];
int x[8] = {1, 2, 2, 1, -1, -1, -2, -2};
int y[8] = {2, 1, -1, -2, 2, -2, 1, -1};
int main(){
	cin >> a >> b >> m >> n;
    a += 2;
    b += 2;
    m += 2;
    n += 2;
	flag[m][n] ++;
	for(int i = 0; i <= 7; i ++) flag[m + x[i]][n + y[i]] ++;
	dp[2][2] = 1;
	for(int i = 0; i <= b; i ++)
	{
		for(int j = 0; j <= a; j ++)
		{
			if(!flag [j - 1][i] && j - 1 >= 0) dp[j][i] += dp[j - 1][i];
			if(!flag [j][i - 1] && i - 1 >= 0) dp[j][i] += dp[j][i - 1];
		}
	}
	cout << dp[a][b];
	return 0;
}
