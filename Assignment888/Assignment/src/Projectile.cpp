#include "../include/Projectile.h"
#include "../include/TransformComponent.h"
#include "../include/Collision2DComponent.h"
#include <iostream>

// 
// projectile struc
Projectile::Projectile(SDL_Renderer* renderer, float x, float y, float speed, bool goingUp, bool isPlayerBullet)
    : mRenderer(renderer), mSpeed(speed), mYDirectionUp(goingUp), mIsFiring(true), isPlayerBullet(isPlayerBullet) {
    
    AddDefaultTransform(x, y, 10.0f, 10.0f);  // (initial)
    AddComponent(std::make_shared<Collision2DComponent>(x, y, 10.0f, 10.0f));  // pass pos to Colli2D
}

// up position
void Projectile::Update(float deltaTime) {
    if (!mIsFiring) return;

    auto transform = GetTransform();
    if (!transform) {
        std::cerr << "[ERROR] Projectile missing TransformComponent.\n";
        return;
    }

    // up bullet
    float movement = mSpeed * deltaTime;
    float newY = transform->GetY() + (mYDirectionUp ? -movement : movement);
    transform->SetY(newY);

    // update colli box
    auto collision = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (collision) {
        collision->GetRectangle().x = transform->GetX();
        collision->GetRectangle().y = transform->GetY();
    }

    // check
    if (newY < 0 || newY > 600) {
        mIsFiring = false;
    }

    // update all compo
    for (auto& [type, component] : mComponents) {
        component->Update(deltaTime);
    }
}


// 
void Projectile::SetInitialPosition(float x, float y) {
    auto transform = GetTransform();
    if (transform) {
        transform->SetX(x);
        transform->SetY(y);
    }
    // 
}




// render
void Projectile::Render(SDL_Renderer* renderer) {
    if (!mIsFiring) return;

    auto transform = GetTransform();
    if (!transform) {
        std::cerr << "[ERROR] Projectile missing TransformComponent (Render).\n";
        return;
    }

    int centerX = static_cast<int>(transform->GetX());
    int centerY = static_cast<int>(transform->GetY());
    int radius = 5;

    // bullet ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }

    // render
    for (auto& [type, component] : mComponents) {
        component->Render(renderer);
    }
}

bool Projectile::IsOffScreen() {
    auto transform = GetTransform();
    if (!transform) return true;

    float y = transform->GetY();
    return y < 0 || y > 600;
}

bool Projectile::CheckCollision(GameEntity& entity) {
    if (!isPlayerBullet) return false;  // no colli when enemy bullet

    auto myCollision = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    auto otherCollision = entity.GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);

    if (!myCollision || !otherCollision) return false;

    SDL_FRect a = myCollision->GetRectangle();
    SDL_FRect b = otherCollision->GetRectangle();

    std::cout << "Checking Collision: Bullet (" << a.x << ", " << a.y << ") vs Enemy (" << b.x << ", " << b.y << ")\n";

    return SDL_HasIntersectionF(&a, &b);
}

