#include "../include/Enemy.h"
#include "../include/TextureComponent.h"
#include "../include/TransformComponent.h"
#include "../include/Collision2DComponent.h"
#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>

Enemy::Enemy(SDL_Renderer* renderer, float x, float y, float speed)
    : GameEntity(), mSpeed(speed) {
    lastShotTime = SDL_GetTicks64() + (rand() % 2000);
}

void Enemy::Initialize(SDL_Renderer* renderer, float x, float y, float speed) {
    // texture
    auto textureComp = std::make_shared<TextureComponent>(renderer, "Assignment/Assets/Alien.bmp");
    AddComponent(textureComp);

    // 
    AddDefaultTransform();
    auto transform = GetTransform();
    if (transform) {
        transform->SetX(x);  // 
        transform->SetY(y);  // 
        transform->SetW(40.0f);  //
        transform->SetH(40.0f);  // 
    }

    // collisionComponent
    AddComponent(std::make_shared<Collision2DComponent>(x, y, 40.0f, 40.0f));  // 使用与Transform相同的大小
}

void Enemy::Update(float deltaTime) {
    auto transform = GetTransform();
    auto collision = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (!transform || !collision) return;

    // update position
    float moveSpeed = mSpeed * deltaTime;
    transform->SetX(transform->GetX() + moveSpeed * moveDirection);

    // update
    collision->Update(deltaTime);  

    if (transform->GetX() <= 0 || transform->GetX() + 40 >= 800) {
        moveDirection *= -1;
        transform->SetY(transform->GetY() + 10);
    }

    Uint64 currentTime = SDL_GetTicks64();
    if (currentTime > lastShotTime) {
        Shoot();
        lastShotTime = currentTime + (rand() % 2000 + 1000);
    }

    // update bullet
    for (auto& projectile : mProjectiles) {
        projectile.Update(deltaTime);
    }

    // clean out screen bullet
    mProjectiles.erase(
        std::remove_if(mProjectiles.begin(), mProjectiles.end(),
            [](Projectile& p) { return p.IsOffScreen(); }),
        mProjectiles.end()
    );
}




void Enemy::Render(SDL_Renderer* renderer) {
    GameEntity::Render(renderer);
    for (auto& projectile : mProjectiles) {
        projectile.Render(renderer);
    }
}

void Enemy::Shoot() {
    auto textureComp = GetComponent<TextureComponent>(ComponentType::TextureComponent);
    auto transform = GetTransform();
    if (!textureComp || !transform) return;

    // 设置为敌人子弹，isPlayerBullet 为 false
    std::shared_ptr<Projectile> newBullet = std::make_shared<Projectile>(
        textureComp->GetRenderer(),
        transform->GetX() + 15,
        transform->GetY() + 40,
        250.0f,
        false,  // 下方向
        false   // 是敌人的子弹，不进行碰撞检测
    );

    // 只渲染敌人子弹，不发送到应用程序
    newBullet->Render(textureComp->GetRenderer());  // 直接渲染子弹而不加入到应用的 projectile 列表
}





