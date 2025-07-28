#include <bits/stdc++.h>
using namespace std;

static int matchGT(const vector<int>& big, const vector<int>& small) {
    int i = 0, j = 0, m = 0;
    while (i < (int)big.size() && j < (int)small.size()) {
        if (big[i] > small[j]) {
            ++m;
            ++i;
            ++j;
        } else {
            ++i;
        }
    }
    return m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, pc;
        string sa, sb;
        cin >> n >> sa >> sb >> pc;

        vector<int> AS, AD, BS, BD;
        AS.reserve(n);
        AD.reserve(n);
        BS.reserve(n);
        BD.reserve(n);

        for (int i = 0; i < n; ++i) {
            if (sa[i] == '1') AS.push_back(i + 1);
            else if (sa[i] == '2') AD.push_back(i + 1);
            if (sb[i] == '1') BS.push_back(i + 1);
            else if (sb[i] == '2') BD.push_back(i + 1);
        }

        vector<int> AL, AH, BL, BH;
        for (int r : AS) {
            if (r < pc) AL.push_back(r);
            else AH.push_back(r);
        }
        for (int r : BS) {
            if (r < pc) BL.push_back(r);
            else BH.push_back(r);
        }

        bool Awin = false;
        int need = (int)AL.size() - 1;
        if (need <= 0) {
            Awin = true;
        } else if ((int)BH.size() >= need) {
            int s1 = matchGT(AH, BH);
            int s2 = matchGT(AD, BD);
            Awin = (s1 + s2 >= need);
        }

        bool Bwin = false;
        if ((int)BL.size() <= 1) {
            int totalB = (int)BS.size() + (int)BD.size();
            if (totalB == 1) {
                if (!BS.empty()) {
                    int r = BS[0];
                    Bwin = (!AS.empty() && AS.front() < r);
                } else {
                    int r = BD[0];
                    Bwin = (!AD.empty() && AD.front() < r);
                }
            } else {
                bool safeSingle = (!BH.empty() && !AS.empty() && BH.back() > AS.front());
                bool safeDouble = (!BD.empty() && !AD.empty() && BD.back() > AD.front());
                Bwin = safeSingle || safeDouble;
            }
        }

        cout << ((Awin || Bwin) ? "Yes" : "No") << '\n';
    }
    return 0;
}
