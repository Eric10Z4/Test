#include <bits/stdc++.h>
using namespace std;

bool bruteD(vector<int> D,int m){
    int n=D.size()-1;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) a[i]=(( -D[i]-i)%m + m)%m;
    int T=160;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vis[0][0]=1;
    for(int t=0;t<T;t++) for(int p=0;p<=n+1;p++) if(vis[t][p]){
        if(1<=p&&p<=n&&(a[p]+t)%m==0) continue;
        for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
    }
    for(int t=0;t<=T;t++) if(vis[t][n+1]) return true;
    return false;
}

int main(){
    int m=3,n=4;
    long long tot=1; for(int i=0;i<n;i++) tot*=m;
    for(long long mask=0;mask<tot;mask++){
        vector<int>D(n+1); long long x=mask;
        for(int i=1;i<=n;i++){D[i]=x%m; x/=m;}
        if(!bruteD(D,m)){
            for(int i=1;i<=n;i++) cout<<D[i];
            cout<<"\n";
        }
    }
}
