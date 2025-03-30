# Card Checking 题解

## 题意简述

三人斗地主变体：

- A、B 同队（农民），C（地主）单人。
- C 只剩 1 张牌，点数为 `pc`。
- A 是第一轮起手。
- 允许的出牌只有两种：
  - 单牌：只能在该点数手里恰好 1 张时出。
  - 对子：该点数有 2 张时出。
- 同一轮只能跟同类型，且点数严格更大；也可以 `pass`。
- 其余规则与题面一致。

问：在最优策略下，农民是否必胜。

---

## 核心观察

1. C 只有 1 张牌，所以它只能参与单牌对抗，且阈值就是 `pc`。
2. 对单牌按与 `pc` 的关系分两类：
   - 危险单牌：`rank < pc`（若它成为当前最大，C 可直接出 `pc` 获胜）。
   - 安全单牌：`rank >= pc`（C 无法压）。
3. 对子回合中，C 永远只能 `pass`。

因此博弈可拆成两个可判定的赢法：

- A 主攻赢（A 负责完成清空）。
- B 单飞赢（A 帮 B 抢到主动后，B 自己清空）。

只要任意一种成立，答案就是 `Yes`。

---

## 记号

- A 的单牌集合 `AS`，对子集合 `AD`。
- B 的单牌集合 `BS`，对子集合 `BD`。
- `AL = {x in AS | x < pc}`，`AH = {x in AS | x >= pc}`。
- `BL = {x in BS | x < pc}`，`BH = {x in BS | x >= pc}`。

所有集合天然按点数递增（按下标扫描得到）。

---

## 判定一：A 主攻赢

设 `k = |AL|`。

- 若 `k <= 1`：A 必胜。
  - 最多只有一张危险单牌，留到最后一手即可。

- 若 `k >= 2`：前 `k-1` 张危险单牌必须先被“处理掉”。
  每处理 1 张，需要两件事：

1. B 先用一张安全单牌接住（否则 C 直接出 `pc`），所以必须有
   `|BH| >= k-1`。
2. 回合结束后，下一轮起手最好回到 A。A 抢回起手有两种方式：
   - **单牌抢回**：A 用更大的安全单牌压 B 的安全单牌。
   - **对子抢回**：让 B 在对子轮先出，然后 A 用更大的对子压回。

于是总抢回次数要满足：

`match(AH, BH) + match(AD, BD) >= k-1`

其中 `match(X, Y)` 表示最大可配对数（`x > y`），排序后双指针贪心即可线性求出。

满足以上两条，A 主攻可行。

---

## 判定二：B 单飞赢

这是 A 第一轮“喂”B 抢主动，然后 B 自己一路出完。

必要条件先看危险单牌：

- 若 `|BL| > 1`，B 不可能清空（危险单牌最多只能留 1 张做终结手）。

接着看 B 的总“出牌单位数”：

`unitsB = |BS| + |BD|`

### 情况 A：`unitsB == 1`

B 只要在第一轮把这唯一一手打出去并压住 A 的起手，就立刻清空获胜。

- 若这唯一单位是单牌 `r`：需要存在 A 单牌 `a < r`（A 可起手出该 `a`）。
- 若这唯一单位是对子 `r`：需要存在 A 对子 `a < r`。

### 情况 B：`unitsB >= 2`

B 第一轮用来接管主动的那手必须是“安全接管手”，否则后续会被 C 卡死：

- 存在 `r in BH`，且存在 `a in AS` 使 `a < r`；或
- 存在 `r in BD`，且存在 `a in AD` 使 `a < r`。

满足其一即可完成接管并继续清空。

---

## 正确性要点（简述）

1. C 的唯一威胁只在单牌阈值 `pc` 上，因此“危险/安全单牌”分类完整刻画了 C 的干预能力。
2. A 主攻时，`k-1` 次危险单牌过渡是不可绕开的硬需求；每次都必须由 B 安全单牌接住，并由 A 通过“更大安全单牌”或“更大对子”拿回节奏，故得到充要条件。
3. B 单飞时，`|BL| > 1` 必败；`|BL| <= 1` 时，首轮若能由安全接管手拿到主动（或本身只剩 1 手直接出完），则后续不再给 C 致胜窗口。
4. 两种方案互斥地覆盖了农民最优协同策略，因此答案为 `Awin || Bwin`。

---

## 复杂度

每组测试：

- 一次线性扫描建集合。
- 两次双指针匹配。

总复杂度 `O(n)`，总输入规模 `sum n <= 1e6`，可通过。

---

## C++17 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

static int matchGT(const vector<int>& big, const vector<int>& small) {
    // maximum number of pairs (b, s) with b > s
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
            int r = i + 1;
            if (sa[i] == '1') AS.push_back(r);
            else if (sa[i] == '2') AD.push_back(r);

            if (sb[i] == '1') BS.push_back(r);
            else if (sb[i] == '2') BD.push_back(r);
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

        // Plan A: A is the finisher
        bool Awin = false;
        int need = (int)AL.size() - 1;
        if (need <= 0) {
            Awin = true;
        } else if ((int)BH.size() >= need) {
            int bySingle = matchGT(AH, BH);
            int byDouble = matchGT(AD, BD);
            Awin = (bySingle + byDouble >= need);
        }

        // Plan B: B solo finish after first takeover
        bool Bwin = false;
        if ((int)BL.size() <= 1) {
            int unitsB = (int)BS.size() + (int)BD.size();

            if (unitsB == 1) {
                if (!BS.empty()) {
                    int r = BS[0];
                    Bwin = (!AS.empty() && AS.front() < r);
                } else {
                    int r = BD[0];
                    Bwin = (!AD.empty() && AD.front() < r);
                }
            } else {
                bool safeSingleTakeover =
                    (!BH.empty() && !AS.empty() && BH.back() > AS.front());
                bool safeDoubleTakeover =
                    (!BD.empty() && !AD.empty() && BD.back() > AD.front());
                Bwin = safeSingleTakeover || safeDoubleTakeover;
            }
        }

        cout << ((Awin || Bwin) ? "Yes" : "No") << '\n';
    }

    return 0;
}
```
