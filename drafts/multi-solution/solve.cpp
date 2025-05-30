#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q;
    if(!(cin>>n>>q)) return 0;
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}    
    int L=1;while((1<<L)<=n) L++;
    vector<int> d(n+1,0), p(n+1,0);
    vector<vector<int>> up(L, vector<int>(n+1,0));
    {
        int r=1;
        vector<int> st;
        st.push_back(r);
        p[r]=r;up[0][r]=r;d[r]=0;
        while(!st.empty()){
            int x=st.back();st.pop_back();
            for(int y:g[x]) if(y!=p[x]){p[y]=x; d[y]=d[x]+1; up[0][y]=p[y]; st.push_back(y);}        
        }
        for(int i=1;i<L;i++) for(int v=1;v<=n;v++) up[i][v]=up[i-1][ up[i-1][v] ];
    }
    auto lca = [&](int a,int b){
        if(a==0||b==0) return 0;
        if(d[a]<d[b]) swap(a,b);
        int k=d[a]-d[b];
        for(int i=0;i<L;i++) if(k>>i&1) a=up[i][a];
        if(a==b) return a;
        for(int i=L-1;i>=0;i--) if(up[i][a]!=up[i][b]){a=up[i][a];b=up[i][b];}
        return up[0][a];
    };
    auto dist = [&](int a,int b){
        if(a==0||b==0) return 0;
        int c=lca(a,b);
        return d[a]+d[b]-2*d[c];
    };
    auto onp = [&](int a,int b,int x){
        if(a==0&&b==0) return true;
        return dist(a,b)==dist(a,x)+dist(x,b);
    };
    struct A{int a,b;bool ok;};
    auto emp = [&](){return A{0,0,true};};
    auto one = [&](int x){return A{x,x,true};};
    auto comb = [&](const A& x,const A& y){
        if(!x.ok||!y.ok) return A{0,0,false};
        if(x.a==0&&x.b==0) return y;
        if(y.a==0&&y.b==0) return x;
        int cands[4]={x.a,x.b,y.a,y.b};
        int p0=cands[0];
        int mx=cands[0];
        int md=-1;
        for(int i=0;i<4;i++){int w=dist(p0,cands[i]);if(w>md){md=w;mx=cands[i];}}
        int my=cands[0];md=-1;
        for(int i=0;i<4;i++){int w=dist(mx,cands[i]);if(w>md){md=w;my=cands[i];}}
        bool ok=true;
        for(int i=0;i<4;i++) if(!onp(mx,my,cands[i])){ok=false;break;}
        if(!ok) return A{0,0,false};
        return A{mx,my,true};
    };

    vector<pair<int,A>> s1,s2;
    auto agg = [&](vector<pair<int,A>>& s){return s.empty()?emp():s.back().second;};
    auto push_back_q = [&](int x){A t=comb(agg(s1), one(x)); s1.push_back({x,t});};
    auto move = [&](){
        if(!s2.empty()) return;
        while(!s1.empty()){
            int x=s1.back().first; s1.pop_back();
            A t=comb(agg(s2), one(x));
            s2.push_back({x,t});
        }
    };
    auto pop_front_q = [&](){
        move();
        if(!s2.empty()) s2.pop_back();
    };
    auto total = [&](){return comb(agg(s2), agg(s1));};

    string out;
    for(int i=0;i<q;i++){
        int t;cin>>t;
        if(t==1){int x;cin>>x;push_back_q(x);} 
        else if(t==2){pop_front_q();}
        else if(t==3){A z=total(); out.push_back((z.ok?'1':'0'));}
    }
    cout<<out;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

struct D {
    vector<int> p, r;
    D(int n=0) { p.resize(n); r.assign(n,0); iota(p.begin(), p.end(), 0); }
    int f(int x){ return p[x]==x?x:p[x]=f(p[x]); }
    void u(int a,int b){ a=f(a); b=f(b); if(a==b) return; if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k,q;
    if(!(cin>>k>>q)) return 0;
    vector<int> p(k);
    for(int i=0;i<k;i++) cin>>p[i];
    vector<int> off(k+1,0);
    for(int i=0;i<k;i++) off[i+1]=off[i]+p[i];
    D d(off[k]);
    for(int i=0;i+1<k;i++){
        int a=p[i], b=p[i+1];
        int u=0,v=0;
        while(u<a && v<b){
            long long s1=u, e1=u+1, d1=a;
            long long s2=v, e2=v+1, d2=b;
            long long l1=s1*d2, l2=s2*d1;
            long long r1=e1*d2, r2=e2*d1;
            long long L=max(l1,l2), R=min(r1,r2);
            if(L<R){
                d.u(off[i]+u, off[i+1]+v);
            }
            if(r1<r2) u++; else v++;
        }
    }
    string out; out.resize(q);
    for(int t=0;t<q;t++){
        int i,j,x,y;
        cin>>i>>j>>x>>y;
        i--; x--; j--; y--;
        int a=off[i]+j;
        int b=off[x]+y;
        out[t]=(d.f(a)==d.f(b))?'1':'0';
    }
    cout<<out;
    return 0;
}
