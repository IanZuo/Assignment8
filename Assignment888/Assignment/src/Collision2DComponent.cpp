#include "../include/Collision2DComponent.h"
#include "../include/GameEntity.h"
#include "../include/TransformComponent.h"
#include "../include/Projectile.h"
#include <SDL.h>
#include <iostream>

Collision2DComponent::Collision2DComponent(float x, float y, float w, float h) {
    mRectangle = {x, y, w, h};
}

void Collision2DComponent::Input(float deltaTime) {
    // Nothing for now
}

void Collision2DComponent::Update(float deltaTime) {
    auto entity = GetGameEntity();
    if (!entity) return;

    auto transform = entity->GetTransform();
    if (!transform) return;

    auto projectile = std::dynamic_pointer_cast<Projectile>(entity);
    if (projectile && !projectile->isPlayerBullet) {
        // no colli if enemy
        return;
    }

    mRectangle.x = transform->GetX();
    mRectangle.y = transform->GetY();
    mRectangle.w = transform->GetW();
    mRectangle.h = transform->GetH();
}


void Collision2DComponent::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // test colli 
    SDL_RenderDrawRectF(renderer, &mRectangle);

    std::cout << "Rendering Collision Box at: " << mRectangle.x << ", " << mRectangle.y << std::endl;  // 确保渲染了正确的位置
}

SDL_FRect& Collision2DComponent::GetRectangle() {
    return mRectangle;
}
