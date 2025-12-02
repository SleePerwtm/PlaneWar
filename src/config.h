#pragma once

#include "raylib.h"

#include <chrono>

using Clock     = std::chrono::steady_clock;
using TimePoint = Clock::time_point;
using Seconds   = std::chrono::duration<float>;

// 在C++中，非整型的静态成员变量不能在类内初始化，除非使用 constexpr
namespace Config {

namespace Window {
constexpr int         WIDTH  = 900;         // 窗口宽度
constexpr int         HEIGHT = 1280;        // 窗口高度
constexpr const char* TITLE  = "Plane War"; // 窗口标题
constexpr int         FPS    = 60;          // 帧率
}; // namespace Window

namespace Keyboard {
constexpr char UP    = KEY_W; // 向上
constexpr char DOWN  = KEY_S; // 向下
constexpr char LEFT  = KEY_A; // 向左
constexpr char RIGHT = KEY_D; // 向右
}; // namespace Keyboard

namespace Player {
constexpr const char* IMG_PATH      = "../assets/player.png"; // 玩家贴图资源
constexpr int         RADIUS        = 16;   // 玩家贴图内接圆半径
constexpr float       SCALE         = 2.0f; // 玩家贴图缩放倍数
constexpr Vector2     POSITION      = {Window::WIDTH * 0.5 - RADIUS * SCALE,
                                       Window::HEIGHT * 0.8 -
                                           RADIUS* SCALE}; // 玩家初始位置
constexpr Vector2     VELOCITY      = {0, 0};              // 玩家初始速度
constexpr Vector2     ACCELERATION  = {0, 0};              // 玩家初始加速度
constexpr int         HP            = 3;                   // 玩家初始血量
constexpr Vector2     MOVE_VELOCITY = {600, 600};          // 设置的移动速度
}; // namespace Player

namespace EnemyPool {
constexpr int         COUNT        = 20;                    // 敌人数量
constexpr const char* IMG_PATH     = "../assets/enemy.png"; // 敌人贴图资源
constexpr int         RADIUS       = 16;   // 敌人贴图内接圆半径
constexpr float       SCALE        = 2.0f; // 敌人贴图缩放倍数
constexpr Vector2     POSITION     = {-RADIUS * 3 * SCALE,
                                      -RADIUS * 3 * SCALE}; // 敌人初始位置
constexpr Vector2     VELOCITY     = {0, 0};                // 敌人初始速度
constexpr Vector2     ACCELERATION = {0, 0};                // 敌人初始加速度
constexpr int         HP           = 1;                     // 敌人初始血量

constexpr int MIN_SPEED = 300; // 敌人最小速度
constexpr int MAX_SPEED = 500; // 敌人最大速度
}; // namespace EnemyPool

namespace EnemyManager {
constexpr Seconds SPAWN_INTERVAL(0.1f); // 敌人生成间隔时间，单位秒
;
} // namespace EnemyManager

namespace BulletPool {
constexpr int         COUNT        = 30;                     // 子弹数量
constexpr const char* IMG_PATH     = "../assets/bullet.png"; // 子弹贴图资源
constexpr int         RADIUS       = 4;    // 子弹贴图内接圆半径
constexpr float       SCALE        = 2.0f; // 子弹贴图缩放倍数
constexpr Vector2     POSITION     = {-RADIUS * 3 * SCALE,
                                      -RADIUS * 3 * SCALE}; // 子弹初始位置
constexpr Vector2     VELOCITY     = {0, 0};                // 子弹初始速度
constexpr Vector2     ACCELERATION = {0, 0};                // 子弹初始加速度
constexpr int         HP           = 1;                     // 子弹初始血量

constexpr int SPEED = 800; // 子弹速度
}; // namespace BulletPool

namespace BulletManager {
constexpr Seconds SPAWN_INTERVAL(0.3f); // 子弹生成间隔时间，单位秒
}; // namespace BulletManager

}; // namespace Config