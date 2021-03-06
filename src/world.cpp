#include "world.hpp"
#include "entity.hpp"

Entity* World::addEntity(Model *model, Texture *texture, GLint ldLocation){
    Entity *entity = new Entity(model, texture, ldLocation);
    entities_.push_back(entity);
    return entity;
}

void World::render(float alpha, uint uniformLocation){
    for(std::vector<Entity*>::iterator it = entities_.begin(); it != entities_.end(); it++){
        (*it)->render(alpha, uniformLocation);
    }
}