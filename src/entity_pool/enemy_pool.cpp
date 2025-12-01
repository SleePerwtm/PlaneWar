#include "enemy_pool.h"

#include "../entity/enemy.h"
#include "entity_pool.h"

#include "raylib.h"

#include <cstddef>
#include <memory>

EnemyPool::EnemyPool(size_t pool_size, Vector2 position, Vector2 velocity,
                     Vector2 acceleration, int radius, int hp, float scale,
                     const char* texture_path, int min_velocity,
                     int max_velocity)
    : EntityPool(pool_size) {
  default_.position     = position;
  default_.velocity     = velocity;
  default_.acceleration = acceleration;
  default_.radius       = radius;
  default_.hp           = hp;
  default_.scale        = scale;
  default_.texture_path = texture_path;
  default_.min_velocity = min_velocity;
  default_.max_velocity = max_velocity;
}

EnemyPool::~EnemyPool() {}

Vector2 EnemyPool::getRandomPosition() const {
  float size_of_entity = 2 * default_.radius * default_.scale;

  int x = GetRandomValue(0, GetScreenWidth() - size_of_entity);
  return Vector2{static_cast<float>(x), -size_of_entity};
}

Vector2 EnemyPool::getRandomVelocity() const {
  Vector2 velocity;
  velocity.x = 0.0f;
  velocity.y = GetRandomValue(default_.min_velocity, default_.max_velocity);
  return velocity;
}

void EnemyPool::createEntities() {
  for (size_t i = 0; i < pool_size_; i++) {
    /* 向对象池中添加 Enemy 对象 */
    // 错误做法：
    // entities_[i] = std::make_unique<Enemy>(...);
    // 当前 entities_ 容量不为 0，但是大小为 0，使用下标访问无法正确赋值
    entities_.push_back(std::make_unique<Enemy>(
        default_.position, default_.velocity, default_.acceleration,
        default_.radius, default_.hp, default_.scale, default_.texture_path,
        TextureType::SHARED));
  }
}

void EnemyPool::setRandomInitialState() {
  for (auto& entity : entities_) {
    entity->set_position(getRandomPosition());
    entity->set_velocity(getRandomVelocity());
  }
}

void EnemyPool::updateEntitiesPosition() {
  for (auto& entity : entities_) {
    entity->updatePosition();
  }
}

void EnemyPool::drawEntities() {
  for (auto& entity : entities_) {
    entity->draw();
  }
}
