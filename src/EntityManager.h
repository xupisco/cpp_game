#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

#include "./Entity.h"
#include "./Component.h"

class EntityManager {
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities();
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> GetEntities() const;
        unsigned int GetEntityCount();
        
    private:
        std::vector<Entity*> entities;
        
};

#endif
