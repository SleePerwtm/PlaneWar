#include "enemy_manager.h"

#include "../config.h"

#include "raylib.h"

#include <memory>

EnemyManager::EnemyManager(std::unique_ptr<EnemyPool> pool,
                           Seconds                    spawn_interval)
    : EntityManager<EnemyPool>(std::move(pool), spawn_interval) {}

void EnemyManager::spawnEntity() {
  for (auto& enemy : pool_->get_entities()) {
    if (!enemy->is_active()) {
      enemy->activate(); // 激活敌人
      // 设置随机初始位置和速度
      Vector2 pos = pool_->getRandomPosition();
      Vector2 vel = pool_->getRandomVelocity();
      enemy->set_position(pos);
      enemy->set_velocity(vel);
      enemy->set_acceleration(Config::EnemyPool::ACCELERATION);
      break;
    }
  }
}

bool EnemyManager::shouldReturnToPool(Entity& entity) const {
  // 移出屏幕下边界则回收
  if (entity.get_position().y > GetScreenHeight()) {
    return true;
  }
  // 血量小于等于 0 则回收
  if (entity.get_hp() <= 0) {
    return true;
  }
  return false;
}

void EnemyManager::returnToPool() {
  for (auto& enemy : pool_->get_entities()) {
    // 检查是否需要回收
    if (shouldReturnToPool(*enemy)) {
      // 设置为不活跃状态
      enemy->deactivate();
      // 移动到屏幕外隐藏位置
      Vector2 hide_pos = Config::EnemyPool::POSITION;
      Vector2 hide_vel = Config::EnemyPool::VELOCITY;     // {0.0f, 0.0f}
      Vector2 hide_acc = Config::EnemyPool::ACCELERATION; // {0.0f, 0.0f}
      int     hp       = Config::EnemyPool::HP;
      enemy->set_position(hide_pos);
      enemy->set_velocity(hide_vel);
      enemy->set_acceleration(hide_acc);
      enemy->set_hp(hp);
    }
  }
}

void EnemyManager::resetEnemies() {
  for (auto& enemy : pool_->get_entities()) {
    // 重置敌人状态
    enemy->deactivate();
    Vector2 hide_pos = Config::EnemyPool::POSITION;
    Vector2 hide_vel = Config::EnemyPool::VELOCITY;     // {0.0f, 0.0f}
    Vector2 hide_acc = Config::EnemyPool::ACCELERATION; // {0.0f, 0.0f}
    int     hp       = Config::EnemyPool::HP;
    enemy->set_position(hide_pos);
    enemy->set_velocity(hide_vel);
    enemy->set_acceleration(hide_acc);
    enemy->set_hp(hp);
  }
}