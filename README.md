# 项目说明

本项目是使用 C++ 语言与 raylib 库编写的飞机大战游戏，实现了基本的游戏功能，包括玩家控制飞机、敌机生成与移动、碰撞检测、得分统计等。该项目作为 2025 年秋季学期面向对象程序设计课程的期末大作业。

该项目使用 CMake 构建，CMakeLists.txt 文件内容使用 AI 辅助生成，并参考了 raylib 官方的 CMake 项目示例。

在项目代码的编写过程中，在我的想法的基础上又参考了 AI 的建议，包括且不限于使用命名空间与常量表达式来管理配置参数、使用模板类来实现实体管理器等。

# 构建与运行

在项目根目录下运行以下命令以构建和运行游戏（使用 MinGW Makefiles 生成器）：

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
./PlaneWar.exe
```

# 项目分析

见 [项目分析.md](项目分析.md) 文件。