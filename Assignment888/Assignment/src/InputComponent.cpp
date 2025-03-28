#include "../include/InputComponent.h"
#include "../include/TransformComponent.h"
#include "../include/GameEntity.h"
#include "../include/Player.h"
#include <iostream>

InputComponent::InputComponent(float speed)
    : mSpeed(speed) {}

void InputComponent::Input(float deltaTime) {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    auto entity = GetGameEntity();
    if (!entity) return;

    auto transform = entity->GetTransform();  // TransformComponent
    if (!transform) return;

    float moveSpeed = mSpeed * deltaTime;

    // left right logic
    if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) {
        transform->SetX(transform->GetX() - moveSpeed);
    }
    if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
        transform->SetX(transform->GetX() + moveSpeed);
    }

    // 
    if (transform->GetX() < 0) transform->SetX(0);
    if (transform->GetX() + transform->GetW() > 800)
        transform->SetX(800 - transform->GetW());

    // bullet firing logic
    Uint64 currentTime = SDL_GetTicks64();
    static Uint64 lastShotTime = 0;

    if ((keystates[SDL_SCANCODE_SPACE]) && (currentTime > lastShotTime + 200)) {
        auto player = std::dynamic_pointer_cast<Player>(entity);
        if (player) {
            player->Shoot();  // 
            lastShotTime = currentTime;
        }
    }
}
