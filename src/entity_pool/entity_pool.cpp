#include "entity_pool.h"

#include <cstddef>

EntityPool::EntityPool(size_t pool_size) : pool_size_(pool_size) {
  entities_.reserve(pool_size);
}

EntityPool::~EntityPool() {
  for (auto& entity : entities_) {
    entity.reset();
  }
}
