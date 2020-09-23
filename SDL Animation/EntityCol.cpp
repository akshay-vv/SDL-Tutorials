#include "Entity.h"

std::vector<EntityCol> EntityCol::EntityColList;

EntityCol::EntityCol() {
    this->entityA = NULL;
    this->entityB = NULL;
}