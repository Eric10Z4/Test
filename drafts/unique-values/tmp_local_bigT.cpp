#include <bits/stdc++.h>
using namespace std;

vector<int> prefixMask(vector<int> a, int m){
    int n=(int)a.size()-1;
    int T=1000;
    vector<vector<char>> vis(T+1, vector<char>(n+1,0));
    vis[0][0]=1;
    vector<int> mask(n+1,0);
    for(int t=0;t<T;t++) for(int p=0;p<=n;p++) if(vis[t][p]){
        if(1<=p && p<=n && (a[p]+t)%m==0) continue;
        if(1<=p && p<=n){
            int x=((t-p)%m+m)%m;
            mask[p]|=(1<<x);
        }
        for(int np=max(0,p-1); np<=min(n,p+1); np++) vis[t+1][np]=1;
    }
    return mask;
}

int main(){
    for(int m=2;m<=6;m++){
        bool ok=true;
        unordered_map<long long,int> mp;
        for(int n=2;n<=6 && ok;n++){
            long long tot=1;
            for(int i=0;i<n;i++) tot*=m;
            for(long long code=0;code<tot && ok;code++){
                vector<int>a(n+1);
                long long x=code;
                for(int i=1;i<=n;i++){a[i]=x%m; x/=m;}
                auto mask=prefixMask(a,m);
                vector<int>D(n+1);
                for(int i=1;i<=n;i++) D[i]=((-(a[i]+i))%m+m)%m;
                for(int i=1;i<n;i++){
                    int Si=mask[i], Sip1=mask[i+1];
                    long long key=Si;
                    key=key*16 + D[i];
                    key=key*16 + D[i+1];
                    auto it=mp.find(key);
                    if(it==mp.end()) mp[key]=Sip1;
                    else if(it->second!=Sip1){
                        ok=false;
                        cout<<"m="<<m<<" inconsistent key found\n";
                        cout<<"Si="<<Si<<" Di="<<D[i]<<" Dip1="<<D[i+1]<<" old="<<it->second<<" new="<<Sip1<<"\n";
                        return 0;
                    }
                }
            }
        }
        cout<<"m="<<m<<" deterministic="<<ok<<"\n";
    }
}
