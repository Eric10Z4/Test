import numpy as np
import cv2
import os
from tqdm import tqdm

# ==================== ⚙️ 配置区域 ====================
# 通过 PRACTICE_EVAL_FOLDER 指定本地输入目录。
EVAL_FOLDER = os.environ.get("PRACTICE_EVAL_FOLDER", "./data/eval_eps")

# 输出视频文件名
OUTPUT_FILENAME = "best_shear_moment.mp4"
# ====================================================

def scan_and_convert():
    print(f"🕵️‍♂️ [服务器端] 正在扫描文件夹: {EVAL_FOLDER}")
    
    if not os.path.exists(EVAL_FOLDER):
        print("❌ 错误：找不到文件夹路径！")
        # 尝试列出上一级目录，帮你看看到底哪儿不对
        try:
            parent = os.path.dirname(EVAL_FOLDER)
            print(f"   上一级目录 {parent} 里的内容: {os.listdir(parent)}")
        except:
            pass
        return

    best_file = None
    max_reward = -999999
    
    # 获取所有 .npz 文件
    try:
        files = [f for f in os.listdir(EVAL_FOLDER) if f.endswith('.npz')]
    except Exception as e:
        print(f"❌ 读取目录失败: {e}")
        return

    print(f"📄 找到 {len(files)} 个录像文件，正在寻找“高分局”...")

    if len(files) == 0:
        print("⚠️ 警告：该目录下没有 .npz 文件！")
        return

    # 扫描得分
    for f in tqdm(files):
        path = os.path.join(EVAL_FOLDER, f)
        try:
            # 只加载 reward 数据，速度很快
            with np.load(path) as data:
                if 'reward' in data:
                    total_reward = np.sum(data['reward'])
                    if total_reward > max_reward:
                        max_reward = total_reward
                        best_file = path
        except Exception:
            continue

    if best_file is None:
        print("❌ 没有找到任何有效数据。")
        return

    print(f"\n🏆 找到最佳表现！")
    print(f"   📂 文件名: {os.path.basename(best_file)}")
    print(f"   💰 总得分: {max_reward}")
    
    if max_reward <= 0:
        print("⚠️ 注意：最高分仅为 0 或负数，视频里可能没有成功的剪羊毛动作，但这是目前表现最好的一局。")

    convert_to_mp4(best_file, OUTPUT_FILENAME)

def convert_to_mp4(npz_path, output_name):
    try:
        data = np.load(npz_path)
        # 寻找图像键名
        key = next((k for k in ['obs', 'image', 'frames', 'rgb'] if k in data), None)
        if not key:
            print("❌ .npz 文件中找不到图像数据 (obs/image/frames)。")
            return

        images = data[key]
        
        # 格式修正 (T, C, H, W) -> (T, H, W, C)
        if images.ndim == 4 and images.shape[1] == 3:
            images = np.transpose(images, (0, 2, 3, 1))

        n, h, w, c = images.shape
        # 使用 mp4v 编码 (Linux 上通常比较通用)
        out = cv2.VideoWriter(output_name, cv2.VideoWriter_fourcc(*'mp4v'), 20.0, (w, h))

        print(f"🎥 正在渲染视频 ({n} 帧)...")
        for i in range(n):
            # RGB 转 BGR (OpenCV 需要)
            frame = cv2.cvtColor(images[i], cv2.COLOR_RGB2BGR)
            out.write(frame)
        
        out.release()
        print(f"\n✨✨✨ 视频已生成：{os.path.abspath(output_name)} ✨✨✨")
        print("👉 请在 WindTerm 文件列表中刷新，然后下载到本地观看截图！")

    except Exception as e:
        print(f"❌ 转换视频出错: {e}")

if __name__ == "__main__":
    scan_and_convert()