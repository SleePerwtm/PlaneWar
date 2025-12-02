使用 C++ 语言与 raylib 库编写的飞机大战游戏。

使用 CMake 构建项目，CMakeLists.txt 文件内容使用 AI 辅助生成，并参考了 raylib 官方的 CMake 项目示例。

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