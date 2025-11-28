#include <bits/stdc++.h>
using namespace std;

bool brute(vector<int> a, int m){
    int n=a.size()-1, T=150;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vis[0][0]=1;
    for(int t=0;t<T;t++) for(int p=0;p<=n+1;p++) if(vis[t][p]){
        if(1<=p && p<=n && (a[p]+t)%m==0) continue;
        for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
    }
    for(int t=0;t<=T;t++) if(vis[t][n+1]) return true;
    return false;
}

bool alg(vector<int> a, int m){
    int n=a.size()-1;
    vector<int>D(n+1);
    for(int i=1;i<=n;i++) D[i]=(m-((a[i]+i)%m))%m;
    int L=(D[1]+1)%m, R=(D[1]-1+m)%m;
    auto dist=[&](int s,int e){return (e-s+m)%m;};
    for(int i=2;i<=n;i++){
        int d=D[i];
        if(dist(L,d)<=dist(L,R)){
            if(d==R && L==R) return false;
            if(d!=R) L=(d+1)%m;
        }
        R=(d-1+m)%m;
    }
    return true;
}

int main(){
    long long fp=0,fn=0,tot=0;
    for(int m=2;m<=5;m++) for(int n=2;n<=6;n++){
        long long all=1;
        for(int i=0;i<n;i++) all*=m;
        for(long long code=0; code<all; code++){
            vector<int>a(n+1); long long x=code;
            for(int i=1;i<=n;i++){a[i]=x%m; x/=m;}
            bool b=brute(a,m), s=alg(a,m);
            fp += (s&&!b);
            fn += (!s&&b);
            tot++;
        }
    }
    cout<<"tot="<<tot<<" fp="<<fp<<" fn="<<fn<<"\n";
}
