# 视频数据辅助草稿

三个 Python 脚本用于查看 NumPy 轨迹文件或导出视频，作为原目录中的辅助代码保存。它们不是刷题解答，不随基础验证自动执行。

- `find.py` / `test.py`：设置 `PRACTICE_NPZ_PATH`，默认读取 `./data/example.npz`。需要 NumPy。
- `find_best_video.py`：设置 `PRACTICE_EVAL_FOLDER`，默认扫描 `./data/eval_eps`。需要 NumPy、OpenCV、tqdm。
- 输入数据、视频及本地路径不上传。脚本沿用原有处理流程，未做算法或性能改造。
