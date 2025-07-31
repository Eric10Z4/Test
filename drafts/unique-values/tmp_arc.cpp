#include <bits/stdc++.h>
using namespace std;

vector<set<int>> getS(vector<int> a, int m){
    int n=(int)a.size()-1;
    int T=300;
    vector<vector<char>> vis(T+1, vector<char>(n+2,0));
    vis[0][0]=1;
    vector<set<int>> S(n+2);
    for(int t=0;t<T;t++) for(int p=0;p<=n+1;p++) if(vis[t][p]){
        if(1<=p && p<=n && (a[p]+t)%m==0) continue;
        if(1<=p && p<=n){
            int x=((t-p)%m+m)%m;
            S[p].insert(x);
        }
        for(int np=max(0,p-1); np<=min(n+1,p+1); np++) vis[t+1][np]=1;
    }
    return S;
}

bool isArc(const set<int>& s, int m){
    if(s.empty()) return true;
    if((int)s.size()==m) return true;
    vector<int> in(m,0);
    for(int x:s) in[x]=1;
    // s is arc iff complement is also arc? easier count transitions
    int trans=0;
    for(int i=0;i<m;i++) if(in[i]!=in[(i+1)%m]) trans++;
    return trans<=2;
}

int main(){
    for(int m=2;m<=8;m++){
        for(int n=1;n<=7;n++){
            long long tot=1;
            for(int i=0;i<n;i++) tot*=m;
            for(long long mask=0;mask<tot;mask++){
                vector<int>a(n+1);
                long long x=mask;
                for(int i=1;i<=n;i++){a[i]=x%m; x/=m;}
                auto S=getS(a,m);
                for(int i=1;i<=n;i++){
                    if(!isArc(S[i],m)){
                        cout<<"not arc m="<<m<<" n="<<n<<" i="<<i<<" a=";
                        for(int j=1;j<=n;j++) cout<<a[j]<<' ';
                        cout<<" S=";
                        for(int z:S[i]) cout<<z<<' ';
                        cout<<"\n";
                        return 0;
                    }
                }
            }
        }
    }
    cout<<"all arcs in searched range\n";
}
