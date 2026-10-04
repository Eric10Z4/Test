#include <bits/stdc++.h>
using namespace std;
int main(){
    int n=4,m=3; vector<int>a={0,1,1,0,0};
    int T=80;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vis[0][0]=1;
    vector<set<int>> sx(n+2), sy(n+2);
    for(int t=0;t<T;t++){
        for(int p=0;p<=n+1;p++) if(vis[t][p]){
            bool safe=true;
            if(1<=p&&p<=n && (a[p]+t)%m==0) safe=false;
            if(!safe) continue;
            sy[p].insert(t%m);
            if(1<=p&&p<=n) sx[p].insert((t-p)%m<0?(t-p)%m+m:(t-p)%m);
            for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<"i="<<i<<" y:";
        for(int r:sy[i]) cout<<r<<' ';
        cout<<" x:";
        for(int r:sx[i]) cout<<r<<' ';
        cout<<"\n";
    }
}
