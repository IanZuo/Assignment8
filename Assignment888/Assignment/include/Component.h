#pragma once
#include <SDL2/SDL.h>
#include "ComponentType.h"
#include <memory>

// Forward declaration
class GameEntity;

struct Component {
    Component() {}

    virtual ~Component() {}

    virtual void Input(float deltaTime) {}
    virtual void Update(float deltaTime) {}
    virtual void Render(SDL_Renderer* renderer) {}

    virtual ComponentType GetType() = 0;

    void SetGameEntity(std::shared_ptr<GameEntity> entity) { mGameEntity = entity; }
    std::shared_ptr<GameEntity> GetGameEntity() const { return mGameEntity.lock(); }

protected:
    std::weak_ptr<GameEntity> mGameEntity; // weak_ptr 
};
