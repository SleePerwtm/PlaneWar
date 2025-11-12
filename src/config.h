#pragma once

struct Config {
    struct Window {
        static const int width = 900;   // 窗口宽度
        static const int height = 1280; // 窗口高度
        // 在C++中，非整型的静态成员变量不能在类内初始化，除非使用 constexpr
        static constexpr const char* title = "Plane War"; // 窗口标题
        static const int fps = 60;                        // 帧率
    };
};