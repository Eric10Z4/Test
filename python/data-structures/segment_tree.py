from __future__ import annotations

from dataclasses import dataclass
from typing import List, Sequence


class SegmentTreeSum:
    """线段树：区间求和 + 单点赋值更新。

    - query(l, r): 闭区间 [l, r] 求和
    - update(i, value): 把 a[i] 赋值为 value

    时间复杂度：build O(n), query/update O(log n)
    """

    def __init__(self, arr: Sequence[int]):
        self.n = len(arr)
        if self.n == 0:
            raise ValueError("arr must be non-empty")
        self._tree = [0] * (4 * self.n)
        self._build(1, 0, self.n - 1, arr)

    def _build(self, node: int, left: int, right: int, arr: Sequence[int]) -> None:
        if left == right:
            self._tree[node] = int(arr[left])
            return
        mid = (left + right) // 2
        self._build(node * 2, left, mid, arr)
        self._build(node * 2 + 1, mid + 1, right, arr)
        self._tree[node] = self._tree[node * 2] + self._tree[node * 2 + 1]

    def update(self, index: int, value: int) -> None:
        if not (0 <= index < self.n):
            raise IndexError("index out of range")
        self._update(1, 0, self.n - 1, index, int(value))

    def _update(self, node: int, left: int, right: int, index: int, value: int) -> None:
        if left == right:
            self._tree[node] = value
            return
        mid = (left + right) // 2
        if index <= mid:
            self._update(node * 2, left, mid, index, value)
        else:
            self._update(node * 2 + 1, mid + 1, right, index, value)
        self._tree[node] = self._tree[node * 2] + self._tree[node * 2 + 1]

    def query(self, ql: int, qr: int) -> int:
        if not (0 <= ql <= qr < self.n):
            raise IndexError("query range out of bounds")
        return self._query(1, 0, self.n - 1, ql, qr)

    def _query(self, node: int, left: int, right: int, ql: int, qr: int) -> int:
        if ql <= left and right <= qr:
            return self._tree[node]
        mid = (left + right) // 2
        res = 0
        if ql <= mid:
            res += self._query(node * 2, left, mid, ql, min(qr, mid))
        if qr > mid:
            res += self._query(node * 2 + 1, mid + 1, right, max(ql, mid + 1), qr)
        return res


@dataclass
class LazySegmentTreeRangeAddSum:
    """懒标记线段树：区间加 + 区间求和。

    - range_add(l, r, delta): 对闭区间 [l, r] 每个元素加 delta
    - range_sum(l, r): 闭区间 [l, r] 求和

    时间复杂度：build O(n), 每次操作 O(log n)
    """

    arr: Sequence[int]

    def __post_init__(self) -> None:
        self.n = len(self.arr)
        if self.n == 0:
            raise ValueError("arr must be non-empty")
        self._tree = [0] * (4 * self.n)
        self._lazy = [0] * (4 * self.n)
        self._build(1, 0, self.n - 1)

    def _build(self, node: int, left: int, right: int) -> None:
        if left == right:
            self._tree[node] = int(self.arr[left])
            return
        mid = (left + right) // 2
        self._build(node * 2, left, mid)
        self._build(node * 2 + 1, mid + 1, right)
        self._tree[node] = self._tree[node * 2] + self._tree[node * 2 + 1]

    def _push(self, node: int, left: int, right: int) -> None:
        lazy_val = self._lazy[node]
        if lazy_val == 0 or left == right:
            return
        mid = (left + right) // 2
        left_node = node * 2
        right_node = node * 2 + 1

        self._lazy[left_node] += lazy_val
        self._lazy[right_node] += lazy_val

        self._tree[left_node] += lazy_val * (mid - left + 1)
        self._tree[right_node] += lazy_val * (right - mid)

        self._lazy[node] = 0

    def range_add(self, ql: int, qr: int, delta: int) -> None:
        if not (0 <= ql <= qr < self.n):
            raise IndexError("range out of bounds")
        self._range_add(1, 0, self.n - 1, ql, qr, int(delta))

    def _range_add(self, node: int, left: int, right: int, ql: int, qr: int, delta: int) -> None:
        if ql <= left and right <= qr:
            self._tree[node] += delta * (right - left + 1)
            self._lazy[node] += delta
            return
        self._push(node, left, right)
        mid = (left + right) // 2
        if ql <= mid:
            self._range_add(node * 2, left, mid, ql, min(qr, mid), delta)
        if qr > mid:
            self._range_add(node * 2 + 1, mid + 1, right, max(ql, mid + 1), qr, delta)
        self._tree[node] = self._tree[node * 2] + self._tree[node * 2 + 1]

    def range_sum(self, ql: int, qr: int) -> int:
        if not (0 <= ql <= qr < self.n):
            raise IndexError("range out of bounds")
        return self._range_sum(1, 0, self.n - 1, ql, qr)

    def _range_sum(self, node: int, left: int, right: int, ql: int, qr: int) -> int:
        if ql <= left and right <= qr:
            return self._tree[node]
        self._push(node, left, right)
        mid = (left + right) // 2
        res = 0
        if ql <= mid:
            res += self._range_sum(node * 2, left, mid, ql, min(qr, mid))
        if qr > mid:
            res += self._range_sum(node * 2 + 1, mid + 1, right, max(ql, mid + 1), qr)
        return res


def _demo() -> None:
    a = [1, 3, 4, 5, 5]

    st = SegmentTreeSum(a)
    print("SegmentTreeSum query(0,2)=", st.query(0, 2))  # 1+3+4=8
    st.update(1, 10)
    print("after update a[1]=10, query(0,2)=", st.query(0, 2))  # 1+10+4=15

    lazy = LazySegmentTreeRangeAddSum(a)
    print("Lazy range_sum(1,4)=", lazy.range_sum(1, 4))  # 3+4+5+5=17
    lazy.range_add(1, 3, 2)
    print("after range_add(1,3,+2), range_sum(1,4)=", lazy.range_sum(1, 4))  # 5+6+7+5=23


if __name__ == "__main__":
    _demo()
