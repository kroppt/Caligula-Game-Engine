#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "entity.hpp"
class World{
    public:
        Entity* addEntity(Model *model, Texture *texture);
        void render(float alpha, uint uniformLocation);
        void update(void);
    private:
        std::vector<Entity*> entities_;
};

#endif