#include <bits/stdc++.h>
using namespace std;

bool exist_strategy(vector<int> a, int m){
    int n = (int)a.size()-1;
    int T = 60; // enough for small m,n search
    vector<vector<char>> vis(T+1, vector<char>(n+2, 0));
    vis[0][0]=1;
    for(int t=0;t<T;t++){
        for(int p=0;p<=n+1;p++) if(vis[t][p]){
            bool caught = false;
            if(1<=p && p<=n){
                if((a[p]+t)%m==0) caught=true;
            }
            if(caught) continue;
            for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
        }
    }
    for(int t=0;t<=T;t++) if(vis[t][n+1]) return true;
    return false;
}

bool shift_only(vector<int> a,int m){
    int n=(int)a.size()-1;
    for(int s=0;s<m;s++){
        bool ok=true;
        for(int i=1;i<=n;i++) if((a[i]+s+i)%m==0){ok=false;break;}
        if(ok) return true;
    }
    return false;
}

int main(){
    for(int m=2;m<=8;m++){
        for(int n=1;n<=7;n++){
            long long tot=1;
            for(int i=0;i<n;i++) tot*=m;
            for(long long mask=0;mask<tot;mask++){
                vector<int> a(n+1);
                long long x=mask;
                for(int i=1;i<=n;i++){a[i]=x%m; x/=m;}
                bool e=exist_strategy(a,m);
                bool s=shift_only(a,m);
                if(e!=s){
                    cout<<"counter m="<<m<<" n="<<n<<" a=";
                    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
                    cout<<" exist="<<e<<" shift="<<s<<"\n";
                    return 0;
                }
            }
        }
    }
    cout<<"no counterexample in searched range\n";
}
