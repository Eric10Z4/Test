#include <bits/stdc++.h>
using namespace std;

static int queries_used = 0;

int ask(const vector<int>& s) {
    ++queries_used;
    cout << "? " << s.size();
    for (int idx : s) {
        cout << ' ' << idx;
    }
    cout << '\n' << flush;

    int ans;
    if (!(cin >> ans)) {
        exit(0);
    }
    if (ans == -1) {
        exit(0);
    }
    return ans;
}

bool has_special_in(const vector<int>& subset, int m) {
    vector<char> in_subset(m + 1, 0);
    for (int idx : subset) {
        in_subset[idx] = 1;
    }

    vector<int> complement;
    complement.reserve(m - (int)subset.size());
    for (int i = 1; i <= m; ++i) {
        if (!in_subset[i]) {
            complement.push_back(i);
        }
    }

    int resp = ask(complement);

    // Parity property for r = answer(U \ subset):
    // r % 2 == |subset| % 2  <=> subset contains 0 special positions.
    // Otherwise subset contains at least 1 special position.
    return (resp & 1) != ((int)subset.size() & 1);
}

int find_one_special(vector<int> candidates, int m) {
    while ((int)candidates.size() > 1) {
        int mid = (int)candidates.size() / 2;
        vector<int> left(candidates.begin(), candidates.begin() + mid);

        if (has_special_in(left, m)) {
            candidates.swap(left);
        } else {
            vector<int> right(candidates.begin() + mid, candidates.end());
            candidates.swap(right);
        }
    }
    return candidates[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        int m = 2 * n + 1;

        queries_used = 0;

        vector<int> all_positions(m);
        iota(all_positions.begin(), all_positions.end(), 1);

        int x = find_one_special(all_positions, m);

        vector<int> without_x;
        without_x.reserve(m - 1);
        for (int i = 1; i <= m; ++i) {
            if (i != x) {
                without_x.push_back(i);
            }
        }
        int y = find_one_special(without_x, m);

        vector<int> without_xy;
        without_xy.reserve(m - 2);
        for (int i = 1; i <= m; ++i) {
            if (i != x && i != y) {
                without_xy.push_back(i);
            }
        }
        int z = find_one_special(without_xy, m);

        cout << "! " << x << ' ' << y << ' ' << z << '\n' << flush;
    }

    return 0;
}
