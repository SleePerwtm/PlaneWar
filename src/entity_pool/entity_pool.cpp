#include "entity_pool.h"

#include <cstddef>
#include <vector>

EntityPool::EntityPool(size_t pool_size) : pool_size_(pool_size) {
  entities_.reserve(pool_size);
}

EntityPool::~EntityPool() {
  for (auto& entity : entities_) {
    entity.reset();
  }
}

void EntityPool::updateEntitiesPosition() {
  for (auto& entity : entities_) {
    if (entity->is_active())
      entity->updatePosition();
  }
}

void EntityPool::drawEntities() {
  for (auto& entity : entities_) {
    if (entity->is_active())
      entity->draw();
  }
}

std::vector<EntityPtr>& EntityPool::get_entities() { return entities_; }

const std::vector<EntityPtr>& EntityPool::get_entities() const {
  return entities_;
}