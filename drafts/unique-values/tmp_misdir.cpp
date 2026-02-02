#include <bits/stdc++.h>
using namespace std;

bool brute(vector<int> a, int m){
    int n=(int)a.size()-1;int T=180;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vis[0][0]=1;
    for(int t=0;t<T;t++) for(int p=0;p<=n+1;p++) if(vis[t][p]){
        if(1<=p&&p<=n&&(a[p]+t)%m==0) continue;
        for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
    }
    for(int t=0;t<=T;t++) if(vis[t][n+1]) return true;
    return false;
}

bool alg(vector<int> a, int m){
    int n=(int)a.size()-1;
    vector<int>D(n+1);
    for(int i=1;i<=n;i++) D[i]=(m-((a[i]+i)%m))%m;
    int L=(D[1]+1)%m, R=(D[1]-1+m)%m;
    auto dist=[&](int st,int ed){return (ed-st+m)%m;};
    bool ok=true;
    for(int i=2;i<=n;i++){
        int d=D[i];
        if(dist(L,d)<=dist(L,R)){
            if(d==R&&L==R){ok=false;break;}
            if(d!=R) L=(d+1)%m;
        }
        R=(d-1+m)%m;
    }
    return ok;
}

int main(){
    long long fp=0,fn=0,tot=0;
    for(int m=2;m<=8;m++) for(int n=2;n<=8;n++){
        long long T=1; for(int i=0;i<n;i++) T*=m;
        for(long long mask=0;mask<T;mask++){
            vector<int>a(n+1); long long x=mask;
            for(int i=1;i<=n;i++){a[i]=x%m; x/=m;}
            bool b=brute(a,m), s=alg(a,m);
            if(s&&!b) fp++;
            if(!s&&b) fn++;
            tot++;
        }
    }
    cout<<"tot="<<tot<<" fp="<<fp<<" fn="<<fn<<"\n";
}
