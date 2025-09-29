#include <bits/stdc++.h>
using namespace std;

bool brute(vector<int> a, int m){
    int n=(int)a.size()-1;
    int T=120;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vis[0][0]=1;
    for(int t=0;t<T;t++){
        for(int p=0;p<=n+1;p++) if(vis[t][p]){
            if(1<=p && p<=n && (a[p]+t)%m==0) continue;
            for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
        }
    }
    for(int t=0;t<=T;t++) if(vis[t][n+1]) return true;
    return false;
}

bool alg(vector<int> a, long long m){
    int n=(int)a.size()-1;
    vector<long long> D(n+1);
    for(int i=1;i<=n;i++) D[i]=(m - ( (a[i] + i)%m ))%m;
    long long L=(D[1]+1)%m, R=(D[1]-1+m)%m;
    auto dist=[&](long long st,long long ed){return (ed-st+m)%m;};
    bool ok=true;
    for(int i=2;i<=n;i++){
        long long d=D[i];
        if(dist(L,d)<=dist(L,R)){
            if(d==R && L==R){ok=false;break;}
            if(d!=R) L=(d+1)%m;
        }
        R=(d-1+m)%m;
    }
    return ok;
}

int main(){
    for(int m=2;m<=9;m++){
        for(int n=2;n<=8;n++){
            long long tot=1;
            for(int i=0;i<n;i++) tot*=m;
            for(long long mask=0;mask<tot;mask++){
                vector<int> a(n+1);
                long long x=mask;
                for(int i=1;i<=n;i++){a[i]=x%m; x/=m;}
                bool b=brute(a,m);
                bool s=alg(a,m);
                if(b!=s){
                    cout<<"m="<<m<<" n="<<n<<" mismatch brute="<<b<<" alg="<<s<<" a=";
                    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
                    cout<<"\n";
                    return 0;
                }
            }
        }
    }
    cout<<"no mismatch in searched range\n";
}
