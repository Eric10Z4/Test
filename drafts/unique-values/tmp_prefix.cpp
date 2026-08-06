#include <bits/stdc++.h>
using namespace std;
int main(){
 int n=4,m=3; vector<int>a={0,1,1,0,0};
 for(int lim=1;lim<=4;lim++){
  int T=80;
  vector<vector<char>> vis(T+1, vector<char>(lim+1,0));
  vis[0][0]=1;
  set<int> S;
  for(int t=0;t<T;t++) for(int p=0;p<=lim;p++) if(vis[t][p]){
    if(1<=p&&p<=lim && (a[p]+t)%m==0) continue;
    if(p==lim){
      int x=((t-p)%m+m)%m; S.insert(x);
    }
    for(int np=max(0,p-1); np<=min(lim,p+1); np++) vis[t+1][np]=1;
  }
  cout<<"lim="<<lim<<" S:"; for(int x:S) cout<<x<<' '; cout<<"\n";
 }
}
