#pragma once

#include "../entity/entity.h"

#include <cstddef>
#include <memory>
#include <vector>

class EntityPool {
protected:
  using EntityPtr = std::unique_ptr<Entity>;

  std::vector<EntityPtr> entities_;
  size_t                 pool_size_;

public:
  EntityPool(size_t pool_size);
  ~EntityPool();

  // 创建实体
  virtual void createEntities() = 0;

  // 更新实体位置
  virtual void updateEntitiesPosition() = 0;
  // 绘制实体
  virtual void drawEntities() = 0;
};
