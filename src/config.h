#pragma once

struct Config {
  struct Window {
    static constexpr int         width  = 900;         // 窗口宽度
    static constexpr int         height = 1280;        // 窗口高度
    static constexpr const char* title  = "Plane War"; // 窗口标题
    static constexpr int         fps    = 60;          // 帧率
  };
};