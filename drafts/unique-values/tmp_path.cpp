#include <bits/stdc++.h>
using namespace std;
int main(){
    int n=3,m=3; vector<int>a={0,1,2,0};
    int T=20;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vector<vector<pair<int,int>>> pre(T+1, vector<pair<int,int>>(n+2, {-1,-1}));
    vis[0][0]=1;
    for(int t=0;t<T;t++){
        for(int p=0;p<=n+1;p++) if(vis[t][p]){
            if(1<=p && p<=n && (a[p]+t)%m==0) continue;
            for(int np=max(0,p-1); np<=min(n+1,p+1); np++){
                if(!vis[t+1][np]){
                    vis[t+1][np]=1;
                    pre[t+1][np]={t,p};
                }
            }
        }
    }
    int et=-1;
    for(int t=0;t<=T;t++) if(vis[t][n+1]){et=t; break;}
    cout<<"et="<<et<<"\n";
    int t=et,p=n+1;
    vector<pair<int,int>> path;
    while(t!=-1){path.push_back({t,p}); auto q=pre[t][p]; t=q.first; p=q.second;}
    reverse(path.begin(), path.end());
    for(auto [tt,pp]:path){
        cout<<"(t="<<tt<<",p="<<pp;
        if(1<=pp&&pp<=n) cout<<",watch="<<((a[pp]+tt)%m==0);
        cout<<")\n";
    }
}
