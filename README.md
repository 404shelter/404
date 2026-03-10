# Mini Metro Advanced Clone (C++ / OpenGL)

这是一个基于你给出的 10 大模块拆分的 **简化但完整骨架实现**，使用 C++17，渲染接口按 OpenGL 组织（即时模式示例）。

## 目录结构（简单清晰）

```text
.
├── CMakeLists.txt
├── README.md
├── assets/
│   ├── audio/
│   ├── fonts/
│   └── textures/
└── src/
    ├── Game.hpp / Game.cpp
    ├── main.cpp
    ├── core/
    │   └── Core.hpp / Core.cpp
    ├── engine/
    │   └── Engine.hpp / Engine.cpp
    ├── world/
    │   └── World.hpp / World.cpp
    ├── metro/
    │   └── Metro.hpp / Metro.cpp
    ├── passenger/
    │   └── Passenger.hpp / Passenger.cpp
    ├── systems/
    │   └── Systems.hpp / Systems.cpp
    ├── ui/
    │   └── UI.hpp / UI.cpp
    ├── render/
    │   └── Render.hpp / Render.cpp
    └── save/
        └── Save.hpp / Save.cpp
```

## 模块覆盖

- Engine：主循环、输入、delta time。
- Core：Vec2/Math/Random/Color。
- World：城市生成、河流、桥梁、站点。
- Metro：线路、列车移动、调度、容量。
- Passenger：乘客状态、上/下车决策、简化路径选择。
- Systems：生成系统、周系统、经济、成就。
- UI：HUD、菜单按钮、GameOver 面板。
- Render：地图/线路/站点/列车统一绘制。
- Save：保存/加载周数、金钱、乘客状态。
- Assets：资源目录预留。

## 运行说明

当前 CMake 会在环境中自动检测 OpenGL + glfw3：

- 若检测到：生成可执行文件 `mini_metro`。
- 若检测不到：仍可成功配置项目（仅跳过可执行文件生成）。

```bash
cmake -S . -B build
cmake --build build
```

> 在你的本机（有 OpenGL + glfw3）即可直接编译运行。
