#include <bits/stdc++.h>
using namespace std;
string solve(int num)
{
    char a[] = {'I', 'X', 'C', 'M'};
    char b[] = {'V', 'L', 'D'};
    string u, ans;
    while(num)
    {
        u += char('0' + num % 10);
        num = num / 10;
    }
    for(int i = u.length() - 1; i >= 0; i --)
    {
        if(i == 3)
        {
            int d = u[i] - '0';
            while(d --) ans += 'M';
        }
        else 
        {
            if(u[i] == '9')
            {
                ans += a[i];
                ans += a[i + 1];
            }
            else if(u[i] >= '5')
            {
                ans += b[i];
                int d = u[i] - '5';
                while(d --) ans += a[i];
            }
            else if(u[i] == '4')
            {
                ans += a[i];
                ans += b[i];
            }
            else 
            {
                int d = u[i] - '0';
                while(d --) ans += a[i];
            }
        }
    }
    return ans;
}
int main()
{
    int a;
    cin >> a;
    cout << solve(a) << endl;
}