#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;
void init()
{
}
void solve()
{
    int n;
    cin >> n;
    string sa, sb;
    cin >> sa >> sb;
    sa = " " + sa;
    sb = " " + sb;
    int Pc;
    cin >> Pc;
    set<int> smaller_A;
    set<int> Paired_A;
    set<int> bigger_A;
    for (int i = 1; i <= n; i++)
    {
        if (sa[i] == '1')
        {
            if (i < Pc)
            {
                smaller_A.insert(i);
            }
            else
            {
                bigger_A.insert(i);
            }
        }
        else if (sa[i] == '2')
        {
            Paired_A.insert(i);
        }
    }
    set<int> smaller_B;
    set<int> Paired_B;
    set<int> bigger_B;
    for (int i = 1; i <= n; i++)
    {
        if (sb[i] == '1')
        {
            if (i < Pc)
            {
                smaller_B.insert(i);
            }
            else
            {
                bigger_B.insert(i);
            }
        }
        else if (sb[i] == '2')
        {
            Paired_B.insert(i);
        }
    }
    if (smaller_B.size() <= 1)
    {
        if (bigger_B.size() && smaller_A.size())
        {
            cout << "Yes" << endl;
            return;
        }
        if (bigger_B.size() && bigger_A.size() && *bigger_A.begin() < *bigger_B.rbegin())
        {
            cout << "Yes" << endl;
            return;
        }
        if (Paired_A.size() && Paired_B.size())
        {
            if (*Paired_A.begin() < *Paired_B.rbegin())
            {
                cout << "Yes" << endl;
                return;
            }
        }
    }
    while (smaller_A.size())
    {
        if (bigger_B.size())
        {
            auto u = bigger_B.rbegin();
            if (Paired_A.size() && Paired_B.size())
            {
                auto paired_choose_B = *Paired_B.begin();
                auto better_A = (Paired_A.upper_bound(paired_choose_B));
                if (better_A != Paired_A.end())
                {
                    smaller_A.extract(*smaller_A.begin());
                    bigger_B.extract(*u);
                    Paired_B.extract(paired_choose_B);
                    Paired_A.extract(better_A);
                    continue;
                }
                // if(*Paired_B.begin())
            }
            auto u_2 = bigger_B.begin();
            if (bigger_A.size())
            {
                auto choosed_bigA = bigger_A.upper_bound(*u_2);
                if (choosed_bigA != bigger_A.end())
                {
                    bigger_A.extract(*choosed_bigA);
                    smaller_A.extract(*smaller_A.begin());
                    bigger_B.extract(*bigger_B.begin());
                    continue;
                }
            }
        }
        break;
    }
    if (smaller_A.size() <= 1)
    {
        cout << "Yes" << endl;
        return;
    }
    else
    {
        cout << "No" << endl;
        return;
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    t = 1;
    cin >> t;
    init();
    while (t--)
    {
        solve();
    }
}