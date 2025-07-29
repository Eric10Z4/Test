flowchart LR
    %% 全局样式定义区 (专门针对PPT的高对比度柔和色彩)
    classDef mcts fill:#e0f2fe,stroke:#0284c7,stroke-width:2px,color:#0f172a
    classDef cnn fill:#ffe4e6,stroke:#e11d48,stroke-width:2px,color:#0f172a
    classDef buffer fill:#f1f5f9,stroke:#475569,stroke-width:2px,color:#0f172a
    classDef group fill:#ffffff,stroke:#cbd5e1,stroke-width:2px,stroke-dasharray: 5 5

    Start((全局启动<br/>随机初始化<br/>CNN 权重)):::cnn

    subgraph Phase1 [阶 段 1 ： 自 对 弈 数 据 采 集]
        direction TB
        M1[MCTS 搜索抵达叶节点]:::mcts --> |请求前向推理| C1[CNN 返回先验概率 P<br/>与状态估值 V]:::cnn
        C1 --> |PUCT 算法引导| M2[执行 400 次 MCTS 模拟<br/>扩展搜索树]:::mcts
        M2 --> M3[依据子节点访问量 N<br/>计算动作概率分布 π]:::mcts
        M3 -.-> |继续单步落子决策| M1
        M3 --> |单局对弈结束| M4[补全终局奖励标签 Z<br/>执行 D8 空间对称增强]:::buffer
    end

    subgraph Phase2 [阶 段 2 ： 网 络 参 数 优 化]
        direction TB
        B1[(经验回放池<br/>Replay Buffer)]:::buffer --> B2{池内总数据量<br/>≥ Batch Size阈值?}
        B2 -- 条件满足 --> B3[均匀采样小批次数据<br/>张量: State, π, Z]:::buffer
        B3 --> C2[前向传播预测 P 与 V<br/>CrossEntropy + MSE <br/>计算 Total Loss]:::cnn
        C2 --> C3[反向传播计算梯度<br/>依据 KL 散度调整学习率<br/>执行 Optimizer Step]:::cnn
    end

    subgraph Phase3 [阶 段 3 ： 模 型 性 能 验 证]
        direction TB
        E1[加载最新 CNN 网络权重<br/>对战纯 MCTS 基线 (10局)]:::mcts --> E2{评估对抗胜率<br/>与运行状态监控}
        E2 -- 胜率突破历史最优 --> E3[模型性能验证通过<br/>序列化参数权重保存至<br/>best_policy.pth]:::cnn
        E2 -- KL发散越界 / 胜率下滑 --> E4[触发 Soft Early Stopping<br/>回滚历史健康参数<br/>执行学习率衰减]:::cnn
    end

    %% 模块之间的主轴流转线
    Start ==> Phase1
    M4 ===> |"沉淀样本 [State, π, Z]"| B1
    C3 ===> |"当前权重单次迭代完成"| Phase3
    
    %% 大循环的闭环线条
    E3 -.-> |进入下一轮主训练循环| Phase1
    E4 -.-> |降低步长, 进入下一轮循环| Phase1
    
    %% 应用子图的边框样式
    class Phase1,Phase2,Phase3 group
