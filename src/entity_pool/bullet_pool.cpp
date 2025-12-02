#include "bullet_pool.h"

#include "../entity/bullet.h"
#include "entity_pool.h"

#include <memory>
#include <vector>

BulletPool::BulletPool(size_t pool_size, Vector2 position, Vector2 velocity,
                       Vector2 acceleration, int radius, int hp, float scale,
                       const char* texture_path, int speed)
    : EntityPool(pool_size) {
  default_.position     = position;
  default_.velocity     = velocity;
  default_.acceleration = acceleration;
  default_.radius       = radius;
  default_.hp           = hp;
  default_.scale        = scale;
  default_.texture_path = texture_path;
  default_.speed        = speed;
}

BulletPool::~BulletPool() {}

void BulletPool::createEntities() {
  for (size_t i = 0; i < pool_size_; i++) {
    /* 向对象池中添加 Bullet 对象 */
    entities_.push_back(std::make_unique<Bullet>(
        default_.position, default_.velocity, default_.acceleration,
        default_.radius, default_.hp, default_.scale, default_.texture_path,
        TextureType::SHARED));
  }
}
