#include <bits/stdc++.h>
using namespace std;

bool cmp(vector<int>& A, vector<int>& B, int d) {
    int la = A.size();
    int lb = B.size() + d;
    
    if (la != lb) return la > lb;
    
    for (int i = B.size() - 1; i >= 0; i--) {
        if (A[i + d] != B[i]) {
            return A[i + d] > B[i];
        }
    }
    return true;
}

void sub(vector<int>& A, vector<int>& B, int d) {
    int t = 0;
    for (int i = 0; i < B.size() || t; i++) {
        int v = t;
        if (i < B.size()) v += B[i];
        
        A[i + d] -= v;
        if (A[i + d] < 0) {
            A[i + d] += 10;
            t = 1;
        } else {
            t = 0;
        }
    }
    while (A.size() > 1 && A.back() == 0) A.pop_back();
}

vector<int> div(vector<int> &A, vector<int> &B) {
    vector<int> C;
    
    if (A.size() < B.size()) return {0};
    
    int d = A.size() - B.size();
    C.assign(d + 1, 0);
    
    for (int i = d; i >= 0; i--) {
        while (cmp(A, B, i)) {
            sub(A, B, i);
            C[i]++;
        }
    }
    
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    
    return C;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string sa, sb;
    cin >> sa >> sb;
    
    vector<int> A, B;
    for (int i = sa.size() - 1; i >= 0; i--) A.push_back(sa[i] - '0');
    for (int i = sb.size() - 1; i >= 0; i--) B.push_back(sb[i] - '0');
    
    vector<int> C = div(A, B);
    
    for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    cout << "\n";
    
    return 0;
}