#include <bits/stdc++.h>
using namespace std;
bool st[1000005];
int primes[1000005],cnt;
int a[100005],b[100005];
void get_primes(int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(!st[i]) primes[cnt++] = i;	
		for(int j = 0; primes[j] <= n / i; j++)
		{
			st[primes[j] * i] = true;  
			if(i % primes[j] == 0) break; 
        }
	}
}
bool check(int x,int u)
{
    u = 0;
    while(primes[u] <= sqrt(x))
    {
        int d = x;
        while(d % primes[u] == 0) d = d / primes[u];
        if(d == 1) 
        {
            a[u] = primes[u];
            return false;
        }
        u ++;
    }
        
    return true;
}
void solve()
{
    int n;
    cin >> n;
    
    bool f = 1;
    cin >> a[0];
    int maxs = a[0];
    for(int i = 1; i < n; i ++) 
    {
        cin >> a[i];
        if(a[i] < maxs) f = 0;
        maxs = max(maxs, a[i]);
    }
    maxs = 0;
    if(f) 
    {
        cout << "Bob" << endl;
        return;
    }
    for(int i = 0; i < n; i ++) 
    {
        if(st[a[i]] == true)
        {
           // cout << a[i] << " ";
            if(check(a[i], i) == true)
            {
                cout << "Alice" << endl;
                return;
            }
        }
    }
    maxs = a[0];
    f = 1;
    for(int i = 1; i < n; i ++) 
    {
        if(a[i] < maxs) f = 0;
        maxs = max(maxs, a[i]);
    }
    if(f) 
        cout << "Bob" << endl;
    else 
        cout << "Alece" << endl;

    }
int main ()
{
    get_primes(1000000);
    
    int t;
    cin >> t;
    
    while(t --) solve();
}