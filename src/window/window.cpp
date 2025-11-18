#include "window.h"

#include "raylib.h"

Window::Window(int width, int height, const char* title)
    : width_(width), height_(height), title_(title) {
  // 调用 raylib 的 InitWindow 函数初始化窗口
  InitWindow(width, height, title);
}

void Window::set_fps(int fps) {
  // 调用 raylib 的 SetTargetFPS 函数设置帧率
  SetTargetFPS(fps);
}

void Window::setBackgroundColor(const Color& color) const {
  // 调用 raylib 的 ClearBackground 函数设置背景颜色
  ClearBackground(color);
}

bool Window::shouldClose() const {
  // 调用 raylib 的 WindowShouldClose 函数返回窗口是否关闭
  return WindowShouldClose();
}

void Window::beginDrawing() const {
  // 调用 raylib 的 BeginDrawing 函数开始绘制
  BeginDrawing();
}

void Window::endDrawing() const {
  // 调用 raylib 的 EndDrawing 函数结束绘制
  EndDrawing();
}

void Window::close() const {
  // 调用 raylib 的 CloseWindow 函数关闭窗口
  CloseWindow();
}
