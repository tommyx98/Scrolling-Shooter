#include "ComponentSystem.h"

void Entity::AddGroupToEntity(Group group) noexcept {
    groupBitset[group] = true;
    entityManager.AddToGroup(this, group);
}