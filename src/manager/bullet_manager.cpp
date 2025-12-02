#include "bullet_manager.h"

#include "../config.h"

BulletManager::BulletManager(std::unique_ptr<BulletPool> pool,
                             Seconds                     spawn_interval,
                             std::shared_ptr<Player>     player)
    : EntityManager<BulletPool>(std::move(pool), spawn_interval),
      player_(player) {}

void BulletManager::spawnEntity() {
  for (auto& bullet : pool_->get_entities()) {
    if (!bullet->is_active()) {
      bullet->activate(); // 激活敌人
      // 设置初始位置和速度
      Vector2 pos = player_->get_position();
      pos.x += player_->get_radius() - bullet->get_radius();
      Vector2 vel{0, -Config::BulletPool::SPEED};
      bullet->set_position(pos);
      bullet->set_velocity(vel);
      bullet->set_acceleration(Config::BulletPool::ACCELERATION);
      break;
    }
  }
}

bool BulletManager::shouldReturnToPool(Entity& entity) const {
  // 子弹完全移出屏幕上边界
  int bullet_height =
      2 * Config::BulletPool::RADIUS * Config::BulletPool::SCALE;
  if (entity.get_position().y < -bullet_height) {
    return true;
  }
  // 血量小于等于 0 则回收
  if (entity.get_hp() <= 0) {
    return true;
  }
  return false;
}

void BulletManager::returnToPool() {
  for (auto& enemy : pool_->get_entities()) {
    // 检查是否需要回收
    if (shouldReturnToPool(*enemy)) {
      // 设置为不活跃状态
      enemy->deactivate();
      // 移动到屏幕外隐藏位置
      Vector2 hide_pos = Config::BulletPool::POSITION;
      Vector2 hide_vel = Config::BulletPool::VELOCITY;     // {0.0f, 0.0f}
      Vector2 hide_acc = Config::BulletPool::ACCELERATION; // {0.0f, 0.0f}
      int     hp       = Config::BulletPool::HP;
      enemy->set_position(hide_pos);
      enemy->set_velocity(hide_vel);
      enemy->set_acceleration(hide_acc);
      enemy->set_hp(hp);
    }
  }
}