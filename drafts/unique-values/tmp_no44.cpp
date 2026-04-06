#include <bits/stdc++.h>
using namespace std;
bool brute(vector<int>a,int m){int n=a.size()-1;int T=200;vector<vector<char>>vis(T+1,vector<char>(n+2,0));vis[0][0]=1;for(int t=0;t<T;t++)for(int p=0;p<=n+1;p++)if(vis[t][p]){if(1<=p&&p<=n&&(a[p]+t)%m==0)continue;for(int np=max(0,p-1);np<=min(n+1,p+1);np++)vis[t+1][np]=1;}for(int t=0;t<=T;t++)if(vis[t][n+1])return true;return false;}
int main(){int m=4,n=4;long long tot=1;for(int i=0;i<n;i++)tot*=m;long long cnt=0;for(long long mask=0;mask<tot;mask++){vector<int>a(n+1);long long x=mask;for(int i=1;i<=n;i++){a[i]=x%m;x/=m;}if(!brute(a,m)){cnt++;cout<<"a:";for(int i=1;i<=n;i++)cout<<a[i]<<' ';cout<<" D:";for(int i=1;i<=n;i++){int d=((-(a[i]+i))%m+m)%m;cout<<d<<' ';}cout<<"\n";}}
cerr<<"cnt="<<cnt<<"\n";
}
