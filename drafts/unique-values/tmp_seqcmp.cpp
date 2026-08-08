#include <bits/stdc++.h>
using namespace std;

bool brute(vector<int> a, int m){
    int n=(int)a.size()-1;
    int T=160;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vis[0][0]=1;
    for(int t=0;t<T;t++) for(int p=0;p<=n+1;p++) if(vis[t][p]){
        if(1<=p && p<=n && (a[p]+t)%m==0) continue;
        for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
    }
    for(int t=0;t<=T;t++) if(vis[t][n+1]) return true;
    return false;
}

bool seq_cond(vector<int> a,int m){
    int n=(int)a.size()-1;
    vector<int>d(n+1);
    for(int i=1;i<=n;i++) d[i]=((-(a[i]+i))%m + m)%m;
    // DP on residue with minimum value?
    // brute over x up to LIMIT
    int LIM=80;
    vector<vector<char>> dp(n+1, vector<char>(LIM+1,0));
    for(int x=0;x<=LIM;x++) if(x%m!=d[1]) dp[1][x]=1;
    for(int i=2;i<=n;i++){
        int pref=0;
        for(int x=0;x<=LIM;x++){
            pref|=dp[i-1][x];
            if(pref && x%m!=d[i]) dp[i][x]=1;
        }
    }
    for(int x=0;x<=LIM;x++) if(dp[n][x]) return true;
    return false;
}

int main(){
    for(int m=2;m<=8;m++){
        bool hasNo=false;
        for(int n=1;n<=8;n++){
            long long tot=1;
            for(int i=0;i<n;i++) tot*=m;
            for(long long mask=0;mask<tot;mask++){
                vector<int>a(n+1);
                long long x=mask;
                for(int i=1;i<=n;i++){a[i]=x%m; x/=m;}
                bool b=brute(a,m);
                bool s=seq_cond(a,m);
                if(b!=s){
                    cout<<"m="<<m<<" n="<<n<<" mismatch b="<<b<<" s="<<s<<" a=";
                    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
                    cout<<"\n";
                    return 0;
                }
                if(!b) hasNo=true;
            }
        }
        cout<<"m="<<m<<" checked, hasNo="<<hasNo<<"\n";
    }
}
