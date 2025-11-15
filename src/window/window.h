#pragma once

#include "raylib.h"

class Window {
  private:
    const int   width_;  // 窗口宽度
    const int   height_; // 窗口高度
    const char* title_;  // 窗口标题
    int         fps_;    // 帧率

  public:
    Window() = delete;
    // 带参构造函数
    Window(int width, int height, const char* title);

    // 设置画布(帧缓冲区)以开始绘制
    void beginDrawing() const;
    // 结束画布绘制和交换缓冲区(双缓冲)
    void endDrawing() const;

    // 设置帧率
    void set_fps(int fps);

    // 设置背景颜色
    void setBackgroundColor(const Color& color) const;

    // 获取窗口是否应该关闭
    bool shouldClose() const;

    // 关闭窗口
    void close() const;

    // 析构函数
    ~Window() = default;
};