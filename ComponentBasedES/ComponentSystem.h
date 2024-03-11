#ifndef MAIN_CPP_COMPONENTSYSTEM_H
#define MAIN_CPP_COMPONENTSYSTEM_H


#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <type_traits>
#include "assert.h"

struct Component;
class Entity;
class EntityManager;

using iDOfComponent = std::size_t;
using Group = std::size_t;

inline iDOfComponent GetUniqueIDForComponent() noexcept{
    static iDOfComponent lastID = 0;
    return lastID++;
}

template<typename T> inline iDOfComponent GetTypeIDOfComponent() noexcept{
    static_assert(std::is_base_of<Component, T>::value, "T must be of type Component");
    static iDOfComponent typeID = GetUniqueIDForComponent();
    return typeID;
}

constexpr std::size_t maximumNumberOfComponents{32};
constexpr std::size_t maximumNumberOfGroups{32};

using ComponentBitset = std::bitset<maximumNumberOfComponents>;
using GroupBitset = std::bitset<maximumNumberOfGroups>;
using ComponentArray = std::array<Component*, maximumNumberOfComponents>;

struct Component{
    Entity *entity;

    virtual void ComponentInitializer(){}
    virtual void ComponentUpdate(){}
    virtual void ComponentDraw(){}

    virtual ~Component(){}
};

class Entity{
public:
    Entity(EntityManager &manager) : entityManager(manager){}

    void UpdateComponentsInEntity(){
        for(auto& component : entitysComponents){
            component->ComponentUpdate();
        }
    }

    void DrawComponentsInEntity(){
        for(auto& component : entitysComponents){
            component->ComponentDraw();
        }
    }

    bool IsEntityActive(){return entityIsActive;}

    void DestroyEntity(){entityIsActive = false;}

    // querys bitset to check if entity has specific component
    template<typename T> bool EntityHasComponent() const{
        return componentBitset[GetTypeIDOfComponent<T>()];
    }

    template<typename T, typename... TArgs> T& AddComponentToEntity(TArgs&&... mArgs){
        // check that entity does not already have entity
        assert(!EntityHasComponent<T>());

        T *component(new T(std::forward<TArgs>(mArgs)...));
        component->entity = this;
        std::unique_ptr<Component> uniquePtr{component};
        entitysComponents.emplace_back(std::move(uniquePtr));

        // adding component to bitset and array to use for easy existence check
        componentArray[GetTypeIDOfComponent<T>()] = component;
        componentBitset[GetTypeIDOfComponent<T>()] = true;

        component->ComponentInitializer();

        return *component;
    }

    template<typename T> T& GetComponentFromEntity() const{
        // first check if exists
        assert(EntityHasComponent<T>());

        auto ptr(componentArray[GetTypeIDOfComponent<T>()]);
        return *static_cast<T*>(ptr);
    }

    bool EntityHasGroup(Group group) const noexcept{
        return groupBitset[group];
    }

    // Method will be defined in cpp file, because it needs to be defined after EntityManager since i am going to call EntityManager::AddGroupToEntity here
    void AddGroupToEntity(Group group) noexcept;

    void RemoveGroupFromEntity(Group group) noexcept{
        groupBitset[group] = false;
    }

private:
    bool entityIsActive = true;
    std::vector<std::unique_ptr<Component>> entitysComponents;
    ComponentArray componentArray;
    ComponentBitset componentBitset;
    GroupBitset groupBitset;
    EntityManager &entityManager;
};

class EntityManager{
public:
    void UpdateAllEntities(){
        for(auto& entity : entities){
            entity->UpdateComponentsInEntity();
        }
    }

    void DrawAllEntities(){
        for(auto& entity : entities){
            entity->DrawComponentsInEntity();
        }
    }

    // refreshes entity groups and checks for entities that are not active and removes them
    void RefreshEntities(){
        RefreshEntityGroups();

        entities.erase(
                std::remove_if(std::begin(entities), std::end(entities),
                               [](const std::unique_ptr<Entity>& mEntity)
                               {
                                   return !mEntity->IsEntityActive();
                               }),
                std::end(entities));
    }

    // removes entities with incorrect groups
    void RefreshEntityGroups(){
        for(auto i(0u); i < maximumNumberOfGroups; ++i){
            auto &vector(groupedEntities[i]);
            vector.erase(std::remove_if(std::begin(vector), std::end(vector),
                                        [i](Entity *entity){
                                            return !entity->IsEntityActive() || !entity->EntityHasGroup(i);
            }), std::end(vector));
        }
    }

    void AddToGroup(Entity *entity, Group group){
        groupedEntities[group].emplace_back(entity);
    }

    Entity& AddEntity(){
        Entity *entity = new Entity(*this);
        std::unique_ptr<Entity> uniquePtr{entity};
        entities.emplace_back(std::move(uniquePtr));
        return *entity;
    }

    std::vector<Entity*>& GetGroup(Group group){
        return groupedEntities[group];
    }


private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maximumNumberOfGroups> groupedEntities;
};

#endif //MAIN_CPP_COMPONENTSYSTEM_H