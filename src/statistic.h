#pragma once

#include "config.h"

struct Statistic {
  static int       score_;       // 分数
  static TimePoint start_time_;  // 游戏开始时间
  static Seconds   time_passed_; // 游戏已进行时间

  // 增加分数
  static void addScore(int points);

  // 获取当前分数
  static int getScore();

  // 更新游戏已进行时间
  static void updateTime(TimePoint current_time);

  // 获取游戏已进行时间
  static Seconds getTimePassed();

  static void reset();
};