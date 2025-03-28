#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SDL.h>
#include <memory>
#include <map>
#include "Component.h"
#include "TransformComponent.h"

class GameEntity : public std::enable_shared_from_this<GameEntity> {
public:
    GameEntity();
    virtual ~GameEntity() = default;

    virtual void Input(float deltaTime);
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    void AddComponent(std::shared_ptr<Component> component);
    void AddDefaultTransform(float x = 0.0f, float y = 0.0f, float w = 40.0f, float h = 40.0f);
    std::shared_ptr<TransformComponent> GetTransform();

    
    template <typename T>
    std::shared_ptr<T> GetComponent(ComponentType type);

    std::shared_ptr<GameEntity> GetThisPtr();

protected:
    std::map<ComponentType, std::shared_ptr<Component>> mComponents;
};

#endif // GAME_ENTITY_H
