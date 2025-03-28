import os
import numpy as np
# 通过 PRACTICE_NPZ_PATH 指定本地 .npz 文件。
path = os.environ.get("PRACTICE_NPZ_PATH", "./data/example.npz")
data = np.load(path)
print("这个 .npz 文件里包含以下数据键名：")
print(list(data.keys()))
print("-" * 20)
for key in data.keys():
    print(f"键名: {key:<20} | 形状: {data[key].shape} | 类型: {data[key].dtype}")